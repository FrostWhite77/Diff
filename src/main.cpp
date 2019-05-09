#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"
#include "folder.hpp"
#include "io.hpp"

using namespace std;

File * GetFile(const string & fileName);
Folder * GetFolder(const string & fileName);
bool Exists(const string path);
void SetCompareType(int type);

bool lineCmpIncase(const string & ll, const string & lr) {
    if(ll.size() != lr.size()) return false;
    for(size_t i = 0; i < ll.size(); i++) {
        if(toupper(ll[i]) != toupper(lr[i])) {
            return false;
        }
    }
    return true;
}

bool compareIgnored(const string & ll, const string & lr) {

    const char * l = ll.c_str();
    const char * r = lr.c_str();

    while (true) {
        while (*l != '\0' && isspace((unsigned char)*l)) l++;
        while (*r != '\0' && isspace((unsigned char)*r)) r++;
        if (*l == '\0' || *r == '\0') {
          return (*r == '\0') - (*l == '\0') == 0;
        }
        if (*l != *r) {
          return (unsigned char)*r - (unsigned char)*l == 0;
        }
        l++;
        r++;
    }

    return 0;
}

bool compareIgnCaseIns(const string & ll, const string & lr) {
    const char * l = ll.c_str();
    const char * r = lr.c_str();

    while (true) {
        while (*l != '\0' && isspace((unsigned char)*l)) l++;
        while (*r != '\0' && isspace((unsigned char)*r)) r++;
        if (*l == '\0' || *r == '\0') {
          return (*r == '\0') - (*l == '\0') == 0;
        }
        if (toupper(*l) != toupper(*r)) {
          return (unsigned char)*r - (unsigned char)*l == 0;
        }
        l++;
        r++;
    }
}

bool lineCmpWthIgnCaseIns(const string & ll, const string & lr) {
    int r = compareIgnCaseIns(ll, lr);
    if(r == 0) return true;
    return false;
}

bool lineCmpWhtIgn(const string & ll, const string & lr) {
    int r = compareIgnored(ll, lr);
    if(r == 0) return true;
    return false;
}

bool charCmp(char x, char y) {
    return toupper(x) == toupper(y); 
}

int CompareType = -1;
bool DifferentTypes = false;

bool caseInsensitive = false;
bool ignoreWhitespace = false;

int main(int argc, char * argv[]) {       
    if(argc <= 2) {
        cout << "Invalid number of arguments!" << endl;
        return 1;
    }

    vector<File *> files;
    vector<Folder *> folders;

    size_t i = 0;
    for(i = 1; i < (size_t)argc && i < 3; i++) {
        string current(argv[i]);
        
        auto file = GetFile(current);
        if(file != NULL) {
            files.push_back(file);
            //cout << argv[i] << " -> is file!" << endl;
            continue;
        }

        auto folder = GetFolder(current);
        if(file != NULL) {
            folders.push_back(folder);
            //cout << argv[i] << " -> is folder!" << endl;
            continue;
        }

        cout << "Error: Can't load " << argv[i] << ". Are you sure, it's a corrent path?" << endl;

        for(auto f : files) delete f;
        for(auto f : folders) delete f;

        return 1;   
    }

    for(i = i; i < (size_t)argc; i++) {
        if(string(argv[i]) == "-i" && CompareType == 1) {
            //cout << "switched to case insenstivite comparison" << endl;
            ignoreWhitespace = true;
        }
        else if(string(argv[i]) == "-c" && CompareType == 1) {
            //cout << "switched to case insenstivite comparison" << endl;
            caseInsensitive = true;
        }
        else {
            cout << "Invalid argument: " << argv[i] << ", possible arguments: -c: case insensitive, -i: ignore whitespace" << endl;

            for(auto f : files) delete f;
            for(auto f : folders) delete f;

            return 1;
        }
    }

    //cout << "CompareType: " << CompareType << " // 0:bin, 1:txt, 2:jsn" << endl;
    //cout << "DifferentTypes: " << boolalpha << DifferentTypes << endl;

    Diff * diff = NULL;
    if(files.size() == 2)
    {
        switch(CompareType)
        {
            case 0:
                diff = new BinDiff(*files[0], *files[1]);
                break;
            case 1:
                diff = new TxtDiff(*files[0], *files[1]);
                break;
            case 2:
                diff = new JsnDiff(*files[0], *files[1]);
                break;
        }

        bool (*func)(const string &, const string &) = NULL;
        if(caseInsensitive && ignoreWhitespace) {
            func = compareIgnCaseIns;
        }
        else if(caseInsensitive) {
            func = lineCmpIncase;
        }
        else if(ignoreWhitespace) {
            func = compareIgnored;
        }

        auto result = diff->Compare(func); 
        result->Print(cout, true);
        delete result;
    }    

    for(auto f : files) delete f;
    for(auto f : folders) delete f;
    if(diff != NULL) delete diff;

    return 0;
}

File * GetFile(const string & fileName) {
    // is binary file
    size_t position = 0;
    if((position = fileName.find(".bin")) != string::npos && position + 4 == fileName.size() && Exists(fileName)) {
        SetCompareType(0);
        return new BinFile(fileName);
    }
    // is text file
    else if((position = fileName.find(".txt")) != string::npos && position + 4 == fileName.size() && Exists(fileName)) {
        SetCompareType(1);
        return new TxtFile(fileName);
    }
    // is json file
    else if((position = fileName.find(".json")) != string::npos && position + 5 == fileName.size() && Exists(fileName)) {
        SetCompareType(2);
        return new JsnFile(fileName);
    }
    else {
        return NULL;
    }
}

Folder * GetFolder(const string & fileName) {
    if(Exists(fileName)) {
        return new Folder(fileName);
    }
    return NULL;
}

bool Exists(const string path) {
    ifstream ifs(path.c_str());
    return ifs.good();    
}

void SetCompareType(int type) {
    if(CompareType == -1) {
        CompareType = type;
        return;
    }

    if(CompareType == type) {
        return;
    } 

    DifferentTypes = true;
}