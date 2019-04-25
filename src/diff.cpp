#include "diff.hpp"

// Diff
Diff::Diff(std::string firstFile, std::string secondFile) : _first(firstFile), _second(secondFile) {

}

Diff::Diff(const Diff & src) : _first(src._first), _second(src._second) {
    if(&src == this) return;
}

Diff::~Diff() {

}

bool Diff::Compare() {
    return true;
}

Diff & Diff::operator=(const Diff & src) {
    if(&src == this) return *this;

    _first = File(src._first);
    _second = File(src._second);

    return *this;
}

std::ostream & operator<<(std::ostream & os, const Diff & src) {
    os << "--General Diff--" << std::endl;
    os << "File 1: " << src._first << std::endl;
    os << "File 2: " << src._second;

    return os;
}

// Binary Diff
BinDiff::BinDiff(std::string firstFile, std::string secondFile) : Diff(firstFile, secondFile) {

}

BinDiff::BinDiff(const BinDiff & src) : Diff(src)  {
    if(&src == this);
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

// Txt Diff
TxtDiff::TxtDiff(std::string firstFile, std::string secondFile) : Diff(firstFile, secondFile) {

}

TxtDiff::TxtDiff(const TxtDiff & src) :Diff(src)  {
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

// Json Diff
JsnDiff::JsnDiff(std::string firstFile, std::string secondFile) : Diff(firstFile, secondFile)  {

}

JsnDiff::JsnDiff(const JsnDiff & src) : Diff(src) {
    if(&src == this) return;
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