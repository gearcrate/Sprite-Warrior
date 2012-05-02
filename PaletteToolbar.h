
#ifndef PALETTE_TOOLBAR
#define PALETTE_TOOLBAR

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/sizer.h>
//#include <wx/grid.h>
#include "wxPaletteManager.h"

class PaletteToolbar : public wxPaletteManager{
public:
  PaletteToolbar(wxWindow* parent,
                 wxWindowID id = wxID_ANY,
                 const wxString& name = wxT("PaletteToolbar")):
    wxPaletteManager(parent, id, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, name){}
};

/*class PaletteToolbar : public wxPanel{
public:
  PaletteToolbar(wxWindow* parent,
                               wxWindowID id = wxID_ANY,
                               const wxString& name = wxT("PaletteToolbar"));
  
private:
  class gridCellRenderer : public wxGridCellRenderer{
  public:
    void Draw(wxGrid& grid,
              wxGridCellAttr& attr,
              wxDC& dc,
              const wxRect& rect,
              int row, int col,
              bool isSelected);
              
    wxSize GetBestSize(wxGrid&, wxGridCellAttr&, wxDC&, int, int);
    wxGridCellRenderer* Clone() const;
  };
};*/

#endif //PALETTE_TOOLBAR