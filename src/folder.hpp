#pragma once

#include "diff.hpp"
#include "io.hpp"

#include <vector>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <algorithm>

class Folder {
    public:
        Folder(std::string folderName = "./");
        Folder(const Folder & src);
        ~Folder();

        std::vector<File *> GetFilesInFolder();

        void CompareFolders(const Folder & f);
        Result * CompareWithFile(const File & f, Diff & diff);
        bool IsInFolder(const std::string & file) const;

    private:
        std::string _folderName;
        std::vector<File *> _files;
};

Folder * CreateFolder(const std::string & filePath);