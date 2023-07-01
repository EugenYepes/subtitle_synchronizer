#include "../inc/convertData.h"

#include <stdio.h>

void test_uitoa(void);

int main(void)
{
    printf("start test cases\n");
    test_uitoa();
}

void test_uitoa(void)
{
    unsigned char numberStr[20];
    int numLen;

    // test cases len = 0
    numLen = 0;
    if (itoua(numberStr, 22, &numLen) == 0) {
        if (numberStr[0] == '2' && numberStr[1] == '2' && numLen == 2) {
            printf("success!\n");
        } else {
            printf("TestCase faild\n");
        }
    }
    numLen = 0;
    if (itoua(numberStr, -7, &numLen) == 0) {
        if (numberStr[0] == '-' && numberStr[1] == '7' && numLen == 1) {
            printf("success!\n");
        } else {
            printf("TestCase faild\n");
        }
    }

    // test cases len > 0
    numLen = 2;
    if (itoua(numberStr, 23, &numLen) == 0) {
        if (numberStr[0] == '2' && numberStr[1] == '3') {
            printf("success!\n");
        } else {
            printf("TestCase faild\n");
        }
    }
    if (itoua(numberStr, -20, &numLen) == 0) {
        if (numberStr[0] == '-' && numberStr[1] == '2' && numberStr[2] == '0') {
            printf("success!\n");
        } else {
            printf("TestCase faild\n");
        }
    }

    // test cases wrong length
    numLen = 1;
    if (itoua(numberStr, 25, &numLen) == 0) {
        printf("success!\n");
    } else {
        printf("TestCase faild\n");
    }
    numLen = 3;
    if (itoua(numberStr, -21, &numLen) == 0) {
        printf("success!\n");
    } else {
        printf("TestCase faild\n");
    }
}