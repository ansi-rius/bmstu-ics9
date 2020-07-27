#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *concat(char **s, int n);

int main(int argc, char **argv) {
    int n; //кол-во строк

    scanf("%d\n", &n);
    
    char **s;
    s = (char **)malloc(sizeof(char*)*n);

    char buf[80]; //храним слово
    int lenbuf;   //размер слова

    for (int i = 0; i < n; i++) {
        gets(buf);
        lenbuf = strlen(buf);  //храним размер слова
        s[i] = (char *)malloc(sizeof(char)*(lenbuf + 1));
        for (int j = 0; j < lenbuf + 1; j++) {
            *(*(s+i)+j)=buf[j]; //помещаем слова в s
        }
    }
    
    char *str = concat(s, n);

    printf("%s\n", str);
    for (int i = 0; i < n; i++) {
        free(*(s+i));
    }

    free(s);
    free(str);

    return 0; 
}

char *concat(char **s, int n) {
    int lenstr = 0; //длина результирующей строки

    for (int i = 0; i < n; i++) {
        lenstr += strlen(s[i]); //ищем общую длинну результирующей строки
    }

    char *str = (char *)malloc(sizeof(char) * (lenstr + 1)); //результ строка
    
    int k = 0;
    for (int i = 0; i < n; i++) {

        int lenbuf = strlen(s[i]); //размер слова

        for (int j = 0; j < lenbuf; j++) {
            str[k] = *(*(s+i)+j);  //склеиваем
            k++;
        }
    }
    str[k] = 0;

    return str;
}