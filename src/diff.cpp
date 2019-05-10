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

Result * BinDiff::Compare(bool (*compareParts)(const string &, const string &)) {
    vector<uint8_t> bytesX = _first->GetBinary();
    vector<uint8_t> bytesY = _second->GetBinary();

    vector<uint8_t> ux;
    vector<uint8_t> uy;

    size_t max = bytesX.size() > bytesY.size() ? bytesY.size() : bytesX.size();
    size_t index;
    bool res = true;
    for(index = 0; index < max; index++) {
        if(bytesX[index] != bytesY[index]) {
            ux.push_back(bytesX[index]);
            uy.push_back(bytesY[index]);
            res = false;
        }
    }

    return new BinResult(_first->GetFileName(), _second->GetFileName(), res, ux, uy);
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

Result * TxtDiff::Compare(bool (*compareParts)(const string &, const string &)) {   
    vector<string> linesX = _first->GetText();
    vector<string> linesY = _second->GetText();

    vector<string> uniqX;
    vector<string> uniqY;
    
    bool res = true;

    if(linesX.size() != linesY.size()) return new TxtResult(_first->GetFileName(), _second->GetFileName(), false);
    for(size_t i = 0; i < linesX.size(); i++) {
        if(compareParts != NULL) {
            if(!compareParts(linesX[i], linesY[i])) {
                uniqX.push_back(linesX[i]);
                uniqY.push_back(linesY[i]);
                res = false;
            }
        }
        else {
            if(linesX[i] != linesY[i]) {
                uniqX.push_back(linesX[i]);
                uniqY.push_back(linesY[i]);
                res = false;
            }
        }
    }

    return new TxtResult(_first->GetFileName(), _second->GetFileName(), res, uniqX, uniqY);
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

Result * JsnDiff::Compare(bool (*compareParts)(const string &, const string &)) {
    return new JsnResult(_first->GetFileName(), _second->GetFileName(), false);
}   

ostream & operator<<(ostream & os, const JsnDiff & src) {
    os << "--JSON Diff--" << endl;
    os << "File 1: " << *src._first << endl;
    os << "File 2: " << *src._second;

    return os;
}

// non-member functions implementation
Diff * CreateDiff(const File * a, const File * b, int comparisonType) {
    int typeA = IO::GetFileType(a->GetFullFileName());
    int typeB = IO::GetFileType(b->GetFullFileName());

    if(comparisonType == -1 && typeA != typeB) return NULL;
    comparisonType = comparisonType == -1 ? typeA : comparisonType;

    switch(comparisonType) {
        case 0:
            return new BinDiff(*a, *b);
        case 1:
            return new TxtDiff(*a, *b);
        case 2:
            return new JsnDiff(*a, *b);
        default:
            return NULL;
    }
}