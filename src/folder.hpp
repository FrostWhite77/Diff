#pragma once

#include "diff.hpp"
#include "io.hpp"

#include <vector>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <algorithm>

/*
 * Folder
 */ 
class Folder {
    public:
        /*
         * Constructor
         * @param[in] folderName: string path to the folder
         */
        Folder(std::string folderName = "./");

        /*
         * Copy Constructor
         * @param[in] src: source instance of Folder
         */ 
        Folder(const Folder & src);

        /*
         * Destructor
         */ 
        ~Folder();

        /*
         * Method to load all files in the folder (. and .. are ignored)
         * @return vector of pointers to File instances (each represents one file)
         */ 
        std::vector<File *> GetFilesInFolder();

        /*
         * Comparation method - compares content of both folders
         * Finds unique files in both of them, if both equals file with same name and extension, files are compared
         * @param[in] f: pointer to the folder to be compared with
         * @return instance of FolderResult with results
         */ 
        Result * CompareFolders(Folder * f);
        
        /*
         * Comparation method - looks for file in folder, if found, files are compared
         * @param[in] f: pointer to the file to be searchod for
         * @return instance of FileFolderResult with results
         */ 
        Result * CompareWithFile(File * f);

        /*
         * Method to find file (filename.extension) 
         * @param[in] file: string filename (filename.extension)
         * @return pointer to the file in folder if found, if not found returns NULL
         */ 
        File * IsInFolder(const std::string & file) const;

    private:
        /*
         * String path to the folder
         */ 
        std::string _folderName;

        /*
         * Vector of files in the folder
         * 
         */ 
        std::vector<File *> _files;
};

/*
 * Function which check if path is folder and creates instance of Folder
 * @param[in] filePath: string filepath
 * @return if filepath is folder returns pointer to the Folder instance, otherwise NULL 
 */ 
Folder * CreateFolder(const std::string & filePath);