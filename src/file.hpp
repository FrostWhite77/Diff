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

class File : public AbstractFile {
    public:
        File(std::string fileName);
        File(const File & src);
        virtual ~File();

        virtual File * Clone() const;
        virtual void Set(const File & src);

        bool IsLoaded() const;
        virtual bool LoadFileData();
        virtual Result CompareWith(File * f, bool showDifferences = false);

        virtual std::ostream & PrintFileInfo(std::ostream & os) const override;
        virtual std::ostream & PrintFileContent(std::ostream & os) const override;

        friend std::ostream & operator<<(std::ostream & os, const File & f);
        File & operator=(const File & src);

    protected:
        std::string _fileName;
        bool _hasBeenLoaded;
};

class BinFile : public File {
    public:
        BinFile(std::string fileName);
        BinFile(const BinFile & src);
        virtual ~BinFile();

        virtual BinFile * Clone() const override;
        virtual void Set(const BinFile & src);

        virtual bool LoadFileData() override;
        virtual Result CompareWith(File * f, bool showDifferences = false) override;

        virtual std::ostream & PrintFileInfo(std::ostream & os) const override;
        virtual std::ostream & PrintFileContent(std::ostream & os) const override;

        friend std::ostream & operator<<(std::ostream & os, const BinFile & f);
        BinFile & operator=(const BinFile & src);

    private:
        std::vector<uint8_t> _bytes;
};