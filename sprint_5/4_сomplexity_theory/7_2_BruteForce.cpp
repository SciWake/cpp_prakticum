#include <iostream>
#include <string>

using namespace std;

template <typename F>
string BruteForceHelper(F check, string password, int position) {
    if (position == password.length()) {
        // Все символы проверены, проверяем пароль
        if (check(password)) {
            return password;
        }
        return "";  // Возвращаем пустую строку, если пароль не найден
    }

    // Рекурсивно вызываем функцию для следующего символа
    for (char c = 'A'; c <= 'Z'; ++c) {
        string newPassword = password;
        newPassword[position] = c;
        string result = BruteForceHelper(check, newPassword, position + 1);
        if (!result.empty()) {
            return result;
        }
    }

    return "";  // Возвращаем пустую строку, если пароль не найден
}

template <typename F>
string BruteForce(F check) {
    string password = "AAAAA"s;
    return BruteForceHelper(check, password, 0);
}

int main() {
    string secretPassword = "ABCDE"s;
    auto check = [secretPassword](const string& s) {
        return s == secretPassword;
    };

    cout << "Secret Password: " << BruteForce(check) << endl;

    return 0;
}
