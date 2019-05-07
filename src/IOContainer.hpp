#pragma once

#include "file.hpp"
#include "folder.hpp"

class IOContainer {
    public:
        IOContainer(File * file, Folder * folder, bool isDir);
        IOContainer(const IOContainer & src);
        ~IOContainer() = default;

        bool IsDir() const;

        File * GetFile() const;
        Folder * GetFolder() const;

    private:
        File * _ptrFile;
        Folder * _ptrFolder;
        bool _isDir;
};