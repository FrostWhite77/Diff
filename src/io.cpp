#include "io.hpp"

using namespace std;

namespace IO {
    bool Exists(const string filePath) {
        return ifstream(filePath).good();
    }

    bool IsFile(const string filePath) {
        struct stat s;
        if(stat(filePath.c_str(), &s) == 0) {
            if(s.st_mode & S_IFREG) return true;
        }
        return false;
    }

    int GetFileType(const string & filePath) {
        if(!IsFile(filePath)) return -1;

        size_t position;
        if((position = filePath.find(".bin")) != string::npos && position + 4 == filePath.size() && Exists(filePath))
            return 0;
        else if((position = filePath.find(".txt")) != string::npos && position + 4 == filePath.size() && Exists(filePath))
            return 1;
        else if((position = filePath.find(".json")) != string::npos && position + 5 == filePath.size() && Exists(filePath))
            return 2;
        else
            return -1;
    }

    bool IsDir(const string filePath) {
        struct stat s;
        if(stat(filePath.c_str(), &s) == 0) {
            if(s.st_mode & S_IFDIR) return true;
        }
        return false;
    }
}