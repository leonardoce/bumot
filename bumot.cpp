#include <wx/wx.h>
#include "bumotstrings.hpp"

/**
 * C e u sip rowe f u rap lin lie bu-mot
 */

class BuMotApp : public wxApp {
public:
  virtual bool OnInit();
};

class BuMotFrame : public wxFrame {
public:
  BuMotFrame(const wxString &title);
};

BuMotFrame::BuMotFrame(const wxString &title) : wxFrame(NULL, -1, title) {
}

bool BuMotApp::OnInit() {
  BuMotFrame *frame = new BuMotFrame(BuMotFrame_Title);
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}

int main(int argc, char **argv) {
}
