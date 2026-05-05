#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <cctype>

/*
Tokenization utility.
Convert raw text into lowercase alphanumeric word tokens.
Non-alphanumeric characters act as word boundaries.
Used by Indexer and SearchEngine to ensure consistency.
*/

inline std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string current;

    for (char c : text) {
        unsigned char uc = static_cast<unsigned char>(c);

        // Build current wrod from alphanumeric characters
        if (std::isalnum(uc)) {
            current += static_cast<char>(std::tolower(uc));
        }

        // End of word -- push and reset
        else if (!current.empty()) {
            tokens.push_back(current);
            current.clear();
        }
    }

    // Add last word if file doesn't end with delimiter
    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}

#endif