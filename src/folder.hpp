#include <vector>
#include <sstream>

class Folder {
    public:
        Folder();
        Folder(const Folder & src);
        ~Folder();

        std::vector<std::string> GetFilesInFolder();

    private:
        std::string _folderName;
};