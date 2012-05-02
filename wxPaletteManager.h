#ifndef WX_PALETTE_MANAGER
#define WX_PALETTE_MANAGER

#include <wx/wx.h>


class wxPaletteManager : public wxControl
{
public:
  wxPaletteManager() {
    Init();
  }

  wxPaletteManager(wxWindow *parent,
                 wxWindowID winid,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = 0,
                 const wxValidator& val = wxDefaultValidator,
                 const wxString& name = wxT("wxPaletteManager")):
    wxControl(parent, winid, pos, size, style, val, name){
    Init();
    Create(parent, winid, pos, size, style, val, name);
  }

  bool Create(wxWindow *parent,
              wxWindowID winid,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0,
              const wxValidator& val = wxDefaultValidator,
              const wxString& name = wxT("wxPaletteManager"));
              
  bool SetColour (unsigned char row, unsigned char col, wxColour new_colour, bool ignore_sync = false);
  bool SetSync   (unsigned char row, unsigned char col, bool sync_state);
  bool ToggleSync(unsigned char row, unsigned char col) {return SetSync(row, col, !GetSync(row, col));}
  bool SwapColours(unsigned char row0, unsigned char col0, unsigned char row1, unsigned char col1);
  bool BatchMove(unsigned char row0, unsigned char col0,
                 unsigned char row1, unsigned char col1,
                 char horizontal, char vertical);
                 
  const wxColour& GetColour(unsigned char row, unsigned char col) const {return colours[row][col];}
  bool GetSync(unsigned char row, unsigned char col) const {return sync[row][col];}

protected:

  void Init();

  virtual wxSize DoGetBestSize() const {
    return wxSize(256, 256);
  }

  void OnPaint(wxPaintEvent&);
  
  void OnSize(wxSizeEvent&) {Refresh();}
  void OnLeftClick(wxMouseEvent&);
  void OnRightClick(wxMouseEvent&);
  void OnDrag(wxMouseEvent&);
  void OnLeftUp(wxMouseEvent&);
  void OnKeyDown(wxKeyEvent&);

private:
  wxColour colours[16][16];
  bool sync[16][16];
  unsigned char primary_row;
  unsigned char primary_col;
  unsigned char secondary_row;
  unsigned char secondary_col;
  unsigned char drag_row;
  unsigned char drag_col;
  
  bool IsDragValid() {return (drag_col < 16 && drag_row < 16);}
  bool IsValidRange(unsigned char row, unsigned char col) {return (row < 16 && col < 16);}
  bool IsColourZero(unsigned char row, unsigned char col) {return (row == 0 && col == 0);}
  void InvalidateDrag() {drag_row = 16; drag_col = 16;}
  
  void DrawPrimaryCursorGraphic(unsigned char row, unsigned char col);
  void DrawSecondaryCursorGraphic(unsigned char row, unsigned char col);
  void DrawDragCursorGraphic(unsigned char row, unsigned char col);
  void DrawColourGrid();

  DECLARE_DYNAMIC_CLASS(wxPaletteManager)
};

#endif //WX_PALETTE_MANAGER