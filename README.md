# NoteSearch
A C++ tool to search for keywords inside of notes based on frequency of occurence. This tool searches through text and markdown notes. Capable of fast keyword searching across mutliple files using inverted index.

# Overview
This project uses C++ to create a Note Searcher that indexes the contents of text files in a directory and allows for fast keyword search across them.
The base of this program uses an inverted index, which is used for information retrieval to map words to the documents they appear in.
The goal is to create a fast and personal search tool that assists in locating specific terms inside a growing set of notes without having to manually
search through each file.

The main structure of the project is an inverted index. An inverted index is a data structure that is used in information retrieval systems. This maps unique words as keys and a list of documents where those words appear.
Some search results would look like the following example below.

Example:

"algorithm" -> [notes1.txt, lecture2.md, coding_sample.txt]

"project" -> [notes1.txt, ProjectIdeas.txt, final_version.md]

# Data Structure Implemented

The inverted index processes each file in a directory, splits the text into words, converts them to lowercase, and removes the punctuation. Each word then becomes a key inside an unordered_map, that value is stored in another unordered_map that keeps track of paths and frequency counts.

Search Process:

- Tokenize the query
- Looks up each word in the inverted index
- Applies AND logic for multi-word searches
- Adds word frequencies together to determine relevance score
- Sorts results by score (Highest to Lowest)
- Extracts a small snippet for preview

Index supports exact and partial matching. An example would be a query for 'tree' would return matches to 'trees' and 'subtree' as well. This is in case the user does not know the full word they are searching.

# How To Run

This project can be ran directly in the github codespace

Build Instructions:
- git clone <repo_link_here>
- cd NoteSearch
- mkdir build
- cd build
- cmake ..
- cmake --build .

Run the program:
- ./notesearch

Usage:
1. When prompted, enter the directory you want to index. Follow the exact example below:
- Enter directory path to index: ../test_docs

2. Enter any keyword or multi-word phrase in the prompt:
- Search> binary tree

3. Type 'exit' to quit

# Example Output

![Preview of a search](image-1.png)

Results are sorted by score that shows how often the query terms appeared in each file. This snippet provides a preview of where the word occurs in the file.