#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"

using namespace std;

int main() {

    BinDiff bd(BinFile("data/file1.bin"), BinFile("data/file2.bin"));
    cout << bd << endl;
    cout << "Are files equal: " << boolalpha << bd.Compare() << endl;

    cout << endl;

    TxtDiff td(TxtFile("data/file1.txt"), TxtFile("data/file2.txt"));
    cout << td << endl;
    cout << "Are files equal: " << boolalpha << td.Compare() << endl;
    
    cout << endl;

    bd.SetFirst(TxtFile("data/file1.txt"));
    bd.SetSecond(BinFile("data/file2.bin"));

    cout << bd << endl;
    cout << "Are files equal: " << boolalpha << bd.Compare() << endl;

    cout << endl;

    td.SetSecond(BinFile("data/file2.bin"));

    cout << td << endl;
    cout << "Are files equal: " << boolalpha << td.Compare() << endl;

    cout << endl;

    td.SetFirst(BinFile("data/file2.bin"));
    td.SetSecond(TxtFile("data/file2.txt"));

    cout << td << endl;
    cout << "Are files equal: " << boolalpha << td.Compare() << endl;

    return 0;
}