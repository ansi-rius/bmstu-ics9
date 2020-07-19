#include <stdio.h>

int main()
{
    int n = 8, i = 0, j = 0, k = 0, s1 = 0, s2 = 0;
    int a[n],b[n];

    for(i=0;i<n;i++)
        scanf("%d", &a[i]);  //1ый массив
    for(j=0;j<n;j++)
        scanf("%d", &b[j]);  //2ой массив
    
    for(i=0;i<n;i++){
        s1 += a[i];
    }
    for(j=0;j<n;j++){
        s2 += b[j];
    }
    if (s1 == s2){
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                if(a[i] == b[j])
                k++;
        }
        if (k > 7) printf("yes");
    }
        else printf("no");
}