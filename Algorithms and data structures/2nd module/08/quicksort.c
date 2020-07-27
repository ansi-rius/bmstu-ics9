#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int i, int j);
int partition(int low, int high, int *p);
void quicksort(int low, int high, int *p, int m);
void print(int *a, int q);

int main(){
        int n, m;
    
    //printf("n = ");
    scanf("%d", &n);

    //printf("m = ");
    scanf("%d", &m);

    int *v;
    
    v = (int *)malloc(sizeof(int)*n);

    int i;
    
    for(i = 0; i < n; i++)
    {
        //printf("v[%d] = ", i);
        scanf("%d", v + i);
    }

    //print(v, n);

    quicksort(0, n-1, v, m);

    print(v, n);
    free(v);

    return 0;
}

void selectsort(int high, int *p){
    int j = 0, i = 0, k = 0;
    j = high;
    while (j > 0){
        k = j;
        i = j - 1;
        while (i>=0){
            if (p[k]<p[i])
                k=i;
            i=i-1;
        }
        swap(p,j,k);
        j = j - 1;
    }
}

void swap(int *a, int i, int j){
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int partition(int low, int high, int *p){
    int i = low;
    int j = low;
    while (j<high){
        if (p[j]<p[high]){
            swap(p,i,j);
            i = i+1;
        }
        j = j+1;
    }
    swap(p,i,high);
    return i;
}

void quicksort(int low, int high, int *p, int m){
    int q = 0;
    if (high-low>m){
        q = partition(low,high, p);
        quicksort(low, q-1, p,m);
        quicksort(q+1, high, p,m);
    }
    else
        selectsort(high,p);
}

void print(int *a, int q){
    //printf("\n");
    for (int i = 0; i < q; ++i)
    {
        printf("%d\n", *(a+i));
    }
}