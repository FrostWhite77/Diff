#include "diff.hpp"

using namespace std;

// Diff
Diff::Diff(const File & firstFile, const File &secondFile, Settings * settings) : _first(firstFile.Clone()), _second(secondFile.Clone()), _settings(settings) {
    _first->Load();
    _second->Load();
}

Diff::Diff(const Diff & src) {
    if(&src == this) return;

    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;
    if(_settings != NULL) delete _settings;

    _first = src._first->Clone();
    _second = src._second->Clone();
    _settings = src._settings->Clone();
}

Diff::~Diff() {
    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;
    if(_settings != NULL) delete _settings;
}

void Diff::SetFirst(const File & file) {
    if(_first != NULL) delete _first;
    _first = file.Clone();

    _first->Load();
}

void Diff::SetSecond(const File & file) {
    if(_second != NULL) delete _second;
    _second = file.Clone(); 

    _second->Load();
}

Diff & Diff::operator=(const Diff & src) {
    if(&src == this) return *this;

    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;

    _first = src._first->Clone();
    _second = src._second->Clone();

    return *this;
}

ostream & operator<<(ostream & os, const Diff & src) {
    os << "--General Diff--" << endl;
    os << "File 1: " << src._first << endl;
    os << "File 2: " << src._second;

    return os;
}

// Binary Diff
BinDiff::BinDiff(const File & firstFile, const File & secondFile) : Diff(firstFile, secondFile) {

}

BinDiff::BinDiff(const BinDiff & src) : Diff(src)  {
    if(&src == this);
}

BinDiff::~BinDiff() {

}

Result BinDiff::Compare(bool (*compareParts)(char, char)) {
    vector<uint8_t> bytesX = _first->GetBinary();
    vector<uint8_t> bytesY = _second->GetBinary();

    if(bytesX.size() != bytesY.size()) return Result(_first->GetFileName(), _second->GetFileName(), false, vector<uint8_t>(), vector<uint8_t>());
    for(size_t i = 0; i < bytesX.size(); i++) {
        if(bytesX[i] != bytesY[i]) return Result(_first->GetFileName(), _second->GetFileName(), false, vector<uint8_t>(), vector<uint8_t>());
    }

    return Result(_first->GetFileName(), _second->GetFileName(), true, vector<uint8_t>(), vector<uint8_t>());
}   

ostream & operator<<(ostream & os, const BinDiff & src) {
    os << "--Binary Diff--" << endl;
    os << "File 1: " << *src._first << endl;
    os << "File 2: " << *src._second;

    return os;
}

// Txt Diff
TxtDiff::TxtDiff(const File & firstFile, const File & secondFile) : Diff(firstFile, secondFile) {

}

TxtDiff::TxtDiff(const TxtDiff & src) :Diff(src)  {
    if(&src == this);
}

TxtDiff::~TxtDiff() {

}

Result TxtDiff::Compare(bool (*compareParts)(char, char)) {
    vector<string> linesX = _first->GetText();
    vector<string> linesY = _second->GetText();

    vector<string> uniqX;
    vector<string> uniqY;
    
    bool res = true;

    if(linesX.size() != linesY.size()) return Result(_first->GetFileName(), _second->GetFileName(), false, linesX, linesY);
    for(size_t i = 0; i < linesX.size(); i++) {
        if(!CompareLines(linesX[i], linesY[i], compareParts)) {
            uniqX.push_back(linesX[i]);
            uniqY.push_back(linesY[i]);
            res = false;
        }
    }

    return Result(_first->GetFileName(), _second->GetFileName(), res, uniqX, uniqY);
}   

bool TxtDiff::CompareLines(string lline, string rline, bool (*compareParts)(char, char)) {
    if(lline.size() != rline.size()) return false;

    for(size_t i = 0; i < lline.size(); i++) {
        if(compareParts != NULL) {
            if(!compareParts(lline[i], rline[i])) return false;
        }
        else {
            if(lline[i] != rline[i]) return false;
        } 
    }

    return true;
}

ostream & operator<<(ostream & os, const TxtDiff & src) {
    os << "--Txt Diff--" << endl;
    os << "File 1: " << *src._first << endl;
    os << "File 2: " << *src._second;

    return os;
}

// Json Diff
JsnDiff::JsnDiff(const File & firstFile, const File & secondFile) : Diff(firstFile, secondFile)  {

}

JsnDiff::JsnDiff(const JsnDiff & src) : Diff(src) {
    if(&src == this) return;
}

JsnDiff::~JsnDiff() {

}

Result JsnDiff::Compare(bool (*compareParts)(char, char)) {
    return Result(_first->GetFileName(), _second->GetFileName(), false, vector<int>(), vector<int>());
}   

ostream & operator<<(ostream & os, const JsnDiff & src) {
    os << "--JSON Diff--" << endl;
    os << "File 1: " << *src._first << endl;
    os << "File 2: " << *src._second;

    return os;
}