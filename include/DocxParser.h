#ifndef DOCXPARSER_H
#define DOCXPARSER_H

#include <string>

/*
DocxParser utility
Extracts raw text content from docx files.
Unzip with miniz and parse the XML with pugixml.
Returns plain std::string with extracted text for tokenization.
*/

std::string extractTextFromDocx(const std:: string& filePath);

#endif