#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGITS 4
#define BASE 256

union Int32{
    int x;
    unsigned char bytes[DIGITS];
};

struct Date {
    int Day, Month, Year;
};

void printInt32(struct Date *S, int n, int m);

int key(struct Date S, int i_key);
struct Date *RadixSort(int q, int m, struct Date *S, int n);
struct Date *DistributionSort(int i_key, int m, struct Date *S, int n);

int main(int argc, char **argv){
    int n, yyyy, mm, dd;

    scanf("%d",&n);
    //printf("%d\n",n);

    struct Date *S = (struct Date *)malloc(sizeof(struct Date)*n);
    
    for(int i=0; i<n; i++){
        scanf("%d %d %d", &yyyy, &mm, &dd);
        S[i].Day = dd;
        S[i].Month = mm;
        S[i].Year = yyyy;
    }

    int q = DIGITS, m = BASE;

    //printInt32(S, n, m);
    
    struct Date *D = RadixSort(q, m, S, n);
    printInt32(D, n, m);
    
    free(D);
    free(S);

    return 0; 
}

int key(struct Date S, int i_key){ //разряды

    switch(DIGITS-1-i_key){
        case 0: return S.Day;
        case 1: return S.Month;
        case 2: return S.Year%BASE;
        case 3: return S.Year/BASE;
    }
}

void printInt32(struct Date *S, int n, int m){
    
    for(int i=0; i<n; i++){
        printf("%d ", S[i].Year);
        printf("%d ", S[i].Month);
        printf("%d\n", S[i].Day);
    }
}

struct Date *RadixSort(int q, int m, struct Date *S, int n){
    struct Date *D = (struct Date *)malloc(sizeof(struct Date)*n);
    int i;
    for(i=0; i<n; i++)
        *(D+i) = *(S+i);
    i = q - 1;
    while(i >= 0){
        D = DistributionSort(i, m, D, n);
        i = i - 1;
    }
    return D;
}

struct Date *DistributionSort(int i_key, int m, struct Date *S, int n){
    int *count = (int *)malloc(sizeof(int)*m);
    int i;
    for(i=0; i<m; i++)
        count[i] = 0;
    
    int j=0,k;
    while (j<n){
        k=key(S[j], i_key);
        count[k]=count[k]+1;
        j=j+1;
    }
    i=1;
    while (i<m){
        count[i]=count[i]+count[i-1];
        i=i+1;
    }


    struct Date *D = (struct Date *)malloc(sizeof(struct Date)*n);
    j=n-1;
    while (j>=0){
        k=key(S[j], i_key);
        i=count[k]-1;
        count[k]=i;
        D[i] = S[j];
        j=j-1;
    }
    
    free(S);
    free(count);

    return D;
}