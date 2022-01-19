#include <cs50.h>
#include <stdio.h>
#include <math.h>



int main(void)
{
    float i;
    do
    {
        i = get_float("Change owed: ");
    }
    while (i < 0.00);

    int cents = roundf(i * 100);
    printf("Total cents: %i\n", cents);

    int j = 0;
    do
    {
        while (cents >= 25)
        {
            cents = cents - 25;
            j++;
        }
        while (cents >= 10)
        {
            cents = cents - 10;
            j++;
        }
        while (cents >= 05)
        {
            cents = cents - 05;
            j++;
        }
        while (cents >= 01)
        {
            cents = cents - 01;
            j++;
        }
    }
    while (cents > 0.00);

    printf("%i\n", j);
}