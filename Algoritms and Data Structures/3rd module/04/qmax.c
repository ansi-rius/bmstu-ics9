#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0;
#define TRUE 1;

struct DStack{
    struct MStack *data;
    int cap;
    int top1, top2;
};

struct MStack{
    int a,b;
};

int StackEmpty1(struct DStack *s){
    int empty = 0;
    if (s->top1 == empty)
        return TRUE
    else return FALSE;
}

int StackEmpty2(struct DStack *s, int n) {
    int empty = n - 1;
    if (s->top2 == empty)
        return TRUE
    else return FALSE;
}

int max(int a, int b){
    int m;
    m = (a > b) ? a : b;
    return m;
}

int Pop1(struct DStack *s){
    if (StackEmpty1(s)){
        printf("Nope\n");
        return 0;
    }
    s->top1 = s->top1 - 1;
    return s->data[s->top1].a;
}

int Pop2(struct DStack *s, int n){
    if (StackEmpty2(s,n)){
        printf("Nope\n");
        return 0;
    }
    s->top2++;
    return s->data[s->top2].a;
}

void Push1(struct DStack *s, int x){
    if (s->top2 < s->top1)
        printf("Full1\n");
    s->data[s->top1].a = x;

    if (s->top1 == 0)
        s->data[s->top1].b = s->data[s->top1].a;
    else {
        if (s->data[s->top1].a > s->data[s->top1 - 1].b) {
            s->data[s->top1].b = s->data[s->top1].a;
        } else
            s->data[s->top1].b = s->data[s->top1 - 1].b;
        //s->data[s->top1].b = max(s->data[s->top1].a , s->data[s->top1 - 1].b); поч-то не пашет
    }
    s->top1 = s->top1 + 1;



}

void Push2(struct DStack *s, int x){
    if (s->top2 < s->top1)
        printf("Full2\n");
    s->data[s->top2].a = x;

    if (s->top2 == s->cap - 1)
        s->data[s->cap - 1].b = s->data[s->cap- 1].a;
    else{
        if (s->data[s->top2].a > s->data[s->top2 + 1].b) {
            s->data[s->top2].b = s->data[s->top2].a;
        } else
            s->data[s->top2].b = s->data[s->top2 + 1].b;
    }
    s->top2 = s->top2 - 1;


    //s->data[s->top1].b = max(s->data[s->top2].a , s->data[s->top2 + 1].b); поч-то не пашет
}

void InitQueue(struct DStack *s, int n){
    s->data = (struct MStack *)malloc(sizeof(struct MStack)*n);
    s->cap = n;
    s->top1 = 0;
    s->top2 = n-1;
}

void Enqueue(struct DStack *s, int x){
    Push1(s,x);
}

int Dequeue(struct DStack *s, int n) {
    if(StackEmpty2(s,n)){
        while (!StackEmpty1(s)){
            Push2(s, Pop1(s));
        }
    }
    return Pop2(s,n);
}


void QueueEmpty(struct DStack *s, int n) {
    printf((StackEmpty1(s)) && (StackEmpty2(s,n)) ? "true\n" : "false\n");
}

int Maximum(struct DStack *s, int n){
    int tme;
    if (StackEmpty1(s))
        return s->data[s->top2 + 1].b;
    else if (StackEmpty2(s,n))
        return s->data[s->top1 - 1].b;
    else{
        tme = ((s->data[s->top2 + 1].b) > (s->data[s->top1 - 1].b)) ? (s->data[s->top2 + 1].b) : (s->data[s->top1 - 1].b);
        return tme;
    }
}

int main() {
    int n, x;
    scanf("%d", &n);
    struct DStack *s = (struct DStack*)malloc(sizeof(struct DStack)*n);
    InitQueue(s,n);

    char buf[80];
    char *request = buf;

    for(int i = 0; i<n; i++){
        scanf("%s", request);
        if (strcmp(request,"ENQ") == 0){
            scanf("%d", &x);
            Enqueue(s,x);
        }
        else if (strcmp(request, "DEQ") == 0){
            printf("%d\n", Dequeue(s,n));
        }
        else if (strcmp(request,"MAX") == 0){
            printf("%d\n", Maximum(s,n));
        }
        else if (strcmp(request, "EMPTY") == 0){
            QueueEmpty(s,n);
        }
        //printf("%d\n", strcmp(request,"ENQ"));
        //printf("%d\n", strcmp(request, "DEQ"));
        //printf("%d\n", strcmp(request,"MAX"));
        //printf("%d\n", strcmp(request, "EMPTY"));
    }
    free(s->data);
    free(s);
    return 0;
}