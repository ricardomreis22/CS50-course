#include <cs50.h>
#include <stdio.h>

int main(void)
{
        long n = get_long(" Number:");

        long m = n;

        int i = 0;

        int mult = 0;

        int sum = 0;

        for (i = 0; n > 0; i++)
        {

                int digit = n % 10;

                // somar pares

                if (i % 2 == 0)
                {
                        sum = sum + digit;
                }

                else
                {
                        // Multiplicar impares
                        if (digit * 2 >= 10)
                        {

                                int aux = (digit * 2) % 10;

                                int aux2 = (digit * 2) / 10;

                                mult = mult + aux + aux2;
                        }

                        else
                        {

                                mult = mult + digit * 2;
                        }
                }
                n = n / 10;
        }

        if ((sum + mult) % 10 == 0)
        {

                do
                {
                        m = m / 10;
                }

                while (m > 100);
                // i identifica os digitos do numero
                if ((m == 34 || m == 37) && i == 15)
                {

                        printf("AMEX\n");
                }

                else if ((m == 51 || m == 52 || m == 53 || m == 54 || m == 55) && i == 16)
                {

                        printf("MASTERCARD\n");
                }

                else if (m / 10 == 4 && (i == 13 || i == 16))

                {

                        printf("VISA\n");
                }
                else
                {

                        printf("INVALID\n");
                }
        }

        else
        {

                printf("INVALID\n");
        }
}