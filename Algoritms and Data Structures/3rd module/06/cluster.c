#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

int main(){
        //Количество узлов кластера
    int N;
    scanf("%d", &N);
    //printf("%d\n", N);

    long int *cluster;
    cluster = (long int *)malloc(sizeof(long int )*N);
    //Первоначальное время в кластерах
    for(int i = 0; i < N; i++)
            *(cluster+i) = 0;
    //Количество задач
    int M;
    scanf("%d", &M);
    //printf("%d\n", M);
    
    //Считываем время задач
    long int t1, t2;
    for(int i = 0; i < M; i++){
        scanf("%li%li", &t1, &t2);
        //printf("%li %li\n", t1, t2);
        //Находим 1-й свободный узел
        int start_first = FALSE;
        for(int i = 0; i < N; i++){
            if(*(cluster+i)<=t1){
                start_first = TRUE;
                *(cluster+i) = t1 + t2;
                break;
            }
        }
        if (!start_first){
            //Находим узел с минимальным временем заверш
            //выполнениня предыдущей задачи
            int i_min = 0;
            for(int i = 1; i < N; i++){
                if(*(cluster+i) < *(cluster+i_min))
                    i_min = i;
            }
            *(cluster+i_min) = *(cluster+i_min) + t2;
        }
    }
    //Находим максимальное время завершения
    long int max = 0;
    for(int i = 0; i < N; i++){
        if(*(cluster+i) > max)
            max = *(cluster+i);
    }
    printf("%li", max);
    free(cluster);
    return 0;
}
