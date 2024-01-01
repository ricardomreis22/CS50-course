#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int rotate(string pt);

int y, z = 0, j = 0;

int main(int argc, string argv[])
{
    int i = 0;

    string x = argv[1];

    if (argc != 2)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }
    while (x[i] != '\0')
    {
        if (isdigit(x[i]) == 0)
        {
            printf("usage: ./caesar key\n");
            return 1;
        }
        i++;
    }

    int key = atoi(x);

    string pt = get_string("plaintext: ");

    printf("ciphertext: ");

    while (pt[j] != '\0')
    {
        if (isalpha(pt[j]) == 0)
        {
            z = pt[j];
        }

        else if (isupper(pt[j]) != 0)
        {
            y = (int) pt[j] - 65;
            z = (y + key) % 26;
            z = z + 65;
        }

        else if (islower(pt[j]) != 0)
        {
            y = (int) pt[j] - 97;
            z = (y + key) % 26;
            z = z + 97;
        }
        j++;
        printf("%c", z);
    }

    printf("\n");
}


/*int rotate(string y)
    {
        if (isupper(pt[j]) != 0)
        {
            y = (int) pt[j] - 65;
            z = (y + key) % 26;
        z = z + 65;
        return z;
        }

    }*/