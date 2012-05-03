#include "wxPaletteManager.h"

DEFINE_EVENT_TYPE(wxEVT_PALETTE_MANAGER_UPDATED)
IMPLEMENT_DYNAMIC_CLASS(wxPaletteManager, wxControl)

bool wxPaletteManager::Create(wxWindow *parent,
                              wxWindowID winid,
                              const wxPoint& pos,
                              const wxSize& size,
                              long style,
                              const wxValidator& val,
                              const wxString& name)
{
  SetId(winid);
  Move(pos);
  //SetSize(size);
  SetSize(wxSize(256, 256));
  SetValidator(val);
  SetName(name);

  return Reparent(parent);
}



void wxPaletteManager::Init()
{
  primary_row = 15;
  primary_col = 15;
  secondary_row = 0;
  secondary_col = 0;
  InvalidateDrag();

  wxColour black(0,0,0);
  wxColour white(255,255,255);

  //Set all palette colours to black
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 16; j++) {
      colours[i][j] = black;
      sync[i][j] = false;
    }
  }

  Connect(wxEVT_PAINT     , wxPaintEventHandler(wxPaletteManager::OnPaint      ));
  Connect(wxEVT_SIZE      , wxSizeEventHandler (wxPaletteManager::OnSize       ));
  Connect(wxEVT_LEFT_DOWN , wxMouseEventHandler(wxPaletteManager::OnLeftClick  ));
  Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(wxPaletteManager::OnRightClick ));
  Connect(wxEVT_LEFT_UP   , wxMouseEventHandler(wxPaletteManager::OnLeftUp     ));
  Connect(wxEVT_MOTION    , wxMouseEventHandler(wxPaletteManager::OnDrag       ));
  Connect(wxEVT_KEY_DOWN  , wxKeyEventHandler  (wxPaletteManager::OnKeyDown    ));
}



void wxPaletteManager::OnPaint(wxPaintEvent&)
{
  DrawColourGrid();

  if(IsDragValid()) {
    DrawDragCursorGraphic(drag_row, drag_col);
  }

  DrawPrimaryCursorGraphic(primary_row, primary_col);

  //Draw the secondary cursor if not overshadowed by the drag cursor
  if(secondary_col != drag_col || secondary_row != drag_row) {
    DrawSecondaryCursorGraphic(secondary_row, secondary_col);
  }
}



void wxPaletteManager::DrawColourGrid()
{
  wxPaintDC dc(this);

  //Erase background to black
  dc.SetBackground(wxColour(0,0,0));
  dc.Clear();
  
  wxColour black(0,0,0);
  wxColour white(255,255,255);

  //Draw the grid of colors
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 16; j++) {
      dc.SetPen(wxPen(colours[i][j]));
      dc.SetBrush(wxBrush(colours[i][j]));
      dc.DrawRectangle(j*16,
                       i*16,
                       16, 16);
      if(sync[i][j]){
        if(colours[i][j].Red() + colours[i][j].Green() + colours[i][j].Blue() < 255){
          dc.SetPen(wxPen(white));
          dc.SetBrush(wxBrush(white));
        }
        else{
          dc.SetPen(wxPen(black));
          dc.SetBrush(wxBrush(black));
        }
        dc.DrawRectangle(j*16 + 2,
                         i*16 + 2,
                         3, 3);
      }
    }
  }

  //Draw the transparency placeholder at palette entry 0
  wxColour grey1(224,224,224);
  wxColour grey2(128,128,128);
  dc.SetPen(wxPen(grey1));
  dc.SetBrush(wxBrush(grey1));
  dc.DrawRectangle(0, 0, 16, 16);
  dc.SetPen(wxPen(grey2));
  dc.SetBrush(wxBrush(grey2));
  dc.DrawRectangle(0 , 0 , 4, 4);
  dc.DrawRectangle(8 , 0 , 4, 4);
  dc.DrawRectangle(0 , 8 , 4, 4);
  dc.DrawRectangle(8 , 8 , 4, 4);
  dc.DrawRectangle(4 , 4 , 4, 4);
  dc.DrawRectangle(12, 4 , 4, 4);
  dc.DrawRectangle(4 , 12, 4, 4);
  dc.DrawRectangle(12, 12, 4, 4);
}



