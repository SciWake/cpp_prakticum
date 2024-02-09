#include "builder.h"

#include <iostream>

using namespace std;

int main() {
    Builder tom;
    Wall wall(3.5, 2.45);

    cout << tom.CalcBricksNeeded(wall) << endl;
    return 0;
}