#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check number of argument
    if (argc != 2)
    {
        printf("Run like that : %s file.jpeg\n", argv[0]);
        return 1;
    }

    // open & check then file isn't NULL
    FILE *memory = fopen(argv[1], "r");
    if (memory == NULL)
    {
        printf("Could not open the file\n");
        return 1;
    }

    // define variables and buffer
    BYTE buffer[512];
    FILE *outfile = NULL;
    int count = 0;
    char filename[8];

    while (fread(&buffer, 512, 1, memory) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)    // check header
        {
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                outfile = fopen(filename, "w");
                fwrite(buffer, 512, 1, outfile);
                count++;
            }
            else
            {
                fclose(outfile);
                sprintf(filename, "%03i.jpg", count);
                outfile = fopen(filename, "w");
                fwrite(buffer, 512, 1, outfile);
                count++;
            }
        }
        else if (count > 0)   // write until next header
        {
            fwrite(buffer, 512, 1, outfile);
        }
    }
    fclose(outfile); // close outfile and memory
    fclose(memory);
}