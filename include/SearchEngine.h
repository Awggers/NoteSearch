#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <unordered_map>
#include <vector>

/*
Class purpose:
queries inverted index that is created by Indexer.
Allows searching for multiple word and returns file paths.
*/


class SearchEngine{
public:
    using Index = std::unordered_map<std::string, std::vector<std::string>>;

    explicit SearchEngine(const Index& idx);

    //Search for one or more words
    std::vector<std::string> search(const std::string& query) const;

private:
    const Index& index;
    
    // Split query string into lowercase word tokens

    std::vector<std::string> tokenize(const std::string& text) const;

    // The preference is exact matches but
    // if no exact match exists, return files for substrings instead
    std::vector<std::string> getFilesForTerm(const std::string& term) const;
};

#endif