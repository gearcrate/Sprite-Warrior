#ifndef COLOUR_SLIDER
#define COLOUR_SLIDER

#include <wx/wx.h>
#include "wxColourExt.h"

enum wxColourSliderStyles {
  RGB_R = 1,
  RGB_G,
  RGB_B,
  HSL_H,
  HSL_S,
  HSL_L,
  HSV_H,
  HSV_S,
  HSV_V,
  CMY_C,
  CMY_M,
  CMY_Y
};

class wxColourSlider : public wxControl
{
public:
  wxColourSlider() {
    Init();
  }

  wxColourSlider(wxWindow *parent,
                 wxWindowID winid,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = HSL_H,
                 const wxValidator& val = wxDefaultValidator,
                 const wxString& name = wxT("wxColourSlider")):
    wxControl(parent, winid, pos, size, style, val, name){
    Init();
    Create(parent, winid, pos, size, style, val, name);
  }

  bool Create(wxWindow *parent,
              wxWindowID winid,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = HSL_H,
              const wxValidator& val = wxDefaultValidator,
              const wxString& name = wxT("wxColourSlider"));

  void SetColourMode(long style);
  
  void SetRefColour(const wxColourExt& new_colour, bool update_cursor = false);
  void SetCursorPos(float pos, bool update_ref_colour = false);
  void SetNumIncrements(int incr);
  const wxColourExt& GetRefColour() const {return colour;}
  float GetCursorPos() const {return cursor_pos;}
  int GetIncrementPos() const {return (int)(cursor_pos/(1.0/increments));}
  int GetNumIncrements() const {return increments;}

protected:

  void Init() {
    increments = 255;
    SetColourMode(HSL_H);
    SetRefColour(wxColour(0,0,0));
    Connect(wxEVT_PAINT     , wxPaintEventHandler(wxColourSlider::OnPaint   ));
    Connect(wxEVT_SIZE      , wxSizeEventHandler (wxColourSlider::OnSize    ));
    Connect(wxEVT_LEFT_DOWN , wxMouseEventHandler (wxColourSlider::OnMouse  ));
    Connect(wxEVT_MOTION    , wxMouseEventHandler (wxColourSlider::OnMouse  ));
    Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler (wxColourSlider::OnScroll ));
    Connect(wxEVT_LEFT_UP   , wxMouseEventHandler (wxColourSlider::OnMouseUp));
  }

  virtual wxSize DoGetBestSize() const {
    //return wxSize(128, 32);
    return GetSize();
    //return wxDefaultSize;
  }

  void OnPaint(wxPaintEvent&);
  void PaintTicks();
  void PaintRGB_R(wxPaintEvent&);
  void PaintRGB_G(wxPaintEvent&);
  void PaintRGB_B(wxPaintEvent&);
  void PaintHSL_H(wxPaintEvent&);
  void PaintHSL_S(wxPaintEvent&);
  void PaintHSL_L(wxPaintEvent&);
  void PaintHSV_H(wxPaintEvent&);
  void PaintHSV_S(wxPaintEvent&);
  void PaintHSV_V(wxPaintEvent&);
  void PaintCMY_C(wxPaintEvent&);
  void PaintCMY_M(wxPaintEvent&);
  void PaintCMY_Y(wxPaintEvent&);
  
  void OnSize(wxSizeEvent& event) {
    Refresh();
  }
  
  void OnMouse(wxMouseEvent&);
  void OnMouseUp(wxMouseEvent&);
  void OnScroll(wxMouseEvent&);

private:
  long mode;
  wxColourExt colour;
  float cursor_pos;
  int increments;

  DECLARE_DYNAMIC_CLASS(wxColourSlider)
};

#endif //COLOUR_SLIDER
