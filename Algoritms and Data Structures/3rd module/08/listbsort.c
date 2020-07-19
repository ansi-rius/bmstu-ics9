#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

struct Elem{
        struct Elem *next;
    char *word;
};

struct Elem *bsort(struct Elem *list){
    struct Elem *current;
    char *tmp;
    int swap = FALSE;
    do{
        swap = FALSE;
        current = list;
        while(current!=NULL){
            if((*current).word!=NULL && (*current).next!=NULL){
                if(strlen((*current).word)>strlen((*(*current).next).word)){
                    tmp = (*current).word;
                    (*current).word = (*(*current).next).word;
                    (*(*current).next).word = tmp;
                    swap = TRUE;
                }
            }
            current = (*current).next;
        }
    } while(swap);
    
    return list;
}

int main(){
    struct Elem *list;
    list = (struct Elem *)malloc(sizeof(struct Elem));
    (*list).next = NULL;
    (*list).word = NULL;
    
    char str[255];
    
    gets(str);
    
    //Заполнение списка
    struct Elem *element, *current = list;
    char *word;
    
    int i = 0, start = -1, stop = -1, j;
    
    for(int i=0; i<strlen(str); i++){
        if(str[i]==' ' || i == strlen(str)-1){
            if(i == strlen(str)-1){
                if(start == -1){
                    if(str[i]!=' '){
                        start = i;
                    }
                }
                if(stop == -1){
                    stop = i;
                }
            }
            else{
                if(start!=-1){
                    stop = i - 1;
                }
            }
        }
        else{
            if(start == -1)
                start = i;
        }
        if(start!=-1 && stop!=-1){
            word = (char *)malloc(sizeof(char)*(stop-start+1+1));
            for(j = start; j<=stop; j++){
                word[j - start]=str[j];
            }
            word[j - start]='\0';
            element = (struct Elem *)malloc(sizeof(struct Elem));
            (*element).next = NULL;
            (*element).word = word;
            
            (*current).next = element;
            current = element;

            start=-1;
            stop=-1;
        }
    }
    
    //Сортировка по возрастанию длин
    list = bsort(list);

    //Печать списка
    current = list;
    while(current!=NULL){
        if((*current).word!=NULL){
            word = (*current).word;
            int i = 0;
            while(*(word+i)!='\0'){
                putchar(*(word+i));
                i++;
            }
            putchar(' ');
        }
        current = (*current).next;
    }

    //Очистка списка
    current = list;
    element = list;
    while(current!=NULL){
        free((*current).word);
        current = (*current).next;
        free(element);
        element = current;
    }       

    return 0;
}
