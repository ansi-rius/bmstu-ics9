#include <stdio.h>
#include <stdlib.h>

void MergeSortRec(int low, int high, int *p);
void Merge(int k, int l, int m, int *p);
void InsertSort(int *p, int low, int high);

int main(){
        int n;
    scanf("%d", &n);
    int p[n];

    for(int i = 0; i < n; i++){
        scanf("%d", &p[i]);
    }
    int *buf = p;

    MergeSortRec(0, n-1, buf);

    for(int i = 0; i < n; i++){
        printf("%d\n", p[i]);
    }
}

void InsertSort(int *p, int low, int high){
    int i = low;
    int elem = 0, loc = 0;
    while (i<high+1){
        elem = p[i];
        loc = i - 1;
        while ((loc >= 0) && (abs(p[loc])>abs(elem))){
            p[loc+1] = p[loc];
            loc = loc - 1;
        }
        p[loc+1] = elem;
        i = i + 1;
    }
    //printf("!\n");
}

void MergeSortRec(int low, int high, int *p){
    int med = 0;
    if (high-low+1 <= 5){
        InsertSort(p, low, high);
    }
    else if (low < high){ 
        med = (low+high)/2;
        MergeSortRec(low, med, p);
        MergeSortRec(med+1, high, p);
        Merge(low, med, high, p);
    }
}

void Merge(int k, int l, int m, int *p){
    int t[m-k+1];
    int i = k;
    int j = l+1;
    int h = 0;
    while(h < m - k + 1){
        if ((j <= m) && ((i == l+1) || (abs(p[j]) < abs(p[i])))){
            t[h] = p[j];
            j = j + 1;
        }
        else{
            t[h] = p[i];
            i = i + 1;
        }
        h = h + 1;
    }
    for (int r = 0; r < h; r++)
        p[r+k]=t[r];
}