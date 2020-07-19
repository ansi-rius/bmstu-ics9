#include <cstddef>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;

template <typename T, int M>
class Point {
public:
    vector<T> position;
    Point();
    Point(vector<T> position);
    T getCord(int ind);
};

template <typename T, int M>
T Point<T, M>::getCord(int ind) {
    return position[ind];
};

template <typename T, int M>
class MaterialPoints {
private:
    vector< pair<Point<T, M>, T> > a;

public:
    MaterialPoints()= default;
    void add(Point<T, M> point, T m);
    void massCentre();
    void square();
};

template <typename T, int M>
Point<T, M>::Point() {
    position.resize(M);
}

template <typename T, int M>
Point<T, M>::Point(vector<T> position) {
    this->position = position;
};

template <typename T, int M>
void MaterialPoints<T, M>::add(Point<T, M> point, T m) {
    a.push_back(make_pair(point, m));
}
// тут будет центр масс
template <typename T, int M>
void MaterialPoints<T, M>::massCentre() {
    double denom = 0, num = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < a.size(); j++) {
            num += a[j].second * a[j].first.getCord(i);
            denom += a[j].second;
            //cout <<  "n" << a[j].second * a[j].first.getCord(i) << endl;
        }
        //cout <<  "d" << denom << endl;
        cout << num / denom << endl;
        num = 0; denom = 0;
    }
}

template <typename T, int M>
void MaterialPoints<T, M>::square() {
    T maxX = a[0].first.getCord(0);
    T maxY = a[0].first.getCord(1);
    T minX = a[0].first.getCord(0);
    T minY = a[0].first.getCord(1);

    for (int j = 0; j < a.size(); j++) {
        if (a[j].first.getCord(0) > maxX) {
            maxX = a[j].first.getCord(0);
        }
        if (a[j].first.getCord(1) > maxY) {
            maxY = a[j].first.getCord(1);
        }
        if (a[j].first.getCord(0) < minX) {
            minX = a[j].first.getCord(0);
        }
        if (a[j].first.getCord(1) < minY) {
            minY = a[j].first.getCord(1);
        }
    }
    T s = (abs(minX) + abs(maxX))*(abs(minY) + abs(maxY));
    //cout << (minX) << endl;
    //cout << (maxX) << endl;
    //cout << (minY) << endl;
    //cout << (maxY) << endl;

    cout << s << endl;

};