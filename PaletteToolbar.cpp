#include "PaletteToolbar.h"

/*PaletteToolbar::PaletteToolbar(wxWindow* parent, wxWindowID id, const wxString& name):
  wxPanel(parent, id,
          wxDefaultPosition,
          wxSize(256,256),
          wxTAB_TRAVERSAL,
          name)
{
  wxBoxSizer* palette_box_sizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(palette_box_sizer);
  wxGrid* palette_grid = new wxGrid(this, -1, wxDefaultPosition, wxDefaultSize);
  gridCellRenderer* renderer = new gridCellRenderer();
  palette_grid->DisableDragGridSize();
  palette_grid->DisableDragColSize();
  palette_grid->DisableDragRowSize();
  palette_grid->DisableDragColMove();
  palette_grid->EnableEditing(false);
  palette_grid->EnableGridLines(false);
  palette_grid->SetDefaultCellBackgroundColour(wxColour(0,0,0));
  palette_grid->SetCellHighlightColour(wxColour(255,255,255));
  palette_grid->SetCellHighlightPenWidth(1);
  palette_grid->SetMargins(0,0);
  palette_grid->SetDefaultRenderer(renderer);
  palette_grid->ShowCellEditControl();
  palette_grid->SetDefaultColSize(16);
  palette_grid->SetDefaultRowSize(16);
  palette_grid->SetColLabelSize(0);
  palette_grid->SetRowLabelSize(0);
  palette_grid->CreateGrid(16, 16);
  palette_box_sizer->Add(palette_grid);
  
  palette_grid->SetCellBackgroundColour(0, 0, wxColour(255,255,255));
  palette_grid->SetCellBackgroundColour(0, 1, wxColour(0,0,0));
  palette_grid->SetCellBackgroundColour(0, 2, wxColour(255,0,0));
  palette_grid->SetCellBackgroundColour(0, 3, wxColour(255,255,0));
  palette_grid->SetCellBackgroundColour(0, 4, wxColour(0,255,0));
  palette_grid->SetCellBackgroundColour(0, 5, wxColour(0,255,255));
  palette_grid->SetCellBackgroundColour(0, 6, wxColour(0,0,255));
  palette_grid->SetCellBackgroundColour(0, 7, wxColour(255,0,255));
  palette_grid->SetCellBackgroundColour(15, 15, wxColour(255,255,255));
}


void PaletteToolbar::gridCellRenderer::Draw(wxGrid& grid,
    wxGridCellAttr& attr,
    wxDC& dc,
    const wxRect& rect,
    int row, int col,
    bool isSelected)
{
  dc.SetBrush(wxBrush(wxColour(0,0,0)));
  dc.SetPen(wxPen(wxColour(0,0,0)));
  dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
  
  if(grid.GetGridCursorCol() == col && grid.GetGridCursorRow() == row){
    dc.SetPen(wxPen(wxColour(255,255,255)));
    dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
  }

  if(row == 0 && col == 0){
    attr.SetBackgroundColour(wxColour(255,255,255));
    dc.SetBrush(wxBrush(wxColour(224,224,224)));
    dc.SetPen(wxPen(wxColour(224,224,224)));
    dc.DrawRectangle(rect.x+2, rect.y+2, rect.width-4, rect.height-4);
    dc.SetBrush(wxBrush(wxColour(128,128,128)));
    dc.SetPen(wxPen(wxColour(128,128,128)));
    dc.DrawRectangle(rect.x+5 , rect.y+2 , 3, 3);
    dc.DrawRectangle(rect.x+11, rect.y+2 , 3, 3);
    dc.DrawRectangle(rect.x+2 , rect.y+5 , 3, 3);
    dc.DrawRectangle(rect.x+8 , rect.y+5 , 3, 3);
    dc.DrawRectangle(rect.x+5 , rect.y+8 , 3, 3);
    dc.DrawRectangle(rect.x+11, rect.y+8 , 3, 3);
    dc.DrawRectangle(rect.x+2 , rect.y+11, 3, 3);
    dc.DrawRectangle(rect.x+8 , rect.y+11, 3, 3);
  }
  else{
    dc.SetBrush(wxBrush(attr.GetBackgroundColour()));
    dc.SetPen(wxPen(attr.GetBackgroundColour()));
    dc.DrawRectangle(rect.x+2, rect.y+2, rect.width-4, rect.height-4);
  }
  
  if(isSelected){
    if((attr.GetBackgroundColour().Blue () + 
        attr.GetBackgroundColour().Green()*1.6 +
        attr.GetBackgroundColour().Red  ()  ) / 3 < 128){
      dc.SetPen(wxPen(wxColour(255,255,255)));
      dc.SetBrush(wxBrush(wxColour(255,255,255)));
    }
    else{
      dc.SetPen(wxPen(wxColour(0,0,0)));
      dc.SetBrush(wxBrush(wxColour(0,0,0)));
    }
    dc.DrawRectangle(rect.x + rect.width /2 - 2, 
                     rect.y + rect.height/2 - 2, 
                     4, 4);
  }
}

wxSize PaletteToolbar::gridCellRenderer::GetBestSize(wxGrid&, wxGridCellAttr&, wxDC&, int, int)
{
  return wxSize(16, 16);
}

wxGridCellRenderer* PaletteToolbar::gridCellRenderer::Clone() const
{
  return new gridCellRenderer(*this);
}*/