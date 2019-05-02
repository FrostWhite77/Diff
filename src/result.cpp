#include "result.hpp"

using namespace std;

Result::Result(const string & fileX, const string & fileY, bool result, vector<uint8_t> bytesX, vector<uint8_t> bytesY) : _fileX(fileX), _bytesX(bytesX), _charsX(), _nodesX(), _fileY(fileY), _bytesY(bytesY), _charsY(), _nodesY(), _result(result) {

}

Result::Result(const string & fileX, const string & fileY, bool result, vector<char> charsX, vector<char> charsY) : _fileX(fileX), _bytesX(), _charsX(charsX), _nodesX(), _fileY(fileY), _bytesY(), _charsY(charsY), _nodesY(), _result(result) {

}

Result::Result(const string & fileX, const string & fileY, bool result, vector<string> nodesX, vector<string> nodesY) : _fileX(fileX), _bytesX(), _charsX(), _nodesX(nodesX), _fileY(fileY), _bytesY(), _charsY(), _nodesY(nodesY), _result(result) {

}

Result::Result(const Result & src) {
    if(&src == this) return;
    
    _result = src._result;
    _fileX = src._fileX;
    _fileY = src._fileY;

    _bytesX = src._bytesX;
    _charsX = src._charsX;
    _nodesX = src._nodesX;

    _bytesY = src._bytesY;
    _charsY = src._charsY;
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

vector<char> Result::GetUniqueXChars() const {
    return _charsX;
}

vector<string> Result::GetUniqueXNodes() const {
    return _nodesX;
}

vector<uint8_t> Result::GetUniqueYBytes() const {
    return _bytesY;
}

vector<char> Result::GetUniqueYChars() const {
    return _charsY;
}

vector<string> Result::GetUniqueYNodes() const {
    return _nodesY;
}