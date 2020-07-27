#include <stdio.h>
#include <stdlib.h>

struct Queue{
    int *heap;
    int cap;
    int count;
};

void InitPrioritiQueue(struct Queue *q, int res_size){
    q->heap = (int*)malloc(sizeof(int)*res_size); //!
    q->cap = res_size;
    q->count = 0;
}

void Insert(struct Queue *q, int ptr){
    int i = q->count;
    if (i == q->cap)
        printf("Full :C");
    i = q->count++;
    q->heap[i] = ptr;
    while ((i>0) && (q->heap[i] < q->heap[(i-1)/2])){
        int swp = q->heap[i];
        q->heap[i] = q->heap[(i-1)/2];
        q->heap[(i-1)/2] = swp;
        i = (i-1)/2 ;
    }
}

void swap(struct Queue * q, int i, int j) {
    int tmp = q->heap[i];
    q->heap[i] = q->heap[j];
    q->heap[j] = tmp;
}

int compare(int a, int b){
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

int Heapify(struct Queue *base,int i, int n, int ptr){ //переупорядочить эл-ты, чтобы итый эл явл корнем пир
    //printf("! %d !\n", n);
    while(i<(n/2)){
        int l = 2*i + 1;
        int r = l + 1;
        if ((compare(r,n) < 0) && (compare(base->heap[r],base->heap[l]) < 0))
            l = r;
        if  (compare(base->heap[i], base->heap[l]) <= 0)
            return ptr;
        swap(base, i, l);
        i = l;
    }
    return ptr;
}

int ExtractMax(struct Queue * q)
{
    if (q->count == 0)
        printf("Empty");
    int ptr = q->heap[0];
    q->count--;

    if (q->count >= 0) {
        q->heap[0] = q->heap[q->count];
        return Heapify(q, 0, q->count, ptr);
    }
}

int main() {
    int k, res_size  = 0,num; // кол-во массивов
    scanf("%d", &k);

    int n[k]; // размеры массивов
    for (int i = 0; i<k; i++){
        scanf("%d", &n[i]);
        res_size = res_size + n[i];
    }
/*
    for (int i = 0; i<k; i++)
        printf("%d ", n[i]);
    printf("\n");
    printf("%d ", res_size);
*/
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue)*res_size);
    InitPrioritiQueue(q,res_size);

    for (int i = 0; i<res_size; i++){
        scanf("%d", &num);
        Insert(q, num);
    }
    for (int i = 0; i<res_size; i++){
        printf("%d ", ExtractMax(q));
    }

    free(q->heap);
    free(q);

    return 0;
}