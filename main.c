#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void fileGetFunc();
void createfile (void);
void isDirectoryExists(char path[]);
void createDirectory (char arr[]);
void isFileExists(char path[]);
void fileCreator(char arr[]);
void getStr(char fileName[]);
void insertString(char arr[],char fileName[]);

int counterGlobInsertstr;
int counterQuotesForStr;
int counterQuotesForStr2;

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
        if (c == '\"') {
            counterQuotesForStr++;
        }
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
    char help[100] = {0};
    int counter = 0;
    int i = 0 , j = 0;
    char c = '\0';
    while (1) {
        c = getchar();
        help[j++] = c;
        if (counterGlobInsertstr == 1){
            if (counterQuotesForStr == 1) {
                if ((c != '/' && (((c != '\"' || help[j - 1] == '\\')) && (c != '\"' || help[j - 1] != '\\' || help[j - 2] != '\\')))) {
                    arr[i++] = c;
                }
                else if (c == '/') {
                    isDirectoryExists(arr);
                    break;
                }
                else if ((c == '\"' && help[j - 1] != '\\') || (c == '\"' && help[j - 1] == '\\' && help[j - 2] == '\\')) {  //here is little tricky and may cause bugs be aware
                    isFileExists(arr);
                    break;
                }
            }
            else {
                if (c != '/' && c != ' ') {
                    arr[i++] = c;
                }
                else if (c == '/') {
                    isDirectoryExists(arr);
                    break;
                }
                else if (c == ' ') {
                    isFileExists(arr);
                    break;
                }


            }
        }
        else {
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

//        else if (c == ' ') {
//            isFileExists(arr);
//            break;
//        }

    }


}
void isDirectoryExists(char path[]) {
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

void isFileExists(char fileName[]) { // here if you faced bug it is probably because i changed arr to fileName.
    if (access(fileName,F_OK) == 0) { //it means that it exists
        if (counterGlobInsertstr == 1){
            getStr(fileName);
        }
        else {
            printf("The file already exists!");
        }
    }
    else {
        if (counterGlobInsertstr == 1)
            printf("The file doesn't exist");
        else
            fileCreator(fileName);
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
        if (counterQuotesForStr == 0) {
            counter++;
        }
        if (c == ' ' && ++counter == 2) {
            c = getchar();
            if (c == '\"' && ++counter2 == 1) {
                while(1) {
                    c = getchar();
                    if ((c == '\"' && arr[i - 1] != '\\') || (c == '\"' && arr[i - 1] == '\\' && arr[i - 2] == '\\')) {
                        counterQuotesForStr2++;
                    }

                    if (c == '\\' && arr[i - 1] == '\\') {
                        arr[i - 1] = c;
                        i--;
                    }
                    if (c == 'n' && arr[i - 1] == '\\') {
                        c = '\n';
                        arr[i - 1] = c;
                        i--;
                    }
                    if ((c == '\"' && arr[i - 1] != '\\') || (c == '\"' && arr[i - 1] == '\\' && arr[i - 2] == '\\')) {
                        break;
                    }
                    if (c == '\"' && arr[i - 1] == '\\') {
                        arr [i - 1] = c;
                        i--;
                    }
                    arr[i++] = c;
                }
                insertString(arr,fileName);
            }
            else {
                while(1) {
                    arr[i++] = c;
                    c = getchar();
                    if (c == '\\' && arr[i - 1] == '\\') {
                        arr[i - 1] = c;
                        i--;
                    }
                    if (c == 'n' && arr[i - 1] == '\\') {
                        c = '\n';
                        arr[i - 1] = c;
                        i--;
                    }
                    if (c == '\"' && arr[i - 1] == '\\') {
                        arr [i - 1] = c;
                        i--;
                    }
                    if (c == ' ') {
                        insertString(arr, fileName);
                        break;
                    }
                }
            }
            break; //this break is put here randomly so it may cause some problems.
        }
    }
}
void insertString(char arr[],char fileName[]) {
    char *size = arr;
    int row = 0, col = 0, counter = 0;
    char c;
    while (1) {
        c = getchar();
        if (counterQuotesForStr2 == 1) {
            counter++;
        }
        if (c == ' ' && counter != 1) {
            scanf("%d%c%d",&row,&c,&col);
            break;
        }
    }
    printf("%d %d",row,col);
    FILE *fp;
    char enter[] = "\n";
    char space[] = " ";
    fp = fopen(fileName,"w");
    for (int i = 0; i < row; i++) {
        fwrite(enter,1,sizeof(enter),fp);
    }
    for (int i = 0; i < col; i++) {
        fwrite(space,1,sizeof(space),fp);
    }
    fclose(fp);
    fp = fopen(fileName,"a");
    fwrite(size,1,sizeof(size),fp);
    fclose(fp);
}

