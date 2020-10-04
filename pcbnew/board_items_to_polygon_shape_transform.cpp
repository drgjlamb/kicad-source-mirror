/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2009-2018 Jean-Pierre Charras, jp.charras at wanadoo.fr
 * Copyright (C) 1992-2019 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include <vector>
#include <bezier_curves.h>
#include <base_units.h>     // for IU_PER_MM
#include <pcbnew.h>
#include <pcb_edit_frame.h>
#include <trigo.h>
#include <class_board.h>
#include <class_pad.h>
#include <class_track.h>
#include <class_drawsegment.h>
#include <class_pcb_text.h>
#include <class_zone.h>
#include <class_module.h>
#include <class_edge_mod.h>
#include <convert_basic_shapes_to_polygon.h>
#include <geometry/geometry_utils.h>
#include <geometry/shape_segment.h>
#include <math/util.h>      // for KiROUND


// A helper struct for the callback function
// These variables are parameters used in addTextSegmToPoly.
// But addTextSegmToPoly is a call-back function,
// so we cannot send them as arguments.
struct TSEGM_2_POLY_PRMS {
    int m_textWidth;
    int m_error;
    SHAPE_POLY_SET* m_cornerBuffer;
};
TSEGM_2_POLY_PRMS prms;

// This is a call back function, used by GRText to draw the 3D text shape:
static void addTextSegmToPoly( int x0, int y0, int xf, int yf, void* aData )
{
    TSEGM_2_POLY_PRMS* prm = static_cast<TSEGM_2_POLY_PRMS*>( aData );
    TransformOvalToPolygon( *prm->m_cornerBuffer, wxPoint( x0, y0 ), wxPoint( xf, yf ),
                            prm->m_textWidth, prm->m_error );
}


void BOARD::ConvertBrdLayerToPolygonalContours( PCB_LAYER_ID aLayer, SHAPE_POLY_SET& aOutlines )
{
    // convert tracks and vias:
    for( auto track : m_tracks )
    {
        if( !track->IsOnLayer( aLayer ) )
            continue;

        track->TransformShapeWithClearanceToPolygon( aOutlines, aLayer, 0 );
    }

    // convert pads
    for( auto module : m_modules )
    {
        module->TransformPadsShapesWithClearanceToPolygon( aLayer, aOutlines, 0 );

        // Micro-wave modules may have items on copper layers
        module->TransformGraphicShapesWithClearanceToPolygonSet( aLayer, aOutlines, 0 );
    }

    // convert copper zones
    for( ZONE_CONTAINER* zone : Zones() )
    {
        if( zone->GetLayerSet().test( aLayer ) )
            zone->TransformSolidAreasShapesToPolygon( aLayer, aOutlines );
    }

    // convert graphic items on copper layers (texts)
    for( auto item : m_drawings )
    {
        if( !item->IsOnLayer( aLayer ) )
            continue;

        switch( item->Type() )
        {
        case PCB_SHAPE_T:
            ( (DRAWSEGMENT*) item )->TransformShapeWithClearanceToPolygon( aOutlines, aLayer, 0 );
            break;

        case PCB_TEXT_T:
            ( (TEXTE_PCB*) item )->TransformShapeWithClearanceToPolygonSet( aOutlines, 0 );
            break;

        default:
            break;
        }
    }
}


