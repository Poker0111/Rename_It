#include <wx/wx.h>
#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame=new MainFrame("Rename_It_1.0");
    mainFrame->SetClientSize(400, 250);
    mainFrame->Center();
    mainFrame-> Show();
    return true;
}

