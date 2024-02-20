#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char** argv) {
    // 1
    {
        fstream fout("telefon.txt", ios::out);
        fout << "У меня зазвонил телефон."s << endl;
        fout << "- Кто говорит?"s << endl;
    }

    // // 2 - Перезаписываем поверх
    // {
    //     fstream fout("telefon.txt", ios::in | ios::out);
    //     fout << "- Слон."s << endl;
    // }
    
    // 2 - укажем позицию записи методом seekp
    // {
    //     fstream fout("telefon.txt", ios::in | ios::out);
    //     fout.seekp(72);
    //     fout << "- Слон."s << endl;
    //     cout << "Writing at pos: "s << fout.tellp() << endl;
    // }

    // 2 Перейти при записи в самый конец файла можно командой stream.seekp(0, ios::end)
    {
        fstream fout("telefon.txt", ios::in | ios::out);
        fout.seekp(-16, ios::end);
        fout << "на линии?"s << endl << "- Слон."s << endl;
        cout << "Writing at pos: "s << fout.tellp() << endl;
    }

    // 3
    {
        fstream fin("telefon.txt", ios::in);
        string str;
        while (getline(fin, str)) {
            cout << str << endl;
        }
    }
}