#include "wxColourSlider.h"

IMPLEMENT_DYNAMIC_CLASS(wxColourSlider, wxControl)

bool wxColourSlider::Create(wxWindow *parent,
                            wxWindowID winid,
                            const wxPoint& pos,
                            const wxSize& size,
                            long style,
                            const wxValidator& val,
                            const wxString& name)
{
  SetId(winid);
  Move(pos);
  SetSize(size);
  SetValidator(val);
  SetName(name);

  SetColourMode(style);

  return Reparent(parent);
}



void wxColourSlider::OnMouse(wxMouseEvent& event)
{
  if(event.LeftIsDown()) {
    if(event.GetX() <= 3) {
      SetCursorPos(0, true);
    } else if(event.GetX() >= GetSize().GetWidth()-3) {
      SetCursorPos(1, true);
    } else {
      SetCursorPos(((float)event.GetX()-3)/(GetSize().GetWidth ()-6), true);
    }
    wxScrollEvent notify(wxEVT_SCROLL_THUMBTRACK);
    notify.SetId(GetId());
    wxPostEvent(this, notify);
    Refresh();
  } else {
    event.Skip(true);
  }
}



void wxColourSlider::OnMouseUp(wxMouseEvent& event)
{
  wxScrollEvent notify(wxEVT_SCROLL_THUMBRELEASE);
  notify.SetId(GetId());
  wxPostEvent(this, notify);
  Refresh();
}



void wxColourSlider::OnScroll(wxMouseEvent& event)
{
  if(event.GetWheelRotation() >= 0) {
    SetCursorPos(((float)GetIncrementPos())/increments + 1.0001/increments, true);
    wxScrollEvent notify(wxEVT_SCROLL_THUMBTRACK);
    notify.SetId(GetId());
    wxPostEvent(this, notify);
    Refresh();
  } else if(event.GetWheelRotation() < 0) {
    SetCursorPos(((float)GetIncrementPos())/increments - 0.9999/increments, true);
    wxScrollEvent notify(wxEVT_SCROLL_THUMBTRACK);
    notify.SetId(GetId());
    wxPostEvent(this, notify);
    Refresh();
  }
  wxScrollEvent notify(wxEVT_SCROLL_THUMBRELEASE);
  notify.SetId(GetId());
  wxPostEvent(this, notify);
}


void wxColourSlider::OnPaint(wxPaintEvent& event)
{
  switch(mode) {
  case RGB_R:
    PaintRGB_R(event);
    break;
  case RGB_G:
    PaintRGB_G(event);
    break;
  case RGB_B:
    PaintRGB_B(event);
    break;
  case HSL_H:
    PaintHSL_H(event);
    break;
  case HSL_S:
    PaintHSL_S(event);
    break;
  case HSL_L:
    PaintHSL_L(event);
    break;
  case HSV_H:
    PaintHSV_H(event);
    break;
  case HSV_S:
    PaintHSV_S(event);
    break;
  case HSV_V:
    PaintHSV_V(event);
    break;
  case CMY_C:
    PaintCMY_C(event);
    break;
  case CMY_M:
    PaintCMY_M(event);
    break;
  case CMY_Y:
    PaintCMY_Y(event);
    break;
  }

  PaintTicks();
}



void wxColourSlider::PaintTicks()
{
  wxPaintDC dc(this);

  int cursorX = 3 + cursor_pos * ((float)GetSize().GetWidth ()-7);

  dc.SetPen(wxPen(wxColour(0,0,0)));
  dc.DrawLine (wxPoint(cursorX-3, 0), wxPoint(cursorX+4, 0));
  dc.DrawLine (wxPoint(cursorX-2, 1), wxPoint(cursorX+3, 1));
  dc.DrawLine (wxPoint(cursorX-1, 2), wxPoint(cursorX+2, 2));
  dc.DrawPoint(cursorX, 3);
  dc.DrawLine (wxPoint(cursorX-3, GetSize().GetHeight()-1), wxPoint(cursorX+4, GetSize().GetHeight()-1));
  dc.DrawLine (wxPoint(cursorX-2, GetSize().GetHeight()-2), wxPoint(cursorX+3, GetSize().GetHeight()-2));
  dc.DrawLine (wxPoint(cursorX-1, GetSize().GetHeight()-3), wxPoint(cursorX+2, GetSize().GetHeight()-3));
  dc.DrawPoint(cursorX, GetSize().GetHeight()-4);
}



