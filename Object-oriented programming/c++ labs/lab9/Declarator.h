#include <iostream>                         //44 вариант
#include <vector>
#include <cmath>

class Point {
private:
    std::vector<int> coordinates;
public:
    Point(std::vector<int> &coordinates);
    double dist(Point point);
    friend std::ostream& operator<< (std::ostream& os, Point p) {
        os << "(" << p.coordinates[0];
        for (int i=1; i<p.coordinates.size(); i++) {
            os << ", " << p.coordinates[i];
        }
        os << ")";
        return os;
    }
};

Point::Point(std::vector<int> &coordinates) {
    this->coordinates = coordinates;
}

double Point::dist(Point point) {
    int v=0;
    for (int i=0; i<point.coordinates.size(); i++) {
        //std::cout << this->coordinates[i] << " " << point.coordinates[i] << std::endl;
        //std::cout << (this->coordinates[i] - point.coordinates[i]) << std::endl;
        //std::cout << (this->coordinates[i] - point.coordinates[i])*(this->coordinates[i] - point.coordinates[i]) << std::endl;
        v += (this->coordinates[i] - point.coordinates[i])*(this->coordinates[i] - point.coordinates[i]);
    }
    return sqrt(v);
}

template<typename Point>
class Polyline {
private:
    std::vector<Point> line;
    double dist;
public:
    Polyline <Point>& operator<< (Point& point1);
    Polyline <Point>& operator>> (Point& point1);
    Point& operator[] (int i);
    int count();
    double size();
    bool operator== (const Polyline<Point>& line1);
    bool operator!= (const Polyline<Point>& line1);
    bool operator< (const Polyline<Point>& line1);
    bool operator> (const Polyline<Point>& line1);
    bool operator<= (const Polyline<Point>& line1);
    bool operator>= (const Polyline<Point>& line1);
    friend std::ostream& operator<< (std::ostream& os, Polyline<Point>& p) {
        os << "length: " << p.size() << std::endl << "line: " ;
        os << p[0];
        for (int i=1; i<p.size(); ++i)
            os << ", " << p[i];
        return os;
    }
};

template<typename Point>
double Polyline<Point>::size() {
    return line.size();
}

template<typename Point>
Polyline <Point>& Polyline<Point>::operator<< (Point& point1) {
    line.insert(line.begin(), point1);
    if (line.size() == 1)
        dist += point1.dist(line[0]);
    else
        dist += point1.dist(line[1]);
    return *this;
}

template<typename Point>
Polyline<Point>& Polyline <Point>::operator>> (Point& point1) {
    line.push_back(point1);
    if (line.size() == 1)
        dist += point1.dist(line[line.size() - 1]);
    else
        dist += point1.dist(line[line.size() - 2]);
    //std::cout << "dist in >> " << dist << std::endl;
    return *this;
}

template<typename Point>
Point& Polyline<Point>::operator[](int i) {
    return line[i];
}

template<typename Point>
int Polyline<Point>::count() {
    return line.size();
}

template<typename Point>
bool Polyline<Point>::operator== (const Polyline<Point>& line1) {
    return (this->dist == line1.dist);
}

template<typename Point>
bool Polyline<Point>::operator!=(const Polyline<Point> &line1) {
    return (this->dist != line1.dist);
}

template<typename Point>
bool Polyline<Point>::operator< (const Polyline<Point>& line1) {
    return (this->dist < line1.dist);
}

template<typename Point>
bool Polyline<Point>::operator> (const Polyline<Point>& line1) {
    std::cout << "((" << this->dist << " " << line1.dist << ")) => ";
    return (this->dist > line1.dist);
}

template<typename Point>
bool Polyline<Point>::operator<= (const Polyline<Point>& line1) {
    return (this->dist <= line1.dist);
}

template<typename Point>
bool Polyline<Point>::operator>= (const Polyline<Point>& line1) {
    return (this->dist >= line1.dist);
}