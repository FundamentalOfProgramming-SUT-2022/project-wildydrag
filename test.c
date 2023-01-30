#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main () {
    int i;
    FILE *  fptr;
    char fn[50];
    char str[] = "Guru99 Rocks\n";
    fptr = fopen("test1.txt","w");
    for (i = 0; str[i] != '\n'; i++) {
        fputc(str[i],fptr);
    }
    fclose(fptr);
    return 0;
}
