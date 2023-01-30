#include <stdio.h>
#include <stdlib.h>

void filecreator (void) {
    int i;
    char arr1[] = "arr.txt";
    FILE * fptr;
    char *fileName = arr1; 
    fptr = fopen(fileName,"w");
    fclose(fptr);
}
int main () {
    filecreator();
    return 0;
}
