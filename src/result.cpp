#include "result.hpp"

Result::Result(bool comparationResult) : _comparationResult(comparationResult) {
    
}

bool Result::GetResult() const {
    return _comparationResult;
}

std::ostream & Result::Print(std::ostream & os) {
    os << "Diff Result" << "\n";
    return os;
}