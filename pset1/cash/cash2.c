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
    while (i <= 0.00);

    int cents = roundf(i * 100);
        printf("%.2f\n", i);

    int j = 0;
    do
    {
        if (cents >= 25)
        {
            cents = cents - 25;
            j++;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
            j++;
        }
        else if (cents >= 05)
        {
            cents = cents - 05;
            j++;
        }
        else if (cents >= 01)
        {
            cents = cents - 01;
            j++;
        }
    }
    while (i > 0.00);

    printf("%i\n", j);
}