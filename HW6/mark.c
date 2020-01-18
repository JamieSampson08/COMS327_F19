#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct
typedef struct node Node;
struct node {
    int number;
    Node *next;
};

// prototypes
void initEmptyNodes(Node *nodes, int size);
void connectNodes(int srcLoc, int destLoc, bool isVariable);
void findNodes(int size);
bool inFound(int* found, int value, int size);
void printNodes(int *nodeNums, int size);
void sortInts(int *found, int size);

Node *variables;
Node *createdNodes;

int main(int argc, char** argv) {
//    FILE *file = fopen(argv[1], "r");
//    if(!file){
//        fprintf(stderr, "Error opening: %s", argv[1]);
//        exit(1);
//    }
    FILE *file = stdin;

    // init program variables
    variables = malloc(9 * sizeof(Node));
    if(!variables){
        fprintf(stderr, "Malloc failed on init program variables");
        exit(1);
    }
    initEmptyNodes(variables, 9);

    int numNodes = 0;
    char currentChar = ' ';
    bool expectingChar = true;
    bool restrictValue = false;
    bool varNode = false;
    int currentValue = 0;
    int srcLoc = -1;
    int destLoc = -1;

    while(!feof(file)){
        // handle input line 1
        if(!numNodes){
            fscanf(file, "%d", &numNodes);
            if (!numNodes){
                fprintf(stderr, "Invalid number of nodes: %d", numNodes);
                exit(1);
            }
            createdNodes = malloc(numNodes * sizeof(Node));
            if(!createdNodes){
                fprintf(stderr, "Malloc failed on createdNodes");
                exit(1);
            }
            initEmptyNodes(createdNodes, numNodes);
            continue;
        }

        if(expectingChar){
            currentChar = fgetc(file);

            // skip whitespace
            if(currentChar == '\n' || currentChar == '\r' || currentChar == '\t' || currentChar == ' '){
                continue;
            }

            // V varNum->nodeDest
            if(currentChar == 'V') {
                varNode = true;
                restrictValue = true;
            }

            // expecting another char after `-`
            if(currentChar != '-'){
                expectingChar = false;
            }
        }
        else {
            fscanf(file, "%d", &currentValue);
            if(currentValue > numNodes || (restrictValue && currentValue > 9)){
                fprintf(stderr, "Invalid integer value: %d", currentValue);
                exit(1);
            }

            if(srcLoc == -1){
                srcLoc = currentValue;
            }
            else {
                destLoc = currentValue;
            }

            if(srcLoc != -1 && destLoc != -1){
                connectNodes(srcLoc, destLoc, varNode);
                srcLoc = -1;
                destLoc = -1;
                varNode = false;
            }
            restrictValue = false;
            expectingChar = true;
        }
    }
    findNodes(numNodes);
    return 0;
}

/**
 * Fills an array of nodes with NULL for next and their
 * corresponding number
 * @param nodes to fill
 * @param size of nodes array
 */
void initEmptyNodes(Node *nodes, int size){
    unsigned int i;
    Node *node;
    for(i = 0; i < size; i++){
        node = malloc(sizeof(Node));
        if(!node){
            fprintf(stderr, "Malloc failed on `node`");
            exit(1);
        }
        node->number = i+1;
        node->next = 0;
        nodes[i] = *node;
	free(node);
    }
}

/**
 * Links two nodes together
 * @param srcLoc node/variable number
 * @param destLoc node number
 * @param isVariable if src is variable node
 */
void connectNodes(int srcLoc, int destLoc, bool isVariable){
    if(isVariable){
        if (destLoc != 0){
            variables[srcLoc-1].next = &createdNodes[destLoc-1];
        }
        else {
            variables[srcLoc-1].next = 0;
        }
    }
    else{
        if (destLoc != 0) {
            createdNodes[srcLoc - 1].next = &createdNodes[destLoc - 1];
        }
        else {
            createdNodes[srcLoc - 1].next = 0;
        }
    }
}

/**
 * Search for reachable and unreachable nodes
 * @param size number of total nodes
 */
void findNodes(int size){
    unsigned int i;
    Node *currentNode;
    int reachCount = 0;
    int *found = malloc((reachCount+1) * sizeof(int));
    if(!found){
        fprintf(stderr, "Malloc failed on `found`");
        exit(1);
    }

    // finds nodes that are reachable through the variables
    for(i = 0; i < 9; i++){
        if(!variables[i].next){
            continue;
        }
        currentNode = variables[i].next;
        while(currentNode){
            if(inFound(found, currentNode->number, reachCount)){
                break;
            }
            found[reachCount++] = currentNode->number;
            found = realloc(found, (reachCount +1) * sizeof(int));
            if(!found){
                fprintf(stderr, "Realloc failed on found");
                exit(1);
            }
            currentNode = currentNode->next;
        }
    }

    int unreachCount = 0;
    // gathers unreached nodes based on ones found
    int *notFound = malloc((size-reachCount) * sizeof(int));
    if(!notFound){
        fprintf(stderr, "Malloc failed on `notFound`");
        exit(1);
    }

    for(i = 0; i < size; i++){
        if (!inFound(found, i+1, reachCount)){
            notFound[unreachCount++] = i+1;
        }
    }

    // print the stdout message
    fprintf(stdout, "Reachable: ");
    sortInts(found, reachCount);
    printNodes(found, reachCount);
    fprintf(stdout, "\nUnreachable: ");
    printNodes(notFound, unreachCount);
    fprintf(stdout, "\n");

    free(found);
    free(notFound);
    free(variables);
    free(createdNodes);
}

/**
 * Formats array of ints and prints
 * @param nodeNums array of ints
 * @param size of nodeNums
 */
void printNodes(int *nodeNums, int size){
    unsigned int i;
    for(i = 0; i < size; i++){
        if(i != (size-1)){
            fprintf(stdout, "%d, ", nodeNums[i]);
        }
        else{
            fprintf(stdout, "%d", nodeNums[i]);
        }
    }
}

/**
 * Return if a value is already in an array
 * @param array of ints
 * @param value looking for
 * @param size of array
 * @return if the value is already in array
 */
bool inFound(int* array, int value, int size){
    unsigned int i;
    for(i = 0; i < size; i++){
        if (array[i] == value){
            return true;
        }
    }
    return false;
}

/**
 * Reference: https://www.geeksforgeeks.org/c-program-to-sort-an-array-using-pointers/
 * Sort an array in ascending order
 * @param array to sort
 * @param size of array
 */
void sortInts(int *array, int size){
    int i, t, j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (*(array + j) < *(array + i)) {
                t = *(array + i);
                *(array + i) = *(array + j);
                *(array + j) = t;
            }
        }
    }
}
