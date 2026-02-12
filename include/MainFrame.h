#ifndef MAINFRAME_H
#define MAINFRAMe_H
#include<wx/wx.h>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem; 

#pragma once

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);//konstrukt
private:
    void create();
    void sizer();
    void bine();
    void menubar();
    void Font();

    void file(wxCommandEvent&evt);
    void term(wxCommandEvent&evt);
    void OnUndo(wxCommandEvent&evt);

    void UpdateLanguage();
    void OnLangChange(wxCommandEvent& evt);
    int currentLang = 2;//0=pl 1=jp 2=en

     wxPanel* paneltop;
    wxTextCtrl* text1;
    wxTextCtrl* text2;
    wxButton* button1;
    wxButton* button2;
    wxButton* button3;
    wxString filepath;
    wxStaticText* pathtext;
    wxCheckListBox* checklist;

    wxFont mainFont;
    wxFont jpFont;

    wxMenuBar* menu;

    wxMenu* custom;
    wxMenuItem* item_pl;
    wxMenuItem* item_jp;
    wxMenuItem* item_en;

    wxMenu* Undo;
    wxMenuItem* undoItem;


    std::vector<std::pair<fs::path,fs::path>>Names_files;
    std::vector<std::pair<fs::path,fs::path>>Names_final;
};
#endif