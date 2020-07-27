#include <stdio.h>

int main(){
    unsigned long a,b,m,k = 0;
    
    scanf("%ld", &a);
    scanf("%ld", &b);
    scanf("%ld", &m);

    for(int i = 63; i >= 0; i--){
        if (((a >> i) & 1) == 1){  //реальзация формулы (1)
            k += b;
            k %= m;
            //printf("k1 = %ld  ", k);
        }
        if (i != 0){
            k *= 2;
            k %= m;
            //printf("k2 = %ld  ", k);
        }
    }
    
    printf("%ld\n", k); 
    return 0;
}