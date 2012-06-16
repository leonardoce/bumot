#include <wx/wx.h>
#include "bumotstrings.hpp"

/**
 * C e u sip rowe f u rap lin lie bu-mot
 */

class BuMotApp : public wxApp {
public:
  virtual bool OnInit();
};

bool BuMotApp::OnInit() {
  BuMotFrame *frame = new BuMotFrame(BuMotFrame_Title);
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}

int main(int argc, char **argv) {
}
