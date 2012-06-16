#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include "bumotstrings.hpp"
#include "bumotdb.hpp"
#include <vector>

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
  wxRichTextCtrl *contents;
  wxButton *butFin;
  wxCheckBox *cbFinRap;
  wxCheckBox *cbFinEng;
  wxCheckBox *cbExtended;

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
  SetIcon(wxIcon(wxT("aaaa")));

  wxPanel *kaPanel = new wxPanel(this);
  wxBoxSizer *kaSizer = new wxBoxSizer(wxVERTICAL);

  wxPanel *finPanel = new wxPanel(kaPanel);
  wxBoxSizer *panelSizer = new wxBoxSizer(wxHORIZONTAL);
  
  panelSizer->Add(new wxStaticText(finPanel, -1, Fin_String), 0, 0);
  txtFin = new wxTextCtrl(finPanel, -1, wxT(""));
  panelSizer->Add(txtFin, 1, 0, 0);
  butFin = new wxButton(finPanel, BUTTON_FIN, Fin_Button_String);
  butFin->SetDefault();
  panelSizer->Add(butFin, 0, 0);
  finPanel->SetSizer(panelSizer);
  kaSizer->Add(finPanel, 0, wxEXPAND | wxALL, 5);

  wxPanel *cbPanel = new wxPanel(kaPanel);
  wxBoxSizer *cbPanelSizer = new wxBoxSizer(wxHORIZONTAL);

  cbFinRap = new wxCheckBox(cbPanel, -1, Fin_In_Rap);
  cbFinRap->SetValue(true);
  cbPanelSizer->Add(cbFinRap, 1, wxEXPAND | wxALL, 0);
  cbFinEng = new wxCheckBox(cbPanel, -1, Fin_In_Eng);
  cbFinEng->SetValue(false);
  cbPanelSizer->Add(cbFinEng, 1, wxEXPAND | wxALL, 0);
  cbExtended = new wxCheckBox(cbPanel, -1, Fin_Ext);
  cbExtended->SetValue(false);
  cbPanelSizer->Add(cbExtended, 1, wxEXPAND | wxALL, 0);
  cbPanel->SetSizer(cbPanelSizer);
  kaSizer->Add(cbPanel, 0, wxEXPAND | wxALL, 5);

  contents = new wxRichTextCtrl(kaPanel, -1);
  contents->SetEditable(false);
  kaSizer->Add(contents, 1, wxEXPAND | wxALL, 0);

  kaPanel->SetSizer (kaSizer);  
}

void BuMotFrame::OnFin(wxCommandEvent &evt) {
  if (txtFin->GetValue().Len()==0) {
    wxMessageBox(Message_Fill_Text, BuMotFrame_Title);
    return;
  }

  BuMotFindCriteria criteria;
  criteria.set_search_string(static_cast<const char *>(txtFin->GetValue().char_str()));
  criteria.set_search_in_rap(cbFinRap->GetValue());
  criteria.set_search_in_eng(cbFinEng->GetValue());
  criteria.set_extended_search(cbExtended->GetValue());
  std::vector<BuMotDb::BuMotRecord> result = CurrentDatabase().Find(criteria);

  contents->Clear();
  contents->BeginSuppressUndo();

  contents->BeginParagraphSpacing(0, 10);

  for (std::vector<BuMotDb::BuMotRecord>::iterator it = result.begin();
       it!=result.end(); ++it) {
  
    contents->BeginBold();
    contents->WriteText(wxString(it->get_rapmot().c_str(), wxConvUTF8));
    contents->EndBold();
    contents->WriteText(wxT(": "));
    contents->WriteText(wxString(it->get_engmot().c_str(), wxConvUTF8));
    contents->Newline();
  }

  contents->EndSuppressUndo();
}

bool BuMotApp::OnInit() {
  CurrentDatabase().Init();

  BuMotFrame *frame = new BuMotFrame(BuMotFrame_Title);
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}

IMPLEMENT_APP(BuMotApp)
