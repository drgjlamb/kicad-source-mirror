/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2019-2020 KiCad Developers, see AUTHORS.txt for contributors.
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

#ifndef __BOARD_STATISTICS_TOOL_H
#define __BOARD_STATISTICS_TOOL_H

#include <dialogs/dialog_board_statistics.h>
#include <dialogs/dialog_select_net_from_list.h>
#include <dialogs/dialog_HTML_reporter_base.h>
#include <dialogs/dialog_constraints_reporter.h>
#include <pcb_edit_frame.h>
#include <tools/pcb_actions.h>
#include <tools/pcb_tool_base.h>

class CONNECTIVITY_DATA;

/**
 * PCB_INSPECTION_TOOL
 *
 * Tool for pcb inspection.
 */
class PCB_INSPECTION_TOOL : public wxEvtHandler, public PCB_TOOL_BASE
{
public:
    PCB_INSPECTION_TOOL();

    /// @copydoc TOOL_INTERACTIVE::Init()
    bool Init() override;

    /// @copydoc TOOL_INTERACTIVE::Reset()
    void Reset( RESET_REASON aReason ) override;

    /**
     * Function ShowStatisticDialog()
     *
     * Shows dialog with board statistics
     */
    int ShowStatisticsDialog( const TOOL_EVENT& aEvent );

    ///> Notifies eeschema about the selected item.
    int CrossProbePcbToSch( const TOOL_EVENT& aEvent );

    ///> Highlights net belonging to the item under the cursor.
    int HighlightNet( const TOOL_EVENT& aEvent );

    ///> Clears all board highlights
    int ClearHighlight( const TOOL_EVENT& aEvent );

    ///> Launches a tool to pick the item whose net is going to be highlighted.
    int HighlightNetTool( const TOOL_EVENT& aEvent );

    ///> Performs the appropriate action in response to an eeschema cross-probe.
    int HighlightItem( const TOOL_EVENT& aEvent );

    ///> Updates ratsnest for selected items.
    int UpdateSelectionRatsnest( const TOOL_EVENT& aEvent );

    ///> Hides ratsnest for selected items. Called when there are no items selected.
    int HideDynamicRatsnest( const TOOL_EVENT& aEvent );

    ///> Shows local ratsnest of a component
    int LocalRatsnestTool( const TOOL_EVENT& aEvent );

    int FlipPcbView( const TOOL_EVENT& aEvent );

    int ListNets( const TOOL_EVENT& aEvent );

    ///> Hide the ratsnest for a given net
    int HideNet( const TOOL_EVENT& aEvent );

    ///> Show the ratsnest for a given net
    int ShowNet( const TOOL_EVENT& aEvent );

    ///> Show the clearance resolution for two selected items
    int InspectClearance( const TOOL_EVENT& aEvent );

    int InspectConstraints( const TOOL_EVENT& aEvent );

private:
    ///> Event handler to recalculate dynamic ratsnest
    void ratsnestTimer( wxTimerEvent& aEvent );

    ///> Recalculates dynamic ratsnest for the current selection
    void calculateSelectionRatsnest( const VECTOR2I& aDelta );

    bool highlightNet( const VECTOR2D& aPosition, bool aUseSelection );

    void doHideNet( int aNetCode, bool aHide );

    ///> Bind handlers to corresponding TOOL_ACTIONs
    void setTransitions() override;

    void onListNetsDialogClosed( wxCommandEvent& aEvent );
    void onInspectClearanceDialogClosed( wxCommandEvent& aEvent );
    void onInspectConstraintsDialogClosed( wxCommandEvent& aEvent );

    void reportZoneConnection( ZONE_CONTAINER* aZone, D_PAD* aPad, REPORTER* r );

    void reportClearance( DRC_CONSTRAINT_TYPE_T aClearanceType, PCB_LAYER_ID aLayer,
                          BOARD_ITEM* aA, BOARD_ITEM* aB, REPORTER* r );

private:
    PCB_EDIT_FRAME* m_frame;    // Pointer to the currently used edit frame.

    bool m_probingSchToPcb;     // Recursion guard when cross-probing to EESchema
    int  m_lastNetcode;         // Used for toggling between last two highlighted nets

    CONNECTIVITY_DATA* m_dynamicData;      // Cached connectivity data from the selection

    std::unique_ptr<DIALOG_SELECT_NET_FROM_LIST> m_listNetsDialog;
    DIALOG_SELECT_NET_FROM_LIST::SETTINGS        m_listNetsDialogSettings;

    std::unique_ptr<DIALOG_HTML_REPORTER>        m_inspectClearanceDialog;
    std::unique_ptr<DIALOG_CONSTRAINTS_REPORTER> m_inspectConstraintsDialog;
};

#endif //__BOARD_STATISTICS_TOOL_H
