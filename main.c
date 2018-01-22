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
    newNode->word = (char *) malloc(sizeof(char) * (wordSize));
    strncpy(newNode->word, newWord, wordSize);
    //newNode->word[wordSize] = '\0';
    newNode->count = 1;
    newNode->parentPtr = parent;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;
    return newNode;
}

//Compares new word and recursively moves through tree and creates new node if not found
void checkWord(char newWord[], int wordSize, struct bTreeNode *root){
    //word already exists in tree
    if (strncmp(newWord, root->word, sizeof(char) * wordSize) == 0){
        root->count = root->count + 1;
    }
        //Before Alphabetically
    else if (strcmp(newWord, root->word)<0){
        if(root->leftChildPtr == NULL){
            root->leftChildPtr = newBTreeNode(newWord, wordSize, root);
        }
        else{
            checkWord(newWord, wordSize, root->leftChildPtr);
        }
    }
        //After Alphabetically
    else {
        if(root->rightChildPtr == NULL){
            root->rightChildPtr = newBTreeNode(newWord, wordSize, root);
        }
        else{
        checkWord(newWord, wordSize, root->rightChildPtr);
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
            if  (root == NULL){
                buffer[count] = '\0';
                root = newBTreeNode(buffer, count, NULL);
            }
            else{
                buffer[count] = '\0';
                checkWord(buffer, count, root);
            }
            count = 0;
            clearBuffer(buffer, size);

        }

    }
    if  (root == NULL){
        buffer[count-1] = '\0';
        root = newBTreeNode(buffer, count, NULL);
    }
    else{
        buffer[count-1] = '\0';
        checkWord(buffer, count, root);
    }
    if (feof(fPointer)){
        printf("End of file.");
    }


    fclose(fPointer);

    char * fileSuffix = strpbrk(fileName, "0");
    char outputFileName[50] = "myoutput\0";
    strcat(outputFileName, fileSuffix);
    FILE * outputFile = fopen(outputFileName, "wb");
    inOrderTraversal(root, outputFile);
    fclose(outputFile);

    destroyTree(root);

    exit(0);
}
