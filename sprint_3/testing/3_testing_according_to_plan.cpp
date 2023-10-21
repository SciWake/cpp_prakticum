#include <iostream>
#include <string>

using namespace std;

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные буквы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, - это не палиндромы
string removeSpaces(const string& str) {
    string result;
    for (char c : str) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}


bool IsPalindrome(const string& text) {
    // Напишите недостающий код
    string clear_text = removeSpaces(text);
    if (clear_text.empty()) {
        return false;
    }
    int left = 0;
    int right = clear_text.size() - 1;
    while (left < right)
    {
        if (clear_text[left] != clear_text[right]) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}


int main() {
    string text;
    getline(cin, text);

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    } else {
        cout << "not a palindrome"s << endl;
    }
}