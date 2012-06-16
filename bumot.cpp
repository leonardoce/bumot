#include <wx/wx.h>
#include <wx/html/htmlwin.h>
#include "bumotstrings.hpp"

const char * const Fin_String = "Eng/RapMoz: ";
const char * const Fin_Button_String = "Fin!";

/**
 * C e u sip rowe f u rap lin lie bu-mot
 */

class BuMotApp : public wxApp {
public:
  virtual bool OnInit();
};

class BuMotFrame : public wxFrame {
private:
  wxTextCtrl *txtFin;
  wxHtmlWindow *contents;
  wxButton *butFin;
public:
  BuMotFrame(const wxString &title);
};

BuMotFrame::BuMotFrame(const wxString &title) : wxFrame(NULL, -1, title) {
  wxBoxSizer *kaSizer = new wxBoxSizer(wxVERTICAL);

  wxPanel *finPanel = new wxPanel(this);
  wxBoxSizer *panelSizer = new wxBoxSizer(wxHORIZONTAL);
  
  panelSizer->Add(new wxStaticText(finPanel, -1, Fin_String), 0, 0);
  txtFin = new wxTextCtrl(finPanel, -1, "");
  panelSizer->Add(txtFin, 1, 0, 0);
  butFin = new wxButton(finPanel, -1, Fin_Button_String);
  panelSizer->Add(butFin, 0, 0);
  finPanel->SetSizer(panelSizer);

  kaSizer->Add(finPanel, 0, wxEXPAND | wxALL, 0);

  contents = new wxHtmlWindow(this);
  kaSizer->Add(contents, 1, wxEXPAND | wxALL, 0);

  SetSizer (kaSizer);
}

bool BuMotApp::OnInit() {
  BuMotFrame *frame = new BuMotFrame(BuMotFrame_Title);
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}

IMPLEMENT_APP(BuMotApp)
