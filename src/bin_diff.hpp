#pragma once

#include "file.hpp"

#include <sstream>

class BinDiff {
    public:
        BinDiff(std::string firstFile, std::string secondFile);
        BinDiff(const BinDiff & src);
        ~BinDiff();
        
        bool Compare();

        friend std::ostream & operator<<(std::ostream & os, const BinDiff & src);

    private:
        File _first;
        File _second;
};