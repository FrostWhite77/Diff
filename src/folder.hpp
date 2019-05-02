#include "diff.hpp"

#include <vector>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>

class Folder {
    public:
        Folder(std::string folderName = "./");
        Folder(const Folder & src);
        ~Folder();

        std::vector<std::string> GetFilesInFolder();

        void CompareFolders(const Folder & f, Diff * diff);

    private:
        std::string _folderName;
};