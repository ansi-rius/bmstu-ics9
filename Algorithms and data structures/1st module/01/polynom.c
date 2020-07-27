#include <stdio.h>
#include <math.h>
#include <string.h>

/*long helper(long a, long b){ //возвожу х в степень при подсчете производной.
    long step = a;
    while(b>1){
        step *= a;
        b--;
    }
    if (b == 0) (step = 1);
    //printf("%d\n", step);
    return step;
}*/

int main(){

    long a1, a2, x;
    int n,i;

    scanf("%d", &n);    //степень полинома
    scanf("%ld", &x);   //x0
    scanf("%ld", &a1);  //1ый коэффициент

    long pol = a1;        //Полином
    int j = n;

    long der = a1 * j;

    for(i = 0;i <= (n - 1); i++) {
        scanf("%ld", &a2); //2ой и все последующие коэффициенты
        j--;
        pol = pol * x + a2;
        if (i != (n-1)){
        der = der*x + a2*j;
        }
    }

    printf("%ld\n", pol);
    printf("%ld\n", der);

    return 0;
}