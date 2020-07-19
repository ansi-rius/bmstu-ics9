#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* Prefix(char *s){
        int len = strlen(s);
    int *pi = (int *)malloc(sizeof(int)*len); //aabaabaabaab
    int t = 0;                //010123456789
    int i = 1;
    pi[0]=t;

    while(i<len){
        while((t>0) && (s[t] != s[i])){
            t = pi[t-1];
        }
        if (s[t] == s[i])
            t++;
        pi[i] = t;
        i++;
    }
    /*for (int j = 0; j<len; j++){
        printf("%d", pi[j]);
    }
    printf("\n");*/
    return pi;
}

int main(int argc, char **argv){
    char *s = argv[1];
    int len = strlen(s);
    int n = 0;
    int k = 0, i = 1;
    int *d = Prefix(s);
    d[0] = 0;
    while (i<len){
        n = i+1;
        if ((d[i]>0) && (n % (n - d[i]) == 0)){
            k = n/(n-d[i]);
            printf("%d %d\n", n, k);
        }
        i++;
    }
    free(d);
    return 0;
}