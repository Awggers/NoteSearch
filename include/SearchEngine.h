#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <unordered_map>
#include <vector>

/*
Class purpose:
queries inverted index that is created by Indexer.
Allows searching for a single word and returns file paths.

This will be expanded:
*/


class SearchEngine{
public:
    using Index = std::unordered_map<std::string, std::vector<std::string>>;

    explicit SearchEngine(const Index& idx);

    //Single word search
    std::vector<std::string> search(const std::string& word) const;

private:
    const Index& index;

};

#endif