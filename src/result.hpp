#pragma once

#include <vector>
#include <sstream>

template <class T>
class Result {
    public: 
        Result(const std::string & fileX, const std::string & fileY, bool result) : _fileX(fileX), _uniqueX(), _fileY(fileY), _uniqueY(), _result(result) {

        }

        Result(const Result & src) {
            if(&src == this) return;

            _result = src._result;

            _fileX = src._fileX;
            _uniqueX = src._uniqueX;

            _fileY = src._fileY;
            _uniqueY = src._uniqueY;
        }

        ~Result() {

        }

        bool GetResult() const {
            return _result;
        }

        std::vector<T> GetDifferX() const {
            return _uniqueX;
        }

        std::vector<T> GetDifferY() const {
            return _uniqueY;
        }   
    
    private:
        std::string _fileX;
        std::vector<T> _uniqueX;
    
        std::string _fileY;
        std::vector<T> _uniqueY;

        bool _result;
};