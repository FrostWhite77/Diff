#pragma once

#include <vector>
#include <sstream>

class Result {
    public:
        Result(const std::string & fileX, const std::string & fileY, bool result);
        Result(const Result & src);
        virtual ~Result();

        bool GetResult() const;

        virtual std::vector<uint8_t> GetUniqueXBytes() const;
        virtual std::vector<std::string> GetUniqueXLines() const;
        virtual std::vector<int> GetUniqueXNodes() const;

        virtual std::vector<uint8_t> GetUniqueYBytes() const;
        virtual std::vector<std::string> GetUniqueYLines() const;
        virtual std::vector<int> GetUniqueYNodes() const;

        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;
        friend std::ostream & operator<<(std::ostream & os, const Result & x);

    protected:
        std::string _fileX;
        std::string _fileY;

        bool _result;
};

class BinResult : public Result {
    public:
        BinResult(const std::string & fileX, const std::string & fileY, bool result);
        BinResult(const std::string & fileX, const std::string & fileY, bool result, std::vector<uint8_t> bytesX, std::vector<uint8_t> bytesY);
        BinResult(const BinResult & src);
        virtual ~BinResult();

        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

    private:
        std::vector<uint8_t> _bytesX;
        std::vector<uint8_t> _bytesY;
};

class TxtResult : public Result {
    public:
        TxtResult(const std::string & fileX, const std::string & fileY, bool result);
        TxtResult(const std::string & fileX, const std::string & fileY, bool result, std::vector<std::string> linesX, std::vector<std::string> linesY);
        TxtResult(const TxtResult & src);
        virtual ~TxtResult();

        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

    private:
        std::vector<std::string> _linesX;
        std::vector<std::string> _linesY;
};

class JsnResult : public Result {
    public:
        JsnResult(const std::string & fileX, const std::string & fileY, bool result);
        JsnResult(const std::string & fileX, const std::string & fileY, bool result, std::vector<int> nodesX, std::vector<int> nodesY);
        JsnResult(const JsnResult & src);
        virtual ~JsnResult();

        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

    private:
        std::vector<int> _nodesX;
        std::vector<int> _nodesY;
};

class FileFolderResult : public Result {
    public:
        FileFolderResult(const std::string & fileX, const std::string & fileY, Result * filesCompareResult);
        FileFolderResult(const FileFolderResult & src);
        virtual ~FileFolderResult();

        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;
    
    private:
        Result * _filesCompareResult;
};
