#include <sstream>

class Result {
    public:
        Result(bool comparationResult = false);

        bool GetResult() const;

        std::ostream & Print(std::ostream & os);
    
    private:
        bool _comparationResult;
};