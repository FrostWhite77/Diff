#include "result.hpp"

using namespace std;

// Result
Result::Result(const string & fileX, const string & fileY, bool result) : _fileX(fileX), _fileY(fileY), _result(result) {

}

Result::Result(const Result & src) {
    if(&src == this) return;
    
    _result = src._result;
    _fileX = src._fileX;
    _fileY = src._fileY;
}

Result::~Result() {

}

bool Result::GetResult() const {
    return _result;
}   

vector<uint8_t> Result::GetUniqueXBytes() const {
    return vector<uint8_t>();
}

vector<string> Result::GetUniqueXLines() const {
    return vector<string>();
}

vector<int> Result::GetUniqueXNodes() const {
    return vector<int>();
}

vector<uint8_t> Result::GetUniqueYBytes() const {
    return vector<uint8_t>();
}

vector<string> Result::GetUniqueYLines() const {
    return vector<string>();
}

vector<int> Result::GetUniqueYNodes() const {
    return vector<int>();
}

ostream & Result::Print(ostream & os, bool verbose) const {
    os << "Comparing " << _fileX << " and " << _fileY << ": result: " << boolalpha << _result;
    return os;
}

ostream & operator<<(ostream & os, const Result & x) {
    return x.Print(os);
}

// BinResult
BinResult::BinResult(const string & fileX, const string & fileY, bool result) : Result(fileX, fileY, result) {

}

BinResult::BinResult(const string & fileX, const string & fileY, bool result, vector<uint8_t> bytesX, vector<uint8_t> bytesY) 
    : Result(fileX, fileY, result), _bytesX(bytesX), _bytesY(bytesY) {

}

BinResult::BinResult(const BinResult & src) : Result(src) {
    if(&src == this) return;

    _bytesX = src._bytesX;
    _bytesY = src._bytesY;
}

BinResult::~BinResult() {

}

ostream & BinResult::Print(ostream & os, bool verbose) const {
    Result::Print(os);

    if(verbose && !_result) {
        os << endl << "Unique bytes in " << _fileX << ": ";
        for(size_t i = 0; i < _bytesX.size(); i++) {
            os << _bytesX[i] << " ";
        }
        
        os << endl << "Unique bytes in " << _fileY << ": ";
        for(size_t i = 0; i < _bytesY.size(); i++) {
            os << _bytesY[i] << " ";
        }
    }

    if(!_result) os << endl;
    return os;
}

// TxtResult
TxtResult::TxtResult(const string & fileX, const string & fileY, bool result) : Result(fileX, fileY, result) {

}

TxtResult::TxtResult(const string & fileX, const string & fileY, bool result, vector<string> linesX, vector<string> linesY) 
    : Result(fileX, fileY, result), _linesX(linesX), _linesY(linesY) {

}

TxtResult::TxtResult(const TxtResult & src) : Result(src) {
    if(&src == this) return;

    _linesX = src._linesX;
    _linesY = src._linesY;
}

TxtResult::~TxtResult() {

}

ostream & TxtResult::Print(ostream & os, bool verbose) const {
    Result::Print(os);

    if(verbose && !_result) {
        os << endl << "Unique lines in " << _fileX << ": " << endl;
        for(size_t i = 0; i < _linesX.size(); i++) {
            os << _linesX[i] << endl;
        }
        
        os << "Unique lines in " << _fileY << ": " << endl;
        for(size_t i = 0; i < _linesY.size(); i++) {
            os << _linesY[i] << endl;
        }
    }
    if(_result) os << endl;
    return os;
}

// JsnResult
JsnResult::JsnResult(const string & fileX, const string & fileY, bool result) : Result(fileX, fileY, result) {

}

JsnResult::JsnResult(const string & fileX, const string & fileY, bool result, vector<int> nodesX, vector<int> nodesY) 
    : Result(fileX, fileY, result), _nodesX(nodesX), _nodesY(nodesY) {

}

JsnResult::JsnResult(const JsnResult & src) : Result(src) {
    if(&src == this) return;

    _nodesX = src._nodesX;
    _nodesY = src._nodesY;
}

JsnResult::~JsnResult() {

}

ostream & JsnResult::Print(ostream & os, bool verbose) const {
    Result::Print(os);

    if(verbose && !_result) {
        os << endl << "Unique nodes in " << _fileX << ": ";
        for(size_t i = 0; i < _nodesX.size(); i++) {
            os << _nodesX[i] << " ";
        }
        
        os << endl << "Unique nodes in " << _fileY << ": ";
        for(size_t i = 0; i < _nodesY.size(); i++) {
            os << _nodesY[i] << " ";
        }
    }

    os << endl;
    return os;
}

// FileFolderResult
FileFolderResult::FileFolderResult(const string & folder, const string & file, Result * filesCompareResult) : Result(folder, file, filesCompareResult != NULL), _filesCompareResult(filesCompareResult) {

}

FileFolderResult::FileFolderResult(const FileFolderResult & src) : Result(src) {
    if(&src == this) return;
}

FileFolderResult::~FileFolderResult() {
    if(_filesCompareResult != NULL) delete _filesCompareResult;
}

ostream & FileFolderResult::Print(std::ostream & os, bool verbose) const {
    os << "File " << _fileY << (_filesCompareResult == NULL ? " wasn't " : " was ") << "found in the folder " << _fileX;

    if(_filesCompareResult != NULL) {
        os << endl;
        _filesCompareResult->Print(os, verbose);
    }
    return os;
}