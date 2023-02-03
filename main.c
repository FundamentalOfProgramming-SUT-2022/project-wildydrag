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
void insertString(char arr[],char fileName[],int len);
void catReadFile(char fileName[]);
//void catGetFunc(void);
void removeStrPoseSize(char fileName[]); //this function is also used for copystr
void removingTheStr(int col,int row,int size,char flag,char fileName[]);
void pasteStr(int ,int,char fileName[]);
void getFuncFind (void);
void getFindTags(char fileName[]);
int findStrFunc(char fileName[]);

int counterrGlobCreateFile;
int counterGlobInsertstr;
int counterQuotesForStr;
int counterQuotesForStr2;
int counterGlobcat;
int counterGlobRemoveStr;
int counterGlobCopyStr;
int counterGlobCutStr;
int counterGlobPaste;
int counterGlobForPasteSize;
int counterGlobFind;
int counterSpecialSpace;
int counterIndexStar;
char strToBeFound[10000];
char *strFindTag[2];
int sizeOf_at;
int counterNotIndex;


int main() {
//    printf("inja miad");
    char *order = (char *) calloc(20,sizeof(char));
    scanf("%s",order);
    if (strcmp(order,"createfile") == 0) {
        counterrGlobCreateFile++;
        fileGetFunc();
//        printf("%d\n",counterrGlobCreateFile);
    }
    else if (strcmp(order,"insertstr") == 0) {
        counterGlobInsertstr++;
        fileGetFunc();
    }
    else if (strcmp(order,"cat") == 0) {
        counterGlobcat++;
        fileGetFunc();
    }
    else if (strcmp(order,"removestr") == 0) {
        counterGlobRemoveStr++;
        fileGetFunc();
    }
    else if (strcmp(order,"copystr") == 0) {
        counterGlobCopyStr++;
        fileGetFunc();
    }
    else if(strcmp(order,"cutstr") == 0) {
        counterGlobCutStr++;
        fileGetFunc();
    }
    else if(strcmp(order,"pastestr") == 0) {
//        printf("inja miad");
        counterGlobPaste++;
        fileGetFunc();
    }
    else if(strcmp(order,"find") == 0) {
        counterGlobFind++;
        fileGetFunc();
    }
}

