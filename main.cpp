#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/tglbtn.h>
#include "PaletteToolbar.h"
#include "wxColourPicker.h"
#include "wxPaletteManager.h"

const int id_colour_picker = 1;
const int id_palette = 1;

// application class
class MyFrame : public wxFrame
{
public:
  MyFrame(wxWindow* parent) : wxFrame(parent, -1, _("Sprite Warrior"),
                                        wxDefaultPosition, wxSize(900,800),
                                        wxDEFAULT_FRAME_STYLE) {
    // notify wxAUI which frame to use
    m_mgr.SetManagedWindow(this);

    // create several text controls
    wxPanel* tools = new wxPanel(this, -1,
                                 wxDefaultPosition, wxSize(128,128));

    palette = new PaletteToolbar(this, id_palette);
    colour_picker = new wxColourPicker(this, id_colour_picker);
    colour_picker->setColour(palette->GetPrimaryColour());

    wxAuiNotebook* tabs = new wxAuiNotebook(this, -1);
    
    wxFlexGridSizer* tool_grid_sizer = new wxFlexGridSizer(4, 0, 0);
    tools->SetSizer(tool_grid_sizer);
    wxToggleButton* btn_pencil = new wxToggleButton(tools, -1, wxEmptyString, wxDefaultPosition, wxSize(32, 32));
    wxToggleButton* btn_fill   = new wxToggleButton(tools, -1, wxEmptyString, wxDefaultPosition, wxSize(32, 32));
    wxToggleButton* btn_brush  = new wxToggleButton(tools, -1, wxEmptyString, wxDefaultPosition, wxSize(32, 32));
    wxToggleButton* btn_rect   = new wxToggleButton(tools, -1, wxEmptyString, wxDefaultPosition, wxSize(32, 32));
    wxToggleButton* btn_line   = new wxToggleButton(tools, -1, wxEmptyString, wxDefaultPosition, wxSize(32, 32));
    wxToggleButton* btn_elipse = new wxToggleButton(tools, -1, wxEmptyString, wxDefaultPosition, wxSize(32, 32));
    tool_grid_sizer->Add(btn_pencil);
    tool_grid_sizer->Add(btn_fill);
    tool_grid_sizer->Add(btn_brush);
    tool_grid_sizer->Add(btn_rect);
    tool_grid_sizer->Add(btn_line);
    tool_grid_sizer->Add(btn_elipse);

    wxAuiPaneInfo tool_pane_info;
    //tool_pane_info.ToolbarPane();
    //tool_pane_info.GripperTop(true);
    tool_pane_info.Right();
    tool_pane_info.Caption(wxT("Palette"));
    tool_pane_info.CloseButton(false);
    tool_pane_info.Resizable(false);
    //tool_pane_info.BottomDockable(false);
    //tool_pane_info.TopDockable(false);

    // add the panes to the manager
    m_mgr.AddPane(colour_picker, tool_pane_info);
    m_mgr.AddPane(palette, tool_pane_info);
    m_mgr.AddPane(tools, tool_pane_info);
    m_mgr.AddPane(tabs, wxCENTER);

    Connect(id_colour_picker, wxEVT_COLOUR_PICKER_UPDATED  , wxColourPickerEventHandler  (MyFrame::OnColorPickerUpdate));
    Connect(id_palette      , wxEVT_PALETTE_MANAGER_UPDATED, wxPaletteManagerEventHandler(MyFrame::OnPaletteManagerUpdate));
    
    // tell the manager to "commit" all the changes just made
    m_mgr.Update();
    
  }

  ~MyFrame() {
    // deinitialize the frame manager
    m_mgr.UnInit();
  }
  
  void OnColorPickerUpdate(wxColourPickerEvent& event){
    palette->SetPrimaryColour(colour_picker->GetColour());
    palette->Refresh();
  }
  
  void OnPaletteManagerUpdate(wxPaletteManagerEvent& event){
    if(event.HasPrimaryColourChanged()){
      colour_picker->setColour(palette->GetPrimaryColour());
      colour_picker->Refresh();
    }
  }

private:
  wxAuiManager m_mgr;
  PaletteToolbar* palette;
  wxColourPicker* colour_picker;
};

// our normal wxApp-derived class, as usual
class MyApp : public wxApp
{
public:

  bool OnInit() {
    SetAppName(wxT("Sprite Warrior"));
    wxFrame* frame = new MyFrame(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
  }
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);
