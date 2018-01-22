#include <stdio.h>
#include <stdlib.h>

void clearBuffer(char buf[], int bufSize){
    for (int i = 0; i < bufSize; ++i) {
        buf[i] = NULL;
    }
}

//Binary Tree Node Struct
struct bTreeNode {
    char *word;
    int count;
    struct bTreeNode *parentPtr;
    struct bTreeNode *leftChildPtr;
    struct bTreeNode *rightChildPtr;
};

struct bTreeNode* newBTreeNode(char newWord[], int wordSize){
    struct bTreeNode * newNode = (struct bTreeNode*)malloc(sizeof(struct bTreeNode));
    newNode->word = (char *) malloc(sizeof(char) * wordSize);
    newNode->word = newWord;
    newNode->count = 1;
    newNode->parentPtr = NULL;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;
    return newNode;
}

int main(int argc, char **argv) {



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

    //read file
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
