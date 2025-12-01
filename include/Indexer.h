#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <unordered_map>
#include <vector>


/*
Class purpose:
- Scanning for text files in the directory
- Reading and extracting words from files
- Build of inverted index structure
    word -> [list of files with word]
*/
  
class Indexer {
public:
    // defines the word as a key and value is a list of paths
    using Index = std::unordered_map<std::string, std::vector<std::string>>;

    Indexer() = default;

    // Build index from given path, the access it
    void buildIndex(const std::string& directoryPath);
    const Index& getIndex() const { 
        return index; 
    }

private:
    Index index;

    void processFile(const std::string& filePath);
    
    // turns raw text into lowercase tokens 
    std::vector<std::string> tokenize(const std::string& text);
};

#endif