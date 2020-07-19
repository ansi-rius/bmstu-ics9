#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <unordered_set>

class FibNumIterator;

class FibNumber
{
private:
    int one;
    int two;
    int num;

    friend class FibNumIterator;
public:
    FibNumIterator begin();
    FibNumIterator end();

    FibNumber(int num);
};


class FibNumIterator:
        public std::iterator<
                std::forward_iterator_tag,
                int,
                ptrdiff_t,
                int*,
                int
        >
{
private:
    FibNumber *n;
    //int index;
    int one1;
    int two1;
    int numb;
    bool is_default;
    //int fib;
    FibNumIterator(FibNumber &n,int one2): n(&n), one1(one2){

        //  std::cout << one1;
        //if (one1 == 0) {
        //std::cout << one1;
        numb = n.num;
        one1 = 1;
        two1 = 0;
        // }
    }

    bool is_end() const { return 0 == one1 ; }

    friend class FibNumber;
public:
    FibNumIterator(): is_default(true) {}

    FibNumIterator(FibNumber &n): n(&n), is_default(false) {
        this->one1 = n.one;
        this->two1 = n.two;
        this->numb = n.num;
        //  std::cout << one1 << two1;
        /* if (numb >= one1) {
             //std::cout << " one = " << n.one << " ";
             this->numb -= one1;

             //std::cout << 1;
         } else {}*/
        // std::cout << 0;
        //std::cout<<*it << " ";
        // std::cout<<n.myvec[ind];

    }

    //FibNumIterator(FibNumber &n): FibNumIterator(n, 1) {}

    bool operator == (const FibNumIterator &other) const
    {
        return  (is_default && other.is_default) ||
                (is_default && other.is_end()) ||
                (is_end() && other.is_default) ||
                (this->one1 == other.one1 && this->two1 == other.two1);
    }

    bool operator != (const FibNumIterator &other) const
    {
        //std::cout<<this->num->x<< " ";
        return !(*this == other);
    }


    FibNumIterator& operator++ ()
    {
        if (is_default) throw "not initialized iterator";
        //if (is_end()) throw "iterator overflow" //?
        if (numb <= one1)
            numb -= one1;
        int i = one1;
        this->one1 = two1;
        this->two1 = i - two1;
        //   std::cout << " one1 = " << one1 << " two1 = " << two1<<" ";
        return *this;
    }

    FibNumIterator operator++ (int)
    {
        FibNumIterator tmp(*this);
        operator++();
        // std::cout << tmp.num->x<< " ";
        return tmp;
    }

    int operator* () {
        if (is_default || is_end()) {
            throw "not initialized iterator";
        }
        if (numb >= one1) {
            //std::cout << " one = " << n.one << " ";
            return 1;
            //std::cout << 1;
        } else {
            return 0;
        }
    }

};



FibNumIterator FibNumber::begin()
{
    return FibNumIterator(*this);
}

FibNumIterator FibNumber::end()
{
    return FibNumIterator(*this, 0);
}
//return FibNumIterator(*this);

FibNumber::FibNumber(int num) {
    this->num = num;
    int x1 = 1, x2 = 2, x3;
    //::vector<int> myvector;

    int i;
    for (i = 0; num >= x2; ++i) {
        //  myvector.push_back(x1);   // 1 2 3 5 8 13
        x3 = x1 + x2;
        x1 = x2;
        x2 = x3;
    }
    // std::cout << x1 << " ";
    // myvector.push_back(x1);
    this->one = x1;
    this->two = x2 - x1;
    // std::cout << one << two;

    // for (std::vector<int>::iterator it = myvec.begin(); it != myvec.end(); ++it) {
    /* for (auto it = begin(); it != end(); ++it) {
         //std::cout << " it = " << it<< std::endl;
         FibNumIterator(*this, it);
         //std::cout << j;
     }*/
    //std::cout << " it = " << end();
    //std::cout << " j = "<< j;
}

template <class FibNumIterator>
void reverse (FibNumIterator first, FibNumIterator last)
{
    while ((first!=last)&&(first!=--last)) {
        std::iter_swap (first,last);
        ++first;
    }
}


int main () {
    try {
        std::cout << "fib 2 : ";
        FibNumber n1(17); //17-13=4 4-8=0 4-5=0 4-3=1 1-2=0 1-1=0     //  100100
        for (FibNumIterator it = n1.begin(); it != n1.end(); it++) {
            //FibNumIterator(&n1);
            std::cout << *it;
        }
        std::cout << std::endl;
        std::cout << "fib 3 : ";
        FibNumber n2(3);
        for (FibNumIterator it = n2.begin(); it != n2.end(); it) {
            //FibNumIterator(&n1);
            std::cout << *it++;
        }
        std::cout << std::endl;

        std::cout << "fib 2 == fib 3 : " << (&n1 == &n2) << std::endl;
        std::cout << "fib 2 != fib 3 : " << (&n1 != &n2) << std::endl;
        std::cout << "fib 3 == fib 3 : " << (&n2 == &n2) << std::endl;
    }
    catch (const char *err) {
        std::cout << "error " << err << std::endl;
    }

    return 0;
}