#include <sstream>
#include <iostream>

#include "file.hpp"
//#include "result.hpp"

class Diff {
    public:
        Diff();
        Diff(const File & x, const File & y);
        Diff(const File * x, const File * y);
        Diff(const Diff & src);
        ~Diff();

        Diff * Clone() const;
        void Set(const Diff & src);

        Result Compare();
        void SetFile(const std::string & filePath);

        std::ostream & Print(std::ostream & os) const;
        std::ostream & GetFileXInfo(std::ostream & os) const;
        std::ostream & GetFileYInfo(std::ostream & os) const;

        friend std::ostream & operator<<(std::ostream & os, const Diff & diff);
        Diff & operator=(const Diff & src);        

    private:
        int _fileToSwap;

        File * _fileX = NULL;
        File * _fileY = NULL;
};