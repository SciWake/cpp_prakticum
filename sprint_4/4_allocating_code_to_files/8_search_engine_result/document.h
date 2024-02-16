#pragma once

#include <fstream>
#include <vector>
// #include "search_server.h"

const int MAX_RESULT_DOCUMENT_COUNT = 5;
struct Document {
    Document() = default;
    Document(int id, double relevance, int rating);

    int id = 0;
    double relevance = 0.0;
    int rating = 0;
};
enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};
std::ostream& operator<<(std::ostream& out, const Document& document);
void PrintDocument(const Document& document); // Unused
void PrintMatchDocumentResult(int document_id, const std::vector<std::string>& words, DocumentStatus status); // Unused