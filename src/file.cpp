#include "file.hpp"

using namespace std;

// File
File::File(string fileName) : _isLoaded(false) {
    ParseFileName(fileName);
}

File::File(const File & src) {
    if(&src == this) return;

    _fileName = src._fileName;
    _filePath = src._filePath;
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

string File::GetFileName() const {
    return _fileName;
}

string File::GetFilePath() const {
    return _filePath;
}

string File::GetFullFileName() const {
    return _filePath + "/" + _fileName;
}

vector<uint8_t> File::GetBinary() {
    return vector<uint8_t>();
}

vector<string> File::GetText() {
    return vector<string>();
}

CNode * File::GetJSON() {
    return NULL;
}

ostream & File::Print(ostream & os) const {
    os << _fileName;
    return os;
}

ostream & operator<<(ostream & os, const File & src) {
    return src.Print(os);
}

void File::ParseFileName(std::string arg) {
    size_t lastIndexOfBackSlash = arg.size();
    while(lastIndexOfBackSlash > 0) {
        if(arg[lastIndexOfBackSlash] == '/') break;
        lastIndexOfBackSlash--;
    }
    _filePath = string(arg.substr(0, lastIndexOfBackSlash));
    _fileName = string(arg.substr(lastIndexOfBackSlash + 1, arg.size() - lastIndexOfBackSlash));
}

// BinFile
BinFile::BinFile(string fileName) : File(fileName) {

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
    if(_isLoaded) return true;  

    ifstream f(_filePath + "/" + _fileName);
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

vector<uint8_t> BinFile::GetBinary() {
    if(!_isLoaded) Load();   
    return _bytes;
}

vector<string> BinFile::GetText() {
    if(!_isLoaded) Load();   
    vector<string> lines;

    string s;
    for(size_t i = 0; i < _bytes.size(); i++) {
        char c = (char)_bytes[i];

        if(c == '\n') {
            lines.push_back(s);
            s.clear();
        }
        else {
            s.push_back(c);
        }
    }

    if(s.size() > 0) lines.push_back(s);
    return lines;
}

CNode * BinFile::GetJSON() {
    return NULL;
}

ostream & BinFile::Print(ostream & os) const {
    os << "[bin] " << _fileName;
    if(_isLoaded) os << " (size: " << GetFileSize() << ")";
    return os;
}

ostream & operator<<(ostream & os, const BinFile & src) {
    return src.Print(os);
}

// TxtFile
TxtFile::TxtFile(string fileName) : File(fileName) {

}

TxtFile::TxtFile(const TxtFile & src) : File(src) {
    if(&src == this) return;

    _lines = src._lines;
}

TxtFile::~TxtFile() {

}

TxtFile * TxtFile::Clone() const {
    return new TxtFile(*this);
}

size_t TxtFile::GetFileSize() const {
    return _lines.size();
}

bool TxtFile::Load() {
    ifstream f(_filePath + "/" + _fileName);
    if(!f.is_open() || f.bad()) return false;

    string line;
    while(getline(f, line)) {
        _lines.push_back(line);
    }

    f.close();
    if(f.is_open() || f.bad()) return false;

    return _isLoaded = true; 
}

vector<uint8_t> TxtFile::GetBinary() {
    if(!_isLoaded) Load();   
    vector<uint8_t> bytes;

    for(size_t i = 0; i < _lines.size(); i++) {
        for(size_t j = 0; j < _lines[i].size(); j++) {
            bytes.push_back((uint8_t)_lines[i][j]);
        }
    }

    return bytes;
}

vector<string> TxtFile::GetText() {
    if(!_isLoaded) Load();   
    return _lines;
}

CNode * TxtFile::GetJSON() {
    return NULL;
}

ostream & TxtFile::Print(ostream & os) const {
    os << "[txt] " << _fileName;
    if(_isLoaded) os << " (size: " << GetFileSize() << ")";
    return os;
}

ostream & operator<<(ostream & os, const TxtFile & src) {
    return src.Print(os);
}

// JsnFile
JsnFile::JsnFile(string fileName) : File(fileName), _rootNode(NULL) {

}

JsnFile::JsnFile(const JsnFile & src) : File(src), _rootNode(NULL) {
    if(&src == this) return;

    if(_rootNode != NULL) delete _rootNode;

    if(src._rootNode != NULL)
        _rootNode = src._rootNode->Clone();
    else
        _rootNode = NULL;
}

JsnFile::~JsnFile() {
    if(_rootNode != NULL) delete _rootNode;
}

JsnFile * JsnFile::Clone() const {
    return new JsnFile(*this);
}

size_t JsnFile::GetFileSize() const {
    return 0;
}

bool JsnFile::Load() {
    CNode * root = NULL;
    root = LoadAndParseJSON(_filePath + "/" + _fileName);
    
    if(root == NULL) {
        return false;
    }
    
    _rootNode = root;
    _isLoaded = _rootNode != NULL;
    return _isLoaded;
}

vector<uint8_t> JsnFile::GetBinary() {
    BinFile tmp(_filePath + "/" + _fileName);
    vector<uint8_t> bytes = tmp.GetBinary();

    return bytes;
}

vector<string> JsnFile::GetText() {
    TxtFile tmp(_filePath + "/" + _fileName);
    vector<string> lines = tmp.GetText();

    return lines;
}

CNode * JsnFile::GetJSON() {
    if(!_isLoaded) Load();  
    return _rootNode;
}

ostream & JsnFile::Print(ostream & os) const {
    os << "[json] " << _fileName;
    if(_isLoaded) os << " (size: " << GetFileSize() << ")";
    return os;
}

ostream & operator<<(ostream & os, const JsnFile & src) {
    return src.Print(os);
}

// other
File * CreateFile(const std::string & filePath) {
    if(!IO::IsFile(filePath)) return NULL;
    switch(IO::GetFileType(filePath)) {
        case 0:
            return new BinFile(filePath);
        case 1:
            return new TxtFile(filePath);
        case 2:
            return new JsnFile(filePath);
        default:
            return NULL;
    }
}