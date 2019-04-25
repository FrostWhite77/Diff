#pragma once

#include "file.hpp"

#include <sstream>

class TxtDiff {
    public:
        TxtDiff(std::string firstFile, std::string secondFile);
        TxtDiff(const TxtDiff & src);
        ~TxtDiff();
        
        bool Compare();

        friend std::ostream & operator<<(std::ostream & os, const TxtDiff & src);

    private:
        File _first;
        File _second;
};