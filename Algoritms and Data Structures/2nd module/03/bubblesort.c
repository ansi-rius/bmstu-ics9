void bubblesort(unsigned long nel, int (*compare)(unsigned long i, unsigned long j), void (*swap)(unsigned long i, unsigned long j)) 
{ 
    unsigned long r,l,f,z1,z2,k = 0, k1 = 0;

    l = 0;
    r = nel-1;
    f = 1;
    z1 = r;
    z2 = l;

    while (l < r){
        k = 0;
        for(int i = z2; i<r; i++){
            if (compare(i,i+1) > 0){
                swap(i,i+1);
                z1=i;
                k++;
            }
        }
        if (k == 0) break;

        r = z1;
        k1 = 0;
        for (int i = z1; i>l; i--){

            if (compare(i-1,i) > 0){
                swap(i-1,i);
                z2=i;
                k1++;
            }
        }
        if (k1 == 0) break;
        l = z2;
    }
}