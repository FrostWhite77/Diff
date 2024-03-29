#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#include <stack>

using namespace std;

class CPair {
    public:
        CPair() : _key(), _val() {}
        CPair(const string & key, const string val) : _key(key), _val(val) {}
        CPair(const CPair & src) {
            if(&src == this) return;

            _key = src._key;
            _val = src._val;
        }

        string GetKey() const {
            return _key;
        }
        string GetVal() const {
            return _val;
        }

        void SetKey(const string & key) {
            _key = key;
        }
        void SetVal(const string & val) {
            _val = val;
        }

        CPair * Clone() const {
            return new CPair(*this);
        }

    private:
        string _key;
        string _val;
};

class CNode {
    public:
        CNode(string key = "", string val = "") : _key(key), _val(val), _nodes(), _pairs() {

        }

        CNode(const CNode & src) {
            if(&src == this) return;

            _key = src._key;
            _val = src._val;

            for(size_t i = 0; i < _nodes.size(); i++) {
                delete _nodes[i];
            }

            _nodes.clear();

            for(size_t i = 0; i < src._nodes.size(); i++) {
                _nodes.push_back(src._nodes[i]->Clone());
            }

            for(size_t i = 0; i < _pairs.size(); i++) {
                delete _pairs[i];
            }

            _pairs.clear();

            for(size_t i = 0; i < src._pairs.size(); i++) {
                _pairs.push_back(src._pairs[i]->Clone());
            }
        }

        ~CNode() {
            for(size_t i = 0; i < _nodes.size(); i++) {
                delete _nodes[i];
            }

            for(size_t i = 0; i < _pairs.size(); i++) {
                delete _pairs[i];
            }
        }

        CNode * Clone() {
            return new CNode(*this);
        }

        void AddCNode(CNode * node) {
            _nodes.push_back(node);
        }

        void AddPair(CPair * pair) {
            _pairs.push_back(pair);
        }

        void SetKey(const string & key) {
            _key = key;
        }

        void SetVal(const string & val) {
            _val = val;
        }

        void Print(unsigned u = 0) {
            size_t j = 0;
            while(j < u) { cout << " "; j++; }
            cout << "node: " << endl;


            for(size_t i = 0; i < _pairs.size(); i++) {
                size_t j = 0;
                while(j < u) { cout << " "; j++; }
                cout << "pair: " <<_pairs[i]->GetKey() << ": " << _pairs[i]->GetVal() << endl;
            }

            for(size_t i = 0; i < _nodes.size(); i++) {
                _nodes[i]->Print(u + 3);
            }
        }

    private:
        string _key;
        string _val;

        vector<CNode *> _nodes;
        vector<CPair *> _pairs;
};

string ReadJSON(ifstream & ifs);
string ReadJSONNode(ifstream & ifs);
CNode * ParseJSON(const string & json, size_t & i, stack<char> & _stack);

int main() {
    ifstream ifs("jsn1.jsn");
    string loaded = ReadJSON(ifs);

    //cout << loaded << endl;
    return 0;
}

string ReadJSON(ifstream & ifs) {
    string wholeJson;

    while(ifs) {
        if(ifs.peek() == '{') {
            wholeJson.append(ReadJSONNode(ifs));
        }
    }

    ifs.close();

    cout << wholeJson << endl;

    stack<char> st;
    size_t pos = 0;
    CNode * root = ParseJSON(wholeJson, pos, st);

    if(!st.empty()) {
        throw "JSON Format Error!";
    }

    root->Print();
    delete root;

    return wholeJson;
}

CNode * ParseJSON(const string & json, size_t & i, stack<char> & _stack) {
    CNode * node = new CNode;
    char last = 0;
    
    bool lKey = false, lVal = false;

    CPair pair;
    string tmp;

    while(i < json.size()) {        
        // first char is not { => error        
        if(last == 0 && json[i] != '{') {
            throw "JSON Format Error!";
        }

        // { of current CNode => skip
        if(last == 0 && json[i] == '{') {
            //cout << "a" << endl;
            
            last = json[i];
            i++;
            continue;
        }

        if(json[i] == '{' || json[i] == '"') {
            _stack.push(json[i]);
        }
        if(json[i] == '}') {
            char c = _stack.top();
            if(c != '{') throw "JSON Format Error!";
            _stack.pop();
        }
        if(json[i] == '"') {
            char c = _stack.top();
            if(c != '"') throw "JSON Format Error!";
            _stack.pop();
        }

        // not loading key or val, found { => load subnode
        if(!lKey && !lVal && json[i] == '{') {
            //cout << "b" << endl << endl;
            node->AddCNode(ParseJSON(json, i, _stack));
            last = json[i];
            i++;
            //cout << "last is " << last << endl << endl;
            continue;
        }

        // reading key
        if((last == '{' || last == ',') && !lKey && !lVal) {
            //cout << "c" << endl;
            //cout << "last " << last << "| current " << json[i] << endl; 

            lKey = true;
            tmp.clear();
            tmp.push_back(json[i]);
            last = json[i];
            i++;
            continue;
        }

        if(lKey && json[i] != ':' && json[i] != ',') {
            //cout << "d" << endl;
            tmp.push_back(json[i]);          
            last = json[i];
            i++;
            continue;
        }

        if(lKey && json[i] == ':') {
            //cout << "e" << endl;
            pair.SetKey(tmp);
            tmp.clear();
            lKey = false;    
            last = json[i];
            i++;
            continue;
        }

        // reading val
        if(last == ':' && !lKey && !lVal) {
            //cout << "f" << endl;
            lVal = true;
            tmp.clear();
            tmp.push_back(json[i]);
            last = json[i];
            i++;
            continue;
        }

        if(lVal && json[i] != ',' && json[i] != '}') {
            //cout << "g" << endl;
            tmp.push_back(json[i]);   
            last = json[i];       
            i++;
            continue;
        }

        if(lVal && (json[i] == ',' || json[i] == '}')) {
            //cout << "h" << endl;
            pair.SetVal(tmp);
            tmp.clear();
            node->AddPair(pair.Clone());
            lVal = false;
            last = json[i];
            i++;

            if(last == '}' || json[i] == '}') break;
            continue;
        }

        if(!lVal && !lKey && json[i] == '}') {
            //cout << "i" << endl;
            _stack.pop();
            i++;
            break;
        }

        i++;
    }

    return node;
}

string ReadJSONNode(ifstream & ifs) {
    string subnode;
    subnode.push_back(ifs.get());

    while(ifs.peek() != EOF || ifs.peek() != '}' || ifs.good() == true) {
        if((char)ifs.peek() == '{') subnode.append(ReadJSONNode(ifs));
        
        char c = ifs.get();

        if(!isspace(c)) subnode.push_back(c);        
        if(ifs.bad() || ifs.eof() || c == '}') break;
    }

    return subnode;
}