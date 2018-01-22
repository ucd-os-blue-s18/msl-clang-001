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

//Binary Tree Constructor
struct bTreeNode* newBTreeNode(char newWord[], int wordSize, struct bTreeNode* parent){
    struct bTreeNode * newNode = (struct bTreeNode*)malloc(sizeof(struct bTreeNode));
    //Add one to wordSize to account for null terminator
    newNode->word = (char *) malloc(sizeof(char) * (wordSize + 1));
    strcpy(newNode->word, newWord);
    //Add null terminator
    newNode->word[wordSize] = '\0';
    newNode->count = 1;
    newNode->parentPtr = parent;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;
    return newNode;
}

//Compares new word and recursively moves through tree and creates new node if not found
void insertIntoTree(char *newWord, int wordSize, struct bTreeNode *node){
    //word already exists in tree
    if (strcmp(newWord, node->word) == 0){
        node->count = node->count + 1;
    }
        //Before Alphabetically
    else if (strcmp(newWord, node->word) < 0){
        if(node->leftChildPtr == NULL){
            node->leftChildPtr = newBTreeNode(newWord, wordSize, node);
        }
        else{
            insertIntoTree(newWord, wordSize, node->leftChildPtr);
        }
    }
        //After Alphabetically
    else {
        if(node->rightChildPtr == NULL){
            node->rightChildPtr = newBTreeNode(newWord, wordSize, node);
        }
        else{
            insertIntoTree(newWord, wordSize, node->rightChildPtr);
        }
    }
}

void inOrderTraversal(struct bTreeNode * node, FILE * outputFile) {
    if(node->leftChildPtr) {
        inOrderTraversal(node->leftChildPtr, outputFile);
    }

    fprintf(outputFile, "%s: %i\r\n", node->word, node->count);

    if(node->rightChildPtr) {
        inOrderTraversal(node->rightChildPtr, outputFile);
    }

    return;
}


void destroyTree(struct bTreeNode * node) {
    if(node->leftChildPtr) {
        destroyTree(node->leftChildPtr);
    }

    if(node->rightChildPtr) {
        destroyTree(node->rightChildPtr);
    }

    free(node->word);
    free(node);
}

int main(int argc, char **argv) {
    //Open file and check for success
    char fileName[50];
    sprintf(fileName, "%s", argv[1]);
    FILE* fPointer = fopen(fileName, "r");
    if(!fPointer){
        printf("Read file Error!");
        return EXIT_FAILURE;
    }

    //create buffer
    const int size = 30;
    char buffer[size];
    clearBuffer(buffer, size);

    int c;
    int position = 0;
    struct bTreeNode* root = NULL;

    //read file
    do {
        c = fgetc(fPointer);
        if (c == ' ' || c == EOF){
            buffer[position] = '\0';

            if (root == NULL){
                root = newBTreeNode(buffer, position, NULL);
            }
            else {
                insertIntoTree(buffer, position, root);
            }
            position = 0;
            clearBuffer(buffer, size);
        }
        else {
            buffer[position] = c;
            position++;
        }

    } while(c != EOF);
    fclose(fPointer);

    // Generate output file
    char * fileSuffix = strpbrk(fileName, "0");
    char outputFileName[50] = "myoutput\0";
    strcat(outputFileName, fileSuffix);
    FILE * outputFile = fopen(outputFileName, "wb");
    inOrderTraversal(root, outputFile);
    fclose(outputFile);

    destroyTree(root);

    exit(0);
}
