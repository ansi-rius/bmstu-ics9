#include <stdio.h>

int main(){
    
    long  a = 0,   b = 0;
    long a1 = 0,  n1 = 0, b1 = 0;
    long  t = 0,  n2 = 0,  i = 0, max = 0;

    scanf("%ld", &n1); //размер 1го мн-ва

    for(i = 0; i < n1; i++){
        scanf("%ld", &a1); //элементы 1го эл-тов

        if (a1>max)
            max=a1;

        //printf("a= %ld\n", a);

        a |= (1 << a1);

        //printf("a!= %ld\n", a);
    }

    scanf("%ld", &n2); //размер 2го мн-ва

    for(int i = 0; i<n2; i++){
        scanf("%ld", &b1); //элементы 2го эл-тов

        if (b1 > max)
            max=b1;

        b |= (1 << b1);

        //printf("b= %ld\n", b);
    }

    for (i=0; i<=max; i++){
        if ((((a >> i) & 1) == 1) && (((b >> i) & 1) == 1))
            printf("%ld ", i);
    }
    
    return 0;
}