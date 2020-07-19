#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Kadane(float *v, int n){
        int l = 0, r = 0, start = 0, i = 0;
    float maxsum = v[0];
    float sum = 0;
    while(i<n){
        sum = sum+v[i];
        if (sum > maxsum){
            maxsum = sum;
            l = start;
            r = i;
        }
        i++;
        if (sum<0){
            sum = 0;
            start = i;
        }
    }
    printf("%d %d\n", l, r);
}

int main(){
    int n;
    scanf("%d", &n);
    float *a = (float*)malloc(sizeof(float)*n); //числитель
    float *b = (float*)malloc(sizeof(float)*n); //знаменатель
    float *v = (float*)malloc(sizeof(float)*n);

    for (int i = 0; i<n; i++)
        scanf("%f/%f", &a[i], &b[i]);
    
    //for (int i = 0; i<n; i++)
    //  printf("%d/%d\n", a[i], b[i]);

    for(int i = 0; i<n; i++)
        v[i]=log(a[i]/b[i]);

    /*for (int i = 0; i<n; i++)
        printf("%f\n", v[i]);
    */
    Kadane(v, n);

    free(a);
    free(b);
    free(v);

    return 0;
}