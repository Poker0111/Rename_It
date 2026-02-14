#ifndef FILERENAMER_H
#define FILERENAMER_H

#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

bool isAllNumbers(const std::wstring &text);

int getSeasonEpisode(const std::wstring &fileName);
int getSeasonNumber(const std::wstring &fileName);

//int renameRecursive(const fs::path &path, const std::wstring &name,const std::wstring &lang,std::vector<std::pair<fs::path, fs::path>> &names);
void renameFile(const fs::path &path, const fs::path& originalFile, const int seasonNumber, const std::wstring &name,const std::wstring &lang,std::vector<std::pair<fs::path, fs::path>> &names);
void renameFolder(const fs::path &path, const int seasonNumber, const std::wstring &name,const std::wstring &lang,std::vector<std::pair<fs::path, fs::path>> &names);

std::vector<std::pair<fs::path, fs::path>> start(const fs::path &path, const std::wstring &lang);

void UndoAll(std::vector<std::pair<fs::path, fs::path>> &names);
void renameALL(std::vector<std::pair<fs::path, fs::path>> &names);

std::wstring getname(fs::path path);


#endif // FILERENAMER_H