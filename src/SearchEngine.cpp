#include "SearchEngine.h"
#include <cctype>

// Reference to built index no copy necessary

SearchEngine::SearchEngine(const Index& idx) : index(idx){}

/* 
Search for a word - is case sensitive
Return a vector of file paths where the word occurs
*/

std::vector<std::string> SearchEngine::search(const std::string& word) const {
    std::string normalized;
    normalized.reserve(word.size());

    // Normalize to keep only numbers and letters then lowercase them
    for (char c: word) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (std::isalnum(uc)) {
            normalized += static_cast<char>(std::tolower(uc));
        }
    }

    //No valid entry
    if (normalized.empty()) {
        return{};
    }

    // Look up word in index
    auto it = index.find(normalized);
    if (it != index.end()) {
        return it->second;
    }

    return {};
}