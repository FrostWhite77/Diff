#include "file.hpp"

// BinFile
BinFile::BinFile(std::string fileName) : File<uint8_t>(fileName) {
    
}

BinFile::BinFile(const BinFile & src) : File<uint8_t>(src) {
    if(&src == this) return;

    _bytes = src._bytes;
}

BinFile::~BinFile() {

}

BinFile * BinFile::Clone() const {
    return new BinFile(*this);
}

void BinFile::Set(const BinFile & src) {
    _bytes = src._bytes;
}

bool BinFile::LoadFileData() {
    if(_hasBeenLoaded) return true;

    std::ifstream f(_fileName);
    if(!f.is_open() || f.bad()) return false;

    uint8_t byte;
    while(f.peek() != EOF) {
        f.read((char *)&byte, sizeof(byte));
        _bytes.push_back(byte);
    }

    f.close();
    if(f.is_open() || f.bad()) return false;

    _hasBeenLoaded = true;
    return true;
}

Result<uint8_t> BinFile::CompareWith(File * f, bool showDifferences) {
    BinFile * bf = dynamic_cast<BinFile *>(f);
    std::vector<uint8_t> bx, by;

    if(showDifferences && _bytes.size() != bf->_bytes.size()) return Result<uint8_t>(_fileName, bf->_fileName, bx, by);

    size_t x = 0, y = 0;
    while(x < _bytes.size() && y < bf->_bytes.size())
    {
        if(_bytes[x] != bf->_bytes[y])
        {
           bx.push_back(_bytes[x]);
           by.push_back(bf->_bytes[x]);
        }
        
        x++; y++;
    }

    while(x < _bytes.size()) { bx.push_back(_bytes[x]); x++; }
    while(y < bf->_bytes.size()) { by.push_back(bf->_bytes[y]); y++; }
    
    return Result<uint8_t>(_fileName, bf->_fileName, bx, by, bx.size() == 0 && by.size() == 0);
}

std::ostream & BinFile::PrintFileInfo(std::ostream & os) const {
    os << "Binary File: " << _fileName;
    return os;
}

std::ostream & BinFile::PrintFileContent(std::ostream & os) const {
    os << "Content: ";
    if(_hasBeenLoaded) os << _bytes.size() << " bytes";
    else os << "File content has not been loaded yet.";
    return os;
}

std::ostream & operator<<(std::ostream & os, const BinFile & f) {
    f.PrintFileInfo(os);
    f.PrintFileContent(os);
    return os;
}

BinFile & BinFile::operator=(const BinFile & src) {
    if(&src == this) return *this;
    Set(src);
    File<uint8_t>::operator=(src);

    return *this;
}

/*
// TxtFile
TxtFile::TxtFile(std::string fileName) : File<char>(fileName) {

}

TxtFile::TxtFile(const TxtFile & src) : File<char>(src) {
    if(&src == this) return;
    Set(src);
}

TxtFile::~TxtFile() {

}

TxtFile * TxtFile::Clone() const {
    return new TxtFile(*this);
}

void TxtFile::Set(const TxtFile & src) {
    _chars = src._chars;
}

bool TxtFile::LoadFileData() {
    if(_hasBeenLoaded) return true;

    std::ifstream f(_fileName);
    if(!f.is_open() || f.bad()) return false;

    char inChar;
    while(f.peek() != EOF) {
        f.read(&inChar, sizeof(inChar));
        _chars.push_back(inChar);
    }

    f.close();
    if(f.is_open() || f.bad()) return false;

    _hasBeenLoaded = true;
    return true;
}

Result<char> TxtFile::CompareWith(File * f, bool showDifferences) {
    TxtFile * bf = dynamic_cast<TxtFile *>(f);
    std::vector<char> bx, by;

    if(showDifferences && _chars.size() != bf->_chars.size()) return Result<char>(_fileName, bf->_fileName, bx, by);

    size_t x = 0, y = 0;
    while(x < _chars.size() && y < bf->_chars.size())
    {
        if(_chars[x] != bf->_chars[y])
        {
           bx.push_back(_chars[x]);
           by.push_back(bf->_chars[x]);
        }
        
        x++; y++;
    }

    while(x < _chars.size()) { bx.push_back(_chars[x]); x++; }
    while(y < bf->_chars.size()) { by.push_back(bf->_chars[y]); y++; }
    
    return Result<char>(_fileName, bf->_fileName, bx, by, bx.size() == 0 && by.size() == 0);
}

std::ostream & TxtFile::PrintFileInfo(std::ostream & os) const {
    os << "Simple Text File: " << _fileName;
    return os;
}

std::ostream & TxtFile::PrintFileContent(std::ostream & os) const {
    os << "Content: ";
    if(_hasBeenLoaded) os << _chars.size() << " chars";
    else os << "File content has not been loaded yet.";
    return os;
}
 
std::ostream & operator<<(std::ostream & os, const TxtFile & f) {
    f.PrintFileInfo(os);
    f.PrintFileContent(os);
    return os;
}

TxtFile & TxtFile::operator=(const TxtFile & src) {
    if(&src == this) return *this;
    Set(src);
    File<char>::operator=(src);

    return *this;
}
*/