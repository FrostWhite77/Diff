#include "diff.hpp"

using namespace std;

// Diff
Diff::Diff(const File & firstFile, const File &secondFile) : _first(firstFile.Clone()), _second(secondFile.Clone()) {
    _first->Load();
    _second->Load();
}

Diff::Diff(const Diff & src) {
    if(&src == this) return;

    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;

    _first = src._first->Clone();
    _second = src._second->Clone();
}

Diff::~Diff() {
    if(_first != NULL) delete _first; 
    if(_second != NULL) delete _second;
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

Result BinDiff::Compare() {
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

Result TxtDiff::Compare() {
    vector<string> linesX = _first->GetText();
    vector<string> linesY = _second->GetText();

    vector<string> uniqX;
    vector<string> uniqY;
    
    bool res = true;

    if(linesX.size() != linesY.size()) return Result(_first->GetFileName(), _second->GetFileName(), false, linesX, linesY);
    for(size_t i = 0; i < linesX.size(); i++) {
        if(linesX[i] != linesY[i]) {
            uniqX.push_back(linesX[i]);
            uniqY.push_back(linesY[i]);
            res = false;
        }
    }

    return Result(_first->GetFileName(), _second->GetFileName(), res, uniqX, uniqY);
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

Result JsnDiff::Compare() {
    return Result(_first->GetFileName(), _second->GetFileName(), false, vector<int>(), vector<int>());
}   

ostream & operator<<(ostream & os, const JsnDiff & src) {
    os << "--JSON Diff--" << endl;
    os << "File 1: " << *src._first << endl;
    os << "File 2: " << *src._second;

    return os;
}