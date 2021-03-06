#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
 
int integer(char* str) 
{
    int figure = strlen(str) - 1;
    int sum = 0;
    for (int i = figure; i >= 0; i--)
    {
        sum += (str[i] - '0') * pow(10, figure - i);
    }
    return sum;
} 
void printMul(int n, char c) {
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
}
int main(void) {
    // Lab 4
    char s[500];
    printf("Enter string = ");
    scanf("%s", s);
    int i = 0;
    int num = 1;
    char digits[10] = "1";//store string which in term of digits
    int x = 0;
    while (s[i] != '\0') {
        if (isdigit(s[i])) { 
            digits[x] = s[i];
            x += 1;
        } 
        else {
            x = 0;
            num = integer(digits);
            printMul(num, s[i]);

            strcpy(digits, "1");
        }
        i++;
    }
    return 0;
}
