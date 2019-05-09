#pragma once

#include <sys/stat.h>
#include <string>
#include <fstream>

namespace IO {
    bool Exists(const std::string filePath);
    bool IsFile(const std::string filePath);
    int GetFileType(const std::string & filePath);
    bool IsDir(const std::string filePath);
}