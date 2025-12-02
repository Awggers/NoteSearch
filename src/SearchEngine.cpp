#include "SearchEngine.h"

#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

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

std::unordered_map<std::string, int> SearchEngine::getFilesForTerm(const std::string& term) const {

    std::unordered_map<std::string, int> result;

    // Try exact match first
    auto it = index.find(term);
    if (it != index.end()) {

        result = it->second;
        return result;
    }

    // Exact match does not exist: fall back to partial
    for (const auto& kv : index) {
        const std::string& word = kv.first;
        const std::unordered_map<std::string, int>& fileFreqs = kv.second;

        if (word.find(term) != std::string::npos) { // substring match
            for (const auto& fileCountPair : fileFreqs){
                const std::string& filePath = fileCountPair.first;
                int count = fileCountPair.second;
                result[filePath] += count;
            }
        }
    }

    return result;
}


/* 
Search for a word(s) - is case sensitive
- one word search behaves as simple lookup
- multi-word search acts as an AND search. Returns only files that contain all words
- total score = sum of frequencies across all terms. Results are highest to lowest
*/

std::vector<std::string> SearchEngine::search(const std::string& query) const {
    
    // Break the query into lowercase words
    std::vector<std::string> words = tokenize(query);

    if (words.empty()) {
        return {};
    }
    // filePath map is total score:
    std::unordered_map<std::string, int> totalScores;
    
    // filePath map of how many terms the file matched
    std::unordered_map<std::string, int> termMatchCounts;

    int numTerms = static_cast<int>(words.size());

    for (const auto& w : words){
        // Each term, get files and term specific frequencies
        std::unordered_map<std::string, int> filesForTerm = getFilesForTerm(w);

        // If a term has no match, no results returned
        if (filesForTerm.empty()){
            return {};
        }

        for (const auto& fileCountPair : filesForTerm){
            const std::string& filePath = fileCountPair.first;
            int count = fileCountPair.second;

            totalScores[filePath] += count;
            termMatchCounts[filePath] += 1;
        }
    }

    // Files that matched ALL terms
    std::vector<std::pair<std::string, int>> ranked;
    ranked.reserve(totalScores.size());

    for (const auto& scorePair : totalScores){
        const std::string& filePath = scorePair.first;
        int score = scorePair.second;

        auto it = termMatchCounts.find(filePath);
        if (it != termMatchCounts.end() && it->second == numTerms){
            ranked.emplace_back(filePath, score);
        }
    }

    if (ranked.empty()){
        return {};
    }

    // Sort score by descending and tie breaks by filePath alphabetically
    std::sort(ranked.begin(), ranked.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second != b.second){
            return a.second > b.second; // highest score first
        }
        return a.first < b.first; // alphabetical tie-breaker
    });

    std::vector<std::string> results;
    results.reserve(ranked.size());
    for (const auto& p : ranked){
        results.push_back(p.first);
    }

    return results;
}