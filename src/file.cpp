#include "file.hpp"

// File
File::File(std::string fileName) : _fileName(fileName), _isLoaded(false) {

}

File::File(const File & src) {
    if(&src == this) return;

    _fileName = src._fileName;
    _isLoaded = src._isLoaded;
}

File::~File() {

}

File * File::Clone() const {
    return new File(*this);
}

size_t File::GetFileSize() const {
    return 0;
}

bool File::Load() {
    return false;
}

std::vector<uint8_t> File::GetBinary() {
    return std::vector<uint8_t>();
}

std::vector<char> File::GetText() {
    return std::vector<char>();
}

std::vector<std::string> File::GetJSON() {
    return std::vector<std::string>();
}

std::ostream & File::Print(std::ostream & os) const {
    os << _fileName;
    return os;
}

std::ostream & operator<<(std::ostream & os, const File & src) {
    return src.Print(os);
}

// BinFile
BinFile::BinFile(std::string fileName) : File(fileName) {

}

BinFile::BinFile(const BinFile & src) : File(src) {
    if(&src == this) return;

    _bytes = src._bytes;
}

BinFile::~BinFile() {

}

BinFile * BinFile::Clone() const {
    return new BinFile(*this);
}

size_t BinFile::GetFileSize() const {
    return _bytes.size();
}

bool BinFile::Load() {
    if(_isLoaded == false) return true;
    
    std::ifstream f(_fileName);
    if(!f.is_open() || f.bad()) return false;

    uint8_t byte;
    while(f.peek() != EOF) {
        f.read((char *)&byte, sizeof(byte));
        _bytes.push_back(byte);
    }

    f.close();
    if(f.is_open() || f.bad()) return false;

    return _isLoaded = true;   
}

std::vector<uint8_t> BinFile::GetBinary() {
    if(!_isLoaded) Load();   
    return _bytes;
}

std::vector<char> BinFile::GetText() {
    if(!_isLoaded) Load();   
    std::vector<char> chars;
    for(size_t i = 0; i < _bytes.size(); i++) chars.push_back((char)_bytes[i]);
    return chars;
}

std::vector<std::string> BinFile::GetJSON() {
    return std::vector<std::string>();
}

std::ostream & BinFile::Print(std::ostream & os) const {
    os << "[bin] " << _fileName;
    if(_isLoaded) os << " (size: " << GetFileSize() << ")";
    return os;
}

std::ostream & operator<<(std::ostream & os, const BinFile & src) {
    return src.Print(os);
}

// TxtFile
TxtFile::TxtFile(std::string fileName) : File(fileName) {

}

TxtFile::TxtFile(const TxtFile & src) : File(src) {
    if(&src == this) return;

    _chars = src._chars;
}

TxtFile::~TxtFile() {

}

TxtFile * TxtFile::Clone() const {
    return new TxtFile(*this);
}

size_t TxtFile::GetFileSize() const {
    return _chars.size();
}

bool TxtFile::Load() {
    std::ifstream f(_fileName);
    if(!f.is_open() || f.bad()) return false;

    char byte;
    while(f.peek() != EOF) {
        f.read((char *)&byte, sizeof(byte));
        _chars.push_back(byte);
    }

    f.close();
    if(f.is_open() || f.bad()) return false;

    return _isLoaded = true; 
}

std::vector<uint8_t> TxtFile::GetBinary() {
    if(!_isLoaded) Load();   
    std::vector<uint8_t> bytes;
    for(size_t i = 0; i < _chars.size(); i++) bytes.push_back((uint8_t)_chars[i]);
    return bytes;
}

std::vector<char> TxtFile::GetText() {
    if(!_isLoaded) Load();   
    return _chars;
}

std::vector<std::string> TxtFile::GetJSON() {
    return std::vector<std::string>();
}

std::ostream & TxtFile::Print(std::ostream & os) const {
    os << "[txt] " << _fileName;
    if(_isLoaded) os << " (size: " << GetFileSize() << ")";
    return os;
}

std::ostream & operator<<(std::ostream & os, const TxtFile & src) {
    return src.Print(os);
}

// JsnFile
JsnFile::JsnFile(std::string fileName) : File(fileName) {

}

JsnFile::JsnFile(const JsnFile & src) : File(src) {
    if(&src == this) return;

    _nodes = src._nodes;
}

JsnFile::~JsnFile() {

}

JsnFile * JsnFile::Clone() const {
    return new JsnFile(*this);
}

size_t JsnFile::GetFileSize() const {
    return _nodes.size();
}

bool JsnFile::Load() {
    return false;
}

std::vector<uint8_t> JsnFile::GetBinary() {
    if(!_isLoaded) Load();  
    return std::vector<uint8_t>();
}

std::vector<char> JsnFile::GetText() {
    if(!_isLoaded) Load();  
    return std::vector<char>();
}

std::vector<std::string> JsnFile::GetJSON() {
    if(!_isLoaded) Load();  
    return _nodes;
}

std::ostream & JsnFile::Print(std::ostream & os) const {
    os << "[json] " << _fileName;
    if(_isLoaded) os << " (size: " << GetFileSize() << ")";
    return os;
}

std::ostream & operator<<(std::ostream & os, const JsnFile & src) {
    return src.Print(os);
}