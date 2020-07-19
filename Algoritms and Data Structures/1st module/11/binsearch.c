unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) {
    unsigned long a = 0, i = 0;
    unsigned long b = nel - 1;

    while (a <= b) {
        unsigned long i = (a+b)/2;
        
        if (compare(i) > 0){
            b = i - 1;
        }
        else if (compare(i) < 0){
            a = i + 1;
        }
        else if (compare(i) == 0)
            return i; 
    }
    return nel;
}
