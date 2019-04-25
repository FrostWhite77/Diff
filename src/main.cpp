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

    BinDiff bd2(TxtFile("data/file1.txt"), BinFile("data/file2.bin"));
    cout << bd2 << endl;
    cout << "Are files equal: " << boolalpha << bd2.Compare() << endl;

    /*
    JsnDiff jd("data/file.txt", "data/file.txt");
    cout << jd << endl;
    */
    
    return 0;
}