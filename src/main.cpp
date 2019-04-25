#include <iostream>
#include <sstream>
#include <cassert>

#include "diff.hpp"

using namespace std;

int main() { 
    //#include "tests.cpp"
    
    BinFile * bf1 = new BinFile("data/file.txt");
    BinFile * bf2 = new BinFile("data/list.txt");
    
    Diff * d = new Diff(bf1, bf2);
    std::cout << *d << endl;
    d->Compare().Print(std::cout);
    
    delete d;
    
    return 0;
}