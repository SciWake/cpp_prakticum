#include <vector>
#include <algorithm>

struct Document {
    int id;
    int relevance;
};

// Функция-компаратор для сортировки по убыванию релевантности
bool HasDocumentGreaterRelevance(const Document& lhs, const Document& rhs) {
    return lhs.relevance > rhs.relevance;
}

int main() {
    std::vector<Document> documents = {
        {100, 5},
        {101, 8},
        {102, 3}
    };

    std::sort(documents.begin(), documents.end(), HasDocumentGreaterRelevance);

    // Теперь документы отсортированы по убыванию relevance: 8, 5, 3
}
