#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int nod(int x, int y)
{
    int a = abs(x), b = abs(y);
    while (a && b) {
        if (a >= b)
            a -= b;
        else
            b -= a;
    }
    return a | b;
}

int* ComputeLogarithms(int m){
    int k = (1 << (m + 1));
    int *logar = (int*)malloc(k*sizeof(int));
        int i = 1;
    int j = 0;
    while (i<=m){
        k = (1 << i);
        while(j<k){
            logar[j]=i-1;
            j=j+1;
        }
        i=i+1;
    }
    return logar;
}
//запрос к разреженной таблице
int SparseTable_Query(int **ST, int l, int r, int *logar){
    int j = logar[r-l+1];
    int k = (1<<j);
    return nod(ST[l][j], ST[r-k + 1][j]);
}
//построение таблицы
int **SparseTable_build(int *v, int n, int *logar){
    int m = logar[n] + 1;
    int **ST = (int**)malloc(sizeof(int *)*n);
    for (int i = 0; i < n; i++)
        ST[i] = (int*)malloc(sizeof(int)*(m+1));
    
    int i;
    for(i = 0; i < n; i++)
        ST[i][0] = v[i];
    int j;
    for(j = 1; j < m; j++){
        int k = (1 << j);
        for(i = 0; i <= n - k; i++){
            int kl = (1 << (j - 1));
            ST[i][j] = nod(ST[i][j-1], ST[i + kl][j - 1]);
        }
    }
    return ST;
}

int main(){
    int n;
    scanf("%d", &n);
    int *start = (int *)malloc((n+2)*sizeof(int));

    for(int i = 0; i<n; i++)
        scanf("%d", &start[i]);
    
    int *logar = ComputeLogarithms(log2(n)+2);

    int **ST  = SparseTable_build(start, n, logar);

    int m, l, r, i = 0;
    scanf("%d", &m);
    while (i<m){
        scanf("%d %d", &l, &r);
        printf("%d\n", SparseTable_Query(ST, l, r, logar));
        i++;
    }
    free(start);
    free(logar);
    for (int i = 0; i < n; i++)
        free(ST[i]);
    free(ST);
}