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
    for(size_t i = 0; i < _files.size(); i++) {
        if(_files[i] != NULL) delete _files[i];
    }
}

vector<File *> Folder::GetFilesInFolder() {
    vector<File *> files;
    
    DIR * d = opendir(_folderName.c_str());
    struct dirent * dp;

    while ((dp = readdir(d)) != NULL) {
        /*
        if(string(dp->d_name) == "." || string(dp->d_name) == "..") continue;
        if(Exists(dp->d_name)) {
            switch(GetFileType(string(dp->d_name))) {
                case 0:
                    files.push_back(new BinFile(string(dp->d_name)));
                    break;
                case 1:
                    files.push_back(new TxtFile(string(dp->d_name)));
                    break;
                case 2:
                    files.push_back(new JsnFile(string(dp->d_name)));
                    break;
                default:
                    break;
            }
        }
        */
    }

    closedir(d);
    return files;
}

bool Folder::IsInFolder(const string & file) const {
    return false;
    //return find(_files.begin(), _files.end(), file) != _files.end();
}

void Folder::CompareFolders(const Folder & f) {

}

Result * Folder::CompareWithFile(const File & f, Diff & diff) {
    if(!IsInFolder(f.GetFileName())) return new Result(f.GetFileName(), _folderName, false);
    diff.SetFirst(f);
    return new Result(f.GetFileName(), _folderName + "/" + f.GetFileName(), false);
}

// non-member functions implementation
Folder * CreateFolder(const std::string & filePath) {
    if(!IO::IsDir(filePath)) return NULL;
    return new Folder(filePath);
}