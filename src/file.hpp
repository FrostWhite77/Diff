#pragma once

#include "io.hpp"
#include "json.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

/**
 * General File
 */ 
class File {
    public:
        /**
         * Constructor
         * @param fileName string path to the file
         */ 
        File(std::string fileName = "");
        
        /**
         * Copy Constructor
         * @param src source instance of File
         */ 
        File(const File & src);
        
        /**
         * Destructor
         */ 
        virtual ~File();

        /** 
         * Clone method - creates new instance of File 
         * @return pointer to the new instance
         */ 
        virtual File * Clone() const;

        /**
         * Method to return file size
         * @return number of elements in file
         */  
        virtual size_t GetFileSize() const;

        /**
         * Loads the file content 
         */ 
        virtual bool Load();

        /**
         * Method to return file name
         * @return filename
         */ 
        std::string GetFileName() const;

        /**
         * Method to return file path (path to the folder which contains the file)
         * @return filepath
         */ 
        std::string GetFilePath() const;

        /**
         * Method to return whole path including file name
         * @return full filepath 
         */ 
        std::string GetFullFileName() const;

        /**
         * Method to get binary representation of the file
         * @return vector of file bytes
         */ 
        virtual std::vector<uint8_t> GetBinary();
        
        /**
         * Method to get text representation of the file
         * @return vector of file lines
         */ 
        virtual std::vector<std::string> GetText();

        /**
         * Method to get JSON representation of the file
         * @return vector of file nodes
         */ 
        virtual CNode * GetJSON();

        /**
         * Method to print file info to the ostream
         * @param os: ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os) const;

        /**
         * Operator << overload
         * @param os ostream where will be printed
         * @param src instance of File which will be printed
         */ 
        friend std::ostream & operator<<(std::ostream & os, const File & src);

    protected:
        /**
         * FileName (name and extension)
         */ 
        std::string _fileName;

        /**
         * FilePath (path to the file without filename and extension)
         */ 
        std::string _filePath;

        /**
         * bool value which represents if file content has been loaded yet
         */ 
        bool _isLoaded;

    private:
        /**
         * Method to split full filepath to folder and filename.extension
         * @param arg full path
         */ 
        void ParseFileName(std::string arg);
};

/**
 * Binary File
 * @inherit from general File
 * implements binary file
 */ 
class BinFile : public File {
    public:
        /**
         * Constructor
         * @param fileName string path to the file
         */ 
        BinFile(std::string fileName);

        /**
         * Copy Constructor
         * @param src source instance of File
         */ 
        BinFile(const BinFile & src);
        
        /**
         * Destructor
         */ 
        virtual ~BinFile();

        /** 
         * Clone method - creates new instance of BinFile 
         * @return pointer to the new instance
         */ 
        virtual BinFile * Clone() const override;

        /**
         * Method to return file size
         * @return number of elements in file
         */  
        virtual size_t GetFileSize() const override;
        
        /**
         * Loads the file content
         */ 
        virtual bool Load() override;

        /**
         * Method to get binary representation of the file 
         * @return vector of file bytes
         */ 
        virtual std::vector<uint8_t> GetBinary() override;

        /**
         * Method to get text representation of the file
         * @return vector of file lines (bytes parsed)
         */ 
        virtual std::vector<std::string> GetText() override;

        /**
         * Method to get JSON representation of the file
         * @return empty vector - can not represent binary file as JSON
         */ 
        virtual CNode * GetJSON() override;

        /**
         * Method to print file info to the ostream
         * @param os ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os) const override;

        /**
         * Operator << overload
         * @param os ostream where will be printed
         * @param src instance of BinFile which will be printed
         */ 
        friend std::ostream & operator<<(std::ostream & os, const BinFile & src);
    
    private:
        /**
         * Vector of bytes
         */ 
        std::vector<uint8_t> _bytes;
};

/**
 * Text File
 * @inherit from general File
 * implements text file
 */ 
class TxtFile : public File {
    public:
        /**
         * Constructor
         * @param fileName: string path to the file
         */ 
        TxtFile(std::string fileName);

        /**
         * Copy Constructor
         * @param src: source instance of TxtFile
         */ 
        TxtFile(const TxtFile & src);

        /**
         * Destructor
         */ 
        virtual ~TxtFile();

        /** 
         * Clone method - creates new instance of TxtFile 
         * @return pointer to the new instance
         */ 
        virtual TxtFile * Clone() const override;

        /**
         * Method to return file size
         * @return number of elements in file
         */
        virtual size_t GetFileSize() const override;

        /**
         * Loads the file content
         */ 
        virtual bool Load() override;

        /**
         * Method to get binary representation of the file 
         * @return vector of file bytes (lines parsed)
         */ 
        virtual std::vector<uint8_t> GetBinary() override;

        /**
         * Method to get text representation of the file
         * @return vector of file lines
         */ 
        virtual std::vector<std::string> GetText() override;

        /**
         * Method to get JSON representation of the file
         * @return empty vector (can not represent txt file as JSON)
         */ 
        virtual CNode * GetJSON() override;

        /**
         * Method to print file info to the ostream
         * @param os ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os) const override;

        /**
         * Operator << overload
         * @param os ostream where will be printed
         * @param src instance of TxtFile which will be printed
         */ 
        friend std::ostream & operator<<(std::ostream & os, const TxtFile & src);
    
    private:
        /**
         * Vector of lines
         */ 
        std::vector<std::string> _lines;
};

/**
 * JSON File
 * @inherit from general File
 * implements JSON file
 */ 
class JsnFile : public File {
    public:
        /**
         * Constructor
         * @param fileName string path to the file
         */ 
        JsnFile(std::string fileName);

        /**
         * Copy Constructor
         * @param src source instance of JsnFile
         */ 
        JsnFile(const JsnFile & src);

        /**
         * Destructor
         */ 
        virtual ~JsnFile();

        /** 
         * Clone method - creates new instance of JsnFile 
         * @return pointer to the new instance
         */ 
        virtual JsnFile * Clone() const override;

        /**
         * Method to return file size
         * @return number of elements in file
         */
        virtual size_t GetFileSize() const override;

        /**
         * Loads the file content
         */ 
        virtual bool Load() override;

        /**
         * Method to get binary representation of the file 
         * @return vector of file bytes (read from file again)
         */ 
        virtual std::vector<uint8_t> GetBinary() override;

        /**
         * Method to get text representation of the file
         * @return vector of file lines (read from file again)
         */ 
        virtual std::vector<std::string> GetText() override;

        /**
         * Method to get JSON representation of the file
         * @return pointer to root node
         */ 
        virtual CNode * GetJSON() override;

        /**
         * Method to print file info to the ostream
         * @param os ostream where will be printed
         */ 
        virtual std::ostream & Print(std::ostream & os) const override;

        /**
         * Operator << overload
         * @param os ostream where will be printed
         * @param src instance of JsnFile which will be printed
         */ 
        friend std::ostream & operator<<(std::ostream & os, const JsnFile & src);
    
    private:
        /**
         * Vector of nodes
         */ 
        CNode * _rootNode;
};

/**
 * Function, which takes filepath and creates specific instance of file
 * @param filePath full path to file
 * @return pointer to specific file instance 
 */ 
File * CreateFile(const std::string & filePath);