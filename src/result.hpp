#pragma once

#include <vector>
#include <sstream>

class Result {
    public: 
        Result(const std::string & fileX, const std::string & fileY, bool result, std::vector<uint8_t> bytesX, std::vector<uint8_t> bytesY);
        Result(const std::string & fileX, const std::string & fileY, bool result, std::vector<char> charsX, std::vector<char> charsY);
        Result(const std::string & fileX, const std::string & fileY, bool result, std::vector<std::string> nodesX, std::vector<std::string> nodesY);
        Result(const Result & src);
        ~Result();

        bool GetResult() const;

        std::vector<uint8_t> GetUniqueXBytes() const;
        std::vector<char> GetUniqueXChars() const;
        std::vector<std::string> GetUniqueXNodes() const;

        std::vector<uint8_t> GetUniqueYBytes() const;
        std::vector<char> GetUniqueYChars() const;
        std::vector<std::string> GetUniqueYNodes() const;

    private:
        std::string _fileX;
        std::vector<uint8_t> _bytesX;
        std::vector<char> _charsX;
        std::vector<std::string> _nodesX;
    
        std::string _fileY;
        std::vector<uint8_t> _bytesY;
        std::vector<char> _charsY;
        std::vector<std::string> _nodesY;

        bool _result;
};