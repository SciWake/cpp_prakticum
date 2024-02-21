#include <filesystem>
#include <iostream>

using namespace std;
using filesystem::path;


path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

int main() {
    // Неудобный вариант
    // path p = path("a") / path("folder") / path("and") / path("..") / path("a") / path("file.txt");
    // Создадим свой литерал _p
    path p = "a"_p / "folder"_p / "and"_p / ".."_p / "a"_p / "file.txt"_p;

    // выводим естественное представление пути в std::string
    cout << p.string() << endl;
}