#include <stdio.h>
#include <stdlib.h>


int main(){
    int k = 0,n = 0,i = 0;
    int s = 0,max = 0, l = 0;

    scanf("%d", &n);    

    int a[n];

    if (n != 0){
        for(i=0;i<n;i++){
            scanf("%d", &a[i]);
        }
    }

    scanf("%d", &k);

    if ((n != 0) && (k != 0)) {
        for (i=0; i<k; i++){
            max += a[i];
        }

        s = max; 

        for(int i = (k-1); i < (n-1); i++) {

            s = s - a[l] + a[i+1];
            l++;

            if (max <= s){
                max = s;
            }
        }
    }
    
    printf("%d", max);
    return 0;
}