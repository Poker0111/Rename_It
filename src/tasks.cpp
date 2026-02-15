#include "tasks.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <fcntl.h>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

bool isAllNumbers(const string &text) {
    for (const char letter: text) {
        if (!(letter >= '0' && letter <= '9'))
            return false;
    }
    return true;
}

int getSeasonEpisode(const string &fileName) {
    string word;
    for (const char letter: fileName) {
        if (letter == ' ' || letter == '.' || letter == '-' || letter == '_') { 
            if (word.find("E") != std::string::npos && word.size() > 1) {
                string substr = word.substr(word.size() - 2, word.size() - 1); 
                if (isAllNumbers(substr)) {
                    return stoi(substr);
                }
            }
            word = "";
        } else
            word += letter;
    }
    word.clear(); 
    for (const char letter: fileName) {
        if (letter == ' ' || letter == '.' || letter == '-' || letter == '_') {
            if (isAllNumbers(word) && !word.empty() && word.size() <= 2)
                return stoi(word);
            word = "";
        } else
            word += letter;
    }
    if (!word.empty() && isAllNumbers(word) && word.size() <= 2) {
        return stoi(word);
    }
    return -1;
}

int getSeasonNumber(const string &fileName) {
    string word;
    for (const char letter: fileName) {
        if (letter == ' ' || letter == '.' || letter == '-' || letter == '_' || letter == 'S' || letter == 's') {
            if (isAllNumbers(word) && !word.empty() && word.size() <= 2) {
                return stoi(word);
            }
            word = "";
        } else
            word += letter;
    }
    if (isAllNumbers(word) && !word.empty() && word.size() <= 2) {
        return stoi(word);
    }
    return -1;
}

void renameFile(const fs::path &path, const fs::path& originalFile, const int seasonNumber, const wstring &name,const wstring &lang,vector<pair<fs::path, fs::path>> &names) {
    int episodeNumber = getSeasonEpisode(originalFile.string()); 
    std::wstring s_str = (seasonNumber < 10) ? L"0" + std::to_wstring(seasonNumber) : std::to_wstring(seasonNumber);
    std::wstring e_str = (episodeNumber < 10) ? L"0" + std::to_wstring(episodeNumber) : std::to_wstring(episodeNumber);
    std::wstring newname = name + L" S" + s_str + L"E" + e_str;
    
	newname += (originalFile.extension().wstring() == L".ass" || originalFile.extension().wstring() == L".srt") ? (L"." + lang) : L"";
    newname+= originalFile.extension().wstring();
    
	fs::path newpath = path / newname; 
	if(!fs::exists(newpath))
		names.push_back({originalFile,newpath});
    
	
}

void renameFolder(const fs::path &path, const int seasonNumber, const wstring &name,const wstring &lang,vector<pair<fs::path, fs::path>> &names) {
    if (!fs::exists(path)) return;
    if (!fs::is_directory(path)) return;
    for (const auto &entry: fs::directory_iterator(path)) {
        std::wstring ext = entry.path().extension().wstring();
        if (ext==L".mkv"||ext==L".mp4"||ext==L".srt"||ext==L".ass") {
            renameFile(path, entry.path(), seasonNumber, name,lang,names);
        }
    }
}

wstring getname(fs::path path){
    wstring nazwa=L"";
    wstring fileName = path.filename().wstring();
    for(const wchar_t &entry:fileName){
        if(entry==L'(')
            break;
        else
            nazwa+=entry;
    }
    return nazwa;
}

std::vector<std::pair<fs::path, fs::path>> start(const fs::path &path, const std::wstring &lang){
    std::vector<std::pair<fs::path, fs::path>> names;
    wstring nazwa=getname(path);
    std::wstring pathStr = path.wstring();
    std::replace(pathStr.begin(), pathStr.end(), L'\\', L'/');
    fs::path cleanPath(pathStr);
    if (!fs::exists(path) || !fs::is_directory(path)) return names;
    for (const auto &file: fs::directory_iterator(path)) {
        if (!fs::is_directory(file)) {
            std::wstring ext = file.path().extension().wstring();
            if(ext==L".mkv"||ext==L".mp4"||ext==L".srt"||ext==L".ass")
                renameFile(path, file.path(), 1, nazwa,lang,names);
        } else {
            const int seasonNumber = getSeasonNumber(fs::path(file.path()).filename().string());
            renameFolder(file.path(), seasonNumber, nazwa,lang,names);
        }
    }
    return names;
}

void UndoAll(std::vector<std::pair<fs::path, fs::path>> &names) {
    for(const auto [old,news]:names)
        rename(news,old);
}

void renameALL(std::vector<std::pair<fs::path, fs::path>> &names) {
    for(const auto [old,news]:names)
        rename(old,news);
}