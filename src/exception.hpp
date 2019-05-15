#pragma once

#include <sstream>
#include <string>

class JSONFormatErrorException {
    public:
        JSONFormatErrorException(const std::string & file);
        JSONFormatErrorException(const JSONFormatErrorException & src);
        ~JSONFormatErrorException();

        friend std::ostream & operator<<(std::ostream & os, const JSONFormatErrorException & src);
    
    private:
        std::string _file;
};