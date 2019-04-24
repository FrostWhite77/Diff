#include <sstream>
#include <vector>

template<class T>
class Result {
    public:
        Result(const std::string & fileNameX, const std::string & fileNameY, const std::vector<T> & bx, const std::vector<T> & by, bool comparationResult = false);
        Result(const Result<T> & src);
        ~Result();

        Result * Clone() const;
        void Set(const Result & src);

        bool GetResult() const;

        void AddToXBytes(T byte);
        void AddToYBytes(T byte);

        size_t GetXBytesSize() const;
        size_t GetYBytesSize() const;

        std::ostream & Print(std::ostream & os);

    private:
        std::string _fileNameX;
        std::string _fileNameY;

        bool _comparationResult;

        std::vector<T> _fileXBytes;
        std::vector<T> _fileYBytes;

        std::ostream & PrintDiffer(std::ostream & os, const std::string & first, const std::string & second, const std::vector<T> & differs);
};