#include "result.hpp"

using namespace std;

Result::Result(const string & fileX, const string & fileY, bool result, vector<uint8_t> bytesX, vector<uint8_t> bytesY) : _fileX(fileX), _bytesX(bytesX), _linesX(), _nodesX(), _fileY(fileY), _bytesY(bytesY), _linesY(), _nodesY(), _result(result) {

}

Result::Result(const string & fileX, const string & fileY, bool result, vector<string> linesX, vector<string> linesY) : _fileX(fileX), _bytesX(), _linesX(linesX), _nodesX(), _fileY(fileY), _bytesY(), _linesY(linesY), _nodesY(), _result(result) {

}

Result::Result(const string & fileX, const string & fileY, bool result, vector<int> nodesX, vector<int> nodesY) : _fileX(fileX), _bytesX(), _linesX(), _nodesX(nodesX), _fileY(fileY), _bytesY(), _linesY(), _nodesY(nodesY), _result(result) {

}

Result::Result(const Result & src) {
    if(&src == this) return;
    
    _result = src._result;
    _fileX = src._fileX;
    _fileY = src._fileY;

    _bytesX = src._bytesX;
    _linesX = src._linesX;
    _nodesX = src._nodesX;

    _bytesY = src._bytesY;
    _linesY = src._linesY;
    _nodesY = src._nodesY;
}

Result::~Result() {

}

bool Result::GetResult() const {
    return _result;
}   

vector<uint8_t> Result::GetUniqueXBytes() const {
    return _bytesX;
}

vector<string> Result::GetUniqueXLines() const {
    return _linesX;
}

vector<int> Result::GetUniqueXNodes() const {
    return _nodesX;
}

vector<uint8_t> Result::GetUniqueYBytes() const {
    return _bytesY;
}

vector<string> Result::GetUniqueYLines() const {
    return _linesY;
}

vector<int> Result::GetUniqueYNodes() const {
    return _nodesY;
}