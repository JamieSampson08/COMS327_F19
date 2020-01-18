#include <stdio.h>
#include <string.h>

// Created By: Jamie Sampson

// function protoypes
void print_int(char digits[], unsigned numdigits);
int add(char result[], char num1[], char num2[], unsigned numdigits);
void initialize(char digits[], unsigned numdigits, unsigned value);
void copy(char to[], char from[], unsigned numDigits);

int main() {
    int r;
    // change numDigits to change max number of values for result
    int numDigits = 50;
    // 0 = no overflow, 1 = overflow
    int overFlow = 0;

    int result[numDigits];
    int first[numDigits];
    int second[numDigits];
    // init first two values F(0) and F(1)
    initialize(first, numDigits, 0);
    initialize(second, numDigits, 1);

    for (r = 0; ;r++) {
        if (r <= 1) {
            initialize(result, numDigits, r);
        }
        else {
            // mimics algorithm F(n-1) + F(n-2)
            overFlow = add(result, first, second, numDigits);
            copy(first, second, numDigits);
            copy(second, result, numDigits);
        }
        // reached max values
        if (overFlow){
            break;
        }
        // print result
        printf("F(% 4d): ", r);
        print_int(result, numDigits);

    }
    return 0;
}

/*
 * copies one array to the other
 */
void copy(char to[], char from[], unsigned numDigits){
    int i;
    for(i = 0; i < numDigits; i++){
        // logic in place if arrays are of different sizes
        if (from[i] == '\0'){
            break;
        }
        else if (to[i] == '\0'){
            to[i+1] == '\0';
        }
        to[i] = from[i];
    }
}

/*
 * take value and put in digits
 */
void initialize(char digits[], unsigned numdigits, unsigned value){
    int i;
    // converts value to char array
    // sprintf trunks the char array
    char strValue[numdigits];
    sprintf(strValue, "%d", value);
    int index = strlen(strValue)-1;

    // starts at farthest right and places values right to left
    // subs in 0s for any extra spots
    for(i = numdigits-1; i >= 0; i--) {
        if (index >= 0) {
            digits[i] = strValue[index];
            index --;
        }
        else {
            digits[i] = '0';
        }
    }
}

/*
 * returns: 1 if overflow, else 0
 * all three arrays are same size
 * adds things right to left
 */
int add(char result[], char num1[], char num2[], unsigned numdigits){
    int i;
    int addResult;
    // max value of adding two numbers btw 0 - 9 = 18, thus carryOver is either 0 or 1
    int carryOver = 0;
    for(i = numdigits-1; i >= 0; i--){
        // convert char to int
        int value1 = num1[i] - '0';
        int value2 = num2[i] - '0';

        addResult = value1 + value2;

        // adds carryOver to next addition and resets carryOver value
        if (carryOver){
            addResult += 1;
            carryOver = 0;
        }
        // if addResult is great or equal to 10, then carryOver next addition
        if (addResult >= 10){
            carryOver = 1;
            addResult -= 10;
        }
        result[i] = addResult + '0';
    }
    // if there is still a carry over value, then overflow occurred
    if (carryOver){
        return 1;
    }
    return 0;
}

/*
 * print to standard output with commas as thousands separator
 *
 */
void print_int(char digits[], unsigned numdigits){
    int i;
    int index = 0;
    // if 1, is a leading 0, once a num is hit, change to 0
    int leadingZero = 1;

    // set result array to arbitrary size (*2 ensures there is enough space)
    int size = numdigits * 2;
    char result[size];

    for(i = 0; i < numdigits; i++){
        // skip leading zeros
        if (digits[i] == '0' && leadingZero && i != (numdigits-1)){
            continue;
        }
        leadingZero = 0;
        // every 3rd value, need a thousands comma
        if(index != 0 && (numdigits - i) % 3 == 0){
            result[index] = ',';
            index ++;
        }
        result[index] = digits[i];
        index ++;
    }
    // since result array is larger than needed, add '\0'
    result[index] = '\0';
    printf("%s\n", result);
}