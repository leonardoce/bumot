#include <wx/wx.h>
#include <wx/html/htmlwin.h>
#include "bumotstrings.hpp"

/**
 * C e u sip rowe f u rap lin lie bu-mot
 */

class BuMotApp : public wxApp {
public:
  virtual bool OnInit();
};

const int BUTTON_FIN = 600;

class BuMotFrame : public wxFrame {
private:
  wxTextCtrl *txtFin;
  wxHtmlWindow *contents;
  wxButton *butFin;

  void OnFin(wxCommandEvent &evt);
public:
  BuMotFrame(const wxString &title);

protected:
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(BuMotFrame, wxFrame)
EVT_BUTTON(BUTTON_FIN, BuMotFrame::OnFin)
END_EVENT_TABLE()

BuMotFrame::BuMotFrame(const wxString &title) : wxFrame(NULL, -1, title) {
  wxBoxSizer *kaSizer = new wxBoxSizer(wxVERTICAL);

  wxPanel *finPanel = new wxPanel(this);
  wxBoxSizer *panelSizer = new wxBoxSizer(wxHORIZONTAL);
  
  panelSizer->Add(new wxStaticText(finPanel, -1, Fin_String), 0, 0);
  txtFin = new wxTextCtrl(finPanel, -1, "");
  panelSizer->Add(txtFin, 1, 0, 0);
  butFin = new wxButton(finPanel, BUTTON_FIN, Fin_Button_String);
  butFin->SetDefault();
  panelSizer->Add(butFin, 0, 0);
  finPanel->SetSizer(panelSizer);

  kaSizer->Add(finPanel, 0, wxEXPAND | wxALL, 0);

  contents = new wxHtmlWindow(this);
  kaSizer->Add(contents, 1, wxEXPAND | wxALL, 0);

  SetSizer (kaSizer);
}

void BuMotFrame::OnFin(wxCommandEvent &evt) {
  if (txtFin->GetValue().Len()==0) {
    wxMessageBox(Message_Fill_Text, BuMotFrame_Title);
    return;
  }
  wxMessageBox("Bau");
}

bool BuMotApp::OnInit() {
  BuMotFrame *frame = new BuMotFrame(BuMotFrame_Title);
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}

IMPLEMENT_APP(BuMotApp)
