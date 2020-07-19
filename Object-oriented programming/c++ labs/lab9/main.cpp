#include <iostream>
#include <vector>
#include "Declarator.h"

int main() {
    std::vector<int> coordinates;
    std::vector<int> coordinates2;
    std::vector<int> coordinates3;

    coordinates.push_back(0);
    coordinates.push_back(1);
    coordinates.push_back(2);
    Point x1(coordinates);

    coordinates2.push_back(10);
    coordinates2.push_back(20);
    coordinates2.push_back(30);
    Point x2(coordinates2);

    coordinates3.push_back(666);
    coordinates3.push_back(111);
    coordinates3.push_back(222);
    Point x3(coordinates3);
    /*for (int i=0; i<5; i++) {
        std::cout << coordinates[i] << std::endl;
    }*/

    Polyline<Point> line1;
    Polyline<Point> line2;
    //Point y1(coordinates2);

    //Point y2(coordinates2);
    line1.operator<<(x1); //(0, 1, 2)
    line1.operator<<(x3); //(666, 111, 222), (0, 1, 2)
    line1 >> x3;

    line2 << x2;
    line2 >> x3;
    line2 << x3;
    //line2 << y2;
    std::cout << line1 << std::endl;
    std::cout << line2 << std::endl;

    std::cout << "line1 has " << line1.count() << " points" << std::endl;
    std::cout << "line2 has " << line2.count() << " points" << std::endl;
    //
    std::cout << "Dist in Point between x1 & x3: " << x1.dist(x3) << std::endl;
    std::cout << "Dist in Point between x2 & x3: " << x2.dist(x3) << std::endl;
    //
    std::cout << "line1 > line2? => " << (line1>line2) << std::endl;
    std::cout << "line1 < line2? => " << (line1<line2) << std::endl;
    std::cout << "line1 == line2? => " << (line1==line2) << std::endl;
    std::cout << "line1 != line2? => " << (line1!=line2) << std::endl;
}