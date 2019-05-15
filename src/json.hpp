#pragma once

#include "exception.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <stack>

#include <iostream>

class CPair {
    public:
        CPair();
        CPair(const std::string & key, const std::string val);
        CPair(const CPair & src);

        CPair * Clone() const;

        std::string GetKey() const;
        std::string GetVal() const;

        void SetKey(const std::string & key);
        void SetVal(const std::string & val);

        bool operator==(const CPair x) const; 

    private:
        std::string _key;
        std::string _val;
};

class CNode {
    public:
        CNode(const std::string & origin);
        CNode(const CNode & src);
        ~CNode();

        CNode * Clone() const;
        
        void AddCNode(CNode * node);
        void AddPair(CPair * pair);

        bool IsEmpty() const;

        std::string GetOrigin() const;
        void SetOrigin(std::string newOrigin);

        bool EqualsNode(const CNode * node) const;
        bool EqualsPair(const CPair * pair) const;
        bool IsSameAs(const CNode * node, CNode * store = NULL) const;

        std::ostream & Print(std::ostream & os, unsigned u = 0, bool printOrigin = false);

    private:
        std::string _origin;
        std::vector<CNode *> _nodes;
        std::vector<CPair *> _pairs;
};

std::string ReadJSONToString(std::ifstream & ifs);
std::string ReadCNodeToString(std::ifstream & ifs);

bool CheckBasicJSONFormat(const std::string & json);

CNode * LoadAndParseJSON(const std::string & path);

CNode * ReadCNode(const std::string & json, size_t & i, const std::string & origin);
std::string ReadVal(const std::string & json, size_t & i);