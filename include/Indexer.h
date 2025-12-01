#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <unordered_map>
#include <vector>

class Indexer {
public:
    using Index = std::unordered_map<std::string, std::vector<std::string>>;

    Indexer() = default;

    void buildIndex(const std::string& directoryPath);
    const Index& getIndex() const { 
        return index; 
    }

private:
    Index index;

    void processFile(const std::string& filePath);
    std::vector<std::string> tokenize(const std::string& text);
};

#endif