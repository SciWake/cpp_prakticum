#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
// #include <utility>
#include <vector>


#include "document.h"
#include "search_server.h"
#include "string_processing.h"

using namespace std;

// string ReadLine() {
//     string s;
//     getline(cin, s);
//     return s;
// }

// int ReadLineWithNumber() {
//     int result;
//     cin >> result;
//     ReadLine();
//     return result;
// }


// ostream& operator<<(ostream& out, const Document& document) {
//     out << "{ "s
//         << "document_id = "s << document.id << ", "s
//         << "relevance = "s << document.relevance << ", "s
//         << "rating = "s << document.rating << " }"s;
//     return out;
// }




// void PrintDocument(const Document& document) {
//     cout << "{ "s
//          << "document_id = "s << document.id << ", "s
//          << "relevance = "s << document.relevance << ", "s
//          << "rating = "s << document.rating << " }"s << endl;
// }

// void PrintMatchDocumentResult(int document_id, const vector<string>& words, DocumentStatus status) {
//     cout << "{ "s
//          << "document_id = "s << document_id << ", "s
//          << "status = "s << static_cast<int>(status) << ", "s
//          << "words ="s;
//     for (const string& word : words) {
//         cout << ' ' << word;
//     }
//     cout << "}"s << endl;
// }

// void AddDocument(SearchServer& search_server, int document_id, const string& document, DocumentStatus status,
//                  const vector<int>& ratings) {
//     try {
//         search_server.AddDocument(document_id, document, status, ratings);
//     } catch (const invalid_argument& e) {
//         cout << "Ошибка добавления документа "s << document_id << ": "s << e.what() << endl;
//     }
// }

// void FindTopDocuments(const SearchServer& search_server, const string& raw_query) {
//     cout << "Результаты поиска по запросу: "s << raw_query << endl;
//     try {
//         for (const Document& document : search_server.FindTopDocuments(raw_query)) {
//             PrintDocument(document);
//         }
//     } catch (const invalid_argument& e) {
//         cout << "Ошибка поиска: "s << e.what() << endl;
//     }
// }

// void MatchDocuments(const SearchServer& search_server, const string& query) {
//     try {
//         cout << "Матчинг документов по запросу: "s << query << endl;
//         const int document_count = search_server.GetDocumentCount();
//         for (int index = 0; index < document_count; ++index) {
//             const int document_id = search_server.GetDocumentId(index);
//             const auto [words, status] = search_server.MatchDocument(query, document_id);
//             PrintMatchDocumentResult(document_id, words, status);
//         }
//     } catch (const invalid_argument& e) {
//         cout << "Ошибка матчинга документов на запрос "s << query << ": "s << e.what() << endl;
//     }
// }

// template <typename Iterator>
// class IteratorRange {
// public:
//     IteratorRange(Iterator begin, Iterator end)
//         : first_(begin)
//         , last_(end)
//         , size_(distance(first_, last_)) {
//     }

//     Iterator begin() const {
//         return first_;
//     }

//     Iterator end() const {
//         return last_;
//     }

//     size_t size() const {
//         return size_;
//     }

// private:
//     Iterator first_, last_;
//     size_t size_;
// };

// template <typename Iterator>
// ostream& operator<<(ostream& out, const IteratorRange<Iterator>& range) {
//     for (Iterator it = range.begin(); it != range.end(); ++it) {
//         out << *it;
//     }
//     return out;
// }

// template <typename Iterator>
// class Paginator {
// public:
//     Paginator(Iterator begin, Iterator end, size_t page_size) {
//         for (size_t left = distance(begin, end); left > 0;) {
//             const size_t current_page_size = min(page_size, left);
//             const Iterator current_page_end = next(begin, current_page_size);
//             pages_.push_back({begin, current_page_end});

//             left -= current_page_size;
//             begin = current_page_end;
//         }
//     }

//     auto begin() const {
//         return pages_.begin();
//     }

//     auto end() const {
//         return pages_.end();
//     }

//     size_t size() const {
//         return pages_.size();
//     }

// private:
//     vector<IteratorRange<Iterator>> pages_;
// };

// template <typename Container>
// auto Paginate(const Container& c, size_t page_size) {
//     return Paginator(begin(c), end(c), page_size);
// }


class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server)
        : search_server_(search_server)
        , no_results_requests_(0)
        , current_time_(0) {
    }
    // сделаем "обертки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
        const auto result = search_server_.FindTopDocuments(raw_query, document_predicate);
        AddRequest(result.size());
        return result;
    }

    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status) {
        const auto result = search_server_.FindTopDocuments(raw_query, status);
        AddRequest(result.size());
        return result;
    }

    vector<Document> AddFindRequest(const string& raw_query) {
        const auto result = search_server_.FindTopDocuments(raw_query);
        AddRequest(result.size());
        return result;
    }

    int GetNoResultRequests() const {
        return no_results_requests_;
    }

private:
    struct QueryResult {
        uint64_t timestamp;
        int results;
    };
    deque<QueryResult> requests_;
    const SearchServer& search_server_;
    int no_results_requests_;
    uint64_t current_time_;
    const static int min_in_day_ = 1440;

    void AddRequest(int results_num) {
        // новый запрос - новая секунда
        ++current_time_;
        // удаляем все результаты поиска, которые устарели
        while (!requests_.empty() && min_in_day_ <= current_time_ - requests_.front().timestamp) {
            if (0 == requests_.front().results) {
                --no_results_requests_;
            }
            requests_.pop_front();
        }
        // сохраняем новый результат поиска
        requests_.push_back({current_time_, results_num});
        if (0 == results_num) {
            ++no_results_requests_;
        }
    }
};


// ==================== для примера =========================
int main() {
    SearchServer search_server("and in at"s);
    RequestQueue request_queue(search_server);

    search_server.AddDocument(1, "curly cat curly tail"s, DocumentStatus::ACTUAL, {7, 2, 7});
    search_server.AddDocument(2, "curly dog and fancy collar"s, DocumentStatus::ACTUAL, {1, 2, 3});
    search_server.AddDocument(3, "big cat fancy collar "s, DocumentStatus::ACTUAL, {1, 2, 8});
    search_server.AddDocument(4, "big dog sparrow Eugene"s, DocumentStatus::ACTUAL, {1, 3, 2});
    search_server.AddDocument(5, "big dog sparrow Vasiliy"s, DocumentStatus::ACTUAL, {1, 1, 1});
    
    // 1439 запросов с нулевым результатом
    for (int i = 0; i < 1439; ++i) {
        request_queue.AddFindRequest("empty request"s);
    }
    // все еще 1439 запросов с нулевым результатом
    request_queue.AddFindRequest("curly dog"s);
    // новые сутки, первый запрос удален, 1438 запросов с нулевым результатом
    request_queue.AddFindRequest("big collar"s);
    // первый запрос удален, 1437 запросов с нулевым результатом
    request_queue.AddFindRequest("sparrow"s);
    cout << "Total empty requests: "s << request_queue.GetNoResultRequests() << endl;
}
