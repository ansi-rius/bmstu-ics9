#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int* Delta1(char *s){
        int len = strlen(s), size = 123;
    int *delta1 = (int *)malloc(sizeof(int)*size); //free!
    int a = 0, k = 0;
    while(a<size){
        delta1[a]=len;
        a++;
    }
    int j = 0;
    while(j<len){
        //k = atoi(s[j]);
        delta1[(int)s[j]]=len-j-1;
        j++;
    }
    return delta1;
}

int* Suffix(char *s){
    int len = strlen(s), t = 0;
    int *sigma = (int *)malloc(sizeof(int)*len); //free!
    /*for (int i = 0; i<len; i++){
        sigma[i]= i;
    }*/
    sigma[len - 1] = t = len - 1;
    int i = len - 2;
    while(i>=0){
        while((t<len-1) && (s[t] != s[i])){
            t = sigma[t+1];
        }
        if (s[t] == s[i])
            t--;
        sigma[i]=t;
        i--;
    }
    return sigma;
}

int* Delta2(char *s){
    int len = strlen(s);
    int *delta2 = (int *)malloc(sizeof(int)*len); //free!
    int *omega = Suffix(s);
    int i = 0;
    int t = omega[0];
    while(i<len){
        while(t<i){
            t = omega[t+1];
        }
        delta2[i] = -i+t+len;
        i++;
    }
    i = 0;
    while(i<len-1){
        t = i;
        while(t<len-1){
            t = omega[t+1];
            if (s[i] != s[t])
                delta2[t] = -(i+1)+len;
        }
        i++;
    }
    free(omega); //!
    return delta2;
}

int max(int a, int b)
{
    return a > b ? a : b; 
}

void BMSubst(char *s, char *t){
    int *delta1 = Delta1(s);
    int *delta2 = Delta2(s);
    int i, k = strlen(s)-1;
    while (k<strlen(t)){
        i = strlen(s) - 1;
        while(t[k] == s[i]){
            if (i == 0){
                printf("%d\n", k);
                break;
            }
            i--;
            k--;
        }
        //u = atoi(*(t+k));
        k = k + max(delta1[(int)t[k]], delta2[i]);
    }
    k = strlen(t);
    free(delta1); //!
    free(delta2); //!
}

int main(int argc, char **argv){
    BMSubst(argv[1],argv[2]);
    return 0;
}