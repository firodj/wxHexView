// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/utils.h>
#include <wx/file.h>

#include "wxHexView.h"
#include "DummyDataProvider.h"

///////////////////////////////////////////////////////////////////////////////

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};
wxDECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);

///////////////////////////////////////////////////////////////////////////////

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame() {
        if (data_provider_) delete data_provider_;
    }
  
private:
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxHexDataProvider *data_provider_;

    DECLARE_EVENT_TABLE();
};

///////////////////////////////////////////////////////////////////////////////

bool MyApp::OnInit()
{
     if ( !wxApp::OnInit() )
        return false;

	MyFrame* frame = new MyFrame("wxHexCtrl; Hex Editor Control Application",
        wxDefaultPosition, wxSize(450, 340));
	frame->Show(true);
	return true;
}

///////////////////////////////////////////////////////////////////////////////

static int ID_MenuQuit = wxNewId();
static int ID_MenuAbout = wxNewId();

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_MenuQuit, MyFrame::OnQuit)
    EVT_MENU(ID_MenuAbout, MyFrame::OnAbout)
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////////////

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame((wxFrame*)nullptr, wxID_ANY, title, pos, size),
    data_provider_(nullptr)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(ID_MenuQuit, "&Quit\tAlt-F4", "Quit the application");

    wxMenu* helpMenu = new wxMenu();
    helpMenu->Append(ID_MenuAbout, "&About\tF1", "Show info about this application");

    wxMenuBar* mbar = new wxMenuBar();
    mbar->Append(fileMenu, "&File");
    mbar->Append(helpMenu, "&Help");

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

        DummyDataProvider *dummy_data_provider = new DummyDataProvider();
        data_provider_ = dummy_data_provider;
    wxHexView *hex_view = new wxHexView(this, wxID_ANY);
    hex_view->SetDataProvider(reinterpret_cast<wxHexDataProvider*>(data_provider_));
  
#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText("wxHexCtrl Status Text", 0);
    SetStatusText(wxVERSION_STRING,1);
#endif // wxUSE_STATUSBAR

}

void MyFrame::OnQuit(wxCommandEvent& event)
{
	// true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(wxString::Format
                 (
                    "Welcome to %s!\n"
                    "\n"
                    "This is the minimal wxWidgets sample\n"
                    "running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}