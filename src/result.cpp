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

Result * Result::Clone() const {
    return new Result(*this);
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
    os << "[DIFF] Comparing " << _fileX << " and " << _fileY << endl << "-> Result: " << boolalpha << _result << endl;
    return os;
}

ostream & operator<<(ostream & os, const Result & x) {
    return x.Print(os);
}

// BinResult
BinResult::BinResult(const string & fileX, const string & fileY, bool result) : Result(fileX, fileY, result) {

}

BinResult::BinResult(const string & fileX, const string & fileY, bool result, vector<NumberedByte> bytesX, vector<NumberedByte> bytesY) 
    : Result(fileX, fileY, result), _bytesX(bytesX), _bytesY(bytesY) {

}

BinResult::BinResult(const BinResult & src) : Result(src) {
    if(&src == this) return;

    _bytesX = src._bytesX;
    _bytesY = src._bytesY;
}

BinResult::~BinResult() {

}

Result * BinResult::Clone() const {
    return new BinResult(*this);
}

ostream & BinResult::Print(ostream & os, bool verbose) const {
    Result::Print(os);

    if(verbose && !_result) {
        os << endl << "Unique bytes in " << _fileX << ": " << endl;
        for(size_t i = 0; i < _bytesX.size(); i++) {
            if(i != 0) os << ", ";
            os << "[" << _bytesX[i].first << "]: " <<bitset<8>(_bytesX[i].second);
        }
        
        os << (_bytesX.size() != 0 ? "\n" : "") << endl << "Unique bytes in " << _fileY << ": " << endl;
        for(size_t i = 0; i < _bytesY.size(); i++) {
            if(i != 0) os << ", ";
            os << "[" << _bytesY[i].first << "]: " << bitset<8>(_bytesY[i].second);
        }
    }

    os << endl;
    return os;
}

// TxtResult
TxtResult::TxtResult(const string & fileX, const string & fileY, bool result) : Result(fileX, fileY, result) {

}

TxtResult::TxtResult(const string & fileX, const string & fileY, bool result, vector<NumberedLine> linesX, vector<NumberedLine> linesY) 
    : Result(fileX, fileY, result), _linesX(linesX), _linesY(linesY) {

}

TxtResult::TxtResult(const TxtResult & src) : Result(src) {
    if(&src == this) return;

    _linesX = src._linesX;
    _linesY = src._linesY;
}

TxtResult::~TxtResult() {

}

Result * TxtResult::Clone() const {
    return new TxtResult(*this);
}

ostream & TxtResult::Print(ostream & os, bool verbose) const {
    Result::Print(os);

    if(verbose && !_result) {
        if(_linesX.size() > 0) {
            os << endl << "Unique lines in " << _fileX << ": " << endl;
            for(size_t i = 0; i < _linesX.size(); i++) {
                os << "[" << _linesX[i].first << "]: " << _linesX[i].second << endl;
            }
        }

        if(_linesY.size() > 0) {
            os << endl << "Unique lines in " << _fileY << ": " << endl;
            for(size_t i = 0; i < _linesY.size(); i++) {
                os << "[" << _linesY[i].first << "]: " << _linesY[i].second << endl;
            }
        }
    }
    if(_result) os << endl;
    return os;
}

// JsnResult
JsnResult::JsnResult(const string & fileX, const string & fileY, bool result) : Result(fileX, fileY, result), _differ(NULL) {

}

JsnResult::JsnResult(const string & fileX, const string & fileY, bool result, CNode * differ) : Result(fileX, fileY, result), _differ(differ) {

}

JsnResult::JsnResult(const JsnResult & src) : Result(src) {
    if(&src == this) return;
}

JsnResult::~JsnResult() {
    if(_differ != NULL) delete _differ;
}


Result * JsnResult::Clone() const {
    return new JsnResult(*this);
}

ostream & JsnResult::Print(ostream & os, bool verbose) const {
    Result::Print(os);

    if(verbose && !_result) {
        os << endl;
        _differ->Print(os, 0, true);
    }

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

Result * FileFolderResult::Clone() const {
    return new FileFolderResult(*this);
}

ostream & FileFolderResult::Print(std::ostream & os, bool verbose) const {
    os << "File " << _fileY << (_filesCompareResult == NULL ? " wasn't " : " was ") << "found in the folder " << _fileX;

    if(_filesCompareResult != NULL) {
        os << endl;
        _filesCompareResult->Print(os, verbose);
    }
    return os;
}

// FolderResult
FolderResult::FolderResult(const string & folderX, const string & folderY, bool result, vector<Result *> results, vector<string> uFilesX, vector<string> uFilesY) : Result(folderX, folderY, result), _results(results), _uFilesX(uFilesX), _uFilesY(uFilesY) {

}

FolderResult::FolderResult(const FolderResult & src) : Result(src) {
    if(&src == this) return;

    _uFilesX = src._uFilesX;
    _uFilesY = src._uFilesY;

    for(size_t i = 0; i < _results.size(); i++) {
        delete _results[i];
    }
    for(size_t i = 0; i < src._results.size(); i++) {
        _results.push_back(src._results[i]->Clone());
    }
}

FolderResult::~FolderResult() {
    for(size_t i = 0; i < _results.size(); i++) {
        delete _results[i];
    }
}

Result * FolderResult::Clone() const {
    return new FolderResult(*this);
}

ostream & FolderResult::Print(std::ostream & os, bool verbose) const {
    os << "Folder " << _fileX << " and folder " << _fileY << " are" << (_result ? "" : " not") << " same." << endl;
    
    if(!_result && verbose) {
        if(_uFilesX.size() > 0) {
            os << endl << "Unique files in " << _fileX << ": ";
            for(size_t i = 0; i < _uFilesX.size(); i++) {
                if(i == 0) os << _uFilesX[i];
                else os << ", " << _uFilesX[i];
            }
            os << endl;
        }
        if(_uFilesY.size() > 0) {
            os << endl << "Unique files in " << _fileY << ": ";
            for(size_t i = 0; i < _uFilesY.size(); i++) {
                if(i == 0) os << _uFilesY[i];
                else os << ", " << _uFilesY[i];
            }
            os << endl;
        }

        if(_results.size() > 0) {
            os << endl << "Files in both folders: " << endl;
            for(size_t i = 0; i < _results.size(); i++) {
                _results[i]->Print(os, true);
            }
        }
    }

    return os;
}