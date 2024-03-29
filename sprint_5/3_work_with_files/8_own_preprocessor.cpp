#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using filesystem::path;


path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

path SearchFileInDirectories(const path& filename, const vector<path>& include_directories) {
    for (const auto& directory : include_directories) {
        path abs_path = directory / filename;
        if (exists(abs_path) && is_regular_file(abs_path)) {
            return abs_path;
        }
    }
    return {};
}

bool Preprocess(const path& in_file, const path& out_file, const vector<path>& include_directories) {
    static regex include_file(R"/(\s*#\s*include\s*"([^ "]*)"\s*)/");
    static regex include_lib(R"/(\s*#\s*include\s*<([^>]*)>\s*)/");
    smatch m;
    string line;
    size_t line_number = 0;
    ifstream in(in_file);
    ofstream out(out_file, ios::out | ios::app);

    auto process_include = [&](const path& included_path) {
        ifstream reader_file(included_path);
        if (reader_file.is_open()) {
            Preprocess(included_path, out_file, include_directories);
            reader_file.close();
        } else {
            cout << "unknown include file "s << included_path.filename().string()
                 << " at file "s << in_file.string() << " at line "s << line_number << endl;
        }
    };

    while (getline(in, line)) {
        ++line_number;
        if (regex_match(line, m, include_file) || regex_match(line, m, include_lib)) {
            path path_file = string(m[1]);
            path full_path = in_file.parent_path() / path_file;

            if (exists(full_path) || ((full_path = SearchFileInDirectories(path_file, include_directories)) != path{})) {
                process_include(full_path);
            } else {
                cout << "unknown include file "s << path_file.filename().string()
                     << " at file "s << in_file.string() << " at line "s << line_number << endl;
                return false;
            }
        } else {
            out << line << endl;
        }
    }

    return true;
}

string GetFileContents(string file) {
    ifstream stream(file);

    // конструируем string по двум итераторам
    return {(istreambuf_iterator<char>(stream)), istreambuf_iterator<char>()};
}

void Test() {
    error_code err;
    filesystem::remove_all("sources"_p, err);
    filesystem::create_directories("sources"_p / "include2"_p / "lib"_p, err);
    filesystem::create_directories("sources"_p / "include1"_p, err);
    filesystem::create_directories("sources"_p / "dir1"_p / "subdir"_p, err);

    {
        ofstream file("sources/a.cpp");
        file << "// this comment before include\n"
                "#include \"dir1/b.h\"\n"
                "// text between b.h and c.h\n"
                "#include \"dir1/d.h\"\n"
                "\n"
                "int SayHello() {\n"
                "    cout << \"hello, world!\" << endl;\n"
                "#   include<dummy.txt>\n"
                "}\n"s;
    }
    {
        ofstream file("sources/dir1/b.h");
        file << "// text from b.h before include\n"
                "#include \"subdir/c.h\"\n"
                "// text from b.h after include"s;
    }
    {
        ofstream file("sources/dir1/subdir/c.h");
        file << "// text from c.h before include\n"
                "#include <std1.h>\n"
                "// text from c.h after include\n"s;
    }
    {
        ofstream file("sources/dir1/d.h");
        file << "// text from d.h before include\n"
                "#include \"lib/std2.h\"\n"
                "// text from d.h after include\n"s;
    }
    {
        ofstream file("sources/include1/std1.h");
        file << "// std1\n"s;
    }
    {
        ofstream file("sources/include2/lib/std2.h");
        file << "// std2\n"s;
    }

    assert((!Preprocess("sources"_p / "a.cpp"_p, "sources"_p / "a.in"_p,
                                  {"sources"_p / "include1"_p,"sources"_p / "include2"_p})));

    ostringstream test_out;
    test_out << "// this comment before include\n"
                "// text from b.h before include\n"
                "// text from c.h before include\n"
                "// std1\n"
                "// text from c.h after include\n"
                "// text from b.h after include\n"
                "// text between b.h and c.h\n"
                "// text from d.h before include\n"
                "// std2\n"
                "// text from d.h after include\n"
                "\n"
                "int SayHello() {\n"
                "    cout << \"hello, world!\" << endl;\n"s;

    assert(GetFileContents("sources/a.in"s) == test_out.str());
}

int main() {
    Test();
}