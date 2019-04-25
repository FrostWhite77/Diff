#pragma once

#include <sstream>

class File {
    public:
        File(std::string fileName);
        File(const File & src);
        ~File();

        friend std::ostream & operator<<(std::ostream & os, const File & src);

    private:
        std::string _fileName;
};