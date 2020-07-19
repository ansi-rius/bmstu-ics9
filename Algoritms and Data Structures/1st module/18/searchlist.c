#include "elem.h"
struct Elem *searchlist(struct Elem *list, int k) //ищем ЦЕЛОЕ число только инт
{ 
    struct Elem *res = list;
    while(res){
        if(res->tag == INTEGER){
            if (res->value.i == k){
                return res;
            }
        }
        if(res->tag == LIST){
            struct Elem *found = searchlist(res->value.list, k); //рекурсия
            if (found){
                return found;
            }
        }
        res = res->tail; //переходим к хвосту
    }
    return res;
}