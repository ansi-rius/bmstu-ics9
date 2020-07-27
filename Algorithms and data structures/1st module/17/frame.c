#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv){
        if (argc != 4){
        printf("Usage: frame <height> <width> <text>\n");
        return 0;
    }
    int h, w, c;
    char *buf;
    h=atoi(argv[1]);
    w=atoi(argv[2]);
    buf = argv[3];
    int len = strlen(buf);
    c = (w-len)/2;
    if ((len > w-2) || ((h-2)<1)){
        printf("Error");
        return 0;
    }
    int i = 0;
    while (i<w){
        printf("*");
        i++;
    }
    printf("\n");
    int n = 2;
    if (h % 2 != 0) n--;
    for (int i = n; i<h/2;i++){
        for (int j = 0; j<w; j++){
            if ((j == 0) || (j == w-1)){
                printf("*");
                if (j == w-1)
                    printf("\n");
            }
            else printf(" ");
        }
    }
    i = h/2;
    if (i == h/2){
        for(int j = 0; j<c;j++){
            if (j == 0)
                printf("*");
            else printf(" ");
            }
        printf("%s", buf);
        for(int j = len+c; j<w;j++){
            if (j == w-1)
                printf("*");
            else printf(" ");
            }
    }
    printf("\n");
    if (h % 2 != 0)
        h -= 1;

    for (int i = (h/2)+1; i<h;i++){
        for (int j = 0; j<w; j++){
            if ((j == 0) || (j == w-1)){
                printf("*");
                if (j == w-1)
                    printf("\n");
            }
            else printf(" ");
        }
    }
    i=0;
    while (i<w){
        printf("*");
        i++;
    }
    printf("\n"); 
    return 0;
}