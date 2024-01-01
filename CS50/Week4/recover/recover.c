#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    int BLOCK_SIZE = 512;

    typedef uint8_t BYTE;

    BYTE bytes[BLOCK_SIZE];

    int n_jpeg = 0;

    char current_filename[8];

    int writing = 0;

    FILE *new_file;

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card for reading and check for NULL

    FILE *raw_file = fopen(argv[1], "r");

    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Open newfile for writing and check for NULL



    // read card until end
    while (fread(bytes, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // JPEG??
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            // 1st JPEG??
            if (n_jpeg == 0)
            {
                sprintf(current_filename, "%03i.jpg", n_jpeg);
                new_file = fopen(current_filename, "w");

                if (new_file == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }

                fwrite(bytes, 1, BLOCK_SIZE, new_file);
            }
            else
            {
                fclose(new_file);
                sprintf(current_filename, "%03i.jpg", n_jpeg);
                new_file = fopen(current_filename, "w");
                fwrite(bytes, 1, BLOCK_SIZE, new_file);
            }
            n_jpeg++;
            writing = 1;
        }
        else
        {
            if (writing == 1)
            {
                fwrite(bytes, 1, BLOCK_SIZE, new_file);
            }
        }
    }
    fclose(new_file);
    fclose(raw_file);
}