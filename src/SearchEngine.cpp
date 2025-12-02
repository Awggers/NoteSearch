#include "SearchEngine.h"
#include <cctype>
#include <unordered_map>
#include <unordered_set>


// Reference to built index no copy necessary

SearchEngine::SearchEngine(const Index& idx) : index(idx){}

std::vector<std::string> SearchEngine::tokenize(const std::string& text) const{
    std::vector<std::string> tokens;
    std::string current;

    for (char c : text) {
        unsigned char uc = static_cast<unsigned char>(c);

        if (std::isalnum(uc)){
            current += static_cast<char>(std::tolower(uc));
        } else if (!current.empty()){
            tokens.push_back(current);
            current.clear();
        }
    }

    if (!current.empty()){
        tokens.push_back(current);
    }
    
    return tokens;
}



/* 
Search for a word(s) - is case sensitive
- one word search behaves as simple lookup
- multi-word search acts as an AND search. Returns only files that contain all words
*/

std::vector<std::string> SearchEngine::search(const std::string& query) const{

    // Break query into clean lowercase words
    auto words = tokenize(query);

    if (words.empty()) {
        return {};
    }

    //Single word search
    if (words.size() == 1){
        const std::string& w = words[0];
        auto it = index.find(w);
        if (it != index.end()){
            return it->second;
        }
        return {};
    }

    // Multi word search and count how many files they appear in.

    std::unordered_map<std::string, int> fileCounts;

    int numTerms = static_cast<int>(words.size());

    for (const auto& w : words){
        auto it = index.find(w);
        if (it == index.end()){
            
            return {};
        }

        const auto& filesForWord = it->second;

        // Avoid counting same file twice for the same word
        std::unordered_set<std::string> seenThisWord;

        for (const auto& filePath : filesForWord){
            if (seenThisWord.insert(filePath).second){
                fileCounts[filePath] += 1;
            }
        }
    }

    // Only files that contain all query words
    std::vector<std::string> results;
    results.reserve(fileCounts.size());

    for (const auto& [filePath, count] : fileCounts){
        if (count == numTerms){
            results.push_back(filePath);
        }
    }

    return results;
}