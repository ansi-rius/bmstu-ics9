#include <stdio.h>
#include <string.h>

int wcount(char *s);

int main(){
        char buf[80] = "";
    int n = 0;

    gets(buf);

    n = wcount(buf);

    printf("%d\n", n);
    
    for(int i=0; i<80; i++)
        buf[i]=0;
}

int wcount(char *s){

    int wc=0,i=0,len=0;
    int boolean = 0; //находимся ли мы в слове

    while (*(s+i) != 0){
        if (*(s+i) != ' ' && boolean == 0){
            boolean = 1;
            wc++;
        }
        else if (*(s+i) == ' ' || *(s+i) == '\n' || *(s+i) == '\t'){ //если вышли из слова
                boolean = 0;
        }
        i++;
    }

    return wc;
}
