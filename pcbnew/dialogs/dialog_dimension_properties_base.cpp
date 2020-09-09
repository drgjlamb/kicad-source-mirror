///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pcb_layer_box_selector.h"

#include "dialog_dimension_properties_base.h"

///////////////////////////////////////////////////////////////////////////

DIALOG_DIMENSION_PROPERTIES_BASE::DIALOG_DIMENSION_PROPERTIES_BASE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : DIALOG_SHIM( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );

	wxBoxSizer* bMainSizer;
	bMainSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizerFormat;
	sbSizerFormat = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Dimension Format") ), wxVERTICAL );

	wxGridBagSizer* gbSizerFormat;
	gbSizerFormat = new wxGridBagSizer( 0, 5 );
	gbSizerFormat->SetFlexibleDirection( wxHORIZONTAL );
	gbSizerFormat->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblValue = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblValue->Wrap( -1 );
	m_lblValue->SetToolTip( _("Measured value of this dimension") );

	gbSizerFormat->Add( m_lblValue, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtValue = new wxTextCtrl( sbSizerFormat->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtValue->Enable( false );
	m_txtValue->SetToolTip( _("Measured value of this dimension") );

	gbSizerFormat->Add( m_txtValue, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_cbOverrideValue = new wxCheckBox( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Override value"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbOverrideValue->SetToolTip( _("When checked, the actual measurement is ignored and any value can be entered") );

	gbSizerFormat->Add( m_cbOverrideValue, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	gbSizerFormat->Add( 20, 0, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), 0, 5 );

	m_lblUnits = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Units:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblUnits->Wrap( -1 );
	m_lblUnits->SetToolTip( _("Units of this dimension (\"automatic\" to follow the units selected in the editor)") );

	gbSizerFormat->Add( m_lblUnits, wxGBPosition( 0, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_cbUnitsChoices[] = { _("Inches"), _("Mils"), _("Millimeters"), _("Automatic") };
	int m_cbUnitsNChoices = sizeof( m_cbUnitsChoices ) / sizeof( wxString );
	m_cbUnits = new wxChoice( sbSizerFormat->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cbUnitsNChoices, m_cbUnitsChoices, 0 );
	m_cbUnits->SetSelection( 0 );
	m_cbUnits->SetToolTip( _("Units of this dimension (\"automatic\" to follow the units selected in the editor)") );

	gbSizerFormat->Add( m_cbUnits, wxGBPosition( 0, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblPrefix = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Prefix:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblPrefix->Wrap( -1 );
	m_lblPrefix->SetToolTip( _("Text to print before the dimension value") );

	gbSizerFormat->Add( m_lblPrefix, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtPrefix = new wxTextCtrl( sbSizerFormat->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtPrefix->SetToolTip( _("Text to print before the dimension value") );

	gbSizerFormat->Add( m_txtPrefix, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_txtUnitsFormat = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Units format:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtUnitsFormat->Wrap( -1 );
	m_txtUnitsFormat->SetToolTip( _("Choose how to display the units") );

	gbSizerFormat->Add( m_txtUnitsFormat, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_cbUnitsFormatChoices[] = { _("1234"), _("1234 mm"), _("1234 (mm)") };
	int m_cbUnitsFormatNChoices = sizeof( m_cbUnitsFormatChoices ) / sizeof( wxString );
	m_cbUnitsFormat = new wxChoice( sbSizerFormat->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cbUnitsFormatNChoices, m_cbUnitsFormatChoices, 0 );
	m_cbUnitsFormat->SetSelection( 1 );
	m_cbUnitsFormat->SetToolTip( _("Choose how to display the units") );

	gbSizerFormat->Add( m_cbUnitsFormat, wxGBPosition( 1, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblSuffix = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Suffix:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblSuffix->Wrap( -1 );
	m_lblSuffix->SetToolTip( _("Text to print after the dimension value") );

	gbSizerFormat->Add( m_lblSuffix, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtSuffix = new wxTextCtrl( sbSizerFormat->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtSuffix->SetToolTip( _("Text to print after the dimension value") );

	gbSizerFormat->Add( m_txtSuffix, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblPrecision = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Precision:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblPrecision->Wrap( -1 );
	m_lblPrecision->SetToolTip( _("Choose how many digits of precision to display") );

	gbSizerFormat->Add( m_lblPrecision, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_cbPrecisionChoices[] = { _("0.0000"), _("0.000"), _("0.00"), _("0.0"), _("0") };
	int m_cbPrecisionNChoices = sizeof( m_cbPrecisionChoices ) / sizeof( wxString );
	m_cbPrecision = new wxChoice( sbSizerFormat->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cbPrecisionNChoices, m_cbPrecisionChoices, 0 );
	m_cbPrecision->SetSelection( 0 );
	m_cbPrecision->SetToolTip( _("Choose how many digits of precision to display") );

	gbSizerFormat->Add( m_cbPrecision, wxGBPosition( 2, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_cbSuppressZeroes = new wxCheckBox( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Suppress trailing zeroes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbSuppressZeroes->SetToolTip( _("When checked, \"0.100\" will be shown as \"0.1\" even if the precision setting is higher") );

	gbSizerFormat->Add( m_cbSuppressZeroes, wxGBPosition( 3, 4 ), wxGBSpan( 1, 2 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblLayer = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Layer:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLayer->Wrap( -1 );
	gbSizerFormat->Add( m_lblLayer, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_cbLayer = new PCB_LAYER_BOX_SELECTOR( sbSizerFormat->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	gbSizerFormat->Add( m_cbLayer, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_lblPreview = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, _("Preview:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblPreview->Wrap( -1 );
	gbSizerFormat->Add( m_lblPreview, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticTextPreview = new wxStaticText( sbSizerFormat->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextPreview->Wrap( -1 );
	m_staticTextPreview->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	gbSizerFormat->Add( m_staticTextPreview, wxGBPosition( 4, 1 ), wxGBSpan( 1, 4 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	gbSizerFormat->AddGrowableCol( 1 );
	gbSizerFormat->AddGrowableCol( 3 );
	gbSizerFormat->AddGrowableCol( 5 );

	sbSizerFormat->Add( gbSizerFormat, 1, wxBOTTOM|wxEXPAND, 5 );


	bMainSizer->Add( sbSizerFormat, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizerText;
	sbSizerText = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Dimension Text") ), wxVERTICAL );

	wxGridBagSizer* gbSizerText;
	gbSizerText = new wxGridBagSizer( 0, 0 );
	gbSizerText->SetFlexibleDirection( wxHORIZONTAL );
	gbSizerText->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblTextWidth = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("Width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextWidth->Wrap( -1 );
	m_lblTextWidth->SetToolTip( _("Text width") );

	gbSizerText->Add( m_lblTextWidth, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtTextWidth = new wxTextCtrl( sbSizerText->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	gbSizerText->Add( m_txtTextWidth, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblTextWidthUnits = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextWidthUnits->Wrap( -1 );
	gbSizerText->Add( m_lblTextWidthUnits, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	gbSizerText->Add( 20, 0, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	m_lblTextPosX = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("Position X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextPosX->Wrap( -1 );
	m_lblTextPosX->SetToolTip( _("Text pos X") );

	gbSizerText->Add( m_lblTextPosX, wxGBPosition( 0, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtTextPosX = new wxTextCtrl( sbSizerText->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	gbSizerText->Add( m_txtTextPosX, wxGBPosition( 0, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblTextPosXUnits = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextPosXUnits->Wrap( -1 );
	gbSizerText->Add( m_lblTextPosXUnits, wxGBPosition( 0, 6 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );

	m_lblTextHeight = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextHeight->Wrap( -1 );
	m_lblTextHeight->SetToolTip( _("Text height") );

	gbSizerText->Add( m_lblTextHeight, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtTextHeight = new wxTextCtrl( sbSizerText->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	gbSizerText->Add( m_txtTextHeight, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblTextHeightUnits = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextHeightUnits->Wrap( -1 );
	gbSizerText->Add( m_lblTextHeightUnits, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblTextPosY = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("Position Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextPosY->Wrap( -1 );
	m_lblTextPosY->SetToolTip( _("Text pos Y") );

	gbSizerText->Add( m_lblTextPosY, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtTextPosY = new wxTextCtrl( sbSizerText->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	gbSizerText->Add( m_txtTextPosY, wxGBPosition( 1, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblTextPosYUnits = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextPosYUnits->Wrap( -1 );
	gbSizerText->Add( m_lblTextPosYUnits, wxGBPosition( 1, 6 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );

	m_lblTextThickness = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("Thickness:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextThickness->Wrap( -1 );
	m_lblTextThickness->SetToolTip( _("Text thickness") );

	gbSizerText->Add( m_lblTextThickness, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtTextThickness = new wxTextCtrl( sbSizerText->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	gbSizerText->Add( m_txtTextThickness, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblTextThicknessUnits = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextThicknessUnits->Wrap( -1 );
	gbSizerText->Add( m_lblTextThicknessUnits, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblTextOrientation = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("Orientation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblTextOrientation->Wrap( -1 );
	m_lblTextOrientation->SetToolTip( _("Text orientation") );

	gbSizerText->Add( m_lblTextOrientation, wxGBPosition( 2, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_cbTextOrientation = new wxComboBox( sbSizerText->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_cbTextOrientation->Append( _("0.0") );
	m_cbTextOrientation->Append( _("90.0") );
	m_cbTextOrientation->Append( _("-90.0") );
	m_cbTextOrientation->Append( _("180.0") );
	gbSizerText->Add( m_cbTextOrientation, wxGBPosition( 2, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_cbItalic = new wxCheckBox( sbSizerText->GetStaticBox(), wxID_ANY, _("Italic"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizerText->Add( m_cbItalic, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_cbKeepAligned = new wxCheckBox( sbSizerText->GetStaticBox(), wxID_ANY, _("Keep aligned with dimension"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbKeepAligned->SetToolTip( _("Automatically set the text orientation to match the dimension lines") );

	gbSizerText->Add( m_cbKeepAligned, wxGBPosition( 3, 4 ), wxGBSpan( 1, 3 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_cbMirrored = new wxCheckBox( sbSizerText->GetStaticBox(), wxID_ANY, _("Mirrored"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbMirrored->SetToolTip( _("Mirror text") );

	gbSizerText->Add( m_cbMirrored, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_lblJustification = new wxStaticText( sbSizerText->GetStaticBox(), wxID_ANY, _("Justification:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblJustification->Wrap( -1 );
	gbSizerText->Add( m_lblJustification, wxGBPosition( 4, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxString m_cbJustificationChoices[] = { _("Left"), _("Center"), _("Right") };
	int m_cbJustificationNChoices = sizeof( m_cbJustificationChoices ) / sizeof( wxString );
	m_cbJustification = new wxChoice( sbSizerText->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cbJustificationNChoices, m_cbJustificationChoices, 0 );
	m_cbJustification->SetSelection( 0 );
	gbSizerText->Add( m_cbJustification, wxGBPosition( 4, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );


	gbSizerText->AddGrowableCol( 1 );
	gbSizerText->AddGrowableCol( 3 );
	gbSizerText->AddGrowableCol( 5 );

	sbSizerText->Add( gbSizerText, 0, wxBOTTOM|wxEXPAND, 5 );


	bMainSizer->Add( sbSizerText, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizerLine;
	sbSizerLine = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Dimension Line") ), wxVERTICAL );

	wxGridBagSizer* gbSizerLine;
	gbSizerLine = new wxGridBagSizer( 0, 0 );
	gbSizerLine->SetFlexibleDirection( wxHORIZONTAL );
	gbSizerLine->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_lblLineThickness = new wxStaticText( sbSizerLine->GetStaticBox(), wxID_ANY, _("Line thickness:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLineThickness->Wrap( -1 );
	m_lblLineThickness->SetToolTip( _("Thickness of the dimension lines") );

	gbSizerLine->Add( m_lblLineThickness, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtLineThickness = new wxTextCtrl( sbSizerLine->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	gbSizerLine->Add( m_txtLineThickness, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_lblLineThicknessUnits = new wxStaticText( sbSizerLine->GetStaticBox(), wxID_ANY, _("unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblLineThicknessUnits->Wrap( -1 );
	gbSizerLine->Add( m_lblLineThicknessUnits, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	gbSizerLine->Add( 20, 0, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	m_lblArrowLength = new wxStaticText( sbSizerLine->GetStaticBox(), wxID_ANY, _("Arrow length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblArrowLength->Wrap( -1 );
	gbSizerLine->Add( m_lblArrowLength, wxGBPosition( 0, 4 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtArrowLength = new wxTextCtrl( sbSizerLine->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	gbSizerLine->Add( m_txtArrowLength, wxGBPosition( 0, 5 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	m_lblArrowLengthUnits = new wxStaticText( sbSizerLine->GetStaticBox(), wxID_ANY, _("unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblArrowLengthUnits->Wrap( -1 );
	gbSizerLine->Add( m_lblArrowLengthUnits, wxGBPosition( 0, 6 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	gbSizerLine->AddGrowableCol( 1 );
	gbSizerLine->AddGrowableCol( 3 );
	gbSizerLine->AddGrowableCol( 5 );

	sbSizerLine->Add( gbSizerLine, 1, wxBOTTOM|wxEXPAND, 5 );


	bMainSizer->Add( sbSizerLine, 0, wxALL|wxEXPAND, 5 );


	bMainSizer->Add( 0, 0, 0, wxTOP, 5 );

	m_staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bMainSizer->Add( m_staticline, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 10 );

	wxBoxSizer* lowerSizer;
	lowerSizer = new wxBoxSizer( wxHORIZONTAL );


	lowerSizer->Add( 0, 0, 1, wxEXPAND, 5 );

	m_sdbSizer = new wxStdDialogButtonSizer();
	m_sdbSizerOK = new wxButton( this, wxID_OK );
	m_sdbSizer->AddButton( m_sdbSizerOK );
	m_sdbSizerCancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer->AddButton( m_sdbSizerCancel );
	m_sdbSizer->Realize();

	lowerSizer->Add( m_sdbSizer, 0, wxALL, 5 );


	bMainSizer->Add( lowerSizer, 0, wxEXPAND, 5 );


	this->SetSizer( bMainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnInitDlg ) );
	m_txtValue->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnDimensionTextChange ), NULL, this );
	m_cbUnits->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnDimensionUnitsChange ), NULL, this );
	m_txtTextWidth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextPosX->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextPosY->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextThickness->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_cbTextOrientation->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtLineThickness->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_sdbSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
}

DIALOG_DIMENSION_PROPERTIES_BASE::~DIALOG_DIMENSION_PROPERTIES_BASE()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnInitDlg ) );
	m_txtValue->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnDimensionTextChange ), NULL, this );
	m_cbUnits->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnDimensionUnitsChange ), NULL, this );
	m_txtTextWidth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextPosX->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextPosY->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtTextThickness->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_cbTextOrientation->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_txtLineThickness->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );
	m_sdbSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_DIMENSION_PROPERTIES_BASE::OnOkClick ), NULL, this );

}
