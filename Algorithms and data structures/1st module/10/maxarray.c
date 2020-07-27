int maxarray(void *base, unsigned long nel, unsigned long width, int (*compare)(void *a, void *b)) { 
    int i, ind = 0;

    unsigned long *max = base;
    
    for(int i = 0; i < nel; i++){
        if (compare((base + i*width),(base + (i+1)*width)) < 0){
            if (compare(max, (base + (i+1)*width)) < 0){
                max = (base + (i+1)*width);
                ind = i+1;
                //printf("%d\n", i);
            }
            //printf("%d\n", ind);
        }
        if (compare((base + i*width),(base + (i+1)*width)) > 0){
            if (compare(max, (base + i*width)) < 0){
                max = (base + i*width);
                ind = i+1;
                //printf("%d\n", i);
            }
            //printf("%d\n", ind);
        }
    }
    return ind;
}