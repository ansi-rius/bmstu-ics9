#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    long x, i=0,k=0,b=0,j=0, d=0;

    scanf("%ld", &x);

    x = labs(x);
    d = sqrt(x)+1;          //размер массива

    unsigned int a[d];

    for (i = 0; i<d;i++){       //заполняю массив единицами
        a[i]=1;
        //printf("a[%d]= %d\n", i, a[i]);
    }

    for (j=2; j<d; j++){
        if (a[j] != 0){
        for (k=j*j; k<d; k+=j)   //обнуление всех не простых чисел
            a[k]=0;
        }
    }
    
    for (i=2; i<d;i++){ //иду с начала
        if (a[i] != 0){
            while (((x % i) == 0) && ((x / i) > 1)){
                x = x / i;
            }
        }
    }
    
    printf("%ld\n", x);
    return 0;
}