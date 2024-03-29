#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"
#include "folder.hpp"
#include "io.hpp"

using namespace std;

void FreeAll(vector<File *> fi, vector<Folder *> fo, Diff * d = NULL, Result * result = NULL);

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
bool verbose = false;

bool caseInsensitive = false;
bool ignoreWhitespace = false;

int main(int argc, char * argv[]) {       
        if(argc <= 2) {
        cout << "Invalid numb   er of arguments!" << endl << endl;

        cout << "Usage: ./diff <file/folder> <file/folder> [PARAMS]" << endl;
        cout << "Diff can determine type of comparison by file extensions (both files have to have same)," << endl
             << "if extensions are different, comparison type must be specified explicitly. Otherwise will program fail." << endl << endl
             << "If one arg is file and other one is folder, in folder is being searched file with same name and extension, if found" << endl
             << "compare will take place, otherwise false." << endl << endl
             << "During folder being compared with folder, same files are searched and compared, and unique files will be printed out." << endl << endl;
        cout << "Param List: " << endl;
        cout << "-v: verbose listing, when files are not same" << endl;
        cout << "-c: case insensitive comparation (effective only for text comparing)" << endl;
        cout << "-i: ignore whitespaces (effective only for text comparing)" << endl;
        cout << "-t=b: binary comparison" << endl;
        cout << "-t=t: text comparison" << endl;

        return 0;
    }

    vector<File *> files;
    vector<Folder *> folders;
    
    size_t i = 0;
    for(i = 1; i < (size_t)argc && i < 3; i++) {
        string current(argv[i]);
        
        File * file = CreateFile(current);
        if(file != NULL) {
            files.push_back(file);
            continue;
        }

        Folder * folder = CreateFolder(current);
        if(folder != NULL) {
            folders.push_back(folder);
            continue;
        }

        cout << "Error: Can't load " << argv[i] << ". Are you sure, it's a corrent path?" << endl;
        FreeAll(files, folders);
        return 1;   
    }

    for(i = i; i < (size_t)argc; i++) {
        string arg(argv[i]);
        if(arg == "-i") {
            //cout << "switched to case insenstivite comparison" << endl;
            ignoreWhitespace = true;
        }
        else if(arg == "-c") {
            //cout << "switched to case insenstivite comparison" << endl;
            caseInsensitive = true;
        }
        else if(arg == "-t=b") {
            CompareType = 0;
        }
        else if(arg == "-t=t") {
            CompareType = 1;
        }
        else if(arg == "-v") {
            verbose = true;
        }
        else {
            cout << "Invalid argument: " << argv[i] << ", possible arguments: -c: case insensitive, -i: ignore whitespace" << endl;
            FreeAll(files, folders);
            return 1;
        }
    }

    Diff * diff = NULL;
    Result * result = NULL;
    try {
        if(files.size() == 2)
        {
            diff = CreateDiff(files[0], files[1], CompareType);
            if(diff == NULL) {
                cout << "Files have different extension. Comparison type must be specifed explicitly." << endl;

                FreeAll(files, folders);
                return 1;
            }

            bool (*func)(const string &, const string &) = NULL;
            if(caseInsensitive && ignoreWhitespace) func = compareIgnCaseIns;
            else if(caseInsensitive) func = lineCmpIncase;
            else if(ignoreWhitespace) func = compareIgnored;

            result = diff->Compare(func); 
            result->Print(cout, verbose);
        }
        else if(files.size() == 1 && folders.size() == 1) {
            result = folders[0]->CompareWithFile(files[0]);
            result->Print(cout, verbose);
        }
        else if(folders.size() == 2) {
            result = folders[0]->CompareFolders(folders[1]);
            result->Print(cout, verbose);
        }

        FreeAll(files, folders, diff, result);
        return 0;
    }
    catch(const JSONFormatErrorException & err) {
        FreeAll(files, folders, diff, result);
        cout << err << "Exiting..." << endl;
        return 1;
    }    

    return 0;
}

void FreeAll(vector<File *> fi, vector<Folder *> fo, Diff * d, Result * result) {
    for(size_t i = 0; i < fi.size(); i++) {
        delete fi[i];
    }
    for(size_t i = 0; i < fo.size(); i++) {
        delete fo[i];
    }
    if(d != NULL) delete d;
    if(result != NULL) delete result;
}