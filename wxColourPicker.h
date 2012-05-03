
#ifndef COLOUR_CHOOSER
#define COLOUR_CHOOSER

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include "wxColourSlider.h"

DECLARE_EVENT_TYPE( wxEVT_COLOUR_PICKER_UPDATED, -1 )

class wxColourPickerEvent: public wxCommandEvent
{
public:
	wxColourPickerEvent( wxEventType commandType = wxEVT_COLOUR_PICKER_UPDATED, int id = 0 )
	:  wxCommandEvent(commandType, id) { }
 
	wxEvent* Clone() const { return new wxColourPickerEvent(*this); }
};

typedef void (wxEvtHandler::*wxColourPickerEventFunction)(wxColourPickerEvent &);

#define wxColourPickerEventHandler(func)                               \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)     \
	wxStaticCastEvent(wxColourPickerEventFunction, &func)

#define EVT_COLOUR_PICKER_UPDATED(id, fn)                                \
	DECLARE_EVENT_TABLE_ENTRY( wxEVT_COLOUR_PICKER_UPDATED, id, wxID_ANY,  \
	(wxObjectEventFunction)(wxEventFunction)                               \
	(wxCommandEventFunction) wxStaticCastEvent(                            \
	wxColourPickerEventFunction, &fn ), (wxObject*) NULL ),



class wxColourPicker : public wxPanel
{
public:
  wxColourPicker(wxWindow* parent,
                 wxWindowID id = wxID_ANY,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = RGB,
                 const wxValidator& val = wxDefaultValidator,
                 const wxString& name = wxT("ColourPicker"));
                
  void setColour(const wxColourExt& new_colour);
  wxColour GetColour() const {return colour_panel0->GetBackgroundColour();}
  void SetColourMode(wxColourSliderStyles mode);

protected:
  void OnScrollChange(wxScrollEvent& event);
  void OnScrollDone(wxScrollEvent& event);
  void OnModeChange(wxCommandEvent& event);

private:
  wxColour colour;
  
  wxPanel* colour_panel0;
  wxPanel* colour_panel1;
  
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
  void SetBarField(wxTextCtrl* field, wxColourSlider* slider);
  void SetAllBarFields();
};

#endif //COLOUR_CHOOSER
