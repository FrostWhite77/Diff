#pragma once

#include <sstream>

class TxtDiff {
    public:
        TxtDiff(std::string firstFile, std::string secondFile);
        TxtDiff(const TxtDiff & src);
        ~TxtDiff();
        
        bool Compare();

        friend std::ostream & operator<<(std::ostream & os, const TxtDiff & src);

    private:
        std::string _first;
        std::string _second;
};