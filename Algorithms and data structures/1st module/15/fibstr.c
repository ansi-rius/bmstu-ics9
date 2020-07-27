#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fibstr(int n){
    int a = 0,i = 0,i0 = 1,i1 = 0, c=0;
    while (a<n){
        i = i0 + i1; //макс фиб + 1. //i0 = f(n-2); i1 = f(n-1)
        i0 = i1;                     //i = f(n); i2 = f(n) + f(n-1)
        i1 = i;
        a++; 
    }

    char *str1 = (char*)calloc(i+1,sizeof(char)); //f(n-2) i0
    str1[0]= 'a';

    char *str2 = (char*)calloc(i+1,sizeof(char)); //f(n-1) i1
    str2[0]= 'b';

    char *res = (char*)calloc(i+1,sizeof(char));
    *res= '\0';
    
    if (n == 1)
        strncpy(res,str1,(strlen(str1)));
    else if (n == 2)
        strncpy(res,str2,(strlen(str2)));
    while(strlen(res) < i){
        strncpy(res,  str1, strlen(str1));                  //res = a.  b 
        strncpy(res + strlen(str1),  str2, strlen(res));   //res = ab  bab
        strncpy(str1, str2, strlen(str2));                  //1 =   b.  ab
        strncpy(str2, res, strlen(res));                    //2 =   ab. bab
    }
    free(str1);
    free(str2);

    return res;
}
int main(){
    int n;
    scanf("%d", &n);
    char *str = fibstr(n);
    printf("%s\n", str);
    free(str);
    return 0;
}