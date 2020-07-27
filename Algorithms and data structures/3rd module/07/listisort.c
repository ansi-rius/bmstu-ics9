#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Elem{
        struct Elem *prev,*next;
    int v;
};

//Печать списка (next)
void iprint(struct Elem *list){
    struct Elem *current;
    current = list;
    do
    {
        printf("%d ",(*current).v);
        current = (*current).next;
    }
    while(current!=list);
    printf("\n");
}

//Печать списка (prev)
void iprint_prev(struct Elem *list){
    struct Elem *current;
    current = list;
    do
    {
        current = (*current).prev;
        printf("%d ",(*current).v);
    }
    while(current!=list);
    printf("\n");
}


//Метод «Вставка»
void isort(struct Elem *list){
    struct Elem *current, *element, *final;
    final = (*list).prev;
    for(current = (*list).next; current!=list; current = (*current).next)
    {
        int x = (*current).v;
        element = (*current).prev;
        while ((element!=final)&&((*element).v > x))
        {
            (*(*element).next).v = (*element).v;
            element = (*element).prev;
        }
        (*(*element).next).v = x;
    }
}

/*
void InsertSort(int* a){
    for (int i = 1; i < n; i++){
        int elem = a[i];
        int loc = i - 1;
        while (loc >= 0 && a[loc] > elem){
            a[loc + 1] = a[j];
            j--;
        }
        a[loc + 1] = x;
    }
}
*/

int main(){
    struct Elem *list;
    list = (struct Elem *)malloc(sizeof(struct Elem));
    (*list).prev = NULL;
    (*list).next = NULL;
    (*list).v = 0;
    
    int n;
    
    scanf("%d",&n);
    
    //Заполнение списка
    struct Elem *element, *current;
    int v;
    
    current = list;
    for(int i=0; i<n; i++){
        scanf("%d",&v);
        if(i==0){
            element = list;
        }else{
            element = (struct Elem *)malloc(sizeof(struct Elem));
        }
        (*element).prev = current;
        (*element).next = list;
        (*element).v = v;

        (*list).prev = element;
        
        (*current).next = element;
        current = element;
    }

    //Печать списка
    //iprint(list);
    //iprint_prev(list);
    
    //Сортировка по возрастанию длин
    isort(list);

    //Печать списка
    iprint(list);

    //Очистка списка
    current = list;
    element = list;
    while((*current).next!=list){
        current = (*current).next;
        free(element);
        element = current;
    }       
    free(element);

    return 0;
}
