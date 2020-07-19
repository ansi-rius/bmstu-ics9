int strdiff(char *a, char *b){
    int res=0, len = 0;

    if (strcmp(a,b) == 0) return -1;

        if (strlen(a) >= strlen(b)) 
            len =  strlen(b);
        else len = strlen(a);

        if (len == 0) return 0;

        for(int i=0; i<=len; i++){ //байты
            if (a[i] == b[i]){
                res +=8;
                //printf("res = %d\n", res);
                continue;
            }

            int j = 0;

            for (int j=0; j<8; j++){
                if (((a[i] >> j) & 1) == ((b[i] >> j) & 1)){ //биты
                    res++;
                    //printf("res! = %d\n", res);
                } else break;
            }
            
        break;
    }
    return res;
}