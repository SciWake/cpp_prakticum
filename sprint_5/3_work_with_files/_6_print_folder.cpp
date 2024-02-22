#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

void CreateFile(path p) {
    ofstream file(p);
    if (file) {
        cout << "Файл создан: "s << p.string() << endl;
    } else {
        cout << "Ошибка создания файла: "s << p.string() << endl;
    }
}

void PrintFileOrFolder(filesystem::file_status status) {
    if (status.type() == filesystem::file_type::regular) {
        cout << "Путь указывает на файл"s << endl;
    } else if (status.type() == filesystem::file_type::directory) {
        cout << "Путь указывает на папку"s << endl;
    } else {
        cout << "Путь указывает другой объект"s << endl;
    }
}
void PrintFileOrFolder(filesystem::path p) {
    error_code err;
    auto status = filesystem::status(p, err);
    
    if (err) {
        return;
    }

    PrintFileOrFolder(status);
}

int main() {
    path p = "a"_p / "folder"_p;
    filesystem::create_directories(p);
    filesystem::create_directory(p / "subfolder"_p);
    std::ofstream(p / "file.txt"_p) << "File content"s;

    for (const auto& dir_entry: filesystem::directory_iterator(p)) {
        PrintFileOrFolder(dir_entry.status());
    }
} 