#include <stdio.h>
#include "cs50.h"
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Declaration of functions and variables
long ccNumber;
int cardType;
int sums = 0;
int digits = 0;
long sayHello();
bool checkLength(long a);
bool checkSum(long b);
void checkType(long c, int d);

/* 
Hello ! This code is developed by Arsalan Ghassemi for the Problem Set 1 of CS50's introduction to Computer Science's course.

It checks the credit card number of the user's input and returns if the card is a valid AMEX, MASTERCARD or VISA.

It first checks the length of the credit card number and if it's incorrect it returns "invalid"

Then it checks the credit card number with Luhn's algorithm and returns "invalid" if the result does not match.

Finally it checks the first digits of the credit card to return if the credit card type.

Feel free to send any ameliorations suggestions at contact@arsadevs.com
*/

int main(void)
{
    // Main function
    sayHello();
    if (!checkLength(ccNumber))
    {
        exit(0);
    }
    if (!checkSum(ccNumber))
    {
        exit(0);
    }
    checkType(ccNumber, digits);
    return 0;
}

long sayHello()
{
    // First function to get the credit card number
    while (ccNumber <= 0)
    {
        ccNumber = get_long("Hello ! Please input the card number to check : \n");
    }
    return ccNumber;
}

bool checkLength(long a)
{
    // Second function to check the lenght of the credit card, returns invalid if not matching
    while (a != 0)
    {
        digits++;
        a /= 10;
    }
    if (digits != 13 && digits != 15 && digits != 16)
    {
        printf("INVALID\n");
        return false;
    }
    return true;
}

bool checkSum(long b)
{
    // Third function to check the credit card number with Luhn's algorithm
    for (int i = 0; b != 0; i++, b /= 10)
    {
        if (i % 2 == 0)
        {
            sums += b % 10;
        }
        else
        {
            int last = (b % 10) * 2;
            sums += (last / 10) + (last % 10);
        }
    }
    if (sums % 10 != 0)
    {
        printf("INVALID\n");
        return false;
    }
    return true;
}

void checkType(long c, int d)
{
    // Last function to return the credit card type / if the type is not found, returns false
    c = c / (pow(10, d - 2));
    if (c == 34 || c == 37)
    {
        printf("AMEX\n");
    }
    else if (c == 51 || c == 52 || c == 53 || c == 54 || c == 55)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        c /= 10;
        if (c == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
            exit(0);
        }
    }
}