void wxPaletteManager::DrawPrimaryCursorGraphic(unsigned char row, unsigned char col)
{
  if(IsValidRange(row, col)) {
    int x_base = col*16;
    int y_base = row*16;

    wxPaintDC dc(this);

    dc.SetPen(wxPen(wxColour(255,255,255)));
    dc.SetBrush(wxBrush(wxColour(0,0,0), wxTRANSPARENT));
    dc.DrawRectangle(x_base,
                     y_base,
                     16, 16);
    dc.SetPen(wxPen(wxColour(0,0,0)));
    dc.DrawRectangle(x_base + 1,
                     y_base + 1,
                     14, 14);
    dc.DrawRectangle(x_base - 1,
                     y_base - 1,
                     18, 18);
  }
}



void wxPaletteManager::DrawSecondaryCursorGraphic(unsigned char row, unsigned char col)
{
  if(IsValidRange(row, col)) {
    int x_base = col*16;
    int y_base = row*16;

    wxPaintDC dc(this);

    dc.SetPen(wxPen(wxColour(0,0,0)));
    dc.SetBrush(wxBrush(wxColour(255,255,255)));
    dc.DrawRectangle(x_base + 5,
                     y_base + 5,
                     6, 6);
    dc.DrawRectangle(x_base + 7,
                     y_base + 7,
                     2, 2);
  }
}



void wxPaletteManager::DrawDragCursorGraphic(unsigned char row, unsigned char col)
{
  if(IsValidRange(row, col)) {
    int x_base = col*16;
    int y_base = row*16;

    wxPaintDC dc(this);

    dc.SetPen(wxPen(wxColour(255,255,255)));
    dc.SetBrush(wxBrush(wxColour(0,0,0), wxTRANSPARENT));
    dc.DrawRectangle(x_base + 1,
                     y_base + 1,
                     14, 14);
    dc.SetPen(wxPen(wxColour(0,0,0)));
    dc.DrawRectangle(x_base + 2,
                     y_base + 2,
                     12, 12);
    dc.DrawRectangle(x_base,
                     y_base,
                     16, 16);

    dc.DrawRectangle(x_base + 3,
                     y_base + 1,
                     2, 1);
    dc.DrawRectangle(x_base + 7,
                     y_base + 1,
                     2, 1);
    dc.DrawRectangle(x_base + 11,
                     y_base + 1,
                     2, 1);
    dc.DrawRectangle(x_base + 3,
                     y_base + 14,
                     2, 1);
    dc.DrawRectangle(x_base + 7,
                     y_base + 14,
                     2, 1);
    dc.DrawRectangle(x_base + 11,
                     y_base + 14,
                     2, 1);

    dc.DrawRectangle(x_base + 1,
                     y_base + 3,
                     1, 2);
    dc.DrawRectangle(x_base + 1,
                     y_base + 7,
                     1, 2);
    dc.DrawRectangle(x_base + 1,
                     y_base + 11,
                     1, 2);
    dc.DrawRectangle(x_base + 14,
                     y_base + 3,
                     1, 2);
    dc.DrawRectangle(x_base + 14,
                     y_base + 7,
                     1, 2);
    dc.DrawRectangle(x_base + 14,
                     y_base + 11,
                     1, 2);
  }
}



void wxPaletteManager::OnLeftClick(wxMouseEvent& event)
{
  long xpos = 0;
  long ypos = 0;
  event.GetPosition(&xpos, &ypos);

  primary_col = (unsigned char)(xpos/16);
  primary_row = (unsigned char)(ypos/16);
  SetFocusFromKbd();
  SendUpdateEvent(true, false, true, false);
  Refresh();
}



void wxPaletteManager::OnRightClick(wxMouseEvent& event)
{
  long xpos = 0;
  long ypos = 0;
  event.GetPosition(&xpos, &ypos);

  secondary_col = (unsigned char)(xpos/16);
  secondary_row = (unsigned char)(ypos/16);
  SetFocusFromKbd();
  SendUpdateEvent(false, true, false, true);
  Refresh();
}



void wxPaletteManager::OnDrag(wxMouseEvent& event)
{
  if(event.LeftIsDown()) {
    long xpos = 0;
    long ypos = 0;
    event.GetPosition(&xpos, &ypos);

    long temp_col = (xpos/16);
    long temp_row = (ypos/16);
    temp_col > 15 ? temp_col = 15 : temp_col;
    temp_col < 0  ? temp_col = 0  : temp_col;
    temp_row > 15 ? temp_row = 15 : temp_row;
    temp_row < 0  ? temp_row = 0  : temp_row;

    if((temp_col != primary_col || temp_row != primary_row) &&
       (temp_col != 0 || temp_row != 0) &&
       (primary_col != 0 || primary_row != 0)) {
      drag_col = (unsigned char)temp_col;
      drag_row = (unsigned char)temp_row;
    } else {
      InvalidateDrag();
    }
    Refresh();
  } else {
    InvalidateDrag();
  }
}



