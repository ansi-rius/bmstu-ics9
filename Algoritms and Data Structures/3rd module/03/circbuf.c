#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue{
    int *data;
    int cap; //размер
    int count; //кол-во жэлем в очереди
    int head; //индекс, откуда брать элем для удаления
    int tail; //индекс, куда класть элем при добавлении
};

void InitQueue(struct queue *q, int n){
    q->data = (int *)malloc(sizeof(n)*n);
    q->cap = n; q->count = 0; q->head = 0; q->tail = 0;
}

void QueueEmpty(struct queue *q){
    int empty = 0;
    if (empty == q->count) printf("true\n");
    else printf("false\n");
}

void Enqueue(struct queue *q, int x){
    if (q->count == q->cap)
        q->data = realloc(q->data, 2*q->cap * sizeof(q->cap));
    q->data[q->tail] = x;
    q->tail = q->tail + 1;
    if (q->tail == q->cap)
        q->tail = 0;
    q->count = q->count + 1;
}

int Dequeue(struct queue *q){
    int x,empty = 0;
    if (empty == q->count){
        printf("Smth went wrong :c");
    }
    
    x = q->data[q->head];
    q->head = q->head + 1;
    if (q->head == q->cap)
        q->head = 0;
    q->count = q->count - 1;
    return x;
}

int main(){
    int n,x;
    int m = 4;
    scanf("%d", &n);

    struct queue *q = (struct queue *)malloc(sizeof(struct queue)*n);
    InitQueue(q, n);

    char buf[80];
    char *request = buf;

    for(int i = 0; i<n; i++){
        scanf("%s", request);
        if (request[0] == 'E' && request[1] == 'N'){
            scanf("%d", &x);
            Enqueue(q,x);
        }
        else if (request[0] == 'D'){ //вывести значение
            printf("%d\n", Dequeue(q));
        }
        else if (request[0] == 'E' && request[1] == 'M'){
            QueueEmpty(q);
        }
    }
    free(q->data);
    free(q);
}