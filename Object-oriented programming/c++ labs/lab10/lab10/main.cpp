#include <iostream>
#include "declarator.h"

int main() {
    string str[5] = {"aaa",
                     "aba",
                     "bbb",
                     "bbbb",
                     "aabb"};
    Strings<string, 5> a(str);

    //cout << str[1][0] << endl;

    for (auto it = a.begin(); it != a.end(); ++it) {
        for (int i=0; i<27; i++) {
            cout << (*it).first;
            cout << " = ";
            cout << (*it).second;
            cout << endl;
        }
    }
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}