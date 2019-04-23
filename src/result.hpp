#include <sstream>
#include <vector>

class Result {
    public:
        Result(const std::string & fileNameX, const std::string & fileNameY, const std::vector<uint8_t> & bx, const std::vector<uint8_t> & by, bool comparationResult = false);
        Result(const Result & src);
        ~Result();

        Result * Clone() const;
        void Set(const Result & src);

        bool GetResult() const;

        void AddToXBytes(uint8_t byte);
        void AddToYBytes(uint8_t byte);

        size_t GetXBytesSize() const;
        size_t GetYBytesSize() const;

        std::ostream & Print(std::ostream & os);
        std::ostream & PrintDiffer(std::ostream & os, const std::string & first, const std::string & second, const std::vector<uint8_t> & differs);

    private:
        std::string _fileNameX;
        std::string _fileNameY;

        bool _comparationResult;

        std::vector<uint8_t> _fileXBytes;
        std::vector<uint8_t> _fileYBytes;
};