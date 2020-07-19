void shellsort(unsigned long nel, int (*compare)(unsigned long i, unsigned long j), void (*swap)(unsigned long i, unsigned long j)) 
{
    unsigned long f0,f1,f;
    unsigned long d=0,i = 0;
    f0 = 1; f1 = 1;
    if ((nel == 1) || (nel == 2)) 
        f=1;
    else {
        for (i = 2; (f0+f1) < nel; i++){
            f=f0+f1;
            f0=f1;
            f1=f;
        }
    }
    
    unsigned long t = 0, j = 0;

    while (f>0){
        for(t = f; t < nel; t++){
            j=t;

            while((j>=f) && (compare(j-f,j) > 0)){
                swap(j,j-f);
                j-=f;
            }
        }

        f1=f;
        f=f0;
        f0=f1-f0;
        if ((f0 == 0) && (f1 == 1)) break;
    }
}