void wxPaletteManager::OnLeftUp(wxMouseEvent& event)
{
  if(IsDragValid()) {
    SwapColours(primary_row, primary_col, drag_row, drag_col);
    primary_col = drag_col;
    primary_row = drag_row;
    SendUpdateEvent(true, false, false, false);
  }
  InvalidateDrag();
  Refresh();
}



void wxPaletteManager::OnKeyDown(wxKeyEvent& event)
{
  if(event.ControlDown()) {
    switch(event.GetKeyCode()) {
    case WXK_UP:
      if(!BatchMove(primary_row  , primary_col,
                    secondary_row, secondary_col,
                    0, -1)) {
        primary_row--;
        secondary_row--;
        bool pri_change = false;
        bool sec_change = false;
        if(IsColourZero(primary_row  , primary_col  )) pri_change = true;
        if(IsColourZero(secondary_row, secondary_col)) sec_change = true;
        SendUpdateEvent(true, true, pri_change, sec_change);
      }
      break;

    case WXK_DOWN:
      if(!BatchMove(primary_row  , primary_col,
                    secondary_row, secondary_col,
                    0, 1)) {
        bool pri_change = false;
        bool sec_change = false;
        if(IsColourZero(primary_row  , primary_col  )) pri_change = true;
        if(IsColourZero(secondary_row, secondary_col)) sec_change = true;
        primary_row++;
        secondary_row++;
        SendUpdateEvent(true, true, pri_change, sec_change);
      }
      break;

    case WXK_LEFT:
      if(!BatchMove(primary_row  , primary_col,
                    secondary_row, secondary_col,
                    -1, 0)) {
        primary_col--;
        secondary_col--;
        bool pri_change = false;
        bool sec_change = false;
        if(IsColourZero(primary_row  , primary_col  )) pri_change = true;
        if(IsColourZero(secondary_row, secondary_col)) sec_change = true;
        SendUpdateEvent(true, true, pri_change, sec_change);
      }
      break;

    case WXK_RIGHT:
      if(!BatchMove(primary_row  , primary_col,
                    secondary_row, secondary_col,
                    1, 0)) {
        bool pri_change = false;
        bool sec_change = false;
        if(IsColourZero(primary_row  , primary_col  )) pri_change = true;
        if(IsColourZero(secondary_row, secondary_col)) sec_change = true;
        primary_col++;
        secondary_col++;
        SendUpdateEvent(true, true, pri_change, sec_change);
      }
      break;

    default:
      event.Skip(true);
      return;
    }
  } else if(event.ShiftDown()) {
    if(event.AltDown()) {
      switch(event.GetKeyCode()) {
      case WXK_UP:
        if(!SwapColours(secondary_row, secondary_col, secondary_row-1, secondary_col)){
          secondary_row--;
          SendUpdateEvent(false, true, false, false);
        }
        break;

      case WXK_DOWN:
        if(!SwapColours(secondary_row, secondary_col, secondary_row+1, secondary_col)){
          secondary_row++;
          SendUpdateEvent(false, true, false, false);
        }
        break;

      case WXK_LEFT:
        if(!SwapColours(secondary_row, secondary_col, secondary_row, secondary_col-1)){
          secondary_col--;
          SendUpdateEvent(false, true, false, false);
        }
        break;

      case WXK_RIGHT:
        if(!SwapColours(secondary_row, secondary_col, secondary_row, secondary_col+1)){
          secondary_col++;
          SendUpdateEvent(false, true, false, false);
        }
        break;

      default:
        event.Skip(true);
        return;
      }
    } else {
      switch(event.GetKeyCode()) {
      case WXK_UP:
        if(!SwapColours(primary_row, primary_col, primary_row-1, primary_col)){
          primary_row--;
          SendUpdateEvent(true, false, false, false);
        }
        break;

      case WXK_DOWN:
        if(!SwapColours(primary_row, primary_col, primary_row+1, primary_col)){
          primary_row++;
          SendUpdateEvent(true, false, false, false);
        }
        break;

      case WXK_LEFT:
        if(!SwapColours(primary_row, primary_col, primary_row, primary_col-1)){
          primary_col--;
          SendUpdateEvent(true, false, false, false);
        }
        break;

      case WXK_RIGHT:
        if(!SwapColours(primary_row, primary_col, primary_row, primary_col+1)){
          primary_col++;
          SendUpdateEvent(true, false, false, false);
        }
        break;

      default:
        event.Skip(true);
        return;
      }
    }
  } else if(event.AltDown()) {
    switch(event.GetKeyCode()) {
    case WXK_UP:
      if(secondary_row > 0){
        secondary_row--;
        SendUpdateEvent(false, true, false, true);
      }
      break;

    case WXK_DOWN:
      if(secondary_row < 15){
        secondary_row++;
        SendUpdateEvent(false, true, false, true);
      }
      break;

    case WXK_LEFT:
      if(secondary_col > 0){
        secondary_col--;
        SendUpdateEvent(false, true, false, true);
      }
      break;

    case WXK_RIGHT:
      if(secondary_col < 15){
        secondary_col++;
        SendUpdateEvent(false, true, false, true);
      }
      break;
      
    case WXK_F1:
    case WXK_HOME:
      secondary_col = 0;
      secondary_row = 0;
      SendUpdateEvent(false, true, false, true);
      break;

    default:
      event.Skip(true);
      return;
    }
  } else {
    unsigned char temp = 0;
    switch(event.GetKeyCode()) {
    case WXK_UP:
      if(primary_row > 0){
        primary_row--;
        SendUpdateEvent(true, false, true, false);
      }
      break;

    case WXK_DOWN:
      if(primary_row < 15){
        primary_row++;
        SendUpdateEvent(true, false, true, false);
      }
      break;

    case WXK_LEFT:
      if(primary_col > 0){
        primary_col--;
        SendUpdateEvent(true, false, true, false);
      }
      break;

    case WXK_RIGHT:
      if(primary_col < 15){
        primary_col++;
        SendUpdateEvent(true, false, true, false);
      }
      break;

    case WXK_F1:
    case WXK_HOME:
      primary_col = 0;
      primary_row = 0;
      SendUpdateEvent(true, false, true, false);
      break;

    case WXK_F2:
      secondary_col = primary_col;
      secondary_row = primary_row;
      SendUpdateEvent(false, true, false, true);
      break;

    case WXK_F3:
      temp = primary_col;
      primary_col = secondary_col;
      secondary_col = temp;
      temp = primary_row;
      primary_row = secondary_row;
      secondary_row = temp;
      SendUpdateEvent(true, true, true, true);
      break;

    case WXK_F4:
      SwapColours(primary_row, primary_col, secondary_row, secondary_col);
      SendUpdateEvent(false, false, true, true);
      break;

    case WXK_F5:
    case WXK_INSERT:
      SetSync  (primary_row, primary_col, GetSync  (secondary_row, secondary_col));
      SetColour(primary_row, primary_col, GetColour(secondary_row, secondary_col));
      SendUpdateEvent(false, false, true, false);
      break;

    case WXK_F6:
      ToggleSync(primary_row, primary_col);
      SendUpdateEvent(false, false, false, false);
      break;

    case WXK_DELETE:
      SetColour(primary_row, primary_col, wxColour(0,0,0));
      SendUpdateEvent(false, false, true, false);
      break;

    default:
      event.Skip(true);
      return;
    }
  }
  Refresh();
}



