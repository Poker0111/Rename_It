#ifndef FILERENAMER_H
#define FILERENAMER_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool isAllNumbers(const std::wstring &text);

int getSeasonEpisode(const std::wstring &fileName);
int getSeasonNumber(const std::wstring &fileName);
int renameRecursive(const fs::path &path, const std::wstring &name,const std::wstring &lang);

void renameFile(const fs::path &path, const fs::path& originalFile, const int seasonNumber, const std::wstring &name,const std::wstring &lang);
void renameFolder(const fs::path &path, const int seasonNumber, const std::wstring &name,const std::wstring &lang);
void start(const std::filesystem::path &path, const std::wstring &name);

std::wstring getname(fs::path path);


#endif // FILERENAMER_H