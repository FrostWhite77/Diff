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

Result * BinDiff::Compare(bool (*compareParts)(const string &, const string &)) {
    vector<uint8_t> bytesX = _first->GetBinary();
    vector<uint8_t> bytesY = _second->GetBinary();
    vector<NumberedByte> ux;
    vector<NumberedByte> uy;

    size_t min = bytesX.size() > bytesY.size() ? bytesY.size() : bytesX.size();
    size_t index;
    bool res = true;
    for(index = 0; index < min; index++) {
        if(bytesX[index] != bytesY[index]) {
            ux.push_back(make_pair(index, bytesX[index]));
            uy.push_back(make_pair(index, bytesY[index]));
            res = false;
        }
    }

    for(size_t i = index; i < bytesX.size(); i++) {
        ux.push_back(make_pair(i, bytesX[i]));
        res = false;
    }
    for(size_t i = index; i < bytesY.size(); i++) {
        uy.push_back(make_pair(i, bytesY[i]));
        res = false;
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
    vector<NumberedLine> uniqX;
    vector<NumberedLine> uniqY;

    size_t min = linesX.size() > linesY.size() ? linesY.size() : linesX.size();
    size_t index;
    bool res = true;

    for(index = 0; index < min; index++) {
        if(compareParts != NULL) {
            if(!compareParts(linesX[index], linesY[index])) {
                uniqX.push_back(make_pair(index, linesX[index]));
                uniqY.push_back(make_pair(index, linesY[index]));
                res = false;
            }
        }
        else {
            if(linesX[index] != linesY[index]) {
                uniqX.push_back(make_pair(index, linesX[index]));
                uniqY.push_back(make_pair(index, linesY[index]));
                res = false;
            }
        }
    }

    for(size_t i = index; i < linesX.size(); i++) {
        uniqX.push_back(make_pair(i, linesX[i]));
        res = false;
    }
    for(size_t i = index; i < linesY.size(); i++) {
        uniqY.push_back(make_pair(i, linesY[i]));
        res = false;
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
    cout << "here" << endl;
    
    CNode * root1 = _first->GetJSON();
    CNode * root2 = _second->GetJSON();
    
    if(root1 == NULL) {
        throw JSONFormatErrorException(_first->GetFullFileName());
    }
    if(root2 == NULL) {
        throw JSONFormatErrorException(_second->GetFullFileName());
    }
    
    CNode * differNode = new CNode("Compare"); 

    cout << "ok" << endl;

    bool r = root1->IsSameAs(root2, differNode);
    return new JsnResult(_first->GetFileName(), _second->GetFileName(), r, differNode);
}   

ostream & operator<<(ostream & os, const JsnDiff & src) {
    os << "--JSON Diff--" << endl;
    os << "File 1: " << *src._first << endl;
    os << "File 2: " << *src._second;

    return os;
}

// non-member functions implementation
Diff * CreateDiff(const File * a, const File * b, int comparisonType) {
    if(a == NULL || b == NULL) return NULL;
    
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