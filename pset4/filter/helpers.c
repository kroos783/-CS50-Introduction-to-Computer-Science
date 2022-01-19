#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00;
            int k = roundf(average);
            image[i][j].rgbtBlue = k;
            image[i][j].rgbtGreen = k;
            image[i][j].rgbtRed = k;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue);
            float sepiaGreen = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue);
            float sepiaBlue = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue);
            int sRed = round(sepiaRed);
            int sGreen = round(sepiaGreen);
            int sBlue = round(sepiaBlue);
            if (sRed > 255)
            {
                sRed = 255;
            }
            if (sGreen > 255)
            {
                sGreen = 255;
            }
            if (sBlue > 255)
            {
                sBlue = 255;
            }
            image[i][j].rgbtRed = sRed;
            image[i][j].rgbtGreen = sGreen;
            image[i][j].rgbtBlue = sBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j < (width / 2); j++)
        {
            buffer = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = buffer;
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blured[height][width];

    // copy image to blurred
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blured[i][j] = image[i][j];
        }
    }

    // work blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter, bRed, bGreen, bBlue;
            counter = bRed = bGreen = bBlue = 0;

            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k > height - 1 || k < 0 || l > width - 1 || l < 0)
                    {
                        continue;
                    }
                    counter++;
                    bRed += image[k][l].rgbtRed;
                    bGreen += image[k][l].rgbtGreen;
                    bBlue += image[k][l].rgbtBlue;
                }
            }
            blured[i][j].rgbtRed = round((float) bRed / counter);
            blured[i][j].rgbtGreen = round((float) bGreen / counter);
            blured[i][j].rgbtBlue = round((float) bBlue / counter);
        }
    }

    // copy blurred to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blured[i][j];
        }
    }
    return;
}
