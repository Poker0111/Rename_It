#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/config.h>
#include <wx/confbase.h>
#include <wx/fileconf.h>
#include <wx/font.h>
#include <filesystem>
#include "MainFrame.h" 
#include "tasks.h"

namespace menuids{
    const int idbar=100;
    const int lang1=101;
    const int lang2=102;
    const int lang3=103;
}

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr,wxID_ANY,title)
{
#ifdef _WIN32
    SetIcon(wxICON(aaaa));
#endif
#ifdef __linux__
#include "ikona_1.xpm"
    SetIcon(wxIcon(b6babdf68ed54392f858693582d66feecjZN8ofwqdP7YHhE));
#endif
    menubar();//create all controls
    create();
    Font();
    sizer();
    bine();
}
void MainFrame::create(){//create controls
    paneltop=new wxPanel(this);
    paneltop->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

    text1=new wxTextCtrl(paneltop,wxID_ANY,"",wxDefaultPosition,wxSize(300,35),wxTE_PROCESS_ENTER);
    button1=new wxButton(paneltop,wxID_ANY,"",wxDefaultPosition,wxSize(100,50));
    button2=new wxButton(paneltop,wxID_ANY,"",wxDefaultPosition,wxSize(100,50));
    pathtext=new wxStaticText(paneltop,wxID_ANY,"",wxDefaultPosition,wxDefaultSize,wxST_NO_AUTORESIZE | wxALIGN_LEFT);
    
    
    wxConfig *config = new wxConfig("LangConfig");//Read Config with last used language
    config->Read("LastLanguage", &currentLang, 2); 
    delete config;
   
    UpdateLanguage();//add language

}

void MainFrame::sizer()//add sizers
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->AddStretchSpacer(1);
    text1->SetMinSize(wxSize(200, 45));
    mainSizer->Add(text1, 0, wxEXPAND | wxALL, 15);
    mainSizer->AddSpacer(5);

    button1->SetMinSize(wxSize(200, 45));
    button2->SetMinSize(wxSize(200, 45));
    mainSizer->Add(button1, 0, wxEXPAND | wxLEFT | wxRIGHT, 100);
    mainSizer->AddSpacer(5);
    mainSizer->Add(pathtext, 0, wxEXPAND | wxLEFT | wxRIGHT, 100);
    mainSizer->AddSpacer(15);
    mainSizer->Add(button2, 0, wxEXPAND | wxLEFT | wxRIGHT, 100);
    mainSizer->AddSpacer(10);
    mainSizer->AddStretchSpacer(1);

    paneltop->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
    

}

void MainFrame::bine()//bind controls to events
{
    button1->Bind(wxEVT_BUTTON,&MainFrame::file,this);
    button2->Bind(wxEVT_BUTTON,&MainFrame::term,this);
    Bind(wxEVT_MENU, &MainFrame::OnLangChange, this, menuids::lang1);
    Bind(wxEVT_MENU, &MainFrame::OnLangChange, this, menuids::lang2);
    Bind(wxEVT_MENU, &MainFrame::OnLangChange, this, menuids::lang3);
    Bind(wxEVT_MENU, &MainFrame::OnUndo, this, wxID_UNDO);
}

void MainFrame::menubar()//add menu bar with language radio items
{
     menu=new wxMenuBar();

    custom=new wxMenu();
    item_en=custom->AppendRadioItem(menuids::lang3,wxT("English"));
    item_pl = custom->AppendRadioItem(menuids::lang1, "Polski");
    item_jp = custom->AppendRadioItem(menuids::lang2, wxT("日本語"));
    
    Undo=new wxMenu();
    undoItem = Undo->Append(wxID_UNDO, "&Undo\tCtrl+Z");

    item_en->Check(true);// Default to English
    menu->Append(Undo,"Edit");
    menu->Append(custom, "Language");

    SetMenuBar(menu);
}

void MainFrame::Font()//setting Fonts
{
    mainFont=wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Segoe UI");
    text1->SetFont(mainFont);
    button1->SetFont(mainFont);
    button2->SetFont(mainFont);
    pathtext->SetFont(mainFont);

    //Fonts for Japanese charcters
    if (currentLang == 1) {
    jpFont=wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Meiryo");
    text1->SetFont(jpFont);
    pathtext->SetFont(jpFont);
}
}

void MainFrame::file(wxCommandEvent &evt)//open directory dialog to choose folder
{
    wxDirDialog files(this,"Choose folder","",wxDD_DIR_MUST_EXIST);

    if(files.ShowModal()==wxID_CANCEL)
        return;

    filepath =files.GetPath();
    UpdateLanguage();
}

void MainFrame::term(wxCommandEvent &evt)//rename files and show message with info
{
    wxString name = text1->GetValue();

    if(filepath.IsEmpty()) {
       wxString msg, title;
        if(currentLang == 0) { msg = wxT("Najpierw wybierz folder!"); title = wxT("Błąd"); }
        else if(currentLang==1) { msg = wxT("最初にフォルダを選択してください！"); title = wxT("エラー"); }
        else{msg="Please choose a folder first!";title="Error";}
        
        wxMessageBox(msg, title, wxOK | wxICON_ERROR);
        return;
    }
    else{
        std::wstring widePath = filepath.ToStdWstring();
        std::wstring wideName = text1->GetValue().ToStdWstring();
        start(widePath,wideName,Names_files);//Names_files is a vectro<pair<path,path>> for old and new names of files
    }
    wxString info, boxTitle,question;

    if(currentLang == 0) {
        info = wxString::Format(wxT("Skrót języka: %s\nŚcieżka: %s"), name, filepath);
        boxTitle = "Informacja";
        question =wxT("\n\nCzy chcesz otworzyć ten folder?  "); 
        
    }
    else if(currentLang==1) {
        info = wxString::Format(wxT("言語の短縮形: %s  \nフォルダ: %s"), name, filepath);
        boxTitle = "情報";
        question =wxT("\n\nこのフォルダを開きますか？"); 
    }
    else{
        info = wxString::Format(wxT("Language Extension: %s\nFilepath: %s"), name, filepath);
        boxTitle = "Info";
        question =wxT("\n\nDo you want to open this folder?"); 
    }
    
    int answer = wxMessageBox(info + question, boxTitle, wxYES_NO | wxICON_QUESTION, this);

if (answer == wxYES) {
    wxLaunchDefaultApplication(filepath);
}
}

void MainFrame::OnUndo(wxCommandEvent&evt)
{
    if (Names_files.empty()) {//if in vector is empty 
        wxString msg, title;
        if(currentLang == 0) { msg = wxT("Brak zmian do cofnięcia"); title = wxT("Informacja"); }
        else if(currentLang==1) { msg = wxT("元に戻す変更はありません"); title = wxT("情報"); }
        else{msg="No changes to undo";title="Info";}
        wxMessageBox(msg, title, wxOK | wxICON_ERROR);
        return;
    }

    UndoAll(Names_files);//undo all renames
    Names_files.clear();//clear vector and resize it
    Names_files.shrink_to_fit();

    wxString msg1, title1;//message for correct undo
        if(currentLang == 0) { msg1 = wxT("cofnięto nazwy wszytkim plikom"); title1 = wxT("Informacja"); }
        else if(currentLang==1) { msg1 = wxT("すべてのファイル名が元に戻されました"); title1 = wxT("情報"); }
        else{msg1="All file names have been reverted";title1="Info";}
    wxMessageBox(msg1, title1, wxOK);
}

void MainFrame::UpdateLanguage() // Update UI labels based on selected language
{
    if(currentLang==0){
        text1->SetFont(mainFont);
        button1->SetFont(mainFont);
        pathtext->SetFont(mainFont);
        button2->SetFont(mainFont);

       text1->SetHint(wxT("Skrót Języka (np. pl, en)"));
        button1->SetLabel(wxT("Wybierz folder"));
        pathtext->SetLabel(wxT("Ścieszka:"+filepath));
        button2->SetLabel(wxT("Zastosuj"));
        menu->SetMenuLabel(1, wxT("Język"));
        menu->SetMenuLabel(0, wxT("Edytuj"));
        undoItem->SetItemLabel(wxT("Cofnij"));
        item_pl->Check(true);
    }
    else if(currentLang==1){
        wxString textPath = filepath;
        textPath.Replace("\\", "/");

         text1->SetFont(jpFont);
        button1->SetFont(jpFont);
        pathtext->SetFont(jpFont);
        button2->SetFont(jpFont);

        text1->SetHint(wxT("言語の短縮形 (例: jp, en)"));
        button1->SetLabel(wxT("フォルダを選択"));
        pathtext->SetLabel(wxT("フォルダ:"+textPath));
        button2->SetLabel(wxT("適用する"));
        menu->SetMenuLabel(1, wxT("言語"));
        menu->SetMenuLabel(0, wxT("編集"));
        undoItem->SetItemLabel(wxT("元に戻す"));
        item_jp->Check(true);
    }
    else{
        text1->SetFont(mainFont);
        button1->SetFont(mainFont);
        pathtext->SetFont(mainFont);
        button2->SetFont(mainFont);

        text1->SetHint(wxT("Language Extension (ex: en, jp)"));
        button1->SetLabel(wxT("Choose Folder"));
        pathtext->SetLabel(wxT("Path:"+filepath));
        button2->SetLabel(wxT("Apply"));
        menu->SetMenuLabel(1, wxT("Language"));
        menu->SetMenuLabel(0, wxT("Edit"));
        undoItem->SetItemLabel(wxT("Undo"));
        item_en->Check(true);
    }
    paneltop->Layout();
}

void MainFrame::OnLangChange(wxCommandEvent &evt)//funcion when radio in menu bar chenge
{
   int id = evt.GetId();

    if (id == menuids::lang1) {
        currentLang = 0;
    } 
    else if (id == menuids::lang2) {
        currentLang = 1;
    }
    else if (id == menuids::lang3) {
       currentLang=2;
    }

    wxConfig *config = new wxConfig("LangConfig");
    config->Write("LastLanguage", currentLang);
    delete config; 
    UpdateLanguage();
}
