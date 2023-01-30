#include <stdio.h>

int main () {
    char arr[30];
    scanf("%s",arr);
    printf("%s",arr);
    while(1) {
        char c;
        c = getchar();
        printf("%c",c);
        if (c == 'p') {
            break;
        }
} 
    return 0;
}
