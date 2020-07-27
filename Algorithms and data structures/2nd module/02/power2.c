#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int sum(long int *v, int n, int *a);
int exponent2(long int s);
int Combination(int *a, int n, int m);

int main(){
        int n;

    scanf("%d\n", &n);

    long int *v = (long int *)malloc(sizeof(long int)*n); //ввод

    for (int i = 0; i < n; i++){
        scanf("%li",(v+i));
    }

    int res = 0; //результат
    int m;
    int *a = (int *)malloc(sizeof(int)*n); //сочетания

    for (int m = 1; m <= n; m++){

        for (int i = 0; i < m; i++){ //сочетания a n эл-тов по m
            a[i] = i + 1;
        }
        res += sum(v, m, a);
        
        while (Combination(a, n, m)){
            res += sum(v, m, a); //результат, кол-во сумм
        }
    }

    free(a); //!

    printf("%d\n", res);

    free(v); //!

    return 0; 
}

int sum(long int *v, int n, int *a){
    long int s = 0;
    for (int i = 0; i < n; i++)
        s += v[a[i] - 1]; //сумма чисел

    return exponent2(s);
}

int exponent2(long int s){ //проверка на степень двойки
    if (s <= 0) return 0;
    int k = 0;
    while(s > 0){
        k += s % 2;

        if (k > 1) return 0;
        s >>= 1; // s = s / 2;
    }
    return 1;
}

int Combination(int *a, int n, int m){ //Сочетания n эл-тов по m
    for (int i = m - 1; i >= 0; --i){

        if (a[i] < n - m + i + 1) {
            a[i]++;
            for (int j = i + 1; j < m; ++j)
                a[j] = a[j - 1] + 1;
            return 1;
        }
    }
    return 0;
}