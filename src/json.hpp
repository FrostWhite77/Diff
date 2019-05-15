#pragma once

#include "exception.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <stack>

#include <iostream>

/**
 * CPair
 * represents pair (key - value) in JSON structure
 */ 
class CPair {
    public:
        /**
         * Empty Constructor
         */ 
        CPair();

        /**
         * Constructor
         * @param key
         * @param value
         */ 
        CPair(const std::string & key, const std::string val);
        
        /**
         * Copy Constructor
         * @param src source instance of CPair
         */ 
        CPair(const CPair & src);

        /**
         * Destructor
         */ 
        ~CPair();

        /** 
         * Clone method - creates new instance of CPair 
         * @return pointer to the new instance
         */ 
        CPair * Clone() const;

        /**
         * Getter for Key
         */ 
        std::string GetKey() const;

        /**
         * Getter for Value
         */ 
        std::string GetVal() const;

        /**
         * Setter for Key
         * @param key new key
         */ 
        void SetKey(const std::string & key);

        /**
         * Setter for Value
         * @param value new value
         */ 
        void SetVal(const std::string & val);

        /**
         * Operator == overload
         * @param x instance of CPair to be compared with
         * @return true if both key and value are equal
         */ 
        bool operator==(const CPair x) const; 

    private:
        /**
         * Key
         */ 
        std::string _key;

        /**
         * Value
         */ 
        std::string _val;
};

/**
 * CNode
 * represents node in JSON structure
 */ 
class CNode {
    public:
        /**
         * Constructor
         * @param origin path to the file, from where was node loaded
         */ 
        CNode(const std::string & origin);

        /**
         * Copy Constructor
         * @param src source instance of CNode
         */ 
        CNode(const CNode & src);

        /**
         * Destructor
         */ 
        ~CNode();

        /** 
         * Clone method - creates new instance of CNode 
         * @return pointer to the new instance
         */ 
        CNode * Clone() const;
        
        /**
         * Method to add node as a subnode to this node
         * @param node pointer to node to be added
         */ 
        void AddCNode(CNode * node);
        
        /**
         * Method to add pair to this node
         * @param node pointer to node to be added
         */ 
        void AddPair(CPair * pair);

        /**
         * Method to get if node has any pairs or subnodes
         * @return true if node has at least one pair or one subnode, otherwise false
         */ 
        bool IsEmpty() const;

        /**
         * Getter for Origin
         */ 
        std::string GetOrigin() const;

        /**
         * Setter for Origin
         * @param origin new origin
         */ 
        void SetOrigin(std::string newOrigin);

        /**
         * Method which is searching node in this node's subnodes
         * @param node pointer to the node to be found
         * @return true if node (all pairs are same and all subnodes are same) was found, otherwise false
         */ 
        bool EqualsNode(const CNode * node) const;

        /**
         * Method which is searching pair in this node's pairs
         * @param pair pointer to the pair to bef ound
         * @return true if pair was found, otherwise false
         */ 
        bool EqualsPair(const CPair * pair) const;

        /**
         * Method which is determinating if two nodes are equal
         * @param node pointer to the node to be compared with
         * @param store pointer to the node where differences will be stored (should be empty)
         * @return true if nodes (all pairs are same and all subnodes are same) are equal, otherwise false
         */ 
        bool IsSameAs(const CNode * node, CNode * store = NULL) const;

        /**
         * Method to print CNode info to the ostream
         * @param os ostream where will be printed
         * @param u number of indentional spaces 
         * @param printOrigin bool value if origin file should be printed
         */ 
        std::ostream & Print(std::ostream & os, unsigned u = 0, bool printOrigin = false);

    private:
        /**
         * Origin (file from where node comes from)
         */ 
        std::string _origin;

        /**
         * Vector of subnodes
         */ 
        std::vector<CNode *> _nodes;

        /**
         * Vector of pairs
         */ 
        std::vector<CPair *> _pairs;
};

/**
 * Function to read all data from file to the string
 * @param ifs ifstream to the origin file
 * @return string which contains loaded JSON
 */ 
std::string ReadJSONToString(std::ifstream & ifs);

/**
 * Support function for ReadJSONToString
 * reads 1 node
 * @param ifs ifstream to the origin file
 * @return string which contains loaded node
 */ 
std::string ReadCNodeToString(std::ifstream & ifs);

/**
 * Function which can check basic JSON format
 * @param json string with loaded JSON
 * @return true if format is valid, otherwise false
 */ 
bool CheckBasicJSONFormat(const std::string & json);

/**
 * Function which reads JSON file from path and creates JSON structure
 * @param path path to the JSON file
 * @return pointer to the CNode which represents root node
 */ 
CNode * LoadAndParseJSON(const std::string & path);

/**
 * Support function for LoadAndParseJSON
 * parse 1 node
 * @param json string with loaded JSON
 * @param i current position in the string
 * @param origin origin file 
 * @return string which contains loaded node
 */ 
CNode * ReadCNode(const std::string & json, size_t & i, const std::string & origin);

/**
 * Support function for LoadAndParseJSON
 * read key/val
 * @param json string with loaded JSON
 * @param i current position in the string
 * @return string which contains loaded key/val
 */ 
std::string ReadVal(const std::string & json, size_t & i);