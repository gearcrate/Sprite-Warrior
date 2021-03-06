#include "wxColourPicker.h"

DEFINE_EVENT_TYPE(wxEVT_COLOUR_PICKER_UPDATED)

const int id_choice_clour_mode = 1;
const int id_slider_bar0 = 2;
const int id_slider_bar1 = 3;
const int id_slider_bar2 = 4;

wxColourPicker::wxColourPicker(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                               const wxSize& size, long style,
                               const wxValidator& val ,const wxString& name):
  wxPanel(parent, id,
          pos,
          wxSize(256, 200),
          style,
          name)
{
  wxBoxSizer* vertical_sizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(vertical_sizer);

  colour_panel0 = new wxPanel(this, -1, wxDefaultPosition, wxSize(192, 32));
  colour_panel1 = new wxPanel(this, -1, wxDefaultPosition, wxSize(64, 32));
  colour_panel0->SetBackgroundColour(wxColour(0,0,0));
  colour_panel1->SetBackgroundColour(wxColour(0,0,0));

  wxBoxSizer* panel_sizer    = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* mode_hex_sizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* slider_sizer0 =  new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* slider_sizer1 =  new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* slider_sizer2 =  new wxBoxSizer(wxHORIZONTAL);

  slider_label_0 = new wxStaticText(this, -1, wxT("  R"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  slider_label_1 = new wxStaticText(this, -1, wxT("  G"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  slider_label_2 = new wxStaticText(this, -1, wxT("  B"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  
  slider0 = new wxColourSlider(this, id_slider_bar0, wxDefaultPosition, wxSize(160,32), RGB_R);
  slider1 = new wxColourSlider(this, id_slider_bar1, wxDefaultPosition, wxSize(160,32), RGB_G);
  slider2 = new wxColourSlider(this, id_slider_bar2, wxDefaultPosition, wxSize(160,32), RGB_B);

  box0 = new wxTextCtrl(this, -1, wxT("0"), wxDefaultPosition, wxSize(0,32));
  box1 = new wxTextCtrl(this, -1, wxT("0"), wxDefaultPosition, wxSize(0,32));
  box2 = new wxTextCtrl(this, -1, wxT("0"), wxDefaultPosition, wxSize(0,32));

  wxArrayString strings;
  strings.Add(wxT("CMY"));
  strings.Add(wxT("HSL"));
  strings.Add(wxT("HSV"));
  strings.Add(wxT("RGB"));

  list_box = new wxChoice(this, id_choice_clour_mode, wxDefaultPosition, wxSize(128,32), strings);
  hex_box = new wxTextCtrl(this, -1, wxT("000000"), wxDefaultPosition, wxSize(0,32));
  
  list_box->SetSelection(3);
  
  SetColourMode((wxColourSliderStyles)style);

  vertical_sizer->Add(panel_sizer   , 1);
  vertical_sizer->Add(mode_hex_sizer, 1);
  vertical_sizer->Add(slider_sizer0 , 1);
  vertical_sizer->Add(slider_sizer1 , 1);
  vertical_sizer->Add(slider_sizer2 , 1);
  
  panel_sizer->Add(colour_panel0, 3);
  panel_sizer->Add(colour_panel1, 1);

  slider_sizer0->Add(slider_label_0, 1, wxALIGN_CENTER);
  slider_sizer1->Add(slider_label_1, 1, wxALIGN_CENTER);
  slider_sizer2->Add(slider_label_2, 1, wxALIGN_CENTER);

  slider_sizer0->Add(slider0, 5, wxALIGN_CENTER);
  slider_sizer1->Add(slider1, 5, wxALIGN_CENTER);
  slider_sizer2->Add(slider2, 5, wxALIGN_CENTER);

  slider_sizer0->Add(box0, 2, wxALIGN_CENTER);
  slider_sizer1->Add(box1, 2, wxALIGN_CENTER);
  slider_sizer2->Add(box2, 2, wxALIGN_CENTER);

  mode_hex_sizer->Add(list_box    , 1, wxALIGN_CENTER);
  //mode_hex_sizer->Add(colour_panel, 2, wxALIGN_CENTER);
  mode_hex_sizer->Add(hex_box     , 1, wxALIGN_CENTER);
  
  Connect(id_choice_clour_mode, wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(wxColourPicker::OnModeChange));
  Connect(wxEVT_SCROLL_THUMBTRACK,  wxScrollEventHandler (wxColourPicker::OnScrollChange));
  Connect(wxEVT_SCROLL_THUMBRELEASE,  wxScrollEventHandler (wxColourPicker::OnScrollDone));
}


void wxColourPicker::setColour(const wxColourExt& new_colour)
{
  colour = new_colour;
  slider0->SetRefColour(new_colour, true);
  slider1->SetRefColour(new_colour, true);
  slider2->SetRefColour(new_colour, true);
  colour_panel0->SetBackgroundColour(new_colour);
  colour_panel1->SetBackgroundColour(new_colour);
  SetAllBarFields();
  SetHexCode();
}



void wxColourPicker::SetHexCode(){
  hex_box->SetValue(wxString::Format(wxT("#%02X%02X%02X"), colour_panel0->GetBackgroundColour().Red(),
                                                           colour_panel0->GetBackgroundColour().Green(),
                                                           colour_panel0->GetBackgroundColour().Blue()));
}



void wxColourPicker::SetBarField(wxTextCtrl* field, wxColourSlider* slider){
  field->SetValue(wxString::Format(wxT("%i"), slider->GetIncrementPos()));
}



void wxColourPicker::SetAllBarFields(){
  SetBarField(box0, slider0);
  SetBarField(box1, slider1);
  SetBarField(box2, slider2);
}



void wxColourPicker::OnScrollChange(wxScrollEvent& event)
{
  switch(event.GetId()){
    case id_slider_bar0:
    slider1->SetRefColour(slider0->GetRefColour());
    slider2->SetRefColour(slider0->GetRefColour());
    colour_panel0->SetBackgroundColour(slider0->GetRefColour());
    SetBarField(box0, slider0);
    break;
    
    case id_slider_bar1:
    slider0->SetRefColour(slider1->GetRefColour());
    slider2->SetRefColour(slider1->GetRefColour());
    colour_panel0->SetBackgroundColour(slider1->GetRefColour());
    SetBarField(box1, slider1);
    break;
    
    case id_slider_bar2:
    slider0->SetRefColour(slider2->GetRefColour());
    slider1->SetRefColour(slider2->GetRefColour());
    colour_panel0->SetBackgroundColour(slider2->GetRefColour());
    SetBarField(box2, slider2);
    break;
  }
  SetHexCode();
  wxColourPickerEvent notify(wxEVT_COLOUR_PICKER_UPDATED);
  notify.SetId(GetId());
  wxPostEvent(GetParent(), notify);
}



void wxColourPicker::OnScrollDone(wxScrollEvent& event)
{
  colour_panel1->SetBackgroundColour(colour_panel0->GetBackgroundColour());
}



void wxColourPicker::SetColourMode(wxColourSliderStyles mode){
  switch(mode){
    case RGB:
    case RGB_R:
    case RGB_G:
    case RGB_B:
    default:
    slider0->SetColourMode(RGB_R);
    slider1->SetColourMode(RGB_G);
    slider2->SetColourMode(RGB_B);
    slider0->SetNumIncrements(255);
    slider1->SetNumIncrements(255);
    slider2->SetNumIncrements(255);
    slider_label_0->SetLabel(wxT("  R"));
    slider_label_1->SetLabel(wxT("  G"));
    slider_label_2->SetLabel(wxT("  B"));
    break;
    
    case HSL:
    case HSL_H:
    case HSL_S:
    case HSL_L:
    slider0->SetColourMode(HSL_H);
    slider1->SetColourMode(HSL_S);
    slider2->SetColourMode(HSL_L);
    slider0->SetNumIncrements(359);
    slider1->SetNumIncrements(100);
    slider2->SetNumIncrements(100);
    slider_label_0->SetLabel(wxT("  H"));
    slider_label_1->SetLabel(wxT("  S"));
    slider_label_2->SetLabel(wxT("  L"));
    break;
    
    case HSV:
    case HSV_H:
    case HSV_S:
    case HSV_V:
    slider0->SetColourMode(HSV_H);
    slider1->SetColourMode(HSV_S);
    slider2->SetColourMode(HSV_V);
    slider0->SetNumIncrements(359);
    slider1->SetNumIncrements(100);
    slider2->SetNumIncrements(100);
    slider_label_0->SetLabel(wxT("  H"));
    slider_label_1->SetLabel(wxT("  S"));
    slider_label_2->SetLabel(wxT("  V"));
    break;
    
    case CMY:
    case CMY_C:
    case CMY_M:
    case CMY_Y:
    slider0->SetColourMode(CMY_C);
    slider1->SetColourMode(CMY_M);
    slider2->SetColourMode(CMY_Y);
    slider0->SetNumIncrements(255);
    slider1->SetNumIncrements(255);
    slider2->SetNumIncrements(255);
    slider_label_0->SetLabel(wxT("  C"));
    slider_label_1->SetLabel(wxT("  M"));
    slider_label_2->SetLabel(wxT("  Y"));
    break;
  }
  SetAllBarFields();
  SetHexCode();
}



void wxColourPicker::OnModeChange(wxCommandEvent& event)
{
  if(event.GetString() == wxT("RGB")) {
    SetColourMode(RGB);
  } else if(event.GetString() == wxT("HSL")) {
    SetColourMode(HSL);
  } else if(event.GetString() == wxT("HSV")) {
    SetColourMode(HSV);
  } else if(event.GetString() == wxT("CMY")) {
    SetColourMode(CMY);
  }
}
