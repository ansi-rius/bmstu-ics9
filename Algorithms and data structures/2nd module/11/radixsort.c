#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGITS 4

union Int32
{
    int x;
    unsigned char bytes[DIGITS];
};

int read_bytes(union Int32 radix, int m);
void printInt32(union Int32 *S, int n, int m);

int key(union Int32 S, int i_key);
union Int32 *RadixSort(int q, int m, union Int32 *S, int n);
union Int32 *DistributionSort(int i_key, int m, union Int32 *S, int n);
union Int32 *NegativePositive(union Int32 *S, int n);

int main(int argc, char **argv){
    int n, x;

    scanf("%d",&n);
    //printf("%d\n",n);

    union Int32 *S;
    S = (union Int32 *)malloc(sizeof(union Int32)*n);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d",&x);
        S[i].x = x;
    }

    int q = DIGITS, m = 256;

    /*
    printInt32(S, n, m);

    for(int j = 0; j<n; j++){
        printf("%d ", S[j].x);
        for(int i = q-1; i>=0; i--){
            printf("\t%d", S[j].bytes[i]);
        }
        printf("\n");
    }
    */
    
    union Int32 *D = RadixSort(q, m, S, n);
    //printInt32(D, n, m);
    D = NegativePositive(D, n);
    printInt32(D, n, m);
    
    free(D); //!
    free(S); //!
    return 0; 
}

int read_bytes(union Int32 S, int m){
    int b = 1, x = 0;
    for(int j=0; j<DIGITS; j++){
        x = x + S.bytes[j] * b;
        b = b * m;
    }
    return x;
}

int key(union Int32 S, int i_key){
    return S.bytes[DIGITS-1-i_key];
}

void printInt32(union Int32 *S, int n, int m){
    for(int i=0; i<n; i++)
        printf("%d ", read_bytes(S[i], m));
    printf("\n");
}

union Int32 *RadixSort(int q, int m, union Int32 *S, int n){
    union Int32 *D;
    D = (union Int32 *)malloc(sizeof(union Int32)*n);
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

union Int32 *DistributionSort(int i_key, int m, union Int32 *S, int n)
{
    int *count;
    count = (int *)malloc(sizeof(int)*m);
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

    union Int32 *D;
    D = (union Int32 *)malloc(sizeof(union Int32)*n);
    j=n-1;
    while (j>=0){
        k=key(S[j], i_key);
        i=count[k]-1;
        count[k]=i;
        D[i] = S[j];
        j=j-1;
    }
    
    free(S); //!
    free(count); //!

    return D;
}

union Int32 *NegativePositive(union Int32 *S, int n){ //располагаю отрицательные
    union Int32 *D;                                   //по нужным местам
    D = (union Int32 *)malloc(sizeof(union Int32)*n);

    int i, start_negative = 0;
    for(i=0; i<n; i++){
        if (((abs((S[i]).bytes[3]-255)) >> 7) == 0){
            start_negative = i;
            break;
        }
    }
    int j = 0;
    for(i=start_negative; i<n; i++,j++)
        *(D+j) = *(S+i);

    for(i=0; i<start_negative; i++,j++)
        *(D+j) = *(S+i);

    free(S); //!

    return D;
}
