#include <stdio.h>
void filegetfunc () {
    char c;
    while (1) {
    c = getchar();
    if (c == '/') {
        //call the relevant function
        

}
}


} 
int main () {
    char arr[100];
    int i = 0;
    char c;
    while (1) {
        //printf("the last input");
        //break;
                c = getchar();
                if (c != '/' && c != '\0' && c != '\"') {
                arr[i++] = c;
                 }
                else if (c == '/') {
                //call the relevant function
                break;
                }
                else if (c == '\0' || c == '\"') {
                //call the relevant function for creating the file and we pass arr to it
                break;
                }
         
         }}

}
