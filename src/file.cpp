#include "file.hpp"

// File
File::File(std::string fileName) : _fileName(fileName), _hasBeenLoaded(false) {

}

File::File(const File & src) {
    if(&src == this) return;
    Set(src);
}

File::~File() {

}

File * File::Clone() const {
    return new File(*this);
}

void File::Set(const File & src) {
    _fileName = src._fileName;
}

bool File::IsLoaded() const {
    return _hasBeenLoaded;
}

bool File::LoadFileData() {
    std::cout << "File::LoadFileContent()" << std::endl;
    return true;
}

Result File::CompareWith(File * f, bool showDifferences) {
    Result diffResult(_fileName, f->_fileName, true); 
    std::cout << "compare function called" << std::endl;
    return diffResult;
}

std::ostream & File::PrintFileInfo(std::ostream & os) const {
    os << "Unspecified File: " << _fileName; 
    return os;
}

std::ostream & File::PrintFileContent(std::ostream & os) const {
    os << "Content: " << "WILL BE ADDED LATER";
    return os;
}

std::ostream & operator<<(std::ostream & os, const File & f) {
    f.PrintFileInfo(os) << "\n";
    f.PrintFileContent(os);
    return os;
}

File & File::operator=(const File & src) {
    if(&src == this) return *this;
    Set(src);
    
    return *this;
}

// BinFile
BinFile::BinFile(std::string fileName) : File(fileName) {
    
}

BinFile::BinFile(const BinFile & src) : File(src) {
    if(&src == this) return;

    _bytes = src._bytes;
    _hasBeenLoaded = src._hasBeenLoaded;
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

Result BinFile::CompareWith(File * f, bool showDifferences) {
    BinFile * bf = dynamic_cast<BinFile *>(f);
    
    if(showDifferences && _bytes.size() != bf->_bytes.size()) return Result(_fileName, bf->_fileName);

    Result _result(_fileName, bf->_fileName);
    size_t x = 0, y = 0;

    while(x < _bytes.size() && y < bf->_bytes.size())
    {
        if(_bytes[x] != bf->_bytes[y])
        {
            _result.AddToXBytes(_bytes[x]);
            _result.AddToYBytes(bf->_bytes[x]);
        }
        
        x++; y++;
    }

    while(x < _bytes.size()) { _result.AddToXBytes(_bytes[x]); x++; }
    while(y < bf->_bytes.size()) { _result.AddToYBytes(bf->_bytes[y]); y++; }
    
    _result.SetResult(_result.GetXBytesSize() == 0 && _result.GetYBytesSize() == 0);
    return _result;
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
    File::operator=(src);

    return *this;
}