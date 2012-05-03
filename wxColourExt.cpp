#include "wxColourExt.h"

float wxColourExt::RgbRed() const
{
  GetRGB(&R, &G, &B);
  return R;
}



float wxColourExt::RgbGreen() const
{
  GetRGB(&R, &G, &B);
  return G;
}



float wxColourExt::RgbBlue() const
{
  GetRGB(&R, &G, &B);
  return B;
}



float wxColourExt::HslHue() const
{
  GetHSL(&H0, &S0, &L0);
  return H0;
}



float wxColourExt::HslSaturation() const
{
  GetHSL(&H0, &S0, &L0);
  return S0;
}



float wxColourExt::HslLuminosity() const
{
  GetHSL(&H0, &S0, &L0);
  return L0;
}



float wxColourExt::HsvHue() const
{
  GetHSV(&H1, &S1, &V1);
  return H1;
}



float wxColourExt::HsvSaturation() const
{
  GetHSV(&H1, &S1, &V1);
  return S1;
}



float wxColourExt::HsvValue() const
{
  GetHSV(&H1, &S1, &V1);
  return V1;
}



float wxColourExt::CmyCyan() const
{
  GetCMY(&C, &M, &Y);
  return C;
}



float wxColourExt::CmyMagenta() const
{
  GetCMY(&C, &M, &Y);
  return M;
}



float wxColourExt::CmyYellow() const
{
  GetCMY(&C, &M, &Y);
  return Y;
}



void wxColourExt::RgbRed(float r)
{
  RgbRed();
  SetRGB(r,G,B);
}



void wxColourExt::RgbGreen(float g)
{
  RgbGreen();
  SetRGB(R,g,B);
}



void wxColourExt::RgbBlue(float b)
{
  RgbBlue();
  SetRGB(R,G,b);
}



void wxColourExt::HslHue(float h)
{
  HslHue();
  SetHSL(h,S0,L0);
}



void wxColourExt::HslSaturation(float s)
{
  HslSaturation();
  SetHSL(H0,s,L0);
}



void wxColourExt::HslLuminosity(float l)
{
  HslLuminosity();
  SetHSL(H0,S0,l);
}



void wxColourExt::HsvHue(float h)
{
  HsvHue();
  SetHSV(h,S1,V1);
}



void wxColourExt::HsvSaturation(float s)
{
  HsvSaturation();
  SetHSV(H1,s,V1);
}



void wxColourExt::HsvValue(float v)
{
  HsvValue();
  SetHSV(H1,S1,v);
}



void wxColourExt::CmyCyan(float c)
{
  CmyCyan();
  SetCMY(c,M,Y);
}



void wxColourExt::CmyMagenta(float m)
{
  CmyMagenta();
  SetCMY(C,m,Y);
}



void wxColourExt::CmyYellow(float y)
{
  CmyYellow();
  SetCMY(C,M,y);
}



void wxColourExt::SetRGB(float  r, float  g, float  b)
{
  R = r;
  G = g;
  B = b;
  last_mode_used = RGB;
  Set(r*255, g*255, b*255);
}



void wxColourExt::GetRGB(float* r, float* g, float* b) const
{
  if(!WasLastMode(RGB)) {
    R = (float)Red()/255;
    G = (float)Green()/255;
    B = (float)Blue()/255;
  }
  *r = R;
  *g = G;
  *b = B;
}



float HueToRGB(float v1, float v2, float vH)
{
  if(vH < 0) vH += 1;
  if(vH > 1) vH -= 1;
  if((6 * vH) < 1) return v1 + (v2 - v1) * 6 * vH;
  if((2 * vH) < 1) return v2;
  if((3 * vH) < 2) return v1 + (v2 - v1) * ((2.0/3) - vH) * 6;
  return v1;
}



void wxColourExt::SetHSL(float  h, float  s, float  l)
{
  H0 = h;
  S0 = s;
  L0 = l;
  last_mode_used = HSL;

  unsigned char r = l * 255;
  unsigned char g = l * 255;
  unsigned char b = l * 255;

  if(s != 0) {
    float var_2 = 0;
    if (l < 0.5) var_2 = l*(1 + s);
    else         var_2 = (l + s) - (s*l);

    float var_1 = 2 * l - var_2;

    r = 255 * HueToRGB(var_1, var_2, h + (1.0/3));
    g = 255 * HueToRGB(var_1, var_2, h);
    b = 255 * HueToRGB(var_1, var_2, h - (1.0/3));
  }

  Set(r, g, b);
}



