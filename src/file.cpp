#include "file.hpp"

File::File(std::string fileName) : _fileName(fileName) {

}

File::File(const File & src) {
    if(&src == this) return;

    _fileName = src._fileName;
}

File::~File() {

}

std::ostream & operator<<(std::ostream & os, const File & src) {
    os << src._fileName;
    return os;
}