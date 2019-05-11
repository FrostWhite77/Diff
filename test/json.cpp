#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class CNode {
    public:
        CNode(string key = "", string val = "") : _key(key), _val(val), _nodes() {

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
        }

        ~CNode() {
            for(size_t i = 0; i < _nodes.size(); i++) {
                delete _nodes[i];
            }
        }

        CNode * Clone() {
            return new CNode(*this);
        }

        void AddCNode(CNode * node) {
            _nodes.push_back(node);
        }

        void SetKey(const string & key) {
            _key = key;
        }

        void SetVal(const string & val) {
            _val = val;
        }

        void Print(unsigned u = 0) {
            size_t i = 0;
            while(i < u) { cout << " "; i++; }
            cout << _key << ": " << _val << endl;

            for(size_t i = 0; i < _nodes.size(); i++) {
                _nodes[i]->Print(u + 3);
            }
        }

    private:
        string _key;
        string _val;

        vector<CNode *> _nodes;
};

CNode * ReadNode(ifstream & ifs) {
    string part;
    ifs.get();

    CNode * node = new CNode();

    while(ifs.good()) {
        if(ifs.peek() == '{') node->AddCNode(ReadNode(ifs));

        char c = ifs.peek();
        if(c != '}') part.push_back(ifs.get());
        else break;
    }

    string key, val;
    size_t i = 0;

    bool inside = false;

    while(i < part.size()) {
        if(!inside && isspace(part[i])) {
            i++;
            continue;
        }
        else {
            if(part[i] == ':') {
                i++;
                break;
            }
            inside = true;
            key.push_back(part[i]);
            i++;
        }
    }

    inside = false;
    while(i < part.size()) {
        if(!inside && part[i] != '"') {
            i++;
            continue;
        }
        else {
            if(!inside && part[i] == '"') {
                i++;
                inside = true;
                continue;
            }
            if(inside && part[i] == '"') {
                break;
            }
            val.push_back(part[i]);
            i++;
        }
    }

    node->SetKey(key);
    node->SetVal(val);

    return node;
}

CNode * ReadJSONFile(const string & path) {
    ifstream ifs(path);
    CNode * root = NULL;

    char x = ifs.peek();
    if(x == '{') {
        root = ReadNode(ifs);
    }    

    ifs.close();
    return root;
} 

int main() {

    CNode * root = ReadJSONFile("jsn1.jsn");
    root->Print();

    delete root;
    return 0;
}