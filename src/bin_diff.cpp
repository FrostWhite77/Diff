#include "bin_diff.hpp"

BinDiff::BinDiff(std::string firstFile, std::string secondFile) : _first(firstFile), _second(secondFile) {

}

BinDiff::BinDiff(const BinDiff & src) {
    if(&src == this);

    _first = src._first;
    _second = src._second;
}

BinDiff::~BinDiff() {

}

bool BinDiff::Compare() {
    return true;
}   

std::ostream & operator<<(std::ostream & os, const BinDiff & src) {
    os << "--Binary Diff--" << std::endl;
    os << "File 1: " << src._first << std::endl;
    os << "File 2: " << src._second;

    return os;
}