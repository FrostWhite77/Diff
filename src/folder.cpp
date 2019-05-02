#include "folder.hpp"

using namespace std;

Folder::Folder(string folderName) : _folderName(folderName), _files() {
    _files = GetFilesInFolder();
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

    if(find(files.begin(), _files.end(), ".") != files.end()) {
        files.erase(find(files.begin(), files.end(), "."));
    }
    if(find(files.begin(), files.end(), "..") != files.end()) {
        files.erase(find(files.begin(), files.end(), ".."));
    }

    return files;
}

bool Folder::IsInFolder(const std::string & file) const {
    return find(_files.begin(), _files.end(), file) != _files.end();
}

void Folder::CompareFolders(const Folder & f, Diff & diff) {
    for(size_t i = 0; i < _files.size(); i++) {
        if(f.IsInFolder(_files[i])) {
            // compare files
            diff.SetFirst(BinFile(_folderName + "/" + _files[i]));
            diff.SetSecond(BinFile(f._folderName + "/" + _files[i]));
            cout << _files[i] << " is in " << _folderName << " and in " << f._folderName << ", are equal: " << boolalpha << diff.Compare().GetResult() << endl;
        }
        else {
            cout << _files[i] << " is in " << _folderName << " but not in " << f._folderName << endl;
        }
    }
}

bool Folder::IsFile(std::string file) const {
    return !IsDir(file);
}

bool Folder::IsDir(std::string file) const {
    return file.size() > 0 && file[file.size() - 1] == '/';
}