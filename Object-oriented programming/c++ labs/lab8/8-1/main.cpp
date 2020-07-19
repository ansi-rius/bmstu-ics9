#include <iostream>
#include <map>
#include "declaration.h"

int main() {
    int x;
    //int coordinates[4][2] = {{3, 4}, {1, -1}, {-3, -3}, {-3, 2}};
    int N = 4;
    int M = 2;

    //int masses[4] = {2, 3, 4, 5};

    std::vector< std::vector <int>> coordinates(N, std::vector<int> (M));
    std::vector <int> masses;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            coordinates[i][j] = 3;
        }
        masses[i] = 2;
    }

    MaterialPoints<int, 2> t(coordinates, masses, N);


    t.print();
    return 0;
}