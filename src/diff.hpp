#pragma once

#include "file.hpp"
#include "result.hpp"
#include "io.hpp"

#include <sstream>
#include <iostream>

/**
 * General Diff
 */ 
class Diff {
    public:
        /**
         * Constructor
         * @param firstFile file to compare
         * @param secondFile file to compare
         * @param settings pointer to Settings 
         */
        Diff(const File & firstFile, const File & secondFile);
        
        /**
         * Copy Constructor
         * @param src source instance of Diff
         */ 
        Diff(const Diff & src);

        /**
         * Destructor
         */
        virtual ~Diff();
        
        /**
         * Function to set first file, which will be compared with another one
         * @param file file
         */
        void SetFirst(const File & file);
        
        /**
         * Function to set second file, which will be compared with another one
         * @param file file
         */
        void SetSecond(const File & file);

        /**
         * Compares two files (set before)
         * @param compareParts pointer to function (takes two strings, returns bool), which will be used during comparation
         * @return pointer Result instance with comparation results
         */
        virtual Result * Compare(bool (*compareParts)(const std::string &, const std::string &) = NULL) = 0;

        /**
         * Operator = overload
         * @param src source instance of Diff
         */ 
        Diff & operator=(const Diff & src);

        /**
         * Operator << overload 
         * @param os ostream, where will be printed
         * @param src instance of Diff to be printed
         */
        friend std::ostream & operator<<(std::ostream & os, const Diff & src);

    protected:
        /**
         * File pointer to first file
         */ 
        File * _first;
        
        /**
         * File pointer to second file
         */ 
        File * _second;
};

/*
 * BinDiff
 * @inherit from general Diff
 * implements binary comparison
 */ 
class BinDiff : public Diff {
    public:
        /*
         * Constructor
         * @param firstFile file to compare
         * @param secondFile file to compare
         */
        BinDiff(const File & firstFile, const File & secondFile);
        
        /*
         * Copy Constructor
         * @param src source instance of BinDiff
         */
        BinDiff(const BinDiff & src);

        /*
         * Destructor
         */
        virtual ~BinDiff();
        
        /*
         * Compares two files (set before) byte by byte, stores unique bytes in both files into Result
         * @param compareParts pointer to function (takes two strings, returns bool), which will be used during comparation
         * @return pointer Result instance with comparation results
         */
        virtual Result * Compare(bool (*compareParts)(const std::string &, const std::string &) = NULL) override;

        /*
         * Operator << overload 
         * @param os ostream, where will be printed
         * @param src instance of BinDiff to be printed
         */
        friend std::ostream & operator<<(std::ostream & os, const BinDiff & src);
};

/*
 * TxtDiff
 * @inherit from general Diff
 * implements text comparison
 */ 
class TxtDiff : public Diff {
    public:
        /*
         * Constructor
         * @param firstFile file to compare
         * @param secondFile file to compare
         */
        TxtDiff(const File & firstFile, const File & secondFile);

        /*
         * Copy Constructor
         * @param src source instance of TxtDiff
         */
        TxtDiff(const TxtDiff & src);

        /*
         * Destructor
         */
        virtual ~TxtDiff();
        
        /*
         * Compares two files (set before) line by line, stores unique lines in both files into Result
         * @param compareParts: pointer to function (takes two strings, returns bool), which will be used during comparation
         * @return pointer Result instance with comparation results
         */
        virtual Result * Compare(bool (*compareParts)(const std::string &, const std::string &) = NULL) override;

        /*
         * Operator << overload 
         * @param os ostream, where will be printed
         * @param src instance of TxtDiff to be printed
         */
        friend std::ostream & operator<<(std::ostream & os, const TxtDiff & src);
};

/*
 * JsnDiff
 * @inherit from general Diff
 * implements text comparison
 */
class JsnDiff : public Diff {
    public:
        /*
         * Constructor
         * @param firstFile file to compare
         * @param secondFile file to compare
         */
        JsnDiff(const File & firstFile, const File & secondFile);

        /*
         * Copy Constructor
         * @param src: source instance of JsnDiff
         */
        JsnDiff(const JsnDiff & src);

        /*
         * Destructor
         */
        virtual ~JsnDiff();
        
        /*
         * Compares two files (set before) node by node, stores unique node in both files into Result
         * @param compareParts: pointer to function (takes two strings, returns bool), which will be used during comparation
         * @return pointer Result instance with comparation results
         */
        virtual Result * Compare(bool (*compareParts)(const std::string &, const std::string &) = NULL) override;

        /*
         * Operator << overload 
         * @param os ostream, where will be printed
         * @param src instance of JsnDiff to be printed
         */
        friend std::ostream & operator<<(std::ostream & os, const JsnDiff & src);
};

/*
 * Function, which takes pointers to two files and by default (by their extensions) creates a diff (bin, txt, jsn)
 * @param a pointer to first file
 * @param b pointer to second file
 * @param comparisonType: int by which can be overriden creating diff (default -1 stands for create by extensions)
 * @return pointer to specific diff instance 
 */ 
Diff * CreateDiff(const File * a, const File * b, int comparisonType = -1);
