void revarray(void *base, unsigned long nel, unsigned long width) { 
    char swap = *(char*)base;

    for(int i = 0; i < nel/2; i++){
        for(int j = 0; j < width; j++){
            swap = *(char*)(width*i + base + j);
            *(char*)(base + width*i + j) = *(char*)(base + width*((nel - 1) - i)+j);
            *(char*)(base + j + width*((nel - 1) - i)) = swap;
        }
    }
}