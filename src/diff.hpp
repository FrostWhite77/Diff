#pragma once

#include "file.hpp"

#include <sstream>

class Diff {
    public:
        Diff(std::string firstFile, std::string secondFile);
        Diff(const Diff & src);
        virtual ~Diff();
        
        virtual bool Compare();

        Diff & operator=(const Diff & src);
        friend std::ostream & operator<<(std::ostream & os, const Diff & src);

    protected:
        File _first;
        File _second;
};

class BinDiff : public Diff {
    public:
        BinDiff(std::string firstFile, std::string secondFile);
        BinDiff(const BinDiff & src);
        virtual ~BinDiff();
        
        virtual bool Compare() override;

        friend std::ostream & operator<<(std::ostream & os, const BinDiff & src);
};

class TxtDiff : public Diff {
    public:
        TxtDiff(std::string firstFile, std::string secondFile);
        TxtDiff(const TxtDiff & src);
        virtual ~TxtDiff();
        
        virtual bool Compare() override;

        friend std::ostream & operator<<(std::ostream & os, const TxtDiff & src);
};

class JsnDiff : public Diff {
    public:
        JsnDiff(std::string firstFile, std::string secondFile);
        JsnDiff(const JsnDiff & src);
        virtual ~JsnDiff();
        
        virtual bool Compare();

        friend std::ostream & operator<<(std::ostream & os, const JsnDiff & src);
};
