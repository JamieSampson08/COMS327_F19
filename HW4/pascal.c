/* Author: Jamie Sampson */

#include <stdio.h>
#include <stdlib.h>

unsigned long** build_Pascal(unsigned N);
void show_Pascal(unsigned long** P, unsigned N);
int getSpaces (unsigned long** P, int col, unsigned N);
void destroy_Pascal(unsigned long** P, unsigned N);

int main() {
    unsigned N;
    unsigned long **p;
    printf("Enter number of Pascal's rows: ");
    scanf("%d", &N);

    p = build_Pascal(N);
    show_Pascal(p, N);
    destroy_Pascal(p, N);
    return 0;
}

/**
 * Builds pascal's trangle with N rows
 * @param N is number of rows in pascal's triangle
 * @return pascale's triangle as an array of arrays
 */
unsigned long** build_Pascal(unsigned N){
    unsigned long **pascal = malloc(N * sizeof(unsigned long));
    if (pascal == 0) {
        free(pascal);
        return NULL;
    }
    unsigned i;
    unsigned j;
    unsigned long *row;
    for(i = 0; i < N; i++){
        row = malloc((i+1) * sizeof(unsigned long));
        if (row == 0){
            free(row);
            return NULL;
        }
        for(j = 0; j <= i; j++){
            if(j == 0 || j == i){
                row[j] = 1;
            }
            else {
                row[j] = pascal[i-1][j-1] + pascal[i-1][j];
            }
        }
        pascal[i] = row;
    }
    return pascal;
}

/**
 * Prints pascal's array in human readable format
 * @param P pascal's array of arrays
 * @param N is number of rows in pascal's triangle
 */
void show_Pascal(unsigned long** P, unsigned N){
    unsigned i;
    unsigned j;
    unsigned spaces;
    for(i = 0; i < N; i++){
        for(j = 0; j <= i; j++){
            spaces = getSpaces(P, j, N);
            printf("%*d ", spaces, P[i][j]);
        }
        printf("\n");
    }
}

/**
 * Calculates the necessary width for each column
 * @param P pascal's array of arrays
 * @param col to determine width of
 * @param N is number of rows in pascal's triangle
 * @return width of max integer
 */
int getSpaces (unsigned long** P, int col, unsigned N){
    unsigned long count = 0;
    unsigned i;
    unsigned max = 0;
    for(i = 0; i < N; i++){
        if (i >= col && (P[i][col] > max)){
            max = P[i][col];
        }
    }
    while(max != 0){
        max /= 10;
        ++count;
    }
    return count;
}

/**
 * Free's each row and then the array holding the rows
 * @param P pascal's array of arrays
 * @param N is number of rows in pascal's triangle
 */
void destroy_Pascal(unsigned long** P, unsigned N){
    unsigned i;
    for(i = 0; i < N; i++){
        free(P[i]);
    }
    free(P);
}