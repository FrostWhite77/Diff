#include "result.hpp"

Result::Result(const std::string & fileNameX, const std::string & fileNameY, const std::vector<uint8_t> & bx, const std::vector<uint8_t> & by, bool comparationResult)
                : _fileNameX(fileNameX), _fileNameY(fileNameY),
                  _comparationResult(comparationResult), _fileXBytes(bx), _fileYBytes(by) {
    
}

Result::Result(const Result & src)
                : _fileNameX(src._fileNameX), _fileNameY(src._fileNameY),
                  _comparationResult(src._comparationResult), _fileXBytes(src._fileXBytes), _fileYBytes(src._fileYBytes) {
    
}

Result::~Result() {

}

Result * Result::Clone() const {
    return new Result(*this);
}

void Result::Set(const Result & src) {
    if(&src == this) return;

    _comparationResult = src._comparationResult;
    _fileXBytes = src._fileXBytes;
    _fileYBytes = src._fileYBytes;
}

bool Result::GetResult() const {
    return _comparationResult;
}

void Result::AddToXBytes(uint8_t byte) {
    _fileXBytes.push_back(byte);
}

void Result::AddToYBytes(uint8_t byte) {
    _fileYBytes.push_back(byte);
}

size_t Result::GetXBytesSize() const {
    return _fileXBytes.size();
}

size_t Result::GetYBytesSize() const {
    return _fileYBytes.size();
}

std::ostream & Result::Print(std::ostream & os) {
    os << "--Diff Result--" << "\n";
    
    os << "Files " << _fileNameX << " and " << _fileNameY << " are" << (_comparationResult ? "" : " not") << " equal." << std::endl;
    if(_comparationResult) return os;

    os << "Bytes in " << _fileNameX << " but not in " << _fileNameY << ": ";
    for(size_t i = 0; i < _fileXBytes.size(); i++) if(i == 0) os << _fileXBytes[i]; else os << ", " << _fileXBytes[i];
    os << std::endl;
    os << "Bytes in " << _fileNameY << " but not in " << _fileNameX << ": ";
    for(size_t i = 0; i < _fileYBytes.size(); i++) if(i == 0) os << _fileYBytes[i]; else os << ", " << _fileYBytes[i];
    os << std::endl;

    return os;
}