#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/tglbtn.h>
#include "PaletteToolbar.h"
#include "wxColourPicker.h"
//#include "wxColourSlider.h"

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

    PaletteToolbar* palette = new PaletteToolbar(this, -1);
    wxColourPicker*  color_chooser = new wxColourPicker(this, -1);

/*    wxColourSlider* text2 = new wxColourSlider(this, -1,  wxT("Test"), wxDefaultPosition, wxSize(100, 16));
    text2->SetColourMode(RGB_R);
    text2->SetRefColour(wxColour(255,128,128));*/

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
    m_mgr.AddPane(color_chooser, tool_pane_info);
    m_mgr.AddPane(palette, tool_pane_info);
    m_mgr.AddPane(tools, tool_pane_info);
    m_mgr.AddPane(tabs, wxCENTER);

    // tell the manager to "commit" all the changes just made
    m_mgr.Update();
  }

  ~MyFrame() {
    // deinitialize the frame manager
    m_mgr.UnInit();
  }

private:
  wxAuiManager m_mgr;
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
