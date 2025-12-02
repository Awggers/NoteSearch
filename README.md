# NoteSearch
Tool to search for keywords inside of notes based on frequency of occurence.

# Overview
This project uses C++ to create a Note Searcher that indexes the contents of text files in a directory and allows for fast keyword search across them.
The base of this program uses an inverted index, which is used for information retrieval to map words to the documents they appear in.
The goal is to create a fast and personal search tool that assists in locating specific terms inside a growing set of notes without having to manually
search through each file.

# Data Structure Implemented
The main structure of the project is an inverted index, as previously stated. This stores the words as keys and a list of documents where those words appear.
Some search results would look like the following example below.

Example:

"algorithm" -> [notes1.txt, lecture2.md, coding_sample.txt]

"project" -> [notes1.txt, ProjectIdeas.txt, final_version.md]

An inverted index reverses the relationship between documents and texts. This means that instead of storing documents and reading them to find a mtach, the program 
builds a lookup table where each word points to the files that contain it. Once the index is created, searching becomes quick and efficient even as the number of files grows.
During indexing, text is tokenized, converted to lowercase, and punctuation removed. 
The results can be displayed in various ways, but my implementation will be ranked by word frequency.


# How To Run

# Example
