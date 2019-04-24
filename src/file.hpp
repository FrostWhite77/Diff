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

template<class T>
class File : public AbstractFile {
    public:
        File(std::string fileName);
        File(const File & src);
        virtual ~File();

        virtual File<T> * Clone() const;
        virtual void Set(const File & src);

        bool IsLoaded() const;
        virtual bool LoadFileData();
        virtual Result<T> CompareWith(File<T> * f, bool showDifferences = false);

        virtual std::ostream & PrintFileInfo(std::ostream & os) const override;
        virtual std::ostream & PrintFileContent(std::ostream & os) const override;

        template <class X>
        friend std::ostream & operator<<(std::ostream & os, const File<X> & f);
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