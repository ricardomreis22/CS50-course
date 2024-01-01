#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argv[2] != NULL)

    {
        return 1;
    }


    string key = argv[1];

    int ch = 0;
    int x = 1;

    while (key[ch] != '\0')
    {
        if (isalpha(key[ch]) == 0)
        {
            printf("Invalid Key\n");
            return 1;
        }
        while (key[x] != '\0')
        {
            //            printf("%c, %c\n",key[ch], key[x]);
            if (tolower(key[ch]) == tolower(key[x]))
            {
                printf("Invalid\n");
                return 1;
            }
            x++;
        }
        //        printf ("\n");
        ch++;
        x = ch + 1;
    }

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 letters\n");

        return 1;
    }

    int ch2;

    int z;

    char c;

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (ch2 = 0; plaintext[ch2] != '\0'; ch2++)
    {
        if (isalpha(plaintext[ch2]) == 0)
        {
            printf("%c", plaintext[ch2]);
        }
        else
        {
            z = (int)plaintext[ch2];

            if (z >= 65 && z <= 90)
            {
                z = z - 65;

                c = (int)key[z];

                if (c >= 97 && c <= 122)

                {
                    c = c - 32;
                }
            }

            else if (z >= 97 && z <= 122)
            {
                z = z - 97;

                c = (int)key[z];

                if (c >= 65 && c <= 90)

                {
                    c = c + 32;
                }
            }
            printf("%c", c);
        }
    }
    printf("\n");
}