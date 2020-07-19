unsigned long peak(unsigned long nel, int (*less)(unsigned long i, unsigned long j)) { 
    unsigned long i = 0, a = 0; //a-нижняя граница
    unsigned long b = nel-1;    //b-верхняя граница

    if ((b-a) == 1)
            return i;
    else
        while (a < b){
            i = (a / 2 + b / 2);
            if (less(i, i + 1))
                a = i + 1;
            else if (less(i, i - 1)) 
                b = i - 1;
            else return i;
        }
    return a;
}
