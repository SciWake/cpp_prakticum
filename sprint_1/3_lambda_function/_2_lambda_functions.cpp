// В вашей поисковой системе есть метод FindTopDocuments, 
// который сортирует документы по релевантности:
vector<Document> FindTopDocuments(const string& raw_query) const {
    const set<string> query_words = ParseQuery(raw_query);
    auto matched_documents = FindAllDocuments(query_words);

    // Сортируем документы по убыванию релевантности
    sort(matched_documents.begin(), matched_documents.end(), HasDocumentGreaterRelevance);

    if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
        matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
    }
    return matched_documents;
}

// Посмотрите на вызов сортировки. В нём вы использовали компаратор 
// HasDocumentGreaterRelevance. У этого компаратора довольно простое тело:
bool HasDocumentGreaterRelevance(const Document& lhs, const Document& rhs) {
    return lhs.relevance > rhs.relevance;
}


// Вот как можно переписать метод FindTopDocuments с лямбда-функцией в качестве компаратора:
vector<Document> FindTopDocuments(const string& raw_query) const {
    const set<string> query_words = ParseQuery(raw_query);
    auto matched_documents = FindAllDocuments(query_words);

    sort(matched_documents.begin(), matched_documents.end(),
        [](const Document& lhs, const Document& rhs) {  // Это лямбда-функция
            return lhs.relevance > rhs.relevance;
        });

    if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
        matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
    }
    return matched_documents;
}

// Впрочем, если нужно, тип возвращаемого значения можно указать явно:
sort(matched_documents.begin(), matched_documents.end(),
    [](const Document& lhs, const Document& rhs) -> bool { // указали тип результата явно
        return lhs.relevance > rhs.relevance;
    });

// Несмотря на то, что лямбда-функции удобны для создания «одноразовых» функций, 
// их можно использовать и многократно. Для этого им надо задать имя и вызывать как обычные функции:
int Test() {
    // Объявили лямбда-функцию quote
    auto quote = [](const string& s) {
        return '"' + s + '"';
    }; // Точка с запятой обязательна, как при объявлении переменной

    string movie1 = "Forrest Gump"s;
    string movie2 = "Green Mile"s;

    // Функцию quote можно вызвать несколько раз
    cout << "My favorite movies are "s << quote(movie1) << " and "s << quote(movie2) << endl;
    // Выведет: My favorite movies are "Forrest Gump" and "Green Mile"
}

// Так как лямбда-функция объявлена близко к месту её использования,
// ей можно дать короткое, но понятное имя
auto by_relevance = [](const Document& lhs, const Document& rhs) {
    return lhs.relevance > rhs.relevance;
};

// Сортируем документы от начала и до конца по релевантности
sort(matched_documents.begin(), matched_documents.end(), by_relevance);