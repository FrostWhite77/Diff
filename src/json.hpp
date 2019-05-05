#pragma once

#include <vector>
#include <string>

class JSONNode {
    public:

    private:
        std::vector<JSONNode> _subNodes;
};

class JSONPair : public JSONNode {
    public:

    private:
        std::string _name;
        std::string _val; 
};

class JSONArray : public JSONNode {
    public:

    private:
        std::string _name;
        std::vector<JSONPair> _vals;
};