void MODULE::TransformPadsShapesWithClearanceToPolygon( PCB_LAYER_ID aLayer,
                                                        SHAPE_POLY_SET& aCornerBuffer,
                                                        int aInflateValue, int aMaxError,
                                                        bool aSkipNPTHPadsWihNoCopper,
                                                        bool aSkipPlatedPads,
                                                        bool aSkipNonPlatedPads ) const
{
    for( D_PAD* pad : m_pads )
    {
        if( aLayer != UNDEFINED_LAYER && !pad->IsOnLayer(aLayer) )
            continue;

        if( !pad->FlashLayer( aLayer ) && IsCopperLayer( aLayer ) )
            continue;

        // NPTH pads are not drawn on layers if the shape size and pos is the same
        // as their hole:
        if( aSkipNPTHPadsWihNoCopper && pad->GetAttribute() == PAD_ATTRIB_NPTH )
        {
            if( pad->GetDrillSize() == pad->GetSize() && pad->GetOffset() == wxPoint( 0, 0 ) )
            {
                switch( pad->GetShape() )
                {
                case PAD_SHAPE_CIRCLE:
                    if( pad->GetDrillShape() == PAD_DRILL_SHAPE_CIRCLE )
                        continue;
                    break;

                case PAD_SHAPE_OVAL:
                    if( pad->GetDrillShape() != PAD_DRILL_SHAPE_CIRCLE )
                        continue;
                    break;

                default:
                    break;
                }
            }
        }

        const bool isPlated = ( ( aLayer == F_Cu ) && pad->FlashLayer( F_Mask ) ) ||
                              ( ( aLayer == B_Cu ) && pad->FlashLayer( B_Mask ) );

        if( aSkipPlatedPads && isPlated )
            continue;

        if( aSkipNonPlatedPads && !isPlated )
            continue;

        wxSize clearance( aInflateValue, aInflateValue );

        switch( aLayer )
        {
        case F_Mask:
        case B_Mask:
            clearance.x += pad->GetSolderMaskMargin();
            clearance.y += pad->GetSolderMaskMargin();
            break;

        case F_Paste:
        case B_Paste:
            clearance += pad->GetSolderPasteMargin();
            break;

        default:
            break;
        }

        // Our standard TransformShapeWithClearanceToPolygon() routines can't handle differing
        // x:y clearance values (which get generated when a relative paste margin is used with
        // an oblong pad).  So we apply this huge hack and fake a larger pad to run the transform
        // on.
        // Of course being a hack it falls down when dealing with custom shape pads (where the
        // size is only the size of the anchor), so for those we punt and just use clearance.x.

        if( ( clearance.x < 0 || clearance.x != clearance.y )
                && pad->GetShape() != PAD_SHAPE_CUSTOM )
        {
            D_PAD dummy( *pad );
            dummy.SetSize( pad->GetSize() + clearance + clearance );
            dummy.TransformShapeWithClearanceToPolygon( aCornerBuffer, aLayer, 0, aMaxError );
        }
        else
        {
            pad->TransformShapeWithClearanceToPolygon( aCornerBuffer, aLayer, clearance.x,
                                                       aMaxError );
        }
    }
}

/**
 * Generate shapes of graphic items (outlines) as polygons added to a buffer.
 * @aCornerBuffer = the buffer to store polygons
 * @aInflateValue = a value to inflate shapes
 * @aError = the maximum error to allow when approximating curves with segments
 * @aIncludeText = indicates footprint text items (reference, value, etc.) should be included
 *                 in the outline
 */
void MODULE::TransformGraphicShapesWithClearanceToPolygonSet( PCB_LAYER_ID aLayer,
                                                              SHAPE_POLY_SET& aCornerBuffer,
                                                              int aInflateValue,
                                                              int aError,
                                                              bool aIncludeText,
                                                              bool aIncludeEdges ) const
{
    std::vector<TEXTE_MODULE *> texts;  // List of TEXTE_MODULE to convert

    for( auto item : GraphicalItems() )
    {
        if( item->Type() == PCB_FP_TEXT_T && aIncludeText )
        {
            TEXTE_MODULE* text = static_cast<TEXTE_MODULE*>( item );

            if( aLayer != UNDEFINED_LAYER && text->GetLayer() == aLayer && text->IsVisible() )
                texts.push_back( text );
        }

        if( item->Type() == PCB_FP_SHAPE_T && aIncludeEdges )
        {
            EDGE_MODULE* outline = (EDGE_MODULE*) item;

            if( aLayer != UNDEFINED_LAYER && outline->GetLayer() == aLayer )
                outline->TransformShapeWithClearanceToPolygon( aCornerBuffer, aLayer, 0, aError );
        }
    }

    if( aIncludeText )
    {
        if( Reference().GetLayer() == aLayer && Reference().IsVisible() )
            texts.push_back( &Reference() );

        if( Value().GetLayer() == aLayer && Value().IsVisible() )
            texts.push_back( &Value() );
    }

    prms.m_cornerBuffer = &aCornerBuffer;

    for( TEXTE_MODULE* textmod : texts )
    {
        bool forceBold = true;
        int  penWidth = 0;      // force max width for bold text

        prms.m_textWidth  = textmod->GetEffectiveTextPenWidth() + ( 2 * aInflateValue );
        prms.m_error = aError;
        wxSize size = textmod->GetTextSize();

        if( textmod->IsMirrored() )
            size.x = -size.x;

        GRText( NULL, textmod->GetTextPos(), BLACK, textmod->GetShownText(),
                textmod->GetDrawRotation(), size, textmod->GetHorizJustify(),
                textmod->GetVertJustify(), penWidth, textmod->IsItalic(), forceBold,
                addTextSegmToPoly, &prms );
    }
}


