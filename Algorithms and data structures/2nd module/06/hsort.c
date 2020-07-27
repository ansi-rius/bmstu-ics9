#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int array[100]; //правильное расположение индексов в результир. массиве
void print(char **s, int n);
void swap(int *a, int i, int j);
void buildheap(int n, int *base);
void heapify(int *base, int i, int n);
void hsort(void *base, size_t nel, size_t width,int (*compare)(const void *a, const void *b));
int compare(const void *a, const void *b);

int main(){
        int n; //кол-во строк
    scanf("%d\n", &n);
    
    char **s = (char **)malloc(sizeof(char*)*n);

    char buf[80]; //храним слово
    int lenbuf;   //размер слова

    for (int i = 0; i < n; i++)
    {
        gets(buf);
        lenbuf = strlen(buf);  //храним размер слова
            *(s + i) = (char *)malloc(sizeof(char)*(lenbuf + 1));
        for (int j = 0; j < lenbuf + 1; j++)
        {
            *(*(s + i) + j)=buf[j]; //помещаем слова в s
        }
    }

    int *counta = (int *)malloc(sizeof(int)*n);
    int count = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < strlen(*(s + i)); j++){
            if (*(*(s + i) + j) == 'a')
                count++;
        }
        //printf("c = %d\n", count);
        *(counta + i) = count;
        count = 0;
    }
    //int *p = counta;

    int k = 0;
    for (k = 0; k < n; k++) array[k] = k;

    hsort(counta,n,80,compare);
    //print(s,n);
    //for (int i = 0; i < n; i++)
        //printf("a = %d\n", counta[i]);

    for (int i = 0; i < n; i++)
        printf("%s\n", s[array[i]]);
    /*for(int i = 0; i<n; i++)
        printf("c[%d]= %d\n", i, *(counta +i));*/

    for (int i = 0; i < n; i++)
        free(*(s+i));

    free(s);
    free(counta);

}

void swap(int *a, int i, int j)
{
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void print(char **s, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", *(s+i));
    }
}

void buildheap(int n, int *base){
    int i = n/2-1;
    while (i >= 0){
        heapify(base, i, n);
        i--;
    }
}

int compare(const void *a, const void *b){
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

void heapify(int *base,int i, int n){ //переупорядочить эл-ты, чтобы итый эл явл корнем пир
    while(1){
        int l = 2*i + 1;
        int r = l + 1;
        int j = i;
        if ((compare(l,n) < 0) && (compare(base[i],base[l]) < 0))
            i = l;
        if  ((compare(r,n) < 0) && (compare(base[i],base[r]) < 0))
            i = r;
        if (compare(i,j) == 0) break;
        swap(base, i,j);
        swap(array,i,j);
    }
}

void hsort(void *base, size_t nel, size_t width,int (*compare)(const void *a, const void *b)) 
{ 
     buildheap(nel, base);
     int i = nel - 1;
     while(i > 0){
        swap (base, 0, i);
        swap (array, 0, i);
        heapify(base,0,i);
        i--;
     }
}