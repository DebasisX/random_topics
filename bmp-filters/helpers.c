#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int r, g, b, i, j;
    int avg;
    double x;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            b = image[i][j].rgbtBlue;
            g = image[i][j].rgbtGreen;
            x = (r + g + b) / 3.0;
            avg = round(x);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, x, y;
    x = 0;
    y = 0;

    RGBTRIPLE temp[x][y];
    int end = (width) / 2;
    for (i = 0; i < height; i++)
    {
        int z = width - 1;
        for (j = 0; j < end; j++)
        {
            temp[x][y] = image[i][j];
            image[i][j] = image[i][z];
            image[i][z] = temp[x][y];
            z--;
        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    //temp image so that proccessed image doesn't get used
    RGBTRIPLE original[height][width];
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    int avg = 0;
    int avg1 = 0;
    int avg2 = 0;
    //Middle
    for (i = 1; i < height - 1; i++)
    {
        for (j = 1; j < width - 1; j++)
        {
            int sum = original[i][j].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i + 1][j].rgbtRed + original[i][j + 1].rgbtRed +
                      original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed +
                      original[i - 1][j - 1].rgbtRed;
            avg = round(sum / 9.0);
            image[i][j].rgbtRed = avg;
            int sum1 = original[i][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j + 1].rgbtBlue +
                       original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue +
                       original[i - 1][j - 1].rgbtBlue;
            avg1 = round(sum1 / 9.0);
            image[i][j].rgbtBlue = avg1;
            int sum2 = original[i][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j + 1].rgbtGreen
                       + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen
                       + original[i - 1][j - 1].rgbtGreen;
            avg2 = round(sum2 / 9.0);
            image[i][j].rgbtGreen = avg2;
        }
    }
    //Top
    for (i = 0, j = 0; j < width; j++)
    {
        if (i == 0 && j == 0)
        {
            int sum = original[i + 1][j + 1].rgbtGreen + original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j + 1].rgbtGreen;
            avg = round(sum / 4.0);
            image[i][j].rgbtGreen = avg;

            int sum1 = original[i + 1][j + 1].rgbtBlue + original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j + 1].rgbtBlue;
            avg1 = round(sum1 / 4.0);
            image[i][j].rgbtBlue = avg1;

            int sum2 = original[i + 1][j + 1].rgbtRed + original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j + 1].rgbtRed;
            avg2 = round(sum2 / 4.0);
            image[i][j].rgbtRed = avg2;
        }
        else if (i == 0 && j == width - 1)
        {
            int sum = original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen;
            avg = round(sum / 4.0);
            image[i][j].rgbtGreen = avg;

            int sum1 = original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue;
            avg1 = round(sum1 / 4.0);
            image[i][j].rgbtBlue = avg1;

            int sum2 = original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed;
            avg2 = round(sum2 / 4.0);
            image[i][j].rgbtRed = avg2;
        }
        else
        {
            int sum = original[i + 1][j].rgbtGreen + original[i][j].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j +
                      1].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen;
            avg = round(sum / 6.0);
            image[i][j].rgbtGreen = avg;
            int sum1 = original[i + 1][j].rgbtBlue + original[i][j].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue
                       + original[i][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue;
            avg1 = sum1 / 6;
            image[i][j].rgbtBlue = avg1;
            int sum2 = original[i + 1][j].rgbtRed + original[i][j].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j + 1].rgbtRed +
                       original[i][j - 1].rgbtRed + original[i][j + 1].rgbtRed;
            avg2 = sum2 / 6;
            image[i][j].rgbtRed = avg2;
        }
    }
    //Bottom
    for (i = height - 1, j = 0; j < width; j++)
    {
        if (i == height - 1 && j == 0)
        {
            int sum = original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen;
            avg = round(sum / 4.0);
            image[i][j].rgbtGreen = avg;
            int sum1 = original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue;
            avg1 = round(sum1 / 4.0);
            image[i][j].rgbtBlue = avg1;
            int sum2 = original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed;
            avg2 = round(sum2 / 4.0);
            image[i][j].rgbtRed = avg2;
        }
        else if (i == height - 1 && j == width - 1)
        {
            int sum = original[i - 1][j].rgbtGreen + original[i][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen + original[i][j - 1].rgbtGreen;
            avg = round(sum / 4.0);
            image[i][j].rgbtGreen = avg;

            int sum1 = original[i - 1][j].rgbtBlue + original[i][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i][j - 1].rgbtBlue;
            avg1 = round(sum1 / 4.0);
            image[i][j].rgbtBlue = avg1;

            int sum2 = original[i - 1][j].rgbtRed + original[i][j].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i][j - 1].rgbtRed;
            avg2 = round(sum2 / 4.0);
            image[i][j].rgbtRed = avg2;
        }
        else
        {
            int sum = original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                      original[i - 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen;
            avg = round(sum / 6.0);
            image[i][j].rgbtGreen = avg;
            int sum1 = original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                       original[i - 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue;
            avg1 = round(sum1 / 6.0);
            image[i][j].rgbtBlue = avg1;
            int sum2 = original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j].rgbtRed +
                       original[i - 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed;
            avg2 = round(sum2 / 6.0);
            image[i][j].rgbtRed = avg2;
        }
    }
    //side1
    for (j = 0, i = 1; i < height - 1; i++)
    {
        int sum = original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen
                  + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen;
        avg = round(sum / 6.0);
        image[i][j].rgbtGreen = avg;
        int sum1 = original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue +
                   original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue;
        avg1 = round(sum1 / 6.0);
        image[i][j].rgbtBlue = avg1;
        int sum2 = original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i + 1][j].rgbtRed +
                   original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed;
        avg2 = round(sum2 / 6.0);
        image[i][j].rgbtRed = avg2;
    }
    //side2
    for (i = 1, j = width - 1; i < height - 1; i++)
    {
        int sum = original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen +
                  original[i - 1][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen;
        avg = round(sum / 6.0);
        image[i][j].rgbtGreen = avg;
        int sum1 = original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue +
                   original[i - 1][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue;
        avg1 = round(sum1 / 6.0);
        image[i][j].rgbtBlue = avg1;
        int sum2 = original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed +
                   original[i - 1][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed;
        avg2 = round(sum2 / 6.0);

        image[i][j].rgbtRed = avg2;
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    //temp image with 1px black border
    RGBTRIPLE original[height + 2][width + 2];
    for (i = 0; i < height + 2; i++)
    {
        for (j = 0; j < width + 2; j++)
        {
            original[i][j].rgbtRed = 0;
            original[i][j].rgbtBlue = 0;
            original[i][j].rgbtGreen = 0;
        }
    }
    //storing copy of image in original in the middle
    for (i = 1; i < height + 1; i++)
    {
        for (j = 1; j < width + 1; j++)
        {
            original[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
            original[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
            original[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
        }
    }
    //using sobel operation to find F(x)sq. +G(x)sq.
    for (i = 1; i < height + 1; i++)
    {
        for (j = 1; j < width + 1; j++)
        {
            int sumR = (-1 * (original[i - 1][j - 1].rgbtRed)) + (-2 * (original[i - 1][j].rgbtRed)) + (-1 *
                       (original[i - 1][j + 1].rgbtRed)) + (1 * (original[i + 1][j - 1].rgbtRed)) + (2 * (original[i + 1][j].rgbtRed)) + (1 *
                               (original[i + 1][j + 1].rgbtRed));
            int sumB = (-1 * (original[i - 1][j - 1].rgbtBlue)) + (-2 * (original[i - 1][j].rgbtBlue)) + (-1 *
                       (original[i - 1][j + 1].rgbtBlue)) + (1 * (original[i + 1][j - 1].rgbtBlue)) + (2 * (original[i + 1][j].rgbtBlue)) + (1 *
                               (original[i + 1][j + 1].rgbtBlue));
            int sumG = (-1 * (original[i - 1][j - 1].rgbtGreen)) + (-2 * (original[i - 1][j].rgbtGreen)) + (-1 *
                       (original[i - 1][j + 1].rgbtGreen)) + (1 * (original[i + 1][j - 1].rgbtGreen)) + (2 * (original[i + 1][j].rgbtGreen)) + (1 *
                               (original[i + 1][j + 1].rgbtGreen));
            int sumRy = (-1 * (original[i - 1][j - 1].rgbtRed)) + (-2 * (original[i][j - 1].rgbtRed)) + (-1 *
                        (original[i + 1][j - 1].rgbtRed)) + (1 * (original[i - 1][j + 1].rgbtRed)) + (2 * (original[i][j + 1].rgbtRed)) + (1 *
                                (original[i + 1][j + 1].rgbtRed));
            int sumBy = (-1 * (original[i - 1][j - 1].rgbtBlue)) + (-2 * (original[i][j - 1].rgbtBlue)) + (-1 *
                        (original[i + 1][j - 1].rgbtBlue)) + (1 * (original[i - 1][j + 1].rgbtBlue)) + (2 * (original[i][j + 1].rgbtBlue)) + (1 *
                                (original[i + 1][j + 1].rgbtBlue));
            int sumGy = (-1 * (original[i - 1][j - 1].rgbtGreen)) + (-2 * (original[i][j - 1].rgbtGreen)) + (-1 *
                        (original[i + 1][j - 1].rgbtGreen)) + (1 * (original[i - 1][j + 1].rgbtGreen)) + (2 * (original[i][j + 1].rgbtGreen)) + (1 *
                                (original[i + 1][j + 1].rgbtGreen));

            int finalR = round(sqrt((sumR * sumR) + (sumRy * sumRy)));
            //storing the image after removing the border
            if (finalR > 255)
            {
                image[i - 1][j - 1].rgbtRed = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtRed = finalR;
            }
            int finalB = round(sqrt((sumB * sumB) + (sumBy * sumBy)));

            if (finalB > 255)
            {
                image[i - 1][j - 1].rgbtBlue = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtBlue = finalB;
            }
            int finalG = round(sqrt((sumG * sumG) + (sumGy * sumGy)));
            if (finalG > 255)
            {
                image[i - 1][j - 1].rgbtGreen = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtGreen = finalG;
            }
        }
    }
    return;
}
/*With this
this is yet another 300 lines of Code*/