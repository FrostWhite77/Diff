#include "exception.hpp"

using namespace std;

JSONFormatErrorException::JSONFormatErrorException(const string & file) : _file(file) {

}

JSONFormatErrorException::JSONFormatErrorException(const JSONFormatErrorException & src) {
    if(&src == this) return;

    _file = src._file;
}

JSONFormatErrorException::~JSONFormatErrorException() {

}

ostream & operator<<(ostream & os, const JSONFormatErrorException & src) {
    os << "JSON Format Error in file: " << src._file << "!" << endl;
    return os;
}