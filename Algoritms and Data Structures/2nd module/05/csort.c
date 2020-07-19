#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_space(char *src);
void csort(char *src, char *dest);
void CountSort(int *a, int n, int *count);

 
int main(int argc, char **argv){
    char src[80];
    gets(src);
    
    clear_space(src); //убрать пробелы
    
    char dest[strlen(src)+1]; //fr!

    csort(src, dest);
    
    printf("%s\n", dest);
    
    return 0; 
}

void clear_space(char *src){
    int i = 0, j = 0, s = 0;
    while(src[i] != '\0'){
        if(src[i] != ' '){
            s = 0;
            src[j]=src[i];
            j++;
        }
        else{
            s++;
            if(s == 1){
                src[j] = ' ';
                j++;
            }
        }
        i++;
    }
    src[j]='\0';
}

void csort(char *src, char *dest){
    int count_word = 1;
    for(int i = 0; i< strlen(src); i++){
        if(src[i] == ' ')
            count_word++;
    }
    //printf("Count word = %d\n", count_word);
    
    int count_idx[count_word]; //fr!
    int count_len[count_word]; //fr!

    count_word = 0;
    int len_word = 0;
    for(int i = 0; i< strlen(src); i++){
        if(src[i] == ' '){
            count_len[count_word] = len_word;
            len_word = 0;
            count_word++;
        }
        else{
            len_word++;
            if(len_word==1)
                count_idx[count_word] = i;
        }
    }
    if(len_word>0){
        count_len[count_word] = len_word;
        count_word++;
    }

    int P[count_word]; //fr!
    CountSort(count_len, count_word, P);

    int d = 0;
    for(int i = 0; i < count_word; i++){
        for(int j = 0; j < count_len[P[i]]; j++){
            dest[d]=src[count_idx[P[i]]+j];
            d++;
        }
        dest[d] = ' ';
        d++;
    }
    dest[d]='\0';
    
    //free(count_len); //!
    //free(count_idx); //!
    //free(P);         //!
}

void CountSort(int *a, int n, int *P){
    int count[n]; //fr!

    for(int j=0; j<n; j++)
        count[j]=0;

    for(int j=0; j<n-1; j++){
        for(int i=j+1; i<n; i++){
            if(a[i]<a[j])
                count[j]=count[j]+1;
            else
                count[i]=count[i]+1;
        }
    }

    for(int j=0; j<n; j++)
        P[count[j]]=j;

    //free(count); //!
}