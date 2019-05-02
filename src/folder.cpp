#include "folder.hpp"

using namespace std;

Folder::Folder(string folderName) : _folderName(folderName) {

}

Folder::Folder(const Folder & src) {
    if(&src == this) return;

    _folderName = src._folderName;
}

Folder::~Folder() {

}

vector<string> Folder::GetFilesInFolder() {
    vector<string> files;
    
    DIR * d = opendir(_folderName.c_str());
    struct dirent * dp;

    while ((dp = readdir(d)) != NULL) {
        files.push_back(dp->d_name);
    }
    closedir(d);
    return files;
}

void Folder::CompareFolders(const Folder & f, Diff * diff) {

}

bool Folder::IsFile(std::string file) const {
    return !IsDir(file);
}

bool Folder::IsDir(std::string file) const {
    return file.size() > 0 && file[file.size() - 1] == '/';
}