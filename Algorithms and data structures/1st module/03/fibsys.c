#include <stdio.h>
#include <math.h>

int main(){

    unsigned long x, i = 0, i0 = 1, i1 = 2, i2=0, t = 1, d=0;

    scanf("%ld", &x);


    while (i1 <= x) {
        i = i0 + i1; //макс фиб + 1. //i0 = f(n-2); i1 = f(n-1)
        i0 = i1;             //i = f(n); i2 = f(n) + f(n-1)
        i1 = i;
        t++;        //счетчик количества цифр в выводе
    }
        
    while (t > 0){
        t--;
        if (i0 <= x){     
            printf("1");  
            x -= i0;  
        }
        else printf("0");
        i = i1 - i0;    
        i1 = i0;          
        i0 = i;      
    }

    return 0;
}