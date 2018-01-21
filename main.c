#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    void clearBuffer(char buf[], int bufSize);

    //Open file and check for success
    FILE* fPointer = fopen("input02.txt", "r");
    if(!fPointer){
        printf("Read file Error!");
        return EXIT_FAILURE;
    }


    //create buffer
    int size = 30;
    char buffer[size];
    clearBuffer(buffer, size);
    int c;
    int count = 0;
    while((c = fgetc(fPointer)) != EOF){
        buffer[count] = c;
        count ++;
        if (c == ' '){
            printf("%s\n", buffer);
            count = 0;
            clearBuffer(buffer, size);

        }

    }
    if (feof(fPointer)){
        printf("End of file.");
    }


    fclose(fPointer);
    exit(0);
}

void clearBuffer(char buf[], int bufSize){
    for (int i = 0; i < bufSize; ++i) {
        buf[i] = NULL;
    }
}