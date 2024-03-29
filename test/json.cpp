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
string ReadVal(const string & json, size_t & i);
bool CheckJSON(const string & json);

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

    bool checkFormat = CheckJSON(wholeJson);
    cout << "JSON Format Check: " << boolalpha << checkFormat << endl;

    return wholeJson;
}

CNode * ParseJSON(const string & json, size_t & i, stack<char> & _stack) {
    CNode * node = new CNode;
    char last = 0, next = 0;
    
    bool lKey = false, lVal = false;

    CPair pair;
    string tmp;

    string nextDelims = ",{:";
    string endDelims = "";
    string * s = &nextDelims;

    while(i < json.size()) {        
        // first char is not { => error        
        if(last == 0 && json[i] != '{') {
            throw "JSON Format Error!";
        }

        next = 0;

        // { of current CNode => skip
        if(last == 0 && json[i] == '{') {
            last = json[i];
            i++;
            continue;
        }

        // not loading key or val, found { => load subnode
        if(json[i] == '{') {
            //cout << "start " << json[i] << endl;
            node->AddCNode(ParseJSON(json, i, _stack));
            last = json[i];
            i++;
            //cout << "end " << json[i] << ", last: " << last << endl;
            continue;
        }

        // reading key
        if(last == '{' || last == ',') {
            pair.SetKey(ReadVal(json, i));
            last = json[i];
            i++;
            continue;
        }

        // reading val
        if(last == ':') {
            pair.SetVal(ReadVal(json, i));
            node->AddPair(pair.Clone());

            pair.SetKey("");
            pair.SetVal("");

            last = json[i];
            i++;
            continue;
        }

        if(last == '}' || json[i] == '}') break;
        else i++;
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

string ReadVal(const string & json, size_t & i) {
    string s;

    while(i < json.size()) {
        if(json[i] == ',' || json[i] == ':' || json[i] == '}') {
            //cout << "read: " << s << endl;
            return s;
        }
        else if(json[i] == '"') {

        }
        else {
            s.push_back(json[i]);
        }

        i++;
    }

    return s;
}

bool CheckJSON(const string & json) {
    stack<char> st;
    bool inside = false, result = true;
    
    const char double_quote = string("\"").c_str()[0];

    char last = 0;
    size_t i = 0;
    while(result && i < json.size()) {
        switch(json[i]) {
            case '{':
                st.push(json[i]);
                break;
            case '}':
                if(st.empty()) {
                    result = false;
                    cout << "missing bracket" << endl;
                    break;
                }
                char c = (char)st.top();
                if(c != '{') {
                    result = false;
                    cout << "missing bracket" << endl;
                    break;
                }
                st.pop();
                break;
        }

        if(!inside && json[i] == '"') {
            st.push('"');
            inside = true;

            if(last != ':') {
                result = false;
                cout << "missing colon" << endl;
            }
        }
        else if(inside && json[i] == '"') {
            char c = (char)st.top();
            if(c != '"') {
                result = false;
                cout << "missing \"" << endl;
            }
            inside = false;
            st.pop();
        }

        
        if(last != 0 && json[i] == '{' && last != ',' && last != '{') {
            cout << "missing comma" << endl;
            result = false;
        }
        else if(last == '}' && (json[i] != ',' && json[i] != '}')) {
            cout << "missing comma" << endl;
            result = false;    
        }

        if(last == ',' && json[i] == '}') {
            cout << "missing key/val" << endl;
            result = false;
        }
        
        last = json[i];
        i++;
    }

    if(!st.empty()) result = false;

    return result;
}