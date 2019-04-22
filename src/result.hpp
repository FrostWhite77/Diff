#include <sstream>
#include <vector>

class Result {
    public:
        Result(const std::string & fileNameX, const std::string & fileNameY, bool comparationResult = false);
        Result(const Result & src);
        ~Result();

        Result * Clone() const;
        void Set(const Result & src);

        bool GetResult() const;
        void SetResult(bool result);

        void AddToXBytes(uint8_t byte);
        void AddToYBytes(uint8_t byte);

        size_t GetXBytesSize() const;
        size_t GetYBytesSize() const;

        std::ostream & Print(std::ostream & os);
    
    private:
        std::string _fileNameX;
        std::string _fileNameY;

        bool _comparationResult;

        std::vector<uint8_t> _fileXBytes;
        std::vector<uint8_t> _fileYBytes;
};