#pragma once

#include "json.hpp"

#include <vector>
#include <sstream>
#include <bitset>

/*
 * General Result
 */ 
class Result {
    public:
        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] result: comparation result
         */ 
        Result(const std::string & fileX, const std::string & fileY, bool result);

        /*
         * Copy Constructor
         * @param[in] src: source instance of Result
         */ 
        Result(const Result & src);

        /*
         * Destructor
         */ 
        virtual ~Result();

        /* 
         * Clone method - creates new instance of Result 
         * @return pointer to the new instance
         */ 
        virtual Result * Clone() const;

        /*
         * Getter for comparation result
         */ 
        bool GetResult() const;

        /*
         * Getter for unique bytes in the first file
         * @return vector of unique bytes in the first file 
         */ 
        virtual std::vector<uint8_t> GetUniqueXBytes() const;
        
        /*
         * Getter for unique lines in the first file
         * @return vector of lines bytes in the first file 
         */ 
        virtual std::vector<std::string> GetUniqueXLines() const;

        /*
         * Getter for unique nodes in the first file
         * @return vector of nodes bytes in the first file 
         */ 
        virtual std::vector<int> GetUniqueXNodes() const;

        /*
         * Getter for unique bytes in the second file
         * @return vector of unique bytes in the second file 
         */ 
        virtual std::vector<uint8_t> GetUniqueYBytes() const;

        /*
         * Getter for unique lines in the second file
         * @return vector of lines bytes in the second file 
         */ 
        virtual std::vector<std::string> GetUniqueYLines() const;

        /*
         * Getter for unique nodes in the second file
         * @return vector of nodes bytes in the second file 
         */ 
        virtual std::vector<int> GetUniqueYNodes() const;

        /*
         * Method to print Result info to the ostream
         * @param[in] os: ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

        /*
         * Operator << overload
         * @param[in] os: ostream where will be printed
         * @param[in] src: instance of Result which will be printed
         */ 
        friend std::ostream & operator<<(std::ostream & os, const Result & x);

    protected:
        /*
         * Full string path to the first file
         */ 
        std::string _fileX;

        /*
         * Full string path to the second file
         */ 
        std::string _fileY;

        /*
         * Comparation result
         */ 
        bool _result;
};

typedef std::pair<size_t, uint8_t> NumberedByte;

/*
 * Binary Result
 * @inherit from general Result
 * implements result of binary comparation
 */ 
class BinResult : public Result {
    public:
        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] result: comparation result
         */ 
        BinResult(const std::string & fileX, const std::string & fileY, bool result);
        
        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] bytesX: vector of unique bytes in the first file
         * @param[in] bytesY: vector of unique bytes in the second file
         * @param[in] result: comparation result
         */ 
        BinResult(const std::string & fileX, const std::string & fileY, bool result, std::vector<NumberedByte> bytesX, std::vector<NumberedByte> bytesY);
        
        /*
         * Copy Constructor
         * @param[in] src: source instance of BinResult
         */ 
        BinResult(const BinResult & src);

        /*
         * Destructor
         */ 
        virtual ~BinResult();

        /* 
         * Clone method - creates new instance of BinResult 
         * @return pointer to the new instance
         */ 
        virtual Result * Clone() const;

        /*
         * Method to print BinResult info to the ostream
         * @param[in] os: ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

    private:
        /*
         * Unique bytes in the first file
         */ 
        std::vector<NumberedByte>_bytesX;

        /*
         * Unique nodes in the second file
         */ 
        std::vector<NumberedByte>_bytesY;
};

typedef std::pair<size_t, std::string> NumberedLine;

/*
 * Text Result
 * @inherit from general Result
 * implements result of text comparation
 */ 
