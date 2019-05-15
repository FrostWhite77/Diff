#pragma once

#include <sstream>
#include <string>

/**
 * JSON Format Error Exception 
 * represents error in JSON format in file .json
 */ 
class JSONFormatErrorException {
    public:
        /**
         * Constructor
         * @param file file where error occured
         */
        JSONFormatErrorException(const std::string & file);

        /**
         * Copy Constructor
         * @param src source instance of JSONFormatErrorException
         */ 
        JSONFormatErrorException(const JSONFormatErrorException & src);
        
        /**
         * Destructor
         */ 
        ~JSONFormatErrorException();

        /**
         * Operator << overload 
         * @param os ostream, where will be printed
         * @param src instance of JSONFormatErrorException to be printed
         */
        friend std::ostream & operator<<(std::ostream & os, const JSONFormatErrorException & src);
    
    private:
        /**
         * File path
         */ 
        std::string _file;
};