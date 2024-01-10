int asciicmp(char* a, char*b){
    int minlen = strlen(a) < strlen(b) ? strlen(a) : strlen(b);
    
    for( int i = 0; i<minlen; i++){
        if(a[i] < b[i]){
            return 1;
        }
        if(b[i] < a[i]){
            return -1;
        }
    }
    return 0;
}