#include "txt_diff.hpp"

TxtDiff::TxtDiff(std::string firstFile, std::string secondFile) : _first(firstFile), _second(secondFile) {

}

TxtDiff::TxtDiff(const TxtDiff & src) :_first(src._first), _second(src._second) {
    if(&src == this);
}

TxtDiff::~TxtDiff() {

}

bool TxtDiff::Compare() {
    return true;
}   

std::ostream & operator<<(std::ostream & os, const TxtDiff & src) {
    os << "--Txt Diff--" << std::endl;
    os << "File 1: " << src._first << std::endl;
    os << "File 2: " << src._second;

    return os;
}