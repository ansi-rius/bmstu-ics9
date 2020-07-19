#include "declarator.h"

int main() {
    int M = 2;
    Point<int, 2> A ({3, 4});
    Point<int, 2> B ({1, -1});
    Point<int, 2> C ({-3, -3});
    Point<int, 2> D ({-3, 2});

    MaterialPoints<int, 2> material;
    material.add(A, 2);
    material.add(B, 3);
    material.add(C, 4);
    material.add(D, 5);

    // Test 2
    /*Point<int, 3> A ({2,1,0});
    Point<int, 3> B ({0,4,0});
    MaterialPoints<int, 3> material;
    material.add(A, 2);
    material.add(B, 3);*/
    //

    if (M != 2) {
        material.massCentre();
    } else {
        material.square();
    }
    return 0;
}