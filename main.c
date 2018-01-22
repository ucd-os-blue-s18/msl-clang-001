#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct bTreeNode* newBTreeNode(char newWord[], int wordSize, struct bTreeNode* parent){
    struct bTreeNode * newNode = (struct bTreeNode*)malloc(sizeof(struct bTreeNode));
    newNode->word = (char *) malloc(sizeof(char) * wordSize);
    strncpy(newNode->word, newWord, wordSize);
    newNode->count = 1;
    newNode->parentPtr = parent;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;
    return newNode;
}

void checkWord(char newWord[], int wordSize, struct bTreeNode *root){
    if (strncmp(newWord, root->word, sizeof(char) * wordSize) == 0){
        root->count = root->count + 1;
        //printf("Word: %s %d\n", root->word, root->count);
    }
        //Before Alphabetically
    else if (strcmp(newWord, root->word)<0){
        if(root->leftChildPtr == NULL){
            root->leftChildPtr = newBTreeNode(newWord, wordSize, root);
            //printf("New Left Word: %s \n", newWord);
        }
        else{
            checkWord(newWord, wordSize, root->leftChildPtr);
        }
    }
        //After Alphabetically
    else {
        if(root->rightChildPtr == NULL){
            root->rightChildPtr = newBTreeNode(newWord, wordSize, root);
            //printf("New Right Word: %s \n", newWord);
        }
        else{
        checkWord(newWord, wordSize, root->rightChildPtr);
        }
    }
}

void inOrderTraversal(struct bTreeNode * node) {
    if(node->leftChildPtr) {
        inOrderTraversal(node->leftChildPtr);
    }

    FILE * outputFile = fopen("test_output.txt", "ab");
    fprintf(outputFile, "%s: %i\r\n", node->word, node->count);
    fclose(outputFile);

    if(node->rightChildPtr) {
        inOrderTraversal(node->rightChildPtr);
    }

    return;
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
    struct bTreeNode* root = NULL;

    //read file
    while((c = fgetc(fPointer)) != EOF){
        buffer[count] = c;
        count ++;
        if (c == ' '){
            //printf("%s\n", buffer);
            if  (root == NULL){
                root = newBTreeNode(buffer, count - 1, NULL);
            }
            else{
                checkWord(buffer, count - 1, root);
            }
            count = 0;
            clearBuffer(buffer, size);

        }

    }
    if (feof(fPointer)){
        printf("End of file.");
    }


    fclose(fPointer);

    inOrderTraversal(root);
    exit(0);
}
