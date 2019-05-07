#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"
#include "folder.hpp"

using namespace std;

File * GetFile(const string & fileName);
Folder * GetFolder(const string & fileName);
bool Exists(const string path);

bool charCmp(char x, char y) {
    return toupper(x) == toupper(y); 
}

int main() {
    
    TxtDiff td(TxtFile("data/txt/sensitivity1.txt"), TxtFile("data/txt/sensitivity2.txt"));
    
    cout << td << endl;
    
    cout << "Are files equal (case insensitive): " << boolalpha << td.Compare(charCmp).GetResult() << endl;
    cout << "Are files equal (case   sensitive): " << boolalpha << td.Compare().GetResult() << endl;

    //cout << endl;

    /*

    TxtDiff td(TxtFile("data/file1.txt"), TxtFile("data/file2.txt"));
    cout << td << endl;
    cout << "Are files equal: " << boolalpha << td.Compare().GetResult() << endl;
    
    cout << endl;

    bd.SetFirst(TxtFile("data/file1.txt"));
    bd.SetSecond(BinFile("data/file2.bin"));

    cout << bd << endl;
    cout << "Are files equal: " << boolalpha << bd.Compare().GetResult() << endl;

    cout << endl;

    td.SetSecond(BinFile("data/file2.bin"));

    cout << td << endl;
    cout << "Are files equal: " << boolalpha << td.Compare().GetResult() << endl;

    cout << endl;

    td.SetFirst(BinFile("data/file2.bin"));
    td.SetSecond(TxtFile("data/file2.txt"));

    cout << td << endl;
    cout << "Are files equal: " << boolalpha << td.Compare().GetResult() << endl;

    cout << endl << "Folder Class: GetFilesInFolder() Test: " << endl;

    Folder fld("./data");
    auto fls = fld.GetFilesInFolder();
    for(const auto & f : fls) {
        cout << f << endl;
    }

    cout << endl;

    TxtDiff td2(TxtFile("data/file1.txt"), TxtFile("data/file2.txt"));
    cout << td2 << endl;
    Result cmpResult = td2.Compare();
    cout << "Are files equal: " << boolalpha << cmpResult.GetResult() << endl;
    
    cout << "unique in X: ";
    auto charsx = cmpResult.GetUniqueXChars();
    for(size_t i = 0; i < charsx.size(); i++) cout << charsx[i];
    cout << endl;

    cout << "unique in Y: ";
    auto charsy = cmpResult.GetUniqueYChars();
    for(size_t i = 0; i < charsy.size(); i++) cout << charsy[i];
    cout << endl;
    
    Folder f1("./data/bin");
    Folder f2("./data/bin");

    f1.CompareFolders(f2, bd);

    TxtDiff tdf (TxtFile("./data/txt/lorem1.txt"), TxtFile("./data/txt/lorem2.txt"));
    Result res = tdf.Compare();

    auto x = res.GetUniqueXLines();
    auto y = res.GetUniqueYLines();

    cout << "x: " << endl;
    for(size_t i = 0; i < x.size(); i++) {
        cout << x[i] << endl;
    }

    cout << "y: " << endl;
    for(size_t i = 0; i < y.size(); i++) {
        cout << y[i] << endl;
    }
    */

    return 0;
}

File * GetFile(const string & fileName) {
    // is binary file
    size_t position = 0;
    if((position = fileName.find(".bin")) != string::npos && position + 4 == fileName.size() && Exists(fileName)) {
        return new BinFile(fileName);
    }
    // is text file
    else if((position = fileName.find(".txt")) != string::npos && position + 4 == fileName.size() && Exists(fileName)) {
        return new TxtFile(fileName);
    }
    // is json file
    else if((position = fileName.find(".json")) != string::npos && position + 5 == fileName.size() && Exists(fileName)) {
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
