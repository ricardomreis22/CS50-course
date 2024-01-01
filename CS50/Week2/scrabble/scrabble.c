#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    if (score1 == score2)
    {
        printf("Tie!\n");
    }

    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else
    {
        printf("Player 2 wins!\n");
    }
}

// TODO: Compute and return score for string


int compute_score(string word)
{
    int x, y, soma = 0, ch = 0;

    while (word[ch] != '\0')
    {
        if (isalpha(word[ch]) == 0)
        {
            y = 0;
        }
        else if (isupper(word[ch]) != 0)
        {
            x = tolower(word[ch]);

            x = (int)x - 97;

            soma = soma + POINTS[x];
        }
        else if (isupper(word[ch]) == 0)
        {
            x = (int)word[ch] - 97;

            soma = soma + POINTS[x];
        }

        ch++;
    }

    return soma;
}
