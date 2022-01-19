#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int key = atoi(argv[1]);
        printf("argc = 2\n");
        printf("argv[1] = %s\n", argv[1]);
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if (isdigit(argv[1][i]))
            {
                printf("success, key = %i\n", key);
            }
            else
            {
                printf("ENTER INT\n");
                return 1;
            }
        }
        string plaintext = get_string("plaintext: ");
        printf("ok\n");
        printf("ciphertext: ");
        for (int i = 0, len = strlen(plaintext); i < len; i++)
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", ((((plaintext[i] + key) - 65) % 26) + 65));
            }
            else if (islower(plaintext[i]))
            {
                printf("%c", ((((plaintext[i] + key) - 97) % 26) + 97));
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
    }
    else
    {
        printf("Usage: %s key", argv[0]);
        return 1;
    }
    printf("\n");
}



