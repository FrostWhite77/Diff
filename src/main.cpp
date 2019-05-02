#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"
#include "folder.hpp"

using namespace std;

int main() {
    BinDiff bd(BinFile("data/file1.bin"), BinFile("data/file2.bin"));
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
    fld.GetFilesInFolder();

    return 0;
}