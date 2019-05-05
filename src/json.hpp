#pragma once

#include <istream>
#include <vector>
#include <string>

class JSONNode {
    public:
        JSONNode();
        JSONNode(const JSONNode & src);
        virtual ~JSONNode(); 

        virtual std::string GetValue() const;

        void AddSubNode(const JSONNode & node);
        virtual bool Load();

        friend std::istream operator>>(std::istream is, JSONNode & node);

    private:
        std::vector<JSONNode *> _subNodes;
};

class JSONPair : public JSONNode {
    public:
        JSONPair();
        JSONPair(const JSONPair & src);
        virtual ~JSONPair(); 

        virtual std::string GetValue() const override;

        virtual bool Load() override;

        friend std::istream operator>>(std::istream is, JSONPair & node);

    private:
        std::string _name;
        std::string _val; 
};

class JSONArray : public JSONNode {
    public:
        JSONArray();
        JSONArray(const JSONArray & src);
        virtual ~JSONArray(); 

        virtual std::string GetValue() const override;

        virtual bool Load() override;

        friend std::istream operator>>(std::istream is, JSONArray & node);

    private:
        std::string _name;
        std::vector<std::string> _vals;
};

JSONNode * ReadNode(std::ifstream ifs);
JSONPair * ReadPair(std::ifstream ifs);
JSONArray * ReadArray(std::ifstream ifs);