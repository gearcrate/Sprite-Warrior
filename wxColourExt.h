
#ifndef WX_COLOR_EXT
#define WX_COLOR_EXT

#include <wx/wx.h>

class wxColourExt : public wxColour{
public:
  wxColourExt():
    wxColour(0,0,0),
    R(0), G(0), B(0),
    last_mode_used(RGB){}
    
  wxColourExt(const wxColour& col):
    wxColour(col),
    R((float)col.Red()/255),
    G((float)col.Green()/255),
    B((float)col.Blue()/255),
    last_mode_used(RGB){}
  
  float RgbRed        () const;
  float RgbGreen      () const;
  float RgbBlue       () const;
  float HslHue        () const;
  float HslSaturation () const;
  float HslLuminosity () const;
  float HsvHue        () const;
  float HsvSaturation () const;
  float HsvValue      () const;
  float CmyCyan       () const;
  float CmyMagenta    () const;
  float CmyYellow     () const;
  
  void RgbRed       (float r);
  void RgbGreen     (float g);
  void RgbBlue      (float b);
  void HslHue       (float h);
  void HslSaturation(float s);
  void HslLuminosity(float l);
  void HsvHue       (float h);
  void HsvSaturation(float s);
  void HsvValue     (float v);
  void CmyCyan      (float c);
  void CmyMagenta   (float m);
  void CmyYellow    (float y);
  
  void SetRGB(float  r, float  g, float  b);
  void GetRGB(float* r, float* g, float* b) const;
  void SetHSL(float  h, float  s, float  l);
  void GetHSL(float* h, float* s, float* l) const;
  void SetHSV(float  h, float  s, float  v);
  void GetHSV(float* h, float* s, float* v) const;
  void SetCMY(float  c, float  m, float  y);
  void GetCMY(float* c, float* m, float* y) const;
  
  operator wxColour(){
    wxColour col(Red(), Green(), Blue(), Alpha());
    return col;
  }
  
private:
  mutable float R , G , B ; //Mode 0;
  mutable float H0, S0, L0; //Mode 1;
  mutable float H1, S1, V1; //Mode 2;
  mutable float C , M , Y ; //Mode 3;
  
  enum colour_mode {RGB, HSL, HSV, CMY} last_mode_used;
  bool WasLastMode(colour_mode last) const {return last_mode_used == last;}
};

#endif //WX_COLOR_EXT