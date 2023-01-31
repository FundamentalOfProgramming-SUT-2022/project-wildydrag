#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void fileGetFunc();
void createfile (void);
int isDirectoryExists(char path[]);
void createDirectory (char arr[]);
void isFileExists(char path[]);
void fileCreator(char arr[]);
void getStr(char fileName[]);

int counterGlobInsertstr;

int main() {
    char *order = (char *) calloc(20,sizeof(char));
    scanf("%s",order);
    if (strcmp(order,"createfile") == 0) {
        fileGetFunc();
    }
    else if (strcmp(order,"insertstr") == 0) {
        counterGlobInsertstr++;
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

    char arr[100] = {0};
    int i = 0;
    char c = '\0';
    while (1) {
        c = getchar();
        if (c != '/' && c != '\0' && c != '\"' && c != '\n') {
            arr[i++] = c;
        }
        else if (c == '/') {
            isDirectoryExists(arr);
            break;
        }
        else if (c == '\0' || c == '\n' || c == '\"') {
            isFileExists(arr);
            break;
        }

    }


}
int isDirectoryExists(char path[]) {
    struct stat stats;

    stat(path,&stats);

    if(S_ISDIR(stats.st_mode)) {
        char *dirName = path;
        chdir(dirName);
        createfile();
    }
    else {
        createDirectory(path);
    }
}


void createDirectory (char path[]) {
    char *dirName = path;
    int dir = 0;
    dir = mkdir(dirName,0777);
    chdir(dirName);
    createfile();
}

void isFileExists(char arr[]) {
    if (access(arr,F_OK) == 0) {
        if (counterGlobInsertstr == 1){
            //do the necessary operations and give file name that is arr.
        }
        else {
            printf("The file already exists!");
        }
    }
    else {
        if (counterGlobInsertstr == 1)
            printf("The file doesn't exist");
        else
            fileCreator(arr);
    }
}


void fileCreator (char arr[]) {
        FILE *fptr;
        char *fileName = arr;
        fptr = fopen(fileName, "w");
        fclose(fptr);
}

void getStr(char fileName[]) {
    char arr[10000];
    int counter = 0, counter2 = 0, i = 0;
    char c;
    while(1) {
        c = getchar();
        if (c == ' ' && ++counter == 2) {
            c = getchar();
            if (c == '\"' && ++counter2 == 1) {
                while(1) {
                    c = getchar();
                    if (c == '\"' && arr[i - 1] != '\\' && arr[i - 2] != '\\')
                        break;
                    arr[i++] = c;
                }
                    //call the relevant function and pass array to it.
            }
            else {
                arr[i++] = c;
                if (c == ' ') {
                    //call the relevant function and pass array to it.
                    break;
                }
            }
        }
    }

}
