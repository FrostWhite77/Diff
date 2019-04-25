#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"

using namespace std;

int main() { 
    BinDiff bd("data/file.bin", "data/file.bin");
    cout << bd << endl;

    cout << endl;

    TxtDiff td("data/file.txt", "data/file.txt");
    cout << td << endl;

    cout << endl;

    JsnDiff jd("data/file.txt", "data/file.txt");
    cout << jd << endl;
    
    return 0;
}