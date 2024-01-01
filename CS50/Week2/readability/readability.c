#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int count_letters(string text);

int count_words(string text);

int count_sentences(string text);


int main(void)
{

    string text = get_string("Text\n");

    int letters = count_letters(text);

    int words = count_words(text);

    int sentences = count_sentences(text);

    // n medio de letras por 100 palavras

    float l = letters * 100.00 / words;

    // n medio de frases por 100 palavras

    float s = sentences * 100.00 / words;

    float index = (0.0588 * l) - (0.296 * s) - 15.8;

    int grade = (int) round(index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}


int count_letters(string text)
{
    int ch = 0;
    int letters = 0;
    while (text[ch] != '\0')
    {
        if (isalpha(text[ch]) != 0)
        {
            letters++;
        }
        ch++;
    }
    return letters;
}

int count_words(string text)
{
    int ch = 0;
    int words = 0;
    while (text [ch] != '\0')
    {
        if (isspace(text [ch]) != 0)
        {
            words++;
        }
        ch++;
    }
    words = words + 1;
    return words;
}

int count_sentences(string text)
{
    int ch = 0;
    int sentences = 0;
    while (text [ch] != '\0')

    {
        if (text[ch] == '.' || text[ch] == '!' || text[ch] == '?')
        {
            sentences++;
        }
        ch++;
    }

    return sentences;

}




