
#ifndef COLOUR_CHOOSER
#define COLOUR_CHOOSER

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include "wxColourSlider.h"

class wxColourPicker : public wxPanel
{
public:
  wxColourPicker(wxWindow* parent,
                wxWindowID id = wxID_ANY,
                const wxString& name = wxT("ColourChooser"));
                
  void setColour(const wxColourExt& new_colour);

protected:
  void OnScrollChange(wxCommandEvent& event);
  void OnModeChange(wxCommandEvent& event);

private:
  wxColour colour;
  
  wxPanel* colour_panel;
  wxStaticText* slider_label_0;
  wxStaticText* slider_label_1;
  wxStaticText* slider_label_2;

  wxColourSlider* slider0;
  wxColourSlider* slider1;
  wxColourSlider* slider2;
  
  wxTextCtrl* box0;
  wxTextCtrl* box1;
  wxTextCtrl* box2;
  
  wxChoice* list_box;
  wxTextCtrl* hex_box;
  
  void SetHexCode();
};

#endif //COLOUR_CHOOSER
