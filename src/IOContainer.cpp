#include "IOContainer.hpp"

IOContainer::IOContainer(File * file, Folder * folder, bool isDir) : _ptrFile(file), _ptrFolder(folder), _isDir(isDir) {

}

IOContainer::IOContainer(const IOContainer & src) {
    if(&src == this) return;

    _ptrFile = src._ptrFile;
    _ptrFolder = _ptrFolder;
    _isDir = src._isDir;
}

bool IOContainer::IsDir() const {
    return _isDir;
}

File * IOContainer::GetFile() const {
    return _ptrFile;
}   

Folder * IOContainer::GetFolder() const {
    return _ptrFolder;
}