#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
void fileGetFunc();
void createfile (void);
int isDirectoryExists(char path[]);
void createDirectory (char arr[]);
void fileCreator(char arr[]);


int main() {
    char *order = (char *) calloc(20,sizeof(char));
    scanf("%s",order);
    if (strcmp(order,"createfile") == 0) {
        fileGetFunc();
    }


}

void fileGetFunc() {
    char c;
    int counter = 0;
    while (1) {
        c = getchar();
        if (c == '/') {
            counter++;
            if (counter == 2) {
                createfile();
                break;
            }
        }
    }
}

void createfile(void) {

    char arr[100];
    int i = 0;
    char c;
    while (1) {
        c = getchar();
        if (c != '/' && c != '\0' && c != '\"' && c != '\n') {
            arr[i++] = c;
        }
        else if (c == '/') {
            isDirectoryExists(arr);
        }
        else if (c == '\0' || c == '\n' || c == '\"') {
            fileCreator(arr);
            break;
        }

    }


}
int isDirectoryExists(char path[]) {
    if(access(path,F_OK) == 0) {
        createDirectory(path);
    }
    else {
        char *dirName = path;
        chdir(dirName);
        createfile();
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