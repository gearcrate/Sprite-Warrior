#ifndef WX_PALETTE_MANAGER
#define WX_PALETTE_MANAGER

#include <wx/wx.h>

DECLARE_EVENT_TYPE( wxEVT_PALETTE_MANAGER_UPDATED, -1 )

class wxPaletteManagerEvent: public wxCommandEvent
{
public:
	wxPaletteManagerEvent( wxEventType commandType = wxEVT_PALETTE_MANAGER_UPDATED, int id = 0 )
	:  wxCommandEvent(commandType, id),
    pri_pos_mov(false),
    sec_pos_mov(false),
    pri_colour_ch(false),
    sec_colour_ch(false){ }
 
	wxEvent* Clone() const { return new wxPaletteManagerEvent(*this); }
  
  void SetState(bool pri_pos_moved, bool sec_pos_moved, bool pri_colour_changed, bool sec_colour_changed);
  bool HasPrimaryMoved()           {return pri_pos_mov;}
  bool HasSecondaryMoved()         {return sec_pos_mov;}
  bool HasPrimaryColourChanged()   {return pri_colour_ch;}
  bool HasSecondaryColourChanged() {return sec_colour_ch;}
  
private:
  bool pri_pos_mov;
  bool sec_pos_mov;
  bool pri_colour_ch;
  bool sec_colour_ch;
};

typedef void (wxEvtHandler::*wxPaletteManagerEventFunction)(wxPaletteManagerEvent &);

#define wxPaletteManagerEventHandler(func)                               \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)     \
	wxStaticCastEvent(wxPaletteManagerEventFunction, &func)

#define EVT_PALETTE_MANAGER_UPDATED(id, fn)                                \
	DECLARE_EVENT_TABLE_ENTRY( wxEVT_PALETTE_MANAGER_UPDATED, id, wxID_ANY,  \
	(wxObjectEventFunction)(wxEventFunction)                               \
	(wxCommandEventFunction) wxStaticCastEvent(                            \
	wxPaletteManagerEventFunction, &fn ), (wxObject*) NULL ),
  
  
  
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
  bool SetPrimaryColour(                                wxColour new_colour, bool ignore_sync = false);
  bool SetSecondaryColour(                              wxColour new_colour, bool ignore_sync = false);
  bool SetSync   (unsigned char row, unsigned char col, bool sync_state);
  bool ToggleSync(unsigned char row, unsigned char col) {return SetSync(row, col, !GetSync(row, col));}
  bool SwapColours(unsigned char row0, unsigned char col0, unsigned char row1, unsigned char col1);
  bool BatchMove(unsigned char row0, unsigned char col0,
                 unsigned char row1, unsigned char col1,
                 char horizontal, char vertical);
                 
  const wxColour& GetColour(unsigned char row, unsigned char col) const {return colours[row][col];}
  const wxColour& GetPrimaryColour  () const {return colours[primary_row][primary_col];}
  const wxColour& GetSecondaryColour() const {return colours[secondary_row][secondary_col];}
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
  
  void SendUpdateEvent(bool pri_pos_moved, bool sec_pos_moved, bool pri_colour_changed, bool sec_colour_changed);

  DECLARE_DYNAMIC_CLASS(wxPaletteManager)
};

#endif //WX_PALETTE_MANAGER