class TxtResult : public Result {
    public:
        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] result: comparation result
         */ 
        TxtResult(const std::string & fileX, const std::string & fileY, bool result);

        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] linesX: vector of unique lines in the first file
         * @param[in] linesY: vector of unique lines in the second file
         * @param[in] result: comparation result
         */ 
        TxtResult(const std::string & fileX, const std::string & fileY, bool result, std::vector<NumberedLine> linesX, std::vector<NumberedLine> linesY);
        
        /*
         * Copy Constructor
         * @param[in] src: source instance of TxtResult
         */ 
        TxtResult(const TxtResult & src);

        /*
         * Destructor
         */ 
        virtual ~TxtResult();

        /* 
         * Clone method - creates new instance of TxtResult 
         * @return pointer to the new instance
         */ 
        virtual Result * Clone() const;

        /*
         * Method to print TxtResult info to the ostream
         * @param[in] os: ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

    private:
        /*
         * Unique lines in the first file
         */ 
        std::vector<NumberedLine> _linesX;

        /*
         * Unique lines in the first file
         */ 
        std::vector<NumberedLine> _linesY;
};

/*
 * JSON Result
 * @inherit from general Result
 * implements result of JSON comparation
 */ 
class JsnResult : public Result {
    public:
        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] result: comparation result
         */ 
        JsnResult(const std::string & fileX, const std::string & fileY, bool result);

        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] nodesX: vector of unique nodes in the first file
         * @param[in] nodesY: vector of unique nodes in the second file
         * @param[in] result: comparation result
         */ 
        JsnResult(const std::string & fileX, const std::string & fileY, bool result, CNode * differ);
        
        /*
         * Copy Constructor
         * @param[in] src: source instance of JsnResult
         */ 
        JsnResult(const JsnResult & src);

        /*
         * Destructor
         */ 
        virtual ~JsnResult();

        /* 
         * Clone method - creates new instance of JsnResult 
         * @return pointer to the new instance
         */ 
        virtual Result * Clone() const;

        /*
         * Method to print JsnResult info to the ostream
         * @param[in] os: ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

    private:
        /*
         * Unique nodes in the first file
         */ 
        CNode * _differ;
};

/*
 * File Folder Result
 * @inherit from general Result
 * implements result of searching file in folder and result of its comparation
 */ 
class FileFolderResult : public Result {
    public:
        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] filesCompareResult: pointer to the result of comparation of the file and file in the folder
         */ 
        FileFolderResult(const std::string & fileX, const std::string & fileY, Result * filesCompareResult);
        
        /*
         * Copy Constructor
         * @param[in] src: source instance of FileFolderResult
         */ 
        FileFolderResult(const FileFolderResult & src);

        /*
         * Destructor
         */ 
        virtual ~FileFolderResult();

        /* 
         * Clone method - creates new instance of FileFolderResult 
         * @return pointer to the new instance
         */ 
        virtual Result * Clone() const;

        /*
         * Method to print FileFolderResult info to the ostream
         * @param[in] os: ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;
    
    private:
        /*
         * Result of the comparation (file x folder)
         */ 
        Result * _filesCompareResult;
};

/*
 * Folder Result
 * @inherit from general Result
 * implements result of comparation of two folders
 */ 
class FolderResult : public Result {
    public:
        /*
         * Constructor
         * @param[in] fileX: string path to the first file
         * @param[in] fileY: string path to the second file
         * @param[in] results: results of comparation of the files with the same names 
         * @param[in] uFilesX: files which are unique for the first folder
         * @param[in] uFilesY: files which are unique for the second folder
         */ 
        FolderResult(const std::string & folderX, const std::string & folderY, bool result, std::vector<Result *> results, std::vector<std::string> uFilesX, std::vector<std::string> uFilesY);
        
        /*
         * Copy Constructor
         * @param[in] src: source instance of FolderResult
         */ 
        FolderResult(const FolderResult & src);

        /*
         * Destructor
         */ 
        virtual ~FolderResult();

        /* 
         * Clone method - creates new instance of FolderResult 
         * @return pointer to the new instance
         */ 
        virtual Result * Clone() const;

        /*
         * Method to print FolderResult info to the ostream
         * @param[in] os: ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os, bool verbose = false) const;

    private:
        /*
         * Result of the comparation of the files with the same name
         */ 
        std::vector<Result *> _results;

        /*
         * Unique files in the first folder
         */ 
        std::vector<std::string> _uFilesX;
        
        /*
         * Unique files in the second folder
         */ 
        std::vector<std::string> _uFilesY;
};