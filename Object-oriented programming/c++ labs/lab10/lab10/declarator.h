#include <string>
#include <vector>
#include <vector>
#include <iostream>

using namespace std;        //43 вариант

template <typename T, int n>
class IterStr;
template <typename T, int n>
class Strings {
private:
    T strs[n];
    friend class IterStr<T, n>;
public:
    Strings(string arr[]) {
        for (int i=0; i<n; i++) {
            this->strs[i] = arr[i];
            //cout << arr[i] << endl;
        }
    }

    IterStr<T, n> begin();
    IterStr<T, n> end();

};

template <typename T, int n>
class IterStr {
private:
    T* s1;
public:
    pair<char, int> let[27];
    IterStr(string* ss) : s1(ss){};

    T& operator[] (int index) {
        return *(s1 + index);
    }

    bool operator== (const IterStr& it) const {
        return s1 == it.s1;
    }

    bool operator!= (const IterStr& it) const {
        return !(*this == it);
    }

    pair<char, int>* Help(T str1, T str2) {
        for (int i=0; i<27; i++) {
            let[i].first = '\0';
            let[i].second = 0;
        }
        //cout << "looking through: " << str1 << " and " << str2 << endl;
        /*if (str1.length() != str2.length()) {
            cout << "Warning : different lens" << endl;
        }*/
        int id = 0;
        for (auto it1 = str1.begin(), it2 = str2.begin(); it1 != str1.end() && it2 != str2.end(); it1++, it2++) {
            if (*it1 == *it2) {
                if (findd(*it1, let) != -1) {
                    let[findd(*it1, let)].first = *it1;
                    let[findd(*it1, let)].second++;
                } else {
                    let[id].first = *it1;
                    let[id].second++;
                    id++;
                }
            }
        }
        /*for (int i=0; i< 27; i++) {
            if (let[i].second != 0) {
                cout << let[i].first << " = " << let[i].second << endl;
            }
        }*/

        if (let[0].second == 0) {
            cout << "No matches" << endl;
        }
        //cout << endl;
        return let;
    }

    int findd(char what,  pair<char, int> where[]) {
        int eq = -1;
        for (int i=0; i<27; i++) {
            if (where[i].first == what) {
                eq = i;
                break;
            }
        }
        return eq;
    }

    pair<char, int> operator* () {
        return *Help(*s1, *(s1+1));
    }

    IterStr operator++ () {
        ++s1;
        return *this;
    }

    IterStr operator++ (int) {
        IterStr tmp(*this);
        ++(*this);
        return tmp;
    }

};

template <typename T, int n>
IterStr<T, n> Strings<T, n>::begin() {
    return IterStr<T, n>(strs);
}

template <typename T, int n>
IterStr<T, n> Strings<T, n>::end() {
    return IterStr<T, n>(strs + n - 1);
}