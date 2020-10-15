#include "helpers.h"
#include  <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float graysc;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //find the averages of color and aply value
            graysc = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.000);
            image[j][i].rgbtBlue = graysc; //aplying to blue
            image[j][i].rgbtGreen = graysc; //aplying to green
            image[j][i].rgbtRed = graysc; //aplying to red
        }
    }
}

//limiting the result of between 0 and 255
int range(int color);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sRed, sGreen, sBlue;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //finding the values for RGB
            sRed = range(round(0.393 * image[j][i].rgbtRed + 0.769 * image[j][i].rgbtGreen + 0.189 * image[j][i].rgbtBlue));
            sGreen = range(round(0.349 * image[j][i].rgbtRed + 0.686 * image[j][i].rgbtGreen + 0.168 * image[j][i].rgbtBlue));
            sBlue = range(round(0.272 * image[j][i].rgbtRed + 0.534 * image[j][i].rgbtGreen + 0.131 * image[j][i].rgbtBlue));
            //Aplaying to each value
            image[j][i].rgbtRed = sRed;
            image[j][i].rgbtGreen = sGreen;
            image[j][i].rgbtBlue = sBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //temporary array to swap values
    int temporary[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temporary[0] = image[i][j].rgbtRed;
            temporary[1] = image[i][j].rgbtGreen;
            temporary[2] = image[i][j].rgbtBlue;
            //swap value
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = temporary[0];
            image[i][width - j - 1].rgbtGreen = temporary[1];
            image[i][width - j - 1].rgbtBlue = temporary[2];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sRed, sGreen, sBlue; //to sum RGB
    float c; //to count

    //temp array
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sRed = 0;
            sGreen = 0;
            sBlue = 0;
            c = 0.00;
            for (int k = -1; k < 2; k++) //suming the value on the picture range
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }
                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }
                    sBlue += image[j + k][i + h].rgbtBlue;
                    sGreen += image[j + k][i + h].rgbtGreen;
                    sRed += image[j + k][i + h].rgbtRed;
                    c++;
                }
            }
            //average value to aply on the picture
            tmp[j][i].rgbtBlue = round(sBlue / c);
            tmp[j][i].rgbtGreen = round(sGreen / c);
            tmp[j][i].rgbtRed = round(sRed / c);
        }
    }

    //copy values from temporary storage
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = tmp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = tmp[j][i].rgbtGreen;
            image[j][i].rgbtRed = tmp[j][i].rgbtRed;
        }
    }
}
//limiting the result of between 0 and 255
int range(int color)
{
    if (color > 255)
    {
        color = 255;
    }
    return color;
}