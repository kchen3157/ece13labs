/**
 * @file    test_game_template.c
 *
 * Test harness for the Hangman game.
 *
 * @author
 *
 * @date
 */
// Standard libraries.
#include <stdio.h>

// User headers.
#include "Game.h"

// List of words as an array of strings.
// ----Add more to test corner cases and different rules.---- //
char* list_of_words[] = {"Hello", "WORLD"};

// Number of words.
int num_words = sizeof(list_of_words) / sizeof(list_of_words[0]);

int main()
{

    // Loop across list of words and feed them into runGame, printing out
    // the test result and comparing to the correct result.

    return 0;
}
