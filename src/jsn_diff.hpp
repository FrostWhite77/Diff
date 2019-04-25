#pragma once

#include <sstream>

class JsnDiff {
    public:
        JsnDiff(std::string firstFile, std::string secondFile);
        JsnDiff(const JsnDiff & src);
        ~JsnDiff();
        
        bool Compare();

        friend std::ostream & operator<<(std::ostream & os, const JsnDiff & src);

    private:
        std::string _first;
        std::string _second;
};