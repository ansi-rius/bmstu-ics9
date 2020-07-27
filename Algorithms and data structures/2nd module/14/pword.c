#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* prefix(char *s){
        int *pi = (int *)malloc(sizeof(int)*(strlen(s) + 1));

    int t = 0, i = 1;
    pi[0]=t;
    while(i < strlen(s)){
        while((t>0) && (s[t] != s[i])){
            t=pi[t-1];
        }
        if (s[t] == s[i])
            t++;
        pi[i]=t;
        i++;
    }
    return pi;
}

int KMPSubst(char *s, char *t){
    int *pi = prefix(s);
    //printf("%d", pi);
    int q=0, k=0;
    while(k < strlen(t)){
        while((q>0) && (s[q] != t[k])){
            q=pi[q-1];
        }
        if (s[q] == t[k]) 
            q++;
        if (q == 0){
                        free(pi);
            return 0;
        }
        if (q == strlen(s))
            q = pi[q-1];
        /*if (q == strlen(s)){
            k = k - strlen(s) + 1;
            //printf("yes");
            //break;
        }*/
        k++;
    }
    free(pi);
    return 1;
}

int main(int argc,char **argv)
{   
    /*char *a = argv[1];
    char *b = argv[2];

    for (int i = 0; i< strlen(a); i++){
        printf("%c", a[i]);
    }
    printf("\n");
    for (int i = 0; i< strlen(b); i++){
        printf("%c", b[i]);
    }
    printf("\n");*/

    int res = KMPSubst(argv[1],argv[2]);
    if (res == 1) printf("yes\n");
    else printf("no\n");
    return 0;
}