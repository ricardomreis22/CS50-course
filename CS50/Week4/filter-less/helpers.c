#include "helpers.h"
#include "math.h"
#include "stdio.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int x, y;
    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width; y++)
        {
            int r = image[x][y].rgbtRed;
            int g = image[x][y].rgbtGreen;
            int b = image[x][y].rgbtBlue;
            int m = round((r + g + b) / 3.0);

            image[x][y].rgbtRed = m;
            image[x][y].rgbtGreen = m;
            image[x][y].rgbtBlue = m;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int x, y;
    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width; y++)
        {
            int r = image[x][y].rgbtRed;
            int g = image[x][y].rgbtGreen;
            int b = image[x][y].rgbtBlue;

            int sepiaRed = round(r * 0.393 + g * 0.769 + b * 0.189);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(r * 0.349 + g * 0.686 + b * 0.168);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(r * 0.272 + g * 0.534 + b * 0.131);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[x][y].rgbtRed = sepiaRed;
            image[x][y].rgbtGreen = sepiaGreen;
            image[x][y].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int x, y;
    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width / 2; y++)
        {
            int z = width - y - 1;
            int tmpRed = image[x][y].rgbtRed;
            image[x][y].rgbtRed = image[x][z].rgbtRed;
            image[x][z].rgbtRed = tmpRed;

            int tmpGreen = image[x][y].rgbtGreen;
            image[x][y].rgbtGreen = image[x][z].rgbtGreen;
            image[x][z].rgbtGreen = tmpGreen;

            int tmpBlue = image[x][y].rgbtBlue;
            image[x][y].rgbtBlue = image[x][z].rgbtBlue;
            image[x][z].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpBlue;
    int tmpGreen;
    int tmpRed;
    float vizinhos;

    RGBTRIPLE imageoriginal[height][width];
    int x, y;
    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width; y++)
        {
            imageoriginal[x][y] = image[x][y];
        }
    }

    for (x = 0; x < height; x++)
    {
        for (y = 0; y < width; y++)
        {

            tmpBlue = 0;
            tmpGreen = 0;
            tmpRed = 0;
            vizinhos = 0.0;

            for (int z = x - 1; z <= x + 1; z++)
            {
                for (int k = y - 1; k <= y + 1; k++)
                {
                    if (z >= 0 && z <= height - 1 && 0 <= k && k <= width - 1)
                    {
                        tmpBlue += imageoriginal[z][k].rgbtBlue;
                        tmpGreen += imageoriginal[z][k].rgbtGreen;
                        tmpRed += imageoriginal[z][k].rgbtRed;
                        vizinhos++;
                    }
                }
            }

            image[x][y].rgbtBlue = round(tmpBlue / vizinhos);
            image[x][y].rgbtGreen = round(tmpGreen / vizinhos);
            image[x][y].rgbtRed = round(tmpRed / vizinhos);
        }
    }

    return;
}
