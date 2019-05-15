#include "json.hpp"

using namespace std;

// CPair
CPair::CPair() : _key(), _val() {

}

CPair::CPair(const string & key, const string val) : _key(key), _val(val) {

}

CPair::CPair(const CPair & src) {
    if(&src == this) return;

    _key = src._key;
    _val = src._val;
}

CPair * CPair::Clone() const {
    return new CPair(*this);
}

string CPair::GetKey() const {
    return _key;
}
string CPair::GetVal() const {
    return _val;
}

void CPair::SetKey(const string & key) {
    _key = key;
}

void CPair::SetVal(const string & val) {
    _val = val;
}

bool CPair::operator==(const CPair x) const {
    return _key == x._key && _val == x._val;
}

// CNode 
CNode::CNode(const string & origin) : _origin(origin), _nodes(), _pairs() {

}

CNode::CNode(const CNode & src) {
    if(&src == this) return;
    
    _origin = src._origin;

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

CNode::~CNode() {
    for(size_t i = 0; i < _nodes.size(); i++) {
        delete _nodes[i];
    }
    for(size_t i = 0; i < _pairs.size(); i++) {
        delete _pairs[i];
    }
}

CNode * CNode::Clone() const {
    return new CNode(*this);
}

void CNode::AddCNode(CNode * node) {
    _nodes.push_back(node);
}

void CNode::AddPair(CPair * pair) {
    _pairs.push_back(pair);
}

bool CNode::IsEmpty() const {
    return _nodes.size() > 0 || _pairs.size() > 0;
}

std::string CNode::GetOrigin() const {
    return _origin;
}

void CNode::SetOrigin(string newOrigin) {
    _origin = newOrigin;
}

bool CNode::EqualsNode(const CNode * node) const {
    for(size_t i = 0; i < _nodes.size(); i++) {
        if(node->IsSameAs(_nodes[i])) return true;
    }

    return false;
}

bool CNode::EqualsPair(const CPair * pair) const {
    for(size_t i =0; i < _pairs.size(); i++) {
        if(*_pairs[i] == *pair) return true;
    }
    return false;
}

bool CNode::IsSameAs(const CNode * node, CNode * store) const {
    bool r = true;
    
    if(_nodes.size() != node->_nodes.size()) {
        //cout << "nodes: " << _nodes.size() << " - " << node->_nodes.size() << endl;       
        r = false;
    }
    if(_pairs.size() != node->_pairs.size()) {
        //cout << "pairs: " << _pairs.size() << " - " << node->_pairs.size() << endl;
        r = false;
    }

    for(size_t i = 0; i < _pairs.size(); i++) {
        if(!node->EqualsPair(_pairs[i])) {
            //cout << "pair missing" << endl;
            r = false;
            if(store != NULL) {
                CPair * tmp = _pairs[i]->Clone();
                tmp->SetVal(tmp->GetVal() + " (" + GetOrigin() + ")");
                store->AddPair(tmp);
            }
        }
    }
    for(size_t i = 0; i < node->_pairs.size(); i++) {
        if(!EqualsPair(node->_pairs[i])) {
            //cout << "pair missing" << endl;
            r = false;
            if(store != NULL) {
                CPair * tmp = node->_pairs[i]->Clone();
                tmp->SetVal(tmp->GetVal() + " (" + node->GetOrigin() + ")");
                store->AddPair(tmp);
            }
        }
    }

    for(size_t i = 0; i < _nodes.size(); i++) {
        if(!node->EqualsNode(_nodes[i])) {
            //cout << "node missing" << endl;
            r = false;
            if(store != NULL) {
                store->AddCNode(_nodes[i]->Clone());
            }
        }
    }
    for(size_t i = 0; i < node->_nodes.size(); i++) {
        if(!EqualsNode(node->_nodes[i])) {
            //cout << "node missing" << endl;
            r = false;
            if(store != NULL) {
                store->AddCNode(node->_nodes[i]->Clone());
            }
        }
    }

    return r;
}

ostream & CNode::Print(ostream & os, unsigned u, bool printOrigin) {
    if(printOrigin && _origin != "") {
        for(size_t i = 0; i < u; i++) os << " ";
        os << "Node from " << _origin << " {" << endl;
    }
    
    for(size_t i = 0; i < _pairs.size(); i++) {
        for(size_t i = 0; i < u + 1; i++) os << " ";        
        os <<_pairs[i]->GetKey() << ": " << _pairs[i]->GetVal() << endl;
    }

    if(_pairs.size() != 0 && _nodes.size() != 0) os << endl;

    for(size_t i = 0; i < _nodes.size(); i++) {
        _nodes[i]->Print(os, u + 1, printOrigin);
    }

    for(size_t i = 0; i < u; i++) os << " ";
    os << "}" << endl;

    return os;
}

// Non-member functions implementation
CNode * LoadAndParseJSON(const string & path) {
    ifstream ifs(path);
    string jsonString = ReadJSONToString(ifs);

    if(!CheckBasicJSONFormat(jsonString)) {
        return NULL;
    }

    size_t pos = 0;
    CNode * rootNode = ReadCNode(jsonString, pos, path);

    return rootNode;
}

string ReadJSONToString(ifstream & ifs) {
    string wholeJson;
    
    while(ifs) {
        if(ifs.peek() == '{') {
            wholeJson.append(ReadCNodeToString(ifs));
        }
    }
    ifs.close();

    return wholeJson;
}

bool CheckBasicJSONFormat(const string & json) {
    stack<char> st;
    bool inside = false, result = true;

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
                    break;
                }
                char c = (char)st.top();
                if(c != '{') {
                    result = false;
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
            }
        }
        else if(inside && json[i] == '"') {
            char c = (char)st.top();
            if(c != '"') {
                result = false;
            }
            inside = false;
            st.pop();
        }

        
        if(last != 0 && json[i] == '{' && last != ',' && last != '{') {
            result = false;
        }
        else if(last == '}' && (json[i] != ',' && json[i] != '}')) {
            result = false;    
        }

        if(last == ',' && json[i] == '}') {
            result = false;
        }
        
        last = json[i];
        i++;
    }

    if(!st.empty()) result = false;
    return result;
}

CNode * ReadCNode(const string & json, size_t & i, const string & origin) {
    CNode * node = new CNode(origin);
    char last = 0;    

    CPair pair;
    string tmp;

    while(i < json.size()) {        
        // { of current CNode => skip
        if(last == 0 && json[i] == '{') {
            last = json[i];
            i++;
            continue;
        }

        // not loading key or val, found { => load subnode
        if(json[i] == '{') {
            node->AddCNode(ReadCNode(json, i, origin));
            last = json[i];
            i++;
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

string ReadVal(const string & json, size_t & i) {
    string s;

    while(i < json.size()) {
        if(json[i] == ',' || json[i] == ':' || json[i] == '}') return s;
        else if(json[i] == '"') {}
        else s.push_back(json[i]);
        
        i++;
    }

    return s;
}

string ReadCNodeToString(ifstream & ifs) {
    string subnode;
    subnode.push_back(ifs.get());

    while(ifs.peek() != EOF || ifs.peek() != '}' || ifs.good() == true) {
        if((char)ifs.peek() == '{') subnode.append(ReadCNodeToString(ifs));
        
        char c = ifs.get();

        if(!isspace(c)) subnode.push_back(c);        
        if(ifs.bad() || ifs.eof() || c == '}') break;
    }

    return subnode;
}