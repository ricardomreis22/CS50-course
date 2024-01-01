#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("height: ");
        if (h > 8 || h < 1)
        {
            printf("invalid\n");
        }

    } while (h > 8 || h < 1);

    // for each row
    for (int i = 1; i <= h; i++)
    {
        // spaces before #
        for (int k = h; k > i; k--)
        {
            printf(" ");
        }

        // print # na mesma linha, de 1 a i
        for (int j = 1; j <= i; j++)
        {

            printf("#");
        }
        // print "  "
        printf("  ");

        // print # na mesma linha, de 1 a i (2 metade da arvore)
        for (int k = 1; k <= i; k++)
        {

            printf("#");
        }

        printf("\n");
    }
}
