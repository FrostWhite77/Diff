#include "jsn_diff.hpp"

JsnDiff::JsnDiff(std::string firstFile, std::string secondFile) : _first(firstFile), _second(secondFile) {

}

JsnDiff::JsnDiff(const JsnDiff & src) {
    if(&src == this);

    _first = src._first;
    _second = src._second;
}

JsnDiff::~JsnDiff() {

}

bool JsnDiff::Compare() {
    return true;
}   

std::ostream & operator<<(std::ostream & os, const JsnDiff & src) {
    os << "--JSON Diff--" << std::endl;
    os << "File 1: " << src._first << std::endl;
    os << "File 2: " << src._second;

    return os;
}