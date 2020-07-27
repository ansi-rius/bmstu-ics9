#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int superstr(char **s, int n, int *a);

void swap(int *a, int i, int j);
int Combination(int *a, int n);


int main(int argc, char **argv)
{
        int n;
        //printf("n = ");
    scanf("%d\n", &n);
    
    char **s;
    s = (char **)malloc(sizeof(char*)*n); //строка

    char buf[80];
    int lenbuf, lenall = 0;

    for (int i = 0; i < n; i++){

        gets (buf); //считываю строки
        lenbuf = strlen(buf);

        *(s+i) = (char *)malloc(sizeof(char)*(lenbuf + 1));

        for (int j = 0; j < lenbuf + 1; j++){
            *(*(s+i)+j)=buf[j];
        }
        lenall+=lenbuf; //ищу макс длину
    }
    int *a = (int *)malloc(sizeof(int)*n); //перестановки

    for (int i = 0; i < n; i++){
        a[i] = i;
    }

    int intersection; //пересечение (какие буквы сошлись в двух словах)
    int max = superstr(s,n,a);
    
    while (Combination(a, n)){
        intersection = superstr(s,n,a);
        if(intersection > max){
            max=intersection; //ищу макс пересечение
        }
    }
    printf("%d\n", lenall-max);

    free(a);
    //
    
    for (int i = 0; i < n; i++){
        free(*(s+i));
    }
    free(s);
    s = 0;

    return 0; 
}

int superstr(char **s, int n, int *a)
{
    int inter = 0;  //кол-во букв в пересечении
    for(int k=1; k<n; k++){
        //printf("%d><%d ", *(a+k-1), *(a+k));

        int prev = *(a+k-1); //индекс предыдущей строки
        int curr = *(a+k);   //индекс текущей строки
        int lenprev = strlen(*(s+prev)); //длина пред
        int lencurr = strlen(*(s+curr)); //длина тек

        for(int i=0; i<lenprev; i++){
            if(*(*(s+prev)+i)==*(*(s+curr)+0)){
                int f = 1; //флаг
                
                for(int j=i; j<lenprev; j++){
                    if(*(*(s+prev)+j) != *(*(s+curr)+j-i) ||
                       *(*(s+curr)+j-i) == lencurr){
                        f = 0; //флаг
                        break;
                    }
                }
                if(f){
                    inter += lenprev - i;
                    break;
                }
            }
        }
    }
    return inter; //кол-во букв в пересечении
}
void swap(int *a, int i, int j)
{
    int swp = a[i]; a[i] = a[j]; a[j] = swp;
}

int Combination(int *a, int n){ //перестановки строк загоняю в массив а
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1]){
        j--;
    }
    if (j == -1){
        return 0; // больше перестановок нет
    }
    int k = n - 1;
    while (a[j] >= a[k]){
        k--;
    }
    swap(a, j, k);
    int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
    while (l<r){
        swap(a, l++, r--);
    }
    return 1;
}