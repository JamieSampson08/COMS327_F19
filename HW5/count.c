// Author - Jamie Sampson
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node Node;
struct node {
    char *word;
    unsigned int count;
    Node *nextNode;
};

Node* addToList(Node* listPtr, char* word);
Node* inList(char *word, Node *listPtr);
void printList(Node *listPtr);

int main(int argc, char** argv) {
//    FILE * file = fopen(argv[1], "r");
//    if(!file) {
//        fprintf(stderr, "Error opening: %s", argv[1]);
//        file = stdin;
//    }
    FILE *file = stdin;
    char *word = malloc(sizeof(char));
    int wordPosition = 0;

    Node *listPtr = NULL;

    while(!feof(file)) {
        // error handling for words longer than 32
        if (wordPosition > 32) {
            fprintf(stderr, "Word in input file contains too many characters.\n");
            exit(1);
        }
        char character = fgetc(file);
        // convert to lower case
        character = tolower(character);
        if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')){
            // append the character to the running word
            word = realloc(word, (wordPosition+1) * sizeof(char));
            word[wordPosition] = character;
            wordPosition++;
        }
        // if character isn't a letter a-z or A-Z
        else {
            // a new word hasn't been started
            if(!word[0]){
                continue;
            }
            word[wordPosition] = '\0';
            // words separated by non-letters, so add to list
            listPtr = addToList(listPtr, word);
            word = malloc(sizeof(char));
            wordPosition = 0;
        }
    }
    printList(listPtr);
    free(word);
}

/**
 * Adds a word node to the list
 * @param listPtr list to append/update to
 * @param word to add/update
 * @return list of words
 */
Node* addToList(Node* listPtr, char* word){
    // check if the node already exists
    Node *foundNode = inList(word, listPtr);
    // if it doesn't exist, make a new node
    if (!foundNode){
        Node *newNode = malloc(sizeof(Node));
        if(!newNode){
            fprintf(stderr, "malloc fail on push\n");
            exit(1);
        }
        // init with count 1 and passed in word
        newNode->word = word;
        newNode->count = 1;
        newNode->nextNode = listPtr;
        listPtr = newNode;
    }
    return listPtr;
}

/**
 * If the word appears in the list already,
 * add one to the count, else return NULL
 * @param word to search for
 * @param listPtr list containing inserted words
 * @return list of words if word found, else NULL
 */
Node* inList(char *word, Node *listPtr){
    // instances for beginning of list (head is null)
    if(!listPtr){
        return NULL;
    }
    Node *currentNode = listPtr;
    while(currentNode){
        // if word is found, increase count by 1
        if (strcmp(currentNode->word, word) == 0){
            currentNode->count ++;
            return currentNode;
        }
        currentNode = currentNode->nextNode;
    }
    return NULL;
}

/**
 * Prints contents of list
 * Format: count word
 * @param listPtr list to print
 */
void printList(Node *listPtr){
    Node *currentNode = listPtr;
    while(currentNode){
        // prints count and corresponding word in requested formatting
        fprintf(stdout, "%d %s\n", currentNode->count, currentNode->word);
        currentNode = currentNode->nextNode;
    }
}
