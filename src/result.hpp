#pragma once

#include <vector>
#include <sstream>

class Result {
    public:
        Result(const std::string & fileX, const std::string & fileY, bool result);
        Result(const std::string & fileX, const std::string & fileY, bool result, std::vector<uint8_t> bytesX, std::vector<uint8_t> bytesY);
        Result(const std::string & fileX, const std::string & fileY, bool result, std::vector<std::string> linesX, std::vector<std::string> linesY);
        Result(const std::string & fileX, const std::string & fileY, bool result, std::vector<int> nodesX, std::vector<int> nodesY);
        Result(const Result & src);
        ~Result();

        bool GetResult() const;

        std::vector<uint8_t> GetUniqueXBytes() const;
        std::vector<std::string> GetUniqueXLines() const;
        std::vector<int> GetUniqueXNodes() const;

        std::vector<uint8_t> GetUniqueYBytes() const;
        std::vector<std::string> GetUniqueYLines() const;
        std::vector<int> GetUniqueYNodes() const;

        std::ostream & Print(std::ostream & os, bool verbose = false) const;
        friend std::ostream & operator<<(std::ostream & os, const Result & x);

    private:
        std::string _fileX;
        std::vector<uint8_t> _bytesX;
        std::vector<std::string> _linesX;
        std::vector<int> _nodesX;
    
        std::string _fileY;
        std::vector<uint8_t> _bytesY;
        std::vector<std::string> _linesY;
        std::vector<int> _nodesY;

        bool _result;
};