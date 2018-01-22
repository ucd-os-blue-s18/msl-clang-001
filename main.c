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
    newNode->word = (char *) malloc(sizeof(char) * (wordSize));
    strncpy(newNode->word, newWord, wordSize);
    //newNode->word[wordSize] = '\0';
    newNode->count = 1;
    newNode->parentPtr = parent;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;
    printf(newNode->word);
    printf("\n");
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
    //printf("%s: %i\r\n", node->word, node->count);
    fprintf(outputFile, "%s: %i\r\n", node->word, node->count);
    fclose(outputFile);

    if(node->rightChildPtr) {
        inOrderTraversal(node->rightChildPtr);
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
    printf("%s\n", buffer);
    //buffer[count] = c;
    //count ++;
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

    FILE * outputFile = fopen("test_output.txt", "wb");
    fclose(outputFile);
    inOrderTraversal(root);
    destroyTree(root);
    exit(0);
}
