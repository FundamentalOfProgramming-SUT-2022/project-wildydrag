#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
void createfolder (void) {
    char s[100];
    char arr[] = "goodbye";
    char *dirName = arr;
    int dir = 0;
    dir  = mkdir(dirName, 0777);
    chdir(dirName);
    printf("%s\n",getcwd(s,100));
}

int main () {
createfolder();
return 0;
}

