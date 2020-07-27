#include <stdio.h>
#include <stdlib.h>

struct stack {
        int *data;
    int top;
    int cap;
};

int max(int a, int b){
    int m;
    m = (a > b) ? a : b;
    return m;
}

int min(int a, int b){
    int m;
    m = a < b ? a : b;
    return m;
}

int StackEmpty(struct stack *s){
    int empty = 0;
    if (empty == s->top) return 1;
    else return 0;
}

void Push(struct stack *s, int x){
    if(s->top == s->cap) printf("Full");
    s->data[s->top] = x;
    s->top = s->top + 1;
}

int Pop(struct stack *s){
    int x;
    if (StackEmpty(s) == 1) printf("You did smth wrong :<");
    else{
        x = s->data[--s->top];
    }
    return x;
}

void InitStack(struct stack *s, int n){
    s->data = (int *)malloc(sizeof(struct stack)*n);
    s->top = 0;
    s->cap = n;
}

int main(){
    int n; //amount of operations
    int x; //number
    int a,b; //operands
    scanf("%d", &n);
    struct stack *s = (struct stack *)malloc(sizeof(struct stack)*n);
    InitStack(s, n);

    char buf[80];
    char *request = buf;

    for (int i = 0; i<n; i++){
        //gets(request);
        scanf("%s", request);
        //printf("request = %s\n", request);
        if (request[0] == 'C'){ //+1 in stack
            scanf("%d", &x);
            //printf("x = %d\n", x);
        }
        else if (request[0] == 'A'){
            a = Pop(s);
            b = Pop(s);
            x = a + b;
        }
        else if (request[0] == 'S' && request[1] == 'U'){
            a = Pop(s);
            b = Pop(s);
            x = a - b;
        }
        else if (request[0] == 'M' && request[1] == 'U'){
            a = Pop(s);
            b = Pop(s);
            x = a * b;
        }
        else if (request[0] == 'D' && request[1] == 'I'){
            a = Pop(s);
            b = Pop(s);
            x = a/b;
        }
        else if (request[0] == 'M' && request[1] == 'A'){
            a = Pop(s);
            b = Pop(s);
            x = max(a,b);
        }
        else if (request[0] == 'M' && request[1] == 'I'){
            a = Pop(s);
            b = Pop(s);
            x = min(a,b);
        }
        else if (request[0] == 'N'){
            a = Pop(s);
            x = (-1)*a;
        }
        else if (request[0] == 'D' && request[1] == 'U'){
            x = Pop(s);
            Push(s, x);
        }
        else if (request[0] == 'S'){
            a = Pop(s);
            x = Pop(s);
            Push(s, a);
        }
        Push(s, x);
        //printf("x = %d\n", x);
    }
    printf("%d\n", Pop(s));
    free(s->data);
    free(s);
}