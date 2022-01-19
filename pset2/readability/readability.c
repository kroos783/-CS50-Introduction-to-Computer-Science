#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("text: ");
    int letters = count_letters(text);
    printf("%i letter(s) \n", letters);
    int words = count_words(text);
    printf("%i word(s) \n", words);
    int sentences = count_sentences(text);
    printf("%i sentence(s) \n", sentences);
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index > 16)
    {
        printf("Grade 16+");
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index < 16 && index > 1)
    {
        printf("Grade %i", (int) round(index));
    }
    printf("\n");
}

int count_letters(string text)
{
    // TODO: Compute and return score for string
    int letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]))
        {
            letters += 1;
        }
        else if (islower(text[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

int count_words(string text)
{
    // TODO: Compute and return score for string
    int words = 1;

    for (int j = 0, len = strlen(text); j < len; j++)
    {
        if (' ' == (text[j]))
        {
            words += 1;
        }
    }
    return words;
}

int count_sentences(string text)
{
    // TODO: Compute and return score for string
    int sentences = 0;

    for (int k = 0, len = strlen(text); k < len; k++)
    {
        if ('.' == (text[k]) || '?' == (text[k]) || '!' == (text[k]))
        {
            sentences += 1;
        }
    }
    return sentences;
}