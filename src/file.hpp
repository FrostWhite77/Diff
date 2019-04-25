#pragma once

#include <sstream>
#include <fstream>
#include <vector>

#include <iostream>

#include "result.hpp"

class AbstractFile {
    public:
        virtual AbstractFile * Clone() const = 0;

        virtual std::ostream & PrintFileInfo(std::ostream & os) const = 0;
        virtual std::ostream & PrintFileContent(std::ostream & os) const = 0; 
};

template<class T = uint8_t>
class File : public AbstractFile {
    public:
        File(std::string fileName);
        File(const File<T> & src);
        virtual ~File();

        virtual File<T> * Clone() const;
        virtual void Set(const File<T> & src);

        bool IsLoaded() const;
        virtual bool LoadFileData();
        
        virtual Result<T> CompareWith(File<T> * f, bool showDifferences = false);

        virtual std::ostream & PrintFileInfo(std::ostream & os) const override;
        virtual std::ostream & PrintFileContent(std::ostream & os) const override;

        friend std::ostream & operator<<(std::ostream & os, const File<T> & f) {
            f.PrintFileInfo(os) << "\n";
            f.PrintFileContent(os);
            return os;
        }

        File<T> & operator=(const File<T> & src);

    protected:
        std::string _fileName;
        bool _hasBeenLoaded;
};

class BinFile : public File<uint8_t> {
    public:
        BinFile(std::string fileName);
        BinFile(const BinFile & src);
        virtual ~BinFile();

        virtual BinFile * Clone() const override;
        virtual void Set(const BinFile & src);

        virtual bool LoadFileData() override;
        virtual Result<uint8_t> CompareWith(File * f, bool showDifferences = false);

        virtual std::ostream & PrintFileInfo(std::ostream & os) const override;
        virtual std::ostream & PrintFileContent(std::ostream & os) const override;

        friend std::ostream & operator<<(std::ostream & os, const BinFile & f);
        BinFile & operator=(const BinFile & src);

    private:
        std::vector<uint8_t> _bytes;
};

/*
class TxtFile : public File<char> {
    public:
        TxtFile(std::string fileName);
        TxtFile(const TxtFile & src);
        virtual ~TxtFile();

        virtual TxtFile * Clone() const override;
        virtual void Set(const TxtFile & src);

        virtual bool LoadFileData() override;
        virtual Result<char> CompareWith(File * f, bool showDifferences = false);

        virtual std::ostream & PrintFileInfo(std::ostream & os) const override;
        virtual std::ostream & PrintFileContent(std::ostream & os) const override;

        friend std::ostream & operator<<(std::ostream & os, const TxtFile & f);
        TxtFile & operator=(const TxtFile & src);

    private:
        std::vector<char> _chars;
};
*/

// File
template<class T>
File<T>::File(std::string fileName) : _fileName(fileName), _hasBeenLoaded(false) {

}

template<class T>
File<T>::File(const File & src) {
    if(&src == this) return;
    Set(src);
}

template<class T>
File<T>::~File() {

}

template<class T>
File<T> * File<T>::Clone() const {
    return new File(*this);
}

template<class T>
void File<T>::Set(const File & src) {
    _fileName = src._fileName;
    _hasBeenLoaded = src._hasBeenLoaded;
}

template<class T>
bool File<T>::IsLoaded() const {
    return _hasBeenLoaded;
}

template<class T>
bool File<T>::LoadFileData() {
    std::cout << "File<T>::LoadFileContent()" << std::endl;
    return true;
}

template<class T>
Result<T> File<T>::CompareWith(File<T> * f, bool showDifferences) {
    std::vector<uint8_t> bx, by;

    std::cout << "compare function called" << std::endl;
    return Result<T>(_fileName, f->_fileName, bx, by, false);
}

template<class T>
std::ostream & File<T>::PrintFileInfo(std::ostream & os) const {
    os << "Unspecified File: " << _fileName; 
    return os;
}

template<class T>
std::ostream & File<T>::PrintFileContent(std::ostream & os) const {
    os << "Content: " << "WILL BE ADDED LATER";
    return os;
}

/*
template<class T>
std::ostream & operator<<(std::ostream & os, const File<T> & f) {
    f.PrintFileInfo(os) << "\n";
    f.PrintFileContent(os);
    return os;
}
*/

template<class T>
File<T> & File<T>::operator=(const File<T> & src) {
    if(&src == this) return *this;
    Set(src);
    
    return *this;
}