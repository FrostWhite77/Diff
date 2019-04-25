#pragma once

#include "file.hpp"

#include <sstream>

class JsnDiff {
    public:
        JsnDiff(std::string firstFile, std::string secondFile);
        JsnDiff(const JsnDiff & src);
        ~JsnDiff();
        
        bool Compare();

        friend std::ostream & operator<<(std::ostream & os, const JsnDiff & src);

    private:
        File _first;
        File _second;
};