void fileGetFunc() {
//    printf("inja miad");
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
//    printf("inja miad");
    char arr[100] = {0};
    char help[100] = {0};
    int counter = 0;
    int i = 0 , j = 0;
    char c = '\0';
    while (1) {
        c = getchar();
        help[j++] = c;
        if (counterGlobInsertstr == 1 || counterGlobRemoveStr == 1 || counterGlobCopyStr == 1
            || counterGlobCutStr == 1 || counterGlobPaste == 1 || counterrGlobCreateFile == 1
            || counterGlobFind == 1){ //this part should be considered if after the address we still take command
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
            if (c != '/' && c != '\0' && c != '\"' && c != '\n') { //this part of code should be improved.
                arr[i++] = c;
            }
            else if (c == '/') {
                isDirectoryExists(arr);
                break;
            }
            else if (c == '\0' || c == '\n' || c == '\"') { //this part of code must be improved
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

    if(S_ISDIR(stats.st_mode)) { //it means that the directory exists.
        char *dirName = path;
        chdir(dirName);
        createfile();
    }
    else {
        if(counterrGlobCreateFile == 1) {
            createDirectory(path);
        }
        else {
            printf("the directory doesn't exist");
        }
//        printf("%d",counterrGlobCreateFile); //why was it printed 11?
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
//    printf("%s",fileName);
//    printf("inja miad");
    int a = access(fileName,F_OK);
//    printf("%d",a);
    if (a == 0) { //it means that it exists
        if (counterGlobInsertstr == 1){
            getStr(fileName);
        }
        if (counterGlobFind == 1) {
            getFindTags(fileName);
        }
        else if (counterGlobRemoveStr == 1 || counterGlobCopyStr == 1 ||
                 counterGlobCutStr == 1 || counterGlobPaste == 1) {
//            printf("inja miad");
            removeStrPoseSize(fileName);
        }
        else if (counterGlobcat == 1) {
            catReadFile(fileName);
        }
        else if (counterrGlobCreateFile == 1){
            printf("The file already exists!");
        }
    }
    else { //the file doesn't exists
        if (counterGlobInsertstr == 1 || counterGlobRemoveStr == 1 || counterGlobcat == 1 ||
            counterGlobCopyStr == 1 || counterGlobCutStr == 1 || counterGlobPaste == 1 ||
            counterGlobFind == 1) //i 'm not sure about cat in this condition think about it later on
            printf("The file doesn't exist"); //later add exit or return 0 after this line of code.
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
    char help[10000];
    int counter = 0, counter2 = 0, i = 0, j = 0,len = 0;
    char c;
    while(1) {
        c = getchar();
        if (counterQuotesForStr == 0 && counter == 0) {
            counter++;
        }
        if (c == ' ') {
            counter++;
        }
        if (c == ' ' && counter == 2) {
            c = getchar();
            if (c == '\"' && ++counter2 == 1) {
                while(1) {
                    c = getchar();
                    if ((c == '\"' && help[j - 1] != '\\') || (c == '\"' && help[j - 1] == '\\' && help[j - 2] == '\\')) {
                        counterQuotesForStr2++;
                    }

                    if (c == '\\' && arr[i - 1] == '\\') {
                        arr[i - 1] = c;
                        i--;
                        len--;
                    }
                    if (c == 'n' && arr[i - 1] == '\\') {
                        c = '\n';
                        arr[i - 1] = c;
                        i--;
                        len--;
                    }
                    if ((c == '\"' && help[j - 1] != '\\') || (c == '\"' && help[j - 1] == '\\' && help[j - 2] == '\\')) {
                        break;
                    }
                    if (c == '\"' && arr[i - 1] == '\\') {
                        arr [i - 1] = c;
                        i--;
                        len--;
                    }
                    arr[i++] = c;
                    help[j++] = c;
                    len++;
                }
                insertString(arr,fileName,len);
            }
            else {
                while(1) {
                    arr[i++] = c;
                    len++;
                    c = getchar();
                    if (c == '\\' && arr[i - 1] == '\\') {
                        arr[i - 1] = c;
                        i--;
                        len--;
                    }
                    if (c == 'n' && arr[i - 1] == '\\') {
                        c = '\n';
                        arr[i - 1] = c;
                        i--;
                        len--;
                    }
                    if (c == '\"' && arr[i - 1] == '\\') {
                        arr [i - 1] = c;
                        i--;
                        len--;
                    }
                    if (c == ' ') {
                        insertString(arr, fileName,len);
                        break;
                    }
                }
            }
            break; //this break is put here randomly so it may cause some problems.
        }
    }
}
void insertString(char arr[],char fileName[],int len) {
    char *size = arr;
    int counterRow = 1, counterCol = 0, counterChar = 0;
    int row = 0, col = 0, counter = 0;
    char c;
    while (1) {
        c = getchar();
        if (counterQuotesForStr2 == 1) {
            counter++;
        }
        if (c == ' ' && counter != 1) {
            scanf("%d%c%d", &row, &c, &col);
            break;
        }
    }

    char *temp = "temp.txt";
    FILE *original;
    FILE *insert;
    original = fopen(fileName, "r");
    insert = fopen(temp, "w");
    if (original == NULL || insert == NULL) {
        printf("unable to open the file");
    }

    while (1) {
        c = fgetc(original);
        if (c == '\n') {
            counterCol++;
            if (counterRow == row && col > counterCol){
                printf("Out of index"); // you have to implement this part of code to
                exit(0);                 //similar parts as well.
            }
            counterRow++;
            counterChar += counterCol;
            counterCol = 0;
        }
        if (c == EOF) {
            if (counterRow < row) {  // good improvements here is made that needs to be implemented on other parts as well
                printf("out of index");
                exit(0);
            }
        }
        else if (c != '\n' && c != EOF) {
            counterCol++;
        }
        if (col != 0) {
            if (counterCol == col && counterRow == row) {
                counterChar += col;
//                printf("inja miyad");
                break;
            }
        }
        else if (col == 0) {
            if (counterRow == row) {
                break;
            }
        }
    }
    rewind(original);
    int counterGeneral = 0;
    while(1) {
        c = fgetc(original);
        if (counterChar == 0) {
            counterGeneral--;
        }
        counterGeneral++;
        if (counterGeneral == counterChar) {
            if (counterChar != 0) {
                fputc(c, insert);
            }
            for (int i = 0; i < len; i++) {
                fputc(arr[i],insert);
                counterGeneral++;
            }
            if (counterChar == 0) {
                fputc(c,insert);
            }
            c = fgetc(original);
        }
        if (c == EOF) {
            break;
        }
        fputc(c,insert);
    }
    fclose(original);
    fclose(insert);
    remove(fileName);
    rename(temp,fileName);
}

void catReadFile(char fileName[]) {
    FILE *fp;
    char c;
    fp = fopen(fileName,"r");
    if (NULL == fp) {
        printf("The file can't be read");
    }
    while(1) {
        c = fgetc(fp);
        if (c != EOF) {
            printf("%c",c);
        }
        else {
            break;
        }
    }
    fclose(fp);
}

void removeStrPoseSize(char fileName[]) {
//    printf("inja miad");
    char c;
    char flag;
    int row = 0, col = 0, size = 0, counterSpace = 0, counterSpace2 = 0;
    while (1) {
        c = getchar();
        if (counterQuotesForStr == 0 && counterSpace == 0) {
            counterSpace++;
        }
        if (c == ' ') { // also test this part when '\"' comes to the game.
            counterSpace++;
        }
        if (counterGlobPaste == 0) {
            if (c == ' ' && counterSpace == 2) {
                scanf("%d%c%d", &row, &c, &col);
                break;
            }
        }
        else if (counterGlobPaste == 1) {
            if (c == ' ' && counterSpace == 2) { // this part of code should be restored to the previous part
                scanf("%d%c%d",&row, &c, &col); // it is redundant
                // call the relevant function
                //give the relevant data to them
                //one of them is insertstr
                // the other is copy or cut strl
                pasteStr(col,row,fileName);
                exit(0);
            }
        }
    }
    while (1) {
        c = getchar();
        if (c == ' ') {
            counterSpace2++;
        }
        if (counterSpace2 == 2) {
            scanf("%d",&size);
        }
        if (c == 'b' || c == 'f') {
            flag = c;
            break;
        }
    }
    removingTheStr(col,row,size,flag,fileName); //it also works for copystr

}

void removingTheStr(int col,int row,int size,char flag,char fileName[]) {
//    printf("the row valus is: %d\n",row);
    counterGlobForPasteSize == size;
    int counterGeneral = 0;
    int counterGeneral2 = 0;
    int j = 0, counterRow = 1, counterCol = 0, counterChar = 0;
    char *temp ="temp.txt";
    char *duplicate =".copy.txt";
    // if there were any bugs you can put char temp[100] as an alternative
    char c;
    FILE *original;
    FILE *del;
    FILE *copy;
    original = fopen(fileName,"r");
    del = fopen(temp,"w"); // just a file opened with the w mode
    copy = fopen(duplicate,"w");
    if (original == NULL || del == NULL) {
        printf("unable to open the file");
    }
    while (1) {
        c = fgetc(original);
        if (c == '\n') {
            counterCol++;
            if (counterRow == row && col > counterRow) {
                printf("out of index");
                exit(0);
            }
            counterRow++;
            counterChar += counterCol;//This part of code is prone to bug be careful and think more if needed
//            printf("%d\n",counterChar);
//            printf("%d\n",counterRow);
            counterCol = 0;
        }
        if (c == EOF) {
            if (counterRow < row) {
                printf("out of index");
                exit(0);
            }
        }
        else if(c != '\n' && c != EOF) { //why is it always true? dubious
            counterCol++;
//            printf("%d ",counterCol);
        }
        if (col != 0) {
            if (counterCol == col && counterRow == row) {
                counterChar += col;
//                printf("inja miyad");
                break;
            }
        }
        else if (col == 0) {
            if(counterRow == row) {
//                printf("%d\n",counterChar);
                break;
            }
        }



    }
    rewind(original);
//    fseek(original,0,SEEK_END);
//    printf("%ld\n",ftell(original));
//    rewind(original);
//    printf("inja miad\n");
    while (1) {
//        printf("miyad");
//        printf("inja miad");
        if (flag == 'f') {
//            printf("inja miad");
            while (1) {
                if (counterGlobCopyStr == 1 || counterGlobCutStr == 1) {
                    while (1) {
                        c = fgetc(original);
                        if (counterChar == 0) {
                            counterGeneral--;
                        }
                        counterGeneral++;
                        if (counterGeneral == counterChar) {
                            if (counterChar == 0 && c != EOF) {
                                fputc(c, copy);
                            }
                            for (int i = 0; i < size; i++) {
                                c = fgetc(original);
                                fputc(c, copy);
                            }
                            rewind(original);
                            break;
                        }
                        else if (c == EOF) { //may cause bugs in that case put if
                            printf("the line position doesn't exist");
                            rewind(original);
                            break;
                        }
                    }
                }
                if (counterGlobCopyStr == 1 && counterGlobCutStr == 0) {
                    break;
                }
                if (counterGlobRemoveStr == 1 || counterGlobCutStr == 1){
                    while(1) {
                        c = fgetc(original);
                        if (counterChar == 0) {
                            counterGeneral2--;
                        }
                        counterGeneral2++;
                        if (counterGeneral2 == (counterChar)) {//may want to add or subtract 1 to or from size
                            if ((counterChar != 0) && (c != EOF)) {
                                fputc(c, del);
                            }
                            for (int i = 0; i < size; i++) {
                                c = fgetc(original); //just take the chars we want to remove and as if put them aside
                                counterGeneral2++;
                            }
                        } else if (c != EOF) {
                            fputc(c, del);
                        }//maybe should be beneath the counter++ or beneath the if
                        else if (c == EOF) {
                            break;
                        }
                    }
                }
                break;
            }
            break; // just put it here be aware not to cause any bugs
        }
        else if (flag == 'b') {
//            printf("inja miad");
            while (1) {
//                printf("inja miad");
                if(counterGlobCopyStr == 1 || counterGlobCutStr == 1) {
//                    printf("inja miad");
                    while(1) {
                        c = fgetc(original);
                        printf("infinite loop");
                        if (counterChar < size) {
                            int static counter = 0;
                            counter++;
                            if (counter == 1) {
                                printf("you want to copy more than existed characters backward");
                            }
                        } else if (counterChar >= size) {
                            counterGeneral++;
                            if (counterChar == size) {
                                counterGeneral--;
                            }
                        }
                        if (counterGeneral == counterChar - size) {
                            if ((counterChar - size) == 0 && (c != EOF)) {
                                fputc(c, copy);
                            }
                            for (int i = 0; i < size; i++) {
                                c = fgetc(original);
                                fputc(c, copy);
//                            counterGeneral++; //i'm not sure whether this part of code is required or not.
                            }
                            rewind(original);
                            break;
                        }
                        else if (c == EOF) { //may cause some bugs.
                            printf("the line position doesn't exist");
                            rewind(original);
                            break;
                        }
                    }
                }
                if (counterGlobCopyStr == 1 && counterGlobCutStr == 0){
                    break;
                }
                if (counterGlobRemoveStr == 1 || counterGlobCutStr == 1) {
                    while(1) {
                        c = fgetc(original);
                        if (counterChar < size) {
                            int static counter2 = 0;
                            counter2++;
                            if (counter2 == 1) {
                                printf("you want to delete more than availabe characters!");
                            }
                        } else if (counterChar >= size) {
                            counterGeneral2++;
                            if (counterChar == size) {
                                counterGeneral2--;
                            }
                        }
                        if (counterGeneral2 == counterChar - size) {
                            if ((counterChar - size) != 0 && (c != EOF)) {
                                fputc(c, del);
                            }
                            for (int i = 0; i < size; i++) {
                                c = fgetc(original);
                                counterGeneral2++;
                            }
                        } else if (c != EOF) {
                            fputc(c, del);
                        } else if (c == EOF) {
                            break;
                        }
                    }
                }
                break;
            }
            break;
        }
//        break;
    }
    fclose(original);
    fclose(del);
    fclose(copy);
    if (counterGlobRemoveStr == 1 || counterGlobCutStr == 1) {
        remove(fileName);
        rename(temp, fileName);
    }
}

void pasteStr(int col,int row,char fileName[]) {
    int counterRow = 1, counterCol = 0, counterChar = 0;
//    printf("inja miad");
    int counter = 0;
    char c;
    char hold;
//    printf("%d %d",row ,col);
    char *temp = "temp.txt";
    char *clipboard = ".copy.txt";
    FILE *original;
    FILE *paste;
    FILE *insert;
    paste = fopen(clipboard, "r");// clipboard which we want to read from
    original = fopen(fileName,"r"); // the file we want to insert from the clipboard
    insert = fopen(temp,"w");
    if (original == NULL || paste == NULL || insert == NULL) {
        printf("unable to open the file");

    }
    while (1) {
        c = fgetc(original);
        if (c == '\n') {
            counterCol++;
            if (counterRow == row && col > counterCol){
                printf("col Out of index"); // you have to implement this part of code to
                exit(0);                 //similar parts as well.
            }
            counterRow++;
            counterChar += counterCol;
            counterCol = 0;
        }
        if (c == EOF) { // this part of code added here and in insert and also should be added in copy and cut
            if (counterRow < row) {
                printf("row out of index");
                exit(0);
            }
        }
        else if (c != '\n' && c != EOF) {
            counterCol++;
        }
        if (col != 0) {
            if (counterCol == col && counterRow == row) {
                counterChar += col;
//                printf("inja miyad");
                break;
            }
        }
        else if (col == 0) {
            if (counterRow == row) {
                break;
            }
        }
    }
    rewind(original);
    int counterGeneral = 0;
    while(1) {
        c = fgetc(original);
        if (counterChar == 0) {
            counterGeneral--;
        }
        counterGeneral++;
        if (counterGeneral == counterChar) {
            if (counterChar != 0) { // this part of code added here and in insert command
                fputc(c, insert);
            }
            hold = c;
            for (int i = 0; c != EOF; i++) {
                c = fgetc(paste);
                if (c != EOF) {
                    fputc(c, insert);
                }
                counterGeneral++;
            }
            if (counterChar == 0) {// this part of code added here and in insert command
                fputc(hold,insert);
            }
            c = fgetc(original);
        }
        if (c == EOF) {
            break;
        }
        fputc(c,insert);
    }
    fclose(original);
    fclose(paste);
    fclose(insert);
    remove(fileName);
    rename(temp,fileName);
}

void getFuncFind () {
    int counterSpace = 0, i = 0, counterNumberOfStars = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ') {
            counterSpace++;
        }
        if (counterSpace == 2) {
            c = getchar();
            if (c == '\"') {
                while (1) {
                    c = getchar();
                    if (c == ' ') {
                        counterSpecialSpace++; //global use

                    }
                    if( (c == '\"' && strToBeFound[i - 1] != '\\') || (c == '\"'
                                                                       && strToBeFound[i - 1] == '\\' && strToBeFound[i - 2] == '\\')) {
                        break;
                    }
                    else {
                        strToBeFound[i++] = c;
                    }
                    if (counterNumberOfStars < 1) {
                        if (c == '*' && strToBeFound[i - 2] != '\\') {
                            counterNumberOfStars++;
                            counterIndexStar += --i;
                            counterNotIndex++;

                        }
                    }

                }
            }
            else {
                while(1) {
                    strToBeFound[i++] = c;
                    c = getchar();
                    if (c == ' ') {
                        break;
                    }
                }
            }
            break;
        }
    }
    fileGetFunc();
}

void getFindTags (char fileName[]) {
    char c;
    int i = 0, z = 0, spacecounter = 0, counterL = 0;
    char help[30];
    while (1) {
        c = getchar();
        help[z++] = c;
        if (c == 'a') {
            c == getchar();
        }
        if (c == ' ') {
            spacecounter++;
            c = getchar();
            if (c != '-' || c == '\0' || c == '\n') {
                break;
            }
            else {
                c = getchar();
            }
        }
        switch (c) {
            case 'b':
                strFindTag[i++] = "byword";
                break;
            case 't': {
                if (help[z - 2] != 'n') {
                    strFindTag[i++] = "at";
                    while (1) {
                        c = getchar();
                        scanf("%d", &sizeOf_at);
                        break;
                    }
                }
                break;
            }
            case 'l':
                counterL++;
                if (counterL == 1) {
                    strFindTag[i++] = "all";
                }
                break;
            case 'c':
                strFindTag[i++] = "count";
                break;
            default:
                break;
        }
        if (i > 2) {
            printf("logical error");
            exit(1);
        }
        if (c == '\0' || c == '\n') {
            break;
        }
    }
    int l = 0;
    if (*(*strFindTag + l) =='c' && *(*(strFindTag + 1) + l ) != '\0') {
        printf("you can not give this input");
    }
    if (*(*strFindTag + l) == 'a' && *(*(strFindTag + 1) + l) == 'a') {
        printf("you can't give this input");
    }

}

int findStrFunc(char fileName[]) {
    char buffer[100000];
    int countwords = 0, starcondition = 0, counterGeneral = 0;  //shows the position of the cursor
    int counterEntranceWhile = 0, len = 0;
    int originalcount = 0; //used for count attribute
    char c;
    int l = 0;
    int n = 0, i = 0, m = 0, j = 0;
    FILE *find;
    find = fopen(fileName, "r");
    m = strlen(strToBeFound); // it may have bugs be aware
    while (1) {
        if (fgets(buffer, 100000, find) == NULL) {
            printf("not found!");
            return 1;
        }
        n = strlen(buffer);

        while (i < n) {
            counterEntranceWhile == 0;
            j = 0;
            starcondition = 1;
            while (starcondition) {
                counterEntranceWhile++;
                starcondition = (i < n && j < m && buffer[i++] == strToBeFound[j++]);
                if (starcondition == 0 && counterEntranceWhile == 1) {
                    break;
                }
                if (buffer[i - 1] == ' ') {
                    countwords++;
                }
                counterGeneral++; //maybe static i donno
            }
            if (counterNotIndex != 0) {
                if (counterIndexStar == --j && counterSpecialSpace == 0) {
                    if (buffer[i - 1] != ' ' && buffer[i - 1] != EOF &&
                        buffer[i - 1] != '\0') {
                        starcondition = 1;
                    }
                } else if (counterIndexStar == --j && counterSpecialSpace != 0) {
                    // this part of code needs to be thought carefully
                }

            }
            if (j == m) {
                originalcount++;
                if (*(*strFindTag + l) == 'b' || *(*(strFindTag + 1) + l) == 'b') {
                    printf("%d", countwords); //it is okay because it is first occurence
                    exit(0); //the countWords my be add or min to one
                } else if (*(*strFindTag + l) == 'a' && *(*strFindTag + ++l) == 't') {
                    if (originalcount == sizeOf_at) {
                        printf("%d", counterGeneral);
                    } else if (sizeOf_at > originalcount) {
                        printf("number of finding is less than at's number");
                        exit(1); //it must return one
                    }
                } else if (*(*strFindTag + l) == 'a' && *(*strFindTag + ++l) == 'l') {
                    printf("%d ", counterGeneral);

                } else if (
                        (*(*strFindTag + l) == 'a' && *(*strFindTag + ++l) == 'l' && *(*(strFindTag + 1) + --l) == 'b')
                        || *(*strFindTag + l) == 'b' && *(*(strFindTag + 1) + --l) == 'a' &&
                           *(*(strFindTag + 1) + ++l) == 'l') {
                    printf("%d ", countwords);
                } else if (
                        (*(*strFindTag + l) == 'a' && *(*strFindTag + ++l) == 't' && *(*(strFindTag + 1) + --l) == 'b')
                        || *(*strFindTag + l) == 'b' && *(*(strFindTag + 1) + --l) == 'a' &&
                           *(*(strFindTag + 1) + ++l) == 't') {
                    if (originalcount == sizeOf_at) {
                        printf("%d", countwords);
                    }
                } else if (*(*strFindTag + l) == '\0' && *(*(strFindTag + 1) + l) == '\0') {
                    printf("%d", counterGeneral);
                    exit(0);
                }


            }
            while (i < n && buffer[i] != ' ') {
                ++i;
            }
            ++i;

        }

    }
    if (*(*strFindTag + l) =='c') {
        printf("%d",originalcount);
    }
    fclose(find);


}