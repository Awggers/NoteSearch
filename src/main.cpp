#include <iostream>
#include <string>

#include "Indexer.h"
#include "SearchEngine.h"

using namespace std; // clean up code in this section

/*
Main loop purpose
- Ask user for directory to be indexed
- Attempt to auto-detect a directory if necessary <- this will come later
- Build inverted index
- Allow repeate searches until exit
*/

int main(){
    Indexer indexer;

    // Ask user for folder path to notes
    string folderPath;
    cout << "Enter directory path to index (example: data): " /*<< "Leave blank to auto-detect: "*/;
    getline(cin, folderPath);

    cout << "Building index ... \n";
    indexer.buildIndex(folderPath);

    // Retrieve completed index and display stats
    const auto& index = indexer.getIndex();
    cout << "Index built. Unique terms: " << index.size() << "\n";

    // Create search engine using built index
    SearchEngine engine(index);

    string query;

    // Command loop
    while (true) {
        cout << "\nSearch>";
        getline(cin, query);

        // Exit option
        if (query == "exit" || query == "quit") {
            cout << "Goodbye! \n";
            break;
        }

        // Perform lookup
        auto results = engine.search(query);

        if (results.empty()) {
            cout << "No results found.\n";
        } else {
            cout << "Found in " << results.size() << " file(s):\n";

            for (const auto& result : results) {
                const string& path = result.first;
                int score = result.second;
                cout << " - " << path << "  (score: " << score << ")\n";
                
                // initially implement calling on private classes, modified to use different public call
                string snippet = engine.getSnippet(path, query);
                if (!snippet.empty()){
                    cout << "  " << snippet << "\n";
                }
            }
        }
    }

    
    return 0;
}