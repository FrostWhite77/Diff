#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"
#include "folder.hpp"

using namespace std;

int main() {
    
    BinDiff bd(BinFile("data/file1.bin"), BinFile("data/file2.bin"));
    
    /*
    cout << bd << endl;
    cout << "Are files equal: " << boolalpha << bd.Compare().GetResult() << endl;

    cout << endl;

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
    */

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


    return 0;
}