void wxColourExt::GetHSL(float* h, float* s, float* l) const
{
  if(!WasLastMode(HSL)) {
    float r, g, b;
    GetRGB(&r, &g, &b);
    float var_Min = r   < g ? r           : g;
    var_Min = var_Min < b ? var_Min : b;
    float var_Max = r       > g ? r       : g;
    var_Max = var_Max > b ? var_Max : b;
    float del_Max = var_Max - var_Min;

    L0 = (var_Max + var_Min) / 2.0;

    if(del_Max==0) {
      H0 = 0.0;
      S0 = 0.0;
    } else {
      if (L0 < 0.5) S0 = del_Max/(var_Max + var_Min);
      else          S0 = del_Max/(2.0 - var_Max - var_Min);

      float del_R = (((var_Max - r)/6.0) + (del_Max/2.0))/del_Max;
      float del_G = (((var_Max - g)/6.0) + (del_Max/2.0))/del_Max;
      float del_B = (((var_Max - b)/6.0) + (del_Max/2.0))/del_Max;

      if      (r == var_Max) H0 = del_B - del_G;
      else if (g == var_Max) H0 = (1.0/3.0) + del_R - del_B;
      else if (b == var_Max) H0 = (2.0/3.0) + del_G - del_R;

      if ( H0 < 0 ) H0 += 1.0;
      if ( H0 > 1 ) H0 -= 1.0;
    }
  }
  *h = H0;
  *s = S0;
  *l = L0;
}



void wxColourExt::SetHSV(float  h, float  s, float  v)
{
  H1 = h;
  S1 = s;
  V1 = v;
  last_mode_used = HSV;

  unsigned char r = v * 255;
  unsigned char g = v * 255;
  unsigned char b = v * 255;

  if(s != 0) {
    float var_h = h * 6;
    if (var_h == 6) var_h = 0;
    float var_i = (int)var_h;
    float var_1 = v * (1 - s);
    float var_2 = v * (1 - s*(var_h - var_i));
    float var_3 = v * (1 - s*(1 - (var_h - var_i)));

    float var_r, var_g, var_b;

    if      ( var_i == 0 ) {
      var_r = v     ;
      var_g = var_3 ;
      var_b = var_1;
    } else if ( var_i == 1 ) {
      var_r = var_2 ;
      var_g = v     ;
      var_b = var_1;
    } else if ( var_i == 2 ) {
      var_r = var_1 ;
      var_g = v     ;
      var_b = var_3;
    } else if ( var_i == 3 ) {
      var_r = var_1 ;
      var_g = var_2 ;
      var_b = v;
    } else if ( var_i == 4 ) {
      var_r = var_3 ;
      var_g = var_1 ;
      var_b = v;
    } else                   {
      var_r = v     ;
      var_g = var_1 ;
      var_b = var_2;
    }

    r = var_r * 255;
    g = var_g * 255;
    b = var_b * 255;
  }

  Set(r,g,b);
}



void wxColourExt::GetHSV(float* h, float* s, float* v) const
{
  if(!WasLastMode(HSV)) {
    float r, g, b;
    GetRGB(&r, &g, &b);
    float var_Min = r   < g ? r           : g;
    var_Min = var_Min < b ? var_Min : b;
    float var_Max = r       > g ? r       : g;
    var_Max = var_Max > b ? var_Max : b;
    float del_Max = var_Max - var_Min;

    V1 = var_Max;

    if(del_Max==0) {
      H1 = 0;
      S1 = 0;
    } else {
      S1 = del_Max/var_Max;

      float del_R = (((var_Max - r)/6.0) + (del_Max/2.0))/del_Max;
      float del_G = (((var_Max - g)/6.0) + (del_Max/2.0))/del_Max;
      float del_B = (((var_Max - b)/6.0) + (del_Max/2.0))/del_Max;

      if      (r == var_Max) H1 = del_B - del_G;
      else if (g == var_Max) H1 = (1.0/3.0) + del_R - del_B;
      else if (b == var_Max) H1 = (2.0/3.0) + del_G - del_R;

      if ( H1 < 0 ) H1 += 1.0;
      if ( H1 > 1 ) H1 -= 1.0;
    }
  }
  *h = H1;
  *s = S1;
  *v = V1;
}



void wxColourExt::SetCMY(float  c, float  m, float  y)
{
  C = c;
  M = m;
  Y = y;
  last_mode_used = CMY;
  Set((1.0-c)*255, (1.0-m)*255, (1.0-y)*255);
}



void wxColourExt::GetCMY(float* c, float* m, float* y) const
{
  if(!WasLastMode(CMY)) {
    C = 1 - (float)Red()/255;
    M = 1 - (float)Green()/255;
    Y = 1 - (float)Blue()/255;
  }
  *c = C;
  *m = M;
  *y = Y;
}
