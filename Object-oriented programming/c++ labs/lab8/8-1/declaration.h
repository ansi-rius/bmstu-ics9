//                                     43 вариант
#include <vector>

template <typename T, int M>
class MaterialPoints {
private:
    std::vector< std::pair<std::vector<T>, T> > a;
public:
    MaterialPoints(std::vector< std::vector <T>> arr, std::vector <T> m, int N);

    void print();
};

template <typename T, int M>
void MaterialPoints<T, M>::print() {
    for (int i=0; i<a.size(); i++)
        std::cout << a[i].second;

}

template <typename T, int M>
MaterialPoints<T, M>::MaterialPoints(std::vector< std::vector <T>> arr, std::vector <T> m, int N){
    for (int i=0; i<N; i++) {
        int j = 0;
        //for (int j=0; j<M; j++){
            //a[i].first[0] = arr[i][0];
            //a[i].first[1] = arr[i][1];
        std::cout << arr[i][j] << std::endl;
        //!a[i].first = arr[i];
        //std::cout << std::make_pair(arr[i], m[i]) << std::endl;
        //a.push_back(std::make_pair(arr[i], m[i]));
        //}
        //!a[i].second = m[i];
    }

}


