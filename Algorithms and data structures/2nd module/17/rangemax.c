#include <stdio.h>
#include <stdlib.h>

int max(int a, int b);
void update(int *res, int i, int j, int v, int a, int b);
void SegmentTree_Update(int *res, int i, int v, int n);
void Build(int *start, int i, int a, int b, int *res);
int SegmentTree_Query(int *res, int n, int l, int r);
void SegmentTree_Build(int *start, int n, int *res);
int query(int *res, int l, int r, int i, int a, int b);

int max(int a, int b){
    return a > b ? a : b; 
}

void update(int *res, int i, int j, int v, int a, int b){
        int medium = 0;
    if (a == b)
        res[i] = v;
    else{
        medium = (a+b)/2;
        if (j<=medium)
            update(res, 2*i+1, j, v, a, medium);
        else
            update(res, 2*i+2, j, v, medium+1, b);
        res[i] = max(res[2*i+1], res[2*i+2]);
    }
}


void SegmentTreeUpdate(int *res, int i, int v, int n){
    update(res, 0, i, v, 0, n-1);
}

void Build(int *start, int i, int a, int b, int *res){
    int medium = 0;
    if (a == b)
        res[i]=start[a];
    else{
        medium = (a+b)/2;
        Build(start, 2*i+1, a, medium, res);
        Build(start, 2*i+2, medium+1, b, res);
        res[i] = max(res[2*i+1], res[2*i+2]);
    }
}

int SegmentTree_Query(int *res, int n, int l, int r){
    int v;
    v = query(res, l, r, 0, 0, n-1);
    return v;
}

void SegmentTree_Build(int *start, int n, int *res){
    Build(start, 0, 0, n-1, res); //res - new tree
}

int query(int *res, int l, int r, int i, int a, int b){
    int medium = 0;
    int v = 0;
    if ((l == a) && (r == b)){
        v = res[i];
    } else {
        medium = (a+b)/2;
        if (r <= medium)
            v = query(res, l, r, 2*i+1, a, medium);
        else if (l > medium)
            v = query(res, l, r, 2*i+2, medium+1, b);
        else{
            v = max(query(res, l, medium, 2*i+1, a, medium), 
                query(res, medium+1, r, 2*i+2, medium+1, b));
        }
    }
    return v;
}

int main(){
    int n;

    scanf("%d", &n);

    int *start = (int *)malloc(sizeof(int)*n);
    for (int i = 0; i<n; i++)
        scanf("%d", &start[i]);
    /*for (int i = 0; i<n; i++)
        printf("start[%d] = %d\n", i, start[i]);*/
    int *res = (int *)malloc(sizeof(int)*n*6);
    int l, r;
    SegmentTree_Build(start, n, res);

    char s[77];
    char *str = s;

    int m = 0;
    scanf("%d", &m); //кол-во операций
    int v = 0; //присвоить значение //UPD
    int i = 0; //элементу с индексом //UPD
    for(int j = 0; j<m; j++){
        scanf("%s", str); // MAX or UPD + 2 number
        if ((str[0] == 'M') && (str[1] == 'A') && (str[2] == 'X')){
            scanf("%d %d", &l, &r);
            printf("%d\n", SegmentTree_Query(res, n, l, r));
        } else {
            if ((str[0] == 'U') && (str[1] == 'P') && (str[2] == 'D')){
                scanf("%d %d", &i, &v);
                SegmentTreeUpdate(res, i, v, n);
            }
        }
    }
    free(start);
    free(res);
}