void ZONE_CONTAINER::TransformSolidAreasShapesToPolygon( PCB_LAYER_ID aLayer,
                                                         SHAPE_POLY_SET& aCornerBuffer,
                                                         int aError ) const
{
    if( !m_FilledPolysList.count( aLayer ) || m_FilledPolysList.at( aLayer ).IsEmpty() )
        return;

    // Just add filled areas if filled polygons outlines have no thickness
    if( !GetFilledPolysUseThickness() || GetMinThickness() == 0 )
    {
        const SHAPE_POLY_SET& polys = m_FilledPolysList.at( aLayer );
        aCornerBuffer.Append( polys );
        return;
    }

    // Filled areas have polygons with outline thickness.
    // we must create the polygons and add inflated polys
    SHAPE_POLY_SET polys = m_FilledPolysList.at( aLayer );

    auto board = GetBoard();
    int maxError = ARC_HIGH_DEF;

    if( board )
        maxError = board->GetDesignSettings().m_MaxError;

    int numSegs = GetArcToSegmentCount( GetMinThickness(), maxError, 360.0 );

    polys.InflateWithLinkedHoles( GetMinThickness()/2, numSegs, SHAPE_POLY_SET::PM_FAST );

    aCornerBuffer.Append( polys );
}


void EDA_TEXT::TransformBoundingBoxWithClearanceToPolygon( SHAPE_POLY_SET* aCornerBuffer,
                                                           int aClearanceValue ) const
{
    if( GetText().Length() == 0 )
        return;

    wxPoint  corners[4];    // Buffer of polygon corners

    EDA_RECT rect = GetTextBox();
    rect.Inflate( aClearanceValue + Millimeter2iu( DEFAULT_TEXT_WIDTH ) );
    corners[0].x = rect.GetOrigin().x;
    corners[0].y = rect.GetOrigin().y;
    corners[1].y = corners[0].y;
    corners[1].x = rect.GetRight();
    corners[2].x = corners[1].x;
    corners[2].y = rect.GetBottom();
    corners[3].y = corners[2].y;
    corners[3].x = corners[0].x;

    aCornerBuffer->NewOutline();

    for( wxPoint& corner : corners )
    {
        // Rotate polygon
        RotatePoint( &corner.x, &corner.y, GetTextPos().x, GetTextPos().y, GetTextAngle() );
        aCornerBuffer->Append( corner.x, corner.y );
    }
}


/**
 * Function TransformShapeWithClearanceToPolygonSet
 * Convert the text shape to a set of polygons (one per segment).
 * @aCornerBuffer = SHAPE_POLY_SET to store the polygon corners
 * @aClearanceValue = the clearance around the text
 * @aError = the maximum error to allow when approximating curves
 */
void TEXTE_PCB::TransformShapeWithClearanceToPolygonSet( SHAPE_POLY_SET& aCornerBuffer,
                                                         int aClearanceValue, int aError ) const
{
    wxSize size = GetTextSize();

    if( IsMirrored() )
        size.x = -size.x;

    bool forceBold = true;
    int  penWidth = GetEffectiveTextPenWidth();

    prms.m_cornerBuffer = &aCornerBuffer;
    prms.m_textWidth = GetEffectiveTextPenWidth() + ( 2 * aClearanceValue );
    prms.m_error = aError;
    COLOR4D color = COLOR4D::BLACK;  // not actually used, but needed by GRText

    if( IsMultilineAllowed() )
    {
        wxArrayString strings_list;
        wxStringSplit( GetShownText(), strings_list, '\n' );
        std::vector<wxPoint> positions;
        positions.reserve( strings_list.Count() );
        GetLinePositions( positions, strings_list.Count() );

        for( unsigned ii = 0; ii < strings_list.Count(); ii++ )
        {
            wxString txt = strings_list.Item( ii );
            GRText( NULL, positions[ii], color, txt, GetTextAngle(), size, GetHorizJustify(),
                    GetVertJustify(), penWidth, IsItalic(), forceBold, addTextSegmToPoly, &prms );
        }
    }
    else
    {
        GRText( NULL, GetTextPos(), color, GetShownText(), GetTextAngle(), size, GetHorizJustify(),
                GetVertJustify(), penWidth, IsItalic(), forceBold, addTextSegmToPoly, &prms );
    }
}


void DRAWSEGMENT::TransformShapeWithClearanceToPolygon( SHAPE_POLY_SET& aCornerBuffer,
                                                        PCB_LAYER_ID aLayer,
                                                        int aClearanceValue, int aError,
                                                        bool ignoreLineWidth ) const
{
    int width = ignoreLineWidth ? 0 : m_Width;

    width += 2 * aClearanceValue;

    // Creating a reliable clearance shape for circles and arcs is not so easy, due to
    // the error created by segment approximation.
    // for a circle this is not so hard: create a polygon from a circle slightly bigger:
    // thickness = width + s_error_max, and radius = initial radius + s_error_max/2
    // giving a shape with a suitable internal radius and external radius
    // For an arc this is more tricky: TODO

    switch( m_Shape )
    {
    case S_CIRCLE:
        if( width == 0 )
            TransformCircleToPolygon( aCornerBuffer, GetCenter(), GetRadius(), aError );
        else
            TransformRingToPolygon( aCornerBuffer, GetCenter(), GetRadius(), aError, width );
        break;

    case S_RECT:
    {
        std::vector<wxPoint> pts = GetRectCorners();

        if( width == 0 )
        {
            aCornerBuffer.NewOutline();

            for( const wxPoint& pt : pts )
                aCornerBuffer.Append( pt );
        }

        if( width > 0 )
        {
            // Add in segments
            TransformOvalToPolygon( aCornerBuffer, pts[0], pts[1], width, aError );
            TransformOvalToPolygon( aCornerBuffer, pts[1], pts[2], width, aError );
            TransformOvalToPolygon( aCornerBuffer, pts[2], pts[3], width, aError );
            TransformOvalToPolygon( aCornerBuffer, pts[3], pts[0], width, aError );
        }
    }
        break;

    case S_ARC:
        TransformArcToPolygon( aCornerBuffer, GetCenter(), GetArcStart(), m_Angle, aError, width );
        break;

    case S_SEGMENT:
        TransformOvalToPolygon( aCornerBuffer, m_Start, m_End, width, aError );
        break;

    case S_POLYGON:
        if( IsPolyShapeValid() )
        {
            // The polygon is expected to be a simple polygon
            // not self intersecting, no hole.
            MODULE* module = GetParentModule();     // NULL for items not in footprints
            double orientation = module ? module->GetOrientation() : 0.0;
            wxPoint offset;

            if( module )
                offset = module->GetPosition();

            // Build the polygon with the actual position and orientation:
            std::vector< wxPoint> poly;
            poly = BuildPolyPointsList();

            for( wxPoint& point : poly )
            {
                RotatePoint( &point, orientation );
                point += offset;
            }

            if( IsPolygonFilled() || width == 0 )
            {
                aCornerBuffer.NewOutline();

                for( wxPoint& point : poly )
                    aCornerBuffer.Append( point.x, point.y );
            }

            if( width > 0 )
            {
                wxPoint pt1( poly[ poly.size() - 1] );

                for( wxPoint pt2 : poly )
                {
                    if( pt2 != pt1 )
                        TransformOvalToPolygon( aCornerBuffer, pt1, pt2, width, aError );

                    pt1 = pt2;
                }
            }
        }
        break;

    case S_CURVE:       // Bezier curve
        {
            std::vector<wxPoint> ctrlPoints = { m_Start, m_BezierC1, m_BezierC2, m_End };
            BEZIER_POLY converter( ctrlPoints );
            std::vector< wxPoint> poly;
            converter.GetPoly( poly, m_Width );

            if( width != 0 )
            {
                for( unsigned ii = 1; ii < poly.size(); ii++ )
                    TransformOvalToPolygon( aCornerBuffer, poly[ii-1], poly[ii], width, aError );
            }
        }
        break;

    default:
        wxFAIL_MSG( "DRAWSEGMENT::TransformShapeWithClearanceToPolygon no implementation for "
                    + PCB_SHAPE_TYPE_T_asString( m_Shape ) );
        break;
    }
}


void TRACK::TransformShapeWithClearanceToPolygon( SHAPE_POLY_SET& aCornerBuffer,
                                                  PCB_LAYER_ID aLayer,
                                                  int aClearanceValue, int aError,
                                                  bool ignoreLineWidth ) const
{
    wxASSERT_MSG( !ignoreLineWidth, "IgnoreLineWidth has no meaning for tracks." );


    switch( Type() )
    {
    case PCB_VIA_T:
    {
        int radius = ( m_Width / 2 ) + aClearanceValue;
        TransformCircleToPolygon( aCornerBuffer, m_Start, radius, aError );
    }
        break;

    case PCB_ARC_T:
    {
        const ARC* arc = static_cast<const ARC*>( this );
        int        width = m_Width + ( 2 * aClearanceValue );
        VECTOR2D   center( arc->GetCenter() );
        double     angle = arc->GetAngle();

        TransformArcToPolygon( aCornerBuffer, (wxPoint) center, GetStart(), angle, aError, width );
    }
        break;

    default:
    {
        int width = m_Width + ( 2 * aClearanceValue );

        TransformOvalToPolygon( aCornerBuffer, m_Start, m_End, width, aError );
    }
        break;
    }
}


void D_PAD::TransformShapeWithClearanceToPolygon( SHAPE_POLY_SET& aCornerBuffer,
                                                  PCB_LAYER_ID aLayer,
                                                  int aClearanceValue, int aError,
                                                  bool ignoreLineWidth ) const
{
    wxASSERT_MSG( !ignoreLineWidth, "IgnoreLineWidth has no meaning for pads." );

    // minimal segment count to approximate a circle to create the polygonal pad shape
    // This minimal value is mainly for very small pads, like SM0402.
    // Most of time pads are using the segment count given by aError value.
    const int pad_min_seg_per_circle_count = 16;
    double  angle = m_orient;
    int     dx = m_size.x / 2;
    int     dy = m_size.y / 2;

    wxPoint padShapePos = ShapePos();         // Note: for pad having a shape offset,
                                              // the pad position is NOT the shape position

    switch( GetShape() )
    {
    case PAD_SHAPE_CIRCLE:
    case PAD_SHAPE_OVAL:
        if( dx == dy )
        {
            TransformCircleToPolygon( aCornerBuffer, padShapePos, dx + aClearanceValue, aError );
        }
        else
        {
            int     half_width = std::min( dx, dy );
            wxPoint delta( dx - half_width, dy - half_width );

            RotatePoint( &delta, angle );

            TransformOvalToPolygon( aCornerBuffer, padShapePos - delta, padShapePos + delta,
                                    ( half_width + aClearanceValue ) * 2, aError );
        }

        break;

    case PAD_SHAPE_TRAPEZOID:
    case PAD_SHAPE_RECT:
    {
        int  ddx = GetShape() == PAD_SHAPE_TRAPEZOID ? m_deltaSize.x / 2 : 0;
        int  ddy = GetShape() == PAD_SHAPE_TRAPEZOID ? m_deltaSize.y / 2 : 0;

        wxPoint corners[4];
        corners[0] = wxPoint( -dx - ddy,  dy + ddx );
        corners[1] = wxPoint(  dx + ddy,  dy - ddx );
        corners[2] = wxPoint(  dx - ddy, -dy + ddx );
        corners[3] = wxPoint( -dx + ddy, -dy - ddx );

        SHAPE_POLY_SET outline;
        outline.NewOutline();

        for( wxPoint& corner : corners )
        {
            RotatePoint( &corner, angle );
            corner += padShapePos;
            outline.Append( corner.x, corner.y );
        }

        if( aClearanceValue )
        {
            int numSegs = std::max( GetArcToSegmentCount( aClearanceValue, aError, 360.0 ),
                                    pad_min_seg_per_circle_count );
            int clearance = aClearanceValue + GetCircleToPolyCorrection( aError );
            outline.Inflate( clearance, numSegs );
            // TODO: clamp the inflated polygon, because it is slightly too big:
            // it was inflated by a value slightly too big to keep rounded corners
            // ouside the pad area.
        }

        aCornerBuffer.Append( outline );
    }
        break;

    case PAD_SHAPE_CHAMFERED_RECT:
    case PAD_SHAPE_ROUNDRECT:
    {
        int    radius = GetRoundRectCornerRadius() + aClearanceValue;
        int    clearance = aClearanceValue + GetCircleToPolyCorrection( aError );
        wxSize shapesize( m_size );

        radius = radius + GetCircleToPolyCorrection( aError );
        shapesize.x += clearance * 2;
        shapesize.y += clearance * 2;
        bool doChamfer = GetShape() == PAD_SHAPE_CHAMFERED_RECT;

        SHAPE_POLY_SET outline;
        TransformRoundChamferedRectToPolygon( outline, padShapePos, shapesize, angle, radius,
                                              doChamfer ? GetChamferRectRatio() : 0.0,
                                              doChamfer ? GetChamferPositions() : 0, aError );

        aCornerBuffer.Append( outline );
    }
        break;

    case PAD_SHAPE_CUSTOM:
    {
        SHAPE_POLY_SET outline;
        MergePrimitivesAsPolygon( &outline, aLayer );
        outline.Rotate( -DECIDEG2RAD( m_orient ) );
        outline.Move( VECTOR2I( m_pos ) );

        if( aClearanceValue )
        {
            int numSegs = std::max( GetArcToSegmentCount( aClearanceValue, aError, 360.0 ),
                                                          pad_min_seg_per_circle_count );
            int clearance = aClearanceValue + GetCircleToPolyCorrection( aError );

            outline.Inflate( clearance, numSegs );
            outline.Simplify( SHAPE_POLY_SET::PM_FAST );
            outline.Fracture( SHAPE_POLY_SET::PM_FAST );
        }

        aCornerBuffer.Append( outline );
    }
        break;

    default:
        wxFAIL_MSG( "D_PAD::TransformShapeWithClearanceToPolygon no implementation for "
                    + PAD_SHAPE_T_asString( GetShape() ) );
        break;
    }
}



bool D_PAD::TransformHoleWithClearanceToPolygon( SHAPE_POLY_SET& aCornerBuffer, int aInflateValue,
                                                 int aError ) const
{
    wxSize drillsize = GetDrillSize();

    if( !drillsize.x || !drillsize.y )
        return false;

    const SHAPE_SEGMENT* seg = GetEffectiveHoleShape();

    TransformOvalToPolygon( aCornerBuffer, (wxPoint) seg->GetSeg().A, (wxPoint) seg->GetSeg().B,
                            seg->GetWidth() + aInflateValue * 2, aError );

    return true;
}


void ZONE_CONTAINER::TransformShapeWithClearanceToPolygon( SHAPE_POLY_SET& aCornerBuffer,
                                                           PCB_LAYER_ID aLayer, int aClearance,
                                                           int aError, bool ignoreLineWidth ) const
{
    wxASSERT_MSG( !ignoreLineWidth, "IgnoreLineWidth has no meaning for zones." );

    if( !m_FilledPolysList.count( aLayer ) )
        return;

    aCornerBuffer = m_FilledPolysList.at( aLayer );

    int numSegs = GetArcToSegmentCount( aClearance, aError, 360.0 );
    aCornerBuffer.Inflate( aClearance, numSegs );
    aCornerBuffer.Simplify( SHAPE_POLY_SET::PM_STRICTLY_SIMPLE );
}
