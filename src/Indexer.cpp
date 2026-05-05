#include "Indexer.h"
#include "Tokenizer.h"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

// Scans directory provided by user and process .txt files

void Indexer::buildIndex(const std::string& directoryPath){
    index.clear();

    // try-catch method used for future capturing future exceptions and catching 
    try{
        //Check if directory exists
        if (!fs::exists(directoryPath)){
            std::cerr << "Directory does not exist: " << directoryPath << "\n";
            return;
        }

        if (!fs::is_directory(directoryPath)){
            std::cerr << "Path is not a directory: " << directoryPath << "\n";
            return;
        }
        
        // Loop through files in directory
        for (const auto& entry : fs::directory_iterator(directoryPath)){

            if (!entry.is_regular_file()){
                continue;
            }

            //Get file extension as a string
            std::string ext = entry.path().extension().string();

            // Process regular .txt files
            if (ext == ".txt" || ext == ".md"){
                processFile(entry.path().string());
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error while indexing directory: " << e.what() << "\n";
        }
}


    // Read file contents and updates index with extracted words

void Indexer::processFile(const std::string& filePath){
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filePath << "\n";
        return;
    }

    // Read full contents into a string
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    //Tokenize into lowercase words
    std::vector<std::string> words = tokenize(content);

    // Store words in the index
    for (const auto& word : words){
        index[word][filePath] += 1;
    }
}