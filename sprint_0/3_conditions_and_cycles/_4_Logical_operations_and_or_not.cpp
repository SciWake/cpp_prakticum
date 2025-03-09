#include <iostream>

using namespace std;

int main() {
    string color1, color2, color3, color;
    int floors1, floors2, floors3, floors;
    
    cin >> color1 >> floors1;
    cin >> color2 >> floors2;
    cin >> color3 >> floors3;
    
    cin >> color >> floors;
    
    bool ignore_color = color == "?"s;
    bool ignore_floor = floors == -1;
    
    if ((ignore_color || color == color1) && (ignore_floor || floors == floors1)) {
        cout << 1 << endl;
    }
    if ((ignore_color || color == color2) && (ignore_floor || floors == floors2)) {
        cout << 2 << endl;
    }
    if ((ignore_color || color == color3) && (ignore_floor || floors == floors3)) {
        cout << 3 << endl;
    }
}