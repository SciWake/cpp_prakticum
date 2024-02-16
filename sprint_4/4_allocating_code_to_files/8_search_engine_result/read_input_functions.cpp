#include "read_input_functions.h"

#include <iostream>


std::string ReadLine() { // Unused
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int ReadLineWithNumber() { // Unused
    int result;
    std::cin >> result;
    ReadLine();
    return result;
}