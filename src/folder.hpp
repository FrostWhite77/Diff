#include "diff.hpp"
#include "ioobject.hpp"

#include <vector>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <algorithm>

class Folder : public IOObject {
    public:
        Folder(std::string folderName = "./");
        Folder(const Folder & src);
        ~Folder();

        std::vector<std::string> GetFilesInFolder();

        void CompareFolders(const Folder & f, Diff & diff);
        Result CompareWithFile(const File & f, Diff & diff);
        bool IsInFolder(const std::string & file) const;

        bool IsFile(std::string file) const;
        bool IsDir(std::string file) const;

    private:
        std::string _folderName;
        std::vector<std::string> _files;
};