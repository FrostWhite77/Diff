#include "settings.hpp"

Settings::Settings(bool caseSensitive, bool ignoreWhitespaces) : _caseSensitive(caseSensitive), _ignoreWhitespaces(ignoreWhitespaces) {

}

Settings::Settings(const Settings & src) {
    if(&src == this) return;

    _caseSensitive = src._caseSensitive;
    _ignoreWhitespaces = src._ignoreWhitespaces;
}

Settings::~Settings() {

}

Settings * Settings::Clone() const {
    return new Settings(*this);
}

bool Settings::CaseSensitive() const {
    return _caseSensitive;
}

bool Settings::IgnoreWhitespaces() const {
    return _ignoreWhitespaces;
}