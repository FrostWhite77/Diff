#pragma once

#include <sstream>
#include <fstream>
#include <vector>

class File {
    public:
        File(std::string fileName = "");
        File(const File & src);
        virtual ~File();

        virtual File * Clone() const;

        virtual size_t GetFileSize() const;
        virtual bool Load();

        std::string GetFileName() const;

        virtual std::vector<uint8_t> GetBinary();
        virtual std::vector<std::string> GetText();
        virtual std::vector<std::string> GetJSON();

        virtual std::ostream & Print(std::ostream & os) const;
        friend std::ostream & operator<<(std::ostream & os, const File & src);

    protected:
        std::string _fileName;
        bool _isLoaded;
};

class BinFile : public File {
    public:
        BinFile(std::string fileName);
        BinFile(const BinFile & src);
        virtual ~BinFile();

        virtual BinFile * Clone() const override;

        virtual size_t GetFileSize() const override;
        virtual bool Load() override;

        virtual std::vector<uint8_t> GetBinary() override;
        virtual std::vector<std::string> GetText() override;
        virtual std::vector<std::string> GetJSON() override;

        virtual std::ostream & Print(std::ostream & os) const override;
        friend std::ostream & operator<<(std::ostream & os, const BinFile & src);
    
    private:
        std::vector<uint8_t> _bytes;
};

class TxtFile : public File {
    public:
        TxtFile(std::string fileName);
        TxtFile(const TxtFile & src);
        virtual ~TxtFile();

        virtual TxtFile * Clone() const override;

        virtual size_t GetFileSize() const override;
        virtual bool Load() override;

        virtual std::vector<uint8_t> GetBinary() override;
        virtual std::vector<std::string> GetText() override;
        virtual std::vector<std::string> GetJSON() override;

        virtual std::ostream & Print(std::ostream & os) const override;
        friend std::ostream & operator<<(std::ostream & os, const TxtFile & src);
    
    private:
        std::vector<std::string> _lines;
};

class JsnFile : public File {
    public:
        JsnFile(std::string fileName);
        JsnFile(const JsnFile & src);
        virtual ~JsnFile();

        virtual JsnFile * Clone() const override;

        virtual size_t GetFileSize() const override;
        virtual bool Load() override;

        virtual std::vector<uint8_t> GetBinary() override;
        virtual std::vector<std::string> GetText() override;
        virtual std::vector<std::string> GetJSON() override;

        virtual std::ostream & Print(std::ostream & os) const override;
        friend std::ostream & operator<<(std::ostream & os, const JsnFile & src);
    
    private:
        std::vector<std::string> _nodes;
};