bool wxPaletteManager::SetColour(unsigned char row, unsigned char col, wxColour new_colour, bool ignore_sync)
{
  if(IsValidRange(row, col) && !IsColourZero(row, col)) {
    //If no sync is setup or ignored, simply assign the new colour
    if(ignore_sync || !sync[row][col]){
      colours[row][col] = new_colour;
    }
    //If sync is enabled, search and change all synched entries
    else{
      wxColour old_colour(colours[row][col]);
      for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
          if(sync[i][j] && colours[i][j] == old_colour){
            colours[i][j] = new_colour;
          }
        }
      }
    }
    return false;
  }
  return true;
}



bool wxPaletteManager::SetPrimaryColour(wxColour new_colour, bool ignore_sync){
  bool ret = SetColour(primary_row, primary_col, new_colour, ignore_sync);
  //SendUpdateEvent(false, false, true, false);
  return ret;
}



bool wxPaletteManager::SetSecondaryColour(wxColour new_colour, bool ignore_sync){
  bool ret = SetColour(secondary_row, secondary_col, new_colour, ignore_sync);
  //SendUpdateEvent(false, false, false, true);
  return ret;
}



bool wxPaletteManager::SetSync(unsigned char row, unsigned char col, bool sync_state)
{
  if(IsValidRange(row, col) && !IsColourZero(row, col)) {
    sync[row][col] = sync_state;
    return false;
  }
  return true;
}



bool wxPaletteManager::SwapColours(unsigned char row0, unsigned char col0,
                                   unsigned char row1, unsigned char col1)
{
  if(IsValidRange(row0, col0) && IsValidRange(row1, col1) &&
     !IsColourZero(row0, col0) && !IsColourZero(row1, col1)) {
    wxColour swap(colours[row0][col0]);
    colours[row0][col0] = colours[row1][col1];
    colours[row1][col1] = swap;
    bool swap2 = sync[row0][col0];
    sync[row0][col0] = sync[row1][col1];
    sync[row1][col1] = swap2;
    return false;
  }
  return true;
}



