#include "tasks.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <fcntl.h>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

bool isAllNumbers(const string &text) {// Check if all characters in the string are digits
	for (const char letter: text) {
		if (!(letter >= '0' && letter <= '9'))
			return false;
	}

	return true;
}

int getSeasonEpisode(const string &fileName) {// Extract episode number from the filename
	string word;

	for (const char letter: fileName) {
		
		if (letter == ' ' || letter == '.' || letter == '-' || letter == '_') {	
			// Handle common separators
			if (word.find("E") != std::string::npos && word.size() > 1) {
				// Check for S0XE0X format (where E is followed by numbers)
				string substr = word.substr(word.size() - 2, word.size() - 1); 
				cout<<word<<endl;
				if (isAllNumbers(substr)) {//chcek for letters
					return stoi(substr);
				}
			}
			word = "";
		} else
			word += letter;
	}

	word.clear(); //clear for next for loop

	// Fallback: check for any 1-2 digit number standalone
	for (const char letter: fileName) {
		if (letter == ' ' || letter == '.' || letter == '-' || letter == '_') {
			cout<<word<<endl;
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

// Extract season number from folder name (similar logic to episode)
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

// Core function to rename a single file
void renameFile(const fs::path &path, const fs::path& originalFile, const int seasonNumber, const wstring &name,const wstring &lang,vector<pair<fs::path, fs::path>> &names) {//rename the file
	int episodeNumber = getSeasonEpisode(originalFile.string()); //get eps number

	// Format numbers to 2 digits (e.g., 1 -> 01)
	std::wstring s_str = (seasonNumber < 10) ? L"0" + std::to_wstring(seasonNumber) : std::to_wstring(seasonNumber);//if eps is less then 10 for S0X if not SXX
	std::wstring e_str = (episodeNumber < 10) ? L"0" + std::to_wstring(episodeNumber) : std::to_wstring(episodeNumber);//same as before
	
	// Construct new filename
	std::wstring newname = name + L" S" + s_str + L"E" + e_str;
	// Add language tag (e.g., .pl, .en) only for subtitle files
	newname += (originalFile.extension().wstring() == L".ass" || originalFile.extension().wstring() == L".srt") ? (L"." + lang) : L"";//add lang extansion (.pl,.en)
	newname+= originalFile.extension().wstring();

	fs::path newpath = path / newname; //create new path
	
	names.push_back({originalFile,newpath});//push back old and new names for undo funcion and check list

	rename(originalFile, newpath);//rename path
}

// Rename all supported files within a specific folder
void renameFolder(const fs::path &path, const int seasonNumber, const wstring &name,const wstring &lang,vector<pair<fs::path, fs::path>> &names) {
	if (!fs::exists(path)) {
		cerr << "Error: Path does not exist! (" << path << ")" << endl;
		return;
	}

	if (!fs::is_directory(path)) {
		cerr << "Error: Provided path is not a folder!" << endl;
		return;
	}

	//loop for all files in folder
	for (const auto &entry: fs::directory_iterator(path)) {
		std::wstring ext = entry.path().extension().wstring();
		if (ext==L".mkv"||ext==L".mp4"||ext==L".srt"||ext==L".ass") {
			renameFile(path, entry.path(), seasonNumber, name,lang,names);
		}
	}
}

// Recursively process the main directory
int renameRecursive(const fs::path &path, const wstring &name,const wstring &lang,vector<pair<fs::path, fs::path>> &names) {//check the main folder 
	if (!fs::exists(path)) {//check
		cout << "Error: Directory not found." << endl;
		return -1;
	}

	if (!fs::is_directory(path)) {//chcek
		cout << "Error: Path is not a directory!" << endl;
		return -1;
	}

	for (const auto &file: fs::directory_iterator(path)) {//search a folder
		if (!fs::is_directory(file)) {
			std::wstring ext = file.path().extension().wstring();

			// Rename files in the root folder (default to Season 1)
			if(ext==L".mkv"||ext==L".mp4"||ext==L".srt"||ext==L".ass")
				renameFile(path, file.path(), 1, name,lang,names);
		} else {
			// Process subfolders as seasons
			const int seasonNumber = getSeasonNumber(fs::path(file.path()).filename().string());
			renameFolder(file.path(), seasonNumber, name,lang,names);
		}
	}

	return 0;
}

// Extract series name from folder name
wstring getname(fs::path path){
	
	wstring nazwa=L"";
	wstring fileName = path.filename().wstring();

	for(const wchar_t &entry:fileName){//removes years in brackets like "(2022)"
		if(entry==L'(')
			break;
		else
			nazwa+=entry;
	}
	return nazwa;
}

// Entry point for the renaming process
void start(const fs::path &path,const wstring &lang,vector<pair<fs::path, fs::path>> &nazwy){
	wstring nazwa=getname(path);
	std::wstring pathStr = path.wstring();
	// Normalize path separators for cross-platform compatibility
    std::replace(pathStr.begin(), pathStr.end(), L'\\', L'/');
	fs::path cleanPath(pathStr);
	renameRecursive(cleanPath,nazwa,lang,nazwy);
}

void UndoAll(std::vector<std::pair<fs::path, fs::path>> &names)//undo all renames
{
	for(const auto [old,news]:names)
		rename(news,old);
}
