#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void createfile (void);
void createDirectory (char arr[]);
void fileCreator(char arr[]);


int main() {
    char *order = (char *) calloc(20,sizeof(char));
    scanf("%s",order);
    if (strcmp(order,"createfile") == 0) {
        createfile();
    }


}

void createfile(void) {
    char arr[100];
    int i = 0;
    char c;
    while (1) {
        c = getchar();
        if (c != '/' && c != '\0' && c != '\"') {
            arr[i++] = c;
        }
        else if (c == '/') {
            createDirectory(arr);
        }
        else if (c == '\0' || c == '\"') {
            fileCreator(arr);
            break;
        }

    }


}

void createDirectory (char arr[]) {
    char *dirName = arr;
    int dir = 0;
    dir = mkdir(dirName,0777);
    chdir(dirName);
    createfile();
}

void fileCreator (char arr[]) {
    FILE * fptr;
    char *fileName = arr;
    fptr = fopen(fileName,"w");
    fclose(fptr);
}
