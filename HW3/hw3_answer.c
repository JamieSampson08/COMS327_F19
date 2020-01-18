#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGITS 10;

void initialize(char digits[], unsigned numdigits, unsigned value){
    unsigned i;
    for(i = 0; i < numdigits; i++){
        digits[i] = '0' + value % 10;
        value /= 10;
    }
}

int add(char result[], char num1[], char num2[], unsigned numdigits){
    int carry = 0;
    int sum;
    unsigned i;
    for(i = 0; i < numdigits; i++){
        result[i] = carry + num1[i] + num2[i] - '0';
        if (result[i] > '9'){
            result[i] -= 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
    }
    return carry;
}

void print_int(char digits[], unsigned num_digits){
    unsigned i;
    /* Skip leading zeros */
    for(i = num_digits; i; i--){
        if(digits[i-1] != '0') break;
    }

    unsigned comma = (i / 3) * 3;

    /* Print stuff */
    for (; i; i--){
        if (i == comma){
            printf(",");
            comma -= 3;
        }
        printf("%c", digits[i-1]);
    }
}

int maint(){
    char A[DIGITS];
    char B[DIGITS];
    char C[DIGITS];

    initialize(A, DIGITS, 0);
    initialize(B, DIGITS, 1);

    printf("F(%3d): ", 0);
    print_int(A, DIGITS);
    printf("\n");

    printf("F(%3d): ", 1);
    print_int(A, DIGITS);
    printf("\n");

    unsigned i;
    for(i = 2; !add(C, A, B, DIGITS); i++){
        printf("F(%3d): ", i);
        print_int(C, DIGITS);
        printf("\n");

        memcpy(A, B, DIGITS);
        memcpy(B, C, DIGITS);
    }
}