#include <stdio.h>
#include <string.h>

void print_substrings(char* s){
    for(; *s != '\0'; s++){
        printf("%d. %s\n", (int)strlen(s), s);
    }
}

int main(){
    char* myname = "Nivedita"; //Feel free to replace this with yours!
    print_substrings(myname);
    return 0;
}
