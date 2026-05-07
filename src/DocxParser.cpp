#include "DocxParser.h"
#include "miniz.h"
#include "pugixml.hpp"

#include <string>
#include <cstring>

/*
Extract text from .docx file.
Process:
1. Open .docx as a ZIP archive using miniz.
2. Locate and read word/document.xml from ZIP.
3. Parse XML with pugixml.
4. Traverse XML tree and extract all text node content.
5. Return as single std::string for tokenization.
*/

std::string extractTextFromDocx(const std::string& filePath) {
    std::string result;

    // Open the .docx ZIP archive
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));

    if (!mz_zip_reader_init_file(&zip, filePath.c_str(), 0)) {
        return "";
    }

    // Locate word/document.xml inside the archive
    int fileIndex = mz_zip_reader_locate_file(&zip, "word/document.xml", nullptr, 0);
    if (fileIndex < 0) {
        mz_zip_reader_end(&zip);
        return "";
    }

    // Read the XML file contents into memory
    size_t xmlSize = 0;
    void* xmlData = mz_zip_reader_extract_to_heap(&zip, fileIndex, &xmlSize, 0);

    if (!xmlData) {
        mz_zip_reader_end(&zip);
        return "";
    }

    // Parse XML with pugixml
    pugi::xml_document doc;
    pugi::xml_parse_result parseResult = doc.load_buffer(xmlData, xmlSize);

    mz_free(xmlData);
    mz_zip_reader_end(&zip);

    if (!parseResult) {
        return "";
    }

    // Walk all <w:t> nodes and collect text content
    for (const pugi::xpath_node& xnode : doc.select_nodes("//w:t")) {
        result += xnode.node().text().get();
        result += " ";
    }

    return result;
}