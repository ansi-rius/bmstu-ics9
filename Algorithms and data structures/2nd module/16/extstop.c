#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int** Delta1(char *s){ //теперь матрица, эвристика стоп-символа расширена
    int len = strlen(s), size = 666, k = 0;
        int **delta1 = (int **)malloc(sizeof(int*)*len); //free!
    for(int a = 0; a < len; a++){
        delta1[a] = (int*)malloc(sizeof(int)*size);
    }

    for(int a = 0; a<len; a++){
        for(int j = 0; j<size; j++)
            delta1[a][j]=len;
    }
    for(int a=0; a<len; a++){
        for(int b = 0; b<len-a; b++){
            delta1[a][s[b]]=len-b-1;
        }
    }
    return delta1;
}

int BMSubst(char *s, char *t){ //без суффикса
    int **delta1 = Delta1(s);
    int lens = strlen(s);
    int a = 0, k = lens-1, lent = strlen(t);
    while(k<lent){
        a = lens-1;
        while(t[k] == s[a]){
            if (a == 0){
                for (a = 0; a<lens; a++)
                    free(delta1[a]);
                free(delta1);
                printf("%d\n", k);
                return 0;
            }
            a--;
            k--;
        }
        //u = atoi(*(t+k));
        k = k + delta1[lens-a-1][t[k]];
    }
    for (a = 0; a<lens; a++)
        free(delta1[a]);
    free(delta1); //!
    printf("%d\n", lent);
    return 0;
}

int main(int argc, char **argv){
    BMSubst(argv[1], argv[2]);
    return 0;
}