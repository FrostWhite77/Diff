class Settings {
    public:
        Settings(bool caseSensitive = false, bool ignoreWhitespaces = false);
        Settings(const Settings & src);
        ~Settings();

        Settings * Clone() const;

        bool CaseSensitive() const;
        bool IgnoreWhitespaces() const;

    private:
        bool _caseSensitive;
        bool _ignoreWhitespaces;
};