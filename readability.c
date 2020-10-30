#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float calculate_coleman_liau_index(int number_of_letters, int number_of_words, int number_of_sentences);

int main(void)
{
    /*
     * This program measures readability level of user input.
     * It uses Coleman-Liau Index to measure it:
     * index = 0.0588 * L - 0.296 * S - 15.8, where:
     * 'L' stands for average number of letters per 100 words,
     * 'S' stands for average number of sentences per 100 words.
     */


    //Getting user input. (as a string)
    string text = get_string("Text: ");


    //Printing out number of letters in text. (every letter without spaces etc.)
    int number_of_letters;
    number_of_letters = count_letters(text);
    //TEST
    //printf("%i letter(s)\n", number_of_letters);
    //TEST


    //Printing out number of words. (number of spaces + 1)
    int number_of_words;
    number_of_words = count_words(text);

    //TEST
    //printf("%i word(s)\n", number_of_words);
    //TEST


    //Printing out number of sentences.(number of punctuation marks)
    int number_of_sentences;
    number_of_sentences = count_sentences(text);

    //TEST
    //printf("%i sentence(s)\n", number_of_sentences);
    //TEST


    //Calculating Coleman-Liau index. (index = 0.0588 * L - 0.296 * S - 15.8)
    float coleman_liau_index = calculate_coleman_liau_index(number_of_letters, number_of_words, number_of_sentences);

    //TEST
    //printf("Coleman-Liau Index: %f\n", coleman_liau_index);
    //TEST



    //Printing out result.
    if (coleman_liau_index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (coleman_liau_index > 16)
    {
        printf("Grade 16+\n");
    }
    if (coleman_liau_index >= 1 && coleman_liau_index <= 16)
    {
        printf("Grade %i\n", (int)round(coleman_liau_index));
    }

}


int count_letters(string text)
{
    //This function counts letters in provided string.
    int letter_counter = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (((int)text[i] > 64 && (int)text[i] < 91) || ((int)text[i] > 96 && (int)text[i] < 123))
        {
            letter_counter++;
        }
    }
    return letter_counter;
}


int count_words(string text)
{
    //This function counts words in provided string.
    //Variable word_counter is set to 1 by default because of mathematical reasons.
    int word_counter = 1;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((int)text[i] == 32)
        {
            word_counter++;
        }
    }
    return word_counter;
}


int count_sentences(string text)
{
    //This function counts sentences in provided string.
    int sentence_counter = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((int)text[i] == 33 || (int)text[i] == 46 || (int)text[i] == 63)
        {
            sentence_counter++;
        }
    }
    return sentence_counter;
}


float calculate_coleman_liau_index(int number_of_letters, int number_of_words, int number_of_sentences)
{
    /*
     * This function calculates The Coleman-Liau index.
     * The Coleman-Liau index of a text is designed to output
     * what (U.S.) grade level is needed to understand the text.
     * The formula is: index = 0.0588 * L - 0.296 * S - 15.8, where:
     * 'L' stands for average number of letters per 100 words,
     * 'S' stands for average number of sentences per 100 words.
     */

    float L = (float)number_of_letters * 100 / number_of_words;
    float S = (float)number_of_sentences * 100 / number_of_words;

    float coleman_liau_index = 0.0588 * L - 0.296 * S - 15.8;

    return coleman_liau_index;
}