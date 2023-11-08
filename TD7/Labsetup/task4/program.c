#include <stdio.h>

unsigned char array1[300] = {
    'H','A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A'
};

unsigned char array2[300] = {
    'H','A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A','H','A','A','A','A','A','A','A','A','A','H',
    'A','A','A','A','A','A','A','A','A'
};

int main() {
    int index;
    int arraysAreEqual = 1;

    for(index = 0; index < 200; index++) {
        if(array1[index] != array2[index]) {
            arraysAreEqual = 0;
            break;
        }
    }

    if(arraysAreEqual) {
        printf("This would run the safe code and display the intended behaviour");
    } else {
        printf("This is where malicious code would be run");
    }

    printf("\n");
    return 0;
}
