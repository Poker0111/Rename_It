#include <wx/wx.h>
#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame=new MainFrame("Rename_It");
    mainFrame->SetClientSize(600, 450);
    mainFrame->Center();
    mainFrame-> Show();
    return true;
}

