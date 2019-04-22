#include "diff.hpp"

Diff::Diff() : _fileToSwap(0), _fileX(NULL), _fileY(NULL) {

}

Diff::Diff(const File & x, const File & y) : _fileToSwap(0), _fileX(x.Clone()), _fileY(y.Clone()) {

}

Diff::Diff(const File * x, const File * y) : _fileToSwap(0), _fileX(x->Clone()), _fileY(y->Clone()) {

}

Diff::Diff(const Diff & src) {
    if(&src == this) return;
    Set(src);
}

Diff::~Diff() {
    if(_fileX != NULL) delete _fileX;
    if(_fileY != NULL) delete _fileY;
}

Diff * Diff::Clone() const {
    return new Diff(*this);
}

void Diff::Set(const Diff & src) {
    if(_fileX != NULL) delete _fileX;
    if(_fileY != NULL) delete _fileY;
    
    _fileX = src._fileX->Clone();
    _fileY = src._fileY->Clone();

    _fileToSwap = src._fileToSwap;
}

Result Diff::Compare() {
    if(_fileX == NULL || _fileY == NULL) throw "Files to compare have not been specified.";
    
    _fileX->LoadFileData();
    _fileY->LoadFileData();

    return Result(_fileX->CompareWith(_fileY));
}

std::ostream & Diff::Print(std::ostream & os) const {
    os << "--Diff Comparator--" << std::endl;

    _fileX->LoadFileData();
    _fileY->LoadFileData();

    _fileX->PrintFileInfo(os);
    os << std::endl;
    _fileX->PrintFileContent(os);
    os << std::endl;

    _fileY->PrintFileInfo(os);
    os << std::endl;
    _fileY->PrintFileContent(os);
    os << std::endl;

    return os;
}

std::ostream & Diff::GetFileXInfo(std::ostream & os) const {
    return _fileX->PrintFileInfo(os);
}

std::ostream & Diff::GetFileYInfo(std::ostream & os) const {
    return _fileY->PrintFileInfo(os);
}

std::ostream & operator<<(std::ostream & os, const Diff & diff) {
    return diff.Print(os);
}

Diff & Diff::operator=(const Diff & src) {
    if(&src == this) return *this;
    Set(src);

    return *this;
}