void wxColourSlider::PaintRGB_R(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    dc.SetPen(wxPen(wxColour((float)(i-2)/(float)(GetSize().GetWidth () - 6)*255, colour.Green(), colour.Blue())));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintRGB_G(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    dc.SetPen(wxPen(wxColour(colour.Red(), (float)(i-2)/(float)(GetSize().GetWidth () - 6)*255, colour.Blue())));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintRGB_B(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    dc.SetPen(wxPen(wxColour( colour.Red(), colour.Green(), (float)(i-2)/(float)(GetSize().GetWidth () - 6)*255)));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintHSL_H(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float h,s,l;
  col.GetHSL(&h,&s,&l);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetHSL((float)(i-2)/(float)(GetSize().GetWidth () - 6), s, l);
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintHSL_S(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float h,s,l;
  col.GetHSL(&h,&s,&l);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetHSL(h, (float)(i-2)/(float)(GetSize().GetWidth () - 6), l);
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintHSL_L(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float h,s,l;
  col.GetHSL(&h,&s,&l);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetHSL(h, s, (float)(i-2)/(float)(GetSize().GetWidth () - 6));
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintHSV_H(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float h,s,v;
  col.GetHSV(&h,&s,&v);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetHSV((float)(i-2)/(float)(GetSize().GetWidth () - 6), s, v);
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintHSV_S(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float h,s,v;
  col.GetHSV(&h,&s,&v);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetHSV(h, (float)(i-2)/(float)(GetSize().GetWidth () - 6), v);
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintHSV_V(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float h,s,v;
  col.GetHSV(&h,&s,&v);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetHSV(h, s, (float)(i-2)/(float)(GetSize().GetWidth () - 6));
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintCMY_C(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float c,m,y;
  col.GetCMY(&c,&m,&y);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetCMY((float)(i-2)/(float)(GetSize().GetWidth () - 6), m, y);
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintCMY_M(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float c,m,y;
  col.GetCMY(&c,&m,&y);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetCMY(c, (float)(i-2)/(float)(GetSize().GetWidth () - 6), y);
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::PaintCMY_Y(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxColourExt col(colour);
  float c,m,y;
  col.GetCMY(&c,&m,&y);

  for(int i = 3; i < GetSize().GetWidth ()-3; i++) {
    col.SetCMY(c, m, (float)(i-2)/(float)(GetSize().GetWidth () - 6));
    dc.SetPen(wxPen(col));
    dc.DrawLine(wxPoint(i, 4), wxPoint(i, GetSize().GetHeight()-4));
  }
}



void wxColourSlider::SetRefColour(const wxColourExt& new_colour, bool update_cursor)
{
  colour = new_colour;

  if(update_cursor) {
    switch(mode) {
    case RGB:
    case RGB_R:
    default:
      SetCursorPos(colour.RgbRed());
      break;

    case RGB_G:
      SetCursorPos(colour.RgbGreen());
      break;

    case RGB_B:
      SetCursorPos(colour.RgbBlue());
      break;

    case HSL:
    case HSL_H:
      SetCursorPos(colour.HslHue());
      break;

    case HSL_S:
      SetCursorPos(colour.HslSaturation());
      break;

    case HSL_L:
      SetCursorPos(colour.HslLuminosity());
      break;

    case HSV:
    case HSV_H:
      SetCursorPos(colour.HsvHue());
      break;

    case HSV_S:
      SetCursorPos(colour.HsvSaturation());
      break;

    case HSV_V:
      SetCursorPos(colour.HsvValue());
      break;

    case CMY:
    case CMY_C:
      SetCursorPos(colour.CmyCyan());
      break;

    case CMY_M:
      SetCursorPos(colour.CmyMagenta());
      break;

    case CMY_Y:
      SetCursorPos(colour.CmyYellow());
      break;
    }
  }

  Refresh();
}



void wxColourSlider::SetCursorPos(float pos, bool update_ref_colour)
{
  pos = pos > 0   ? pos : 0;
  pos = pos < 1.0 ? pos : 1.0;
  cursor_pos = pos;

  if(update_ref_colour) {
    switch(mode) {
    case RGB:
    case RGB_R:
    default:
      colour.RgbRed(pos);
      break;
      
    case RGB_G:
      colour.RgbGreen(pos);
      break;

    case RGB_B:
      colour.RgbBlue(pos);
      break;

    case HSL:
    case HSL_H:
      colour.HslHue(pos);
      break;

    case HSL_S:
      colour.HslSaturation(pos);
      break;

    case HSL_L:
      colour.HslLuminosity(pos);
      break;

    case HSV:
    case HSV_H:
      colour.HsvHue(pos);
      break;

    case HSV_S:
      colour.HsvSaturation(pos);
      break;

    case HSV_V:
      colour.HsvValue(pos);
      break;

    case CMY:
    case CMY_C:
      colour.CmyCyan(pos);
      break;

    case CMY_M:
      colour.CmyMagenta(pos);
      break;

    case CMY_Y:
      colour.CmyYellow(pos);
      break;
    }
  }

  Refresh();
}



void wxColourSlider::SetColourMode(long style)
{
  mode = style;
  SetRefColour(colour, true);
  Refresh();
}



void wxColourSlider::SetNumIncrements(int incr)
{
  incr = incr > 1 ? incr : 1;
  increments = incr;
}