bool wxPaletteManager::BatchMove(unsigned char row0, unsigned char col0,
                                 unsigned char row1, unsigned char col1,
                                 char horizontal, char vertical)
{
  if(horizontal != 0 || vertical != 0) {
    //Compute the source box's edges
    int x_left   = col0 <= col1 ? col0 : col1;
    int x_right  = col0 >  col1 ? col0 : col1;
    int y_top    = row0 <= row1 ? row0 : row1;
    int y_bottom = row0 >  row1 ? row0 : row1;

    //Compute the destination box's edges
    int x_left_dest   = x_left   + horizontal;
    int x_right_dest  = x_right  + horizontal;
    int y_top_dest    = y_top    + vertical  ;
    int y_bottom_dest = y_bottom + vertical  ;

    //Test that inputs are valid.
    if(IsValidRange (x_left      , y_top        ) &&
       IsValidRange (x_right     , y_bottom     ) &&
       IsValidRange (x_left_dest , y_top_dest   ) &&
       IsValidRange (x_right_dest, y_bottom_dest)) {
      //Compute the order in which swaps must be made.
      //Important to avoid accidental overwrite of colours.
      int x_start = horizontal <= 0 ? x_left    : x_right     ;
      int x_end   = horizontal >  0 ? x_left -1 : x_right  + 1;
      int y_start = vertical   <= 0 ? y_top     : y_bottom    ;
      int y_end   = vertical   >  0 ? y_top  -1 : y_bottom + 1;
      int x_dest_start = horizontal <= 0 ? x_left_dest : x_right_dest ;
      int y_dest_start = vertical   <= 0 ? y_top_dest  : y_bottom_dest;
      int x_dir = horizontal <= 0 ? 1 : -1;
      int y_dir = vertical   <= 0 ? 1 : -1;

      wxColour swap;
      bool swap2;
      int i = x_start     ;
      int j = x_start     ;
      int k = x_dest_start;
      int m = y_dest_start;
      
      //If the destination box contains the
      //transparent colour entry, it must be preswaped
      //in order to ensure that the batch swap correctly
      //sets colours in their expected positions.
      if(IsColourZero(x_left_dest , y_top_dest)){
        swap = colours[0][0];
        colours[0][0] = colours[y_top][x_left];
        colours[y_top][x_left] = swap;
        swap2 = sync[0][0];
        sync[0][0] = sync[y_top][x_left];
        sync[y_top][x_left] = swap2;
      }

      //Perform the batch move with calculated parameters above.
      for(i = x_start; i != x_end; i += x_dir) {
        m = y_dest_start;
        for(j = y_start; j != y_end; j += y_dir) {
          swap = colours[j][i];
          colours[j][i] = colours[m][k];
          colours[m][k] = swap;
          swap2 = sync[j][i];
          sync[j][i] = sync[m][k];
          sync[m][k] = swap2;
          m += y_dir;
        }
        k += x_dir;
      }
      
      //If the source box contained the
      //transparent colour entry, it needs to be reswaped
      //into its proper position.
      if(IsColourZero(x_left, y_top)) {
        swap = colours[0][0];
        colours[0][0] = colours[y_top_dest][x_left_dest];
        colours[y_top_dest][x_left_dest] = swap;
        swap2 = sync[0][0];
        sync[0][0] = sync[y_top_dest][x_left_dest];
        sync[y_top_dest][x_left_dest] = swap2;
      }
      return false;
    }
    return true;
  } else {
    return false;
  }
}



void wxPaletteManager::SendUpdateEvent(bool pri_pos_moved, bool sec_pos_moved,
                                       bool pri_colour_changed, bool sec_colour_changed){
  wxPaletteManagerEvent notify(wxEVT_PALETTE_MANAGER_UPDATED);
  notify.SetId(GetId());
  notify.SetState(pri_pos_moved, sec_pos_moved, pri_colour_changed, sec_colour_changed);
  wxPostEvent(GetParent(), notify);
}



void wxPaletteManagerEvent::SetState(bool pri_pos_moved, bool sec_pos_moved, bool pri_colour_changed, bool sec_colour_changed){
  pri_pos_mov   = pri_pos_moved;
  sec_pos_mov   = sec_pos_moved;
  pri_colour_ch = pri_colour_changed;
  sec_colour_ch = sec_colour_changed;
}