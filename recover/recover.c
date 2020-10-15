#include <stdio.h>
#include <stdbool.h>

void recover(FILE *file);
int main(int argc, char *argv[])
{
    //Insure that we recieve the commands
    if (argc != 2)
    {
        fprintf(stderr, "No file found.\nUsage: ./revover file.extention\n");
        return 1;
    }
    //Read the file
    FILE *file = fopen(argv[1], "r");
    //Checking the file
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return 1;
    }

    //Creating new file: buffer and arrays for name
    FILE *image = NULL; // new picture
    unsigned char buffer[512]; //for buffer
    char filename[8];
    int c = 0;
    bool status = false;

    recover(file);

    /*closing all open files
    this condition was found on Stack overflow, responsed by @Blauelf. On this issue: https://cs50.stackexchange.com/questions/26600/segmentation-fault-recover*/
    if (image != NULL)
    {
        fclose(file);
        fclose(image);
    }

    return 0; //for success

}


void recover(FILE *file)
{
    FILE *image = NULL; // new picture
    unsigned char buffer[512]; //for buffer
    char filename[52] = "";
    int c = 0;
    bool status = false;

    //Read the file
    while (fread(buffer, 512, 1, file) == 1)
    {
        //check the beinining of the JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close the present JPEG, to open another
            if (status == true)
            {
                fclose(image); // closing the current file
            }
            else
            {
                status = true;
            }

            sprintf(filename, "%03i.jpg", c);
            image = fopen(filename, "w");
            c++;
        }

        if (status == true)
        {
            fwrite(&buffer, 512, 1, image);
        }
    }
}