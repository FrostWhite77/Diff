#pragma once

#include <sys/stat.h>
#include <string>
#include <fstream>

namespace IO {
    /*
     * Fuction which checks if the path is a valid IO object
     * @param[in] filePath: path of the IO object
     * @return true if is valid, otherwise false
     */ 
    bool Exists(const std::string filePath);
    
    /*
     * Fuction which checks if the path is a valid file
     * @param[in] filePath: path of the file
     * @return true if is existing file, otherwise false
     */ 
    bool IsFile(const std::string filePath);

    /*
     * Fuction which recognize filetype by its extension
     * @param[in] filePath: path of the file
     * @return 0 for binary file(.bin), 1 for text file (.txt), 2 for JSON file (.jsn), otherwise -1
     */ 
    int GetFileType(const std::string & filePath);
   
    /*
     * Fuction which checks if the path is a valid dir
     * @param[in] filePath: path of the dir
     * @return true if is existing dir, otherwise false
     */ 
    bool IsDir(const std::string filePath);
}