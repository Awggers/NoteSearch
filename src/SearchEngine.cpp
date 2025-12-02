#include "SearchEngine.h"
#include <cctype>
#include <unordered_map>
#include <unordered_set>


// Reference to built index no copy necessary

SearchEngine::SearchEngine(const Index& idx) : index(idx){}

std::vector<std::string> SearchEngine::tokenize(const std::string& text) const {
    std::vector<std::string> tokens;
    std::string current;

    for (char c : text) {
        unsigned char uc = static_cast<unsigned char>(c);

        if (std::isalnum(uc)) {
            current += static_cast<char>(std::tolower(uc));
        } else if (!current.empty()) {
            tokens.push_back(current);
            current.clear();
        }
    }

    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}


/*
Single term search:
- Try exact word match first
- If no exact match, fall back to substring against keys
    Example: 'table' will be matched to 'tables', 'hashtable' and so on.
*/


std::vector<std::string> SearchEngine::getFilesForTerm(const std::string& term) const {
    // Try exact match first
    auto it = index.find(term);
    if (it != index.end()) {
        return it->second;
    }

    // Exact match does not exist: fall back to partial
    std::vector<std::string> result;
    std::unordered_set<std::string> seenFiles;

    for (const auto& kv : index) {
        const std::string& word = kv.first;
        const std::vector<std::string>& files = kv.second;

        if (word.find(term) != std::string::npos) { // substring match
            for (const auto& file : files) {
                if (seenFiles.insert(file).second) {
                    result.push_back(file);
                }
            }
        }
    }

    return result;
}


/* 
Search for a word(s) - is case sensitive
- one word search behaves as simple lookup
- multi-word search acts as an AND search. Returns only files that contain all words
*/

std::vector<std::string> SearchEngine::search(const std::string& query) const {
    
    // Break the query into lowercase words
    std::vector<std::string> words = tokenize(query);

    if (words.empty()) {
        return {};
    }

    // Single-word search
    if (words.size() == 1) {
        return getFilesForTerm(words[0]);
    }

    // Multi-word AND search:
    // Count in how many query terms each file appears.
    std::unordered_map<std::string, int> fileCounts;
    int numTerms = static_cast<int>(words.size());

    for (const auto& w : words) {
        std::vector<std::string> filesForTerm = getFilesForTerm(w);

        // If a term matches nothing (exact or partial), no file can satisfy the whole query
        if (filesForTerm.empty()) {
            return {};
        }

        std::unordered_set<std::string> seenThisTerm;

        for (const auto& filePath : filesForTerm) {
            if (seenThisTerm.insert(filePath).second) {
                fileCounts[filePath] += 1;
            }
        }
    }

    // Only files that contain all query terms
    std::vector<std::string> results;
    results.reserve(fileCounts.size());

    for (const auto& kv : fileCounts) {
        const std::string& filePath = kv.first;
        int count = kv.second;

        if (count == numTerms) {
            results.push_back(filePath);
        }
    }

    return results;
}