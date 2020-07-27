#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s[1000000]={0};
    gets(s);
    /*for (int i = 0; i < len; i++){
        printf("%c", sent[i]);
    }*/
    //int m = 26; //букв в алфавите
    int count[27]={0};
    int k, j = 0;
    int n=strlen(s);

    while(j<n){
            k = s[j]-97; //-97 для ключа
        count[k] += 1;
        j++;
    }
    int i=0;
    while(i<26){
        while (count[i]>0){
            count[i]--;
            printf("%c", (i+97));
        }
        i++;
    }
    printf("\n");

    return 0;
}