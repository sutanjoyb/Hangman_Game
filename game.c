#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main()
{
    // Seed the random number generator using the current time
    srand(time(NULL));

    // Creates a 2D Array of words (A list of 15 strings)
    // [15] is the number of words, [20] is the max length of each word
    char wordList[15][20] = {
        "PROGRAMMING", "KEYBOARD", "COMPUTER", "ALGORITHM", "DATABASE",
        "VARIABLE", "FUNCTION", "POINTER", "COMPILER", "NETWORK",
        "SOFTWARE", "HARDWARE", "INTERNET", "SECURITY", "GRAPHICS"};

    // Picks a random word from the 2D array
    int randomIndex = rand() % 15;

    // We treat one row of the 2D array as our secret word string
    char secretWord[20];
    strcpy(secretWord, wordList[randomIndex]);

    int length = strlen(secretWord);

    // Creates an array for the underscores (the "Hidden" word)
    // Needs to be length + 1 to hold the null terminator '\0'
    char displayWord[21];

    int lives = 5;
    int correctGuesses = 0;
    char guess;
    int found;

    // Initialize displayWord with underscores using a loop
    for (int i = 0; i < length; i++)
    {
        displayWord[i] = '_';
    }
    displayWord[length] = '\0'; // Manually setting the end of the string

    printf("=========================================\n");
    printf("---- WELCOME TO THE HANGMAN GAME!! ----\n");
    printf("  Created by: Sutanjoy Bhattacharjee   \n");
    printf("=========================================\n");
    printf("I have picked a secret word. Can you guess it in 5 tries?\n");

    // MAIN GAME LOOP
    // Runs as long as you have lives and haven't finished the word
    while (lives > 0 && correctGuesses < length)
    {

        // Print the current progress (e.g., _ _ _ G R _ M)
        printf("\nWord: ");
        for (int i = 0; i < length; i++)
        {
            printf("%c ", displayWord[i]);
        }

        printf("\nLives left: %d", lives);
        printf("\nGuess a letter: ");

        // Get user input (the space before %c handles the 'Enter' key from previous turns)
        scanf(" %c", &guess);
        guess = toupper(guess); // Convert to uppercase to match our word list

        found = 0; // Reset "found" flag for this turn

        // SEARCH LOOP: Compare the guess to every letter in the secret word array
        for (int i = 0; i < length; i++)
        {

            // Check if guess matches secret letter AND we haven't found it yet
            if (secretWord[i] == guess && displayWord[i] == '_')
            {
                displayWord[i] = guess; // Updates the underscore to the letter
                correctGuesses++;       // Increases win counter
                found = 1;              // Mark that we found a match
            }
            // Checks if the user is guessing a letter they already found
            else if (secretWord[i] == guess && displayWord[i] != '_')
            {
                found = 2;
            }
        }

        // FEEDBACK LOGIC
        if (found == 1)
        {
            printf("Great! '%c' is in the word.\n", guess);
        }
        else if (found == 2)
        {
            printf("You already found '%c'! Try something else.\n", guess);
        }
        else
        {
            lives--; // Deducts a life for a wrong guess
            printf("Sorry, '%c' is not there.\n", guess);
        }
    }

    // FINAL RESULT (Win or Loss)
    if (correctGuesses == length)
    {
        printf("\n==============================");
        printf("\nVICTORY! You guessed it!");
        printf("\nThe word was: %s\n", secretWord);
        printf("==============================\n");
    }
    else
    {
        printf("\n==============================");
        printf("\nLOST!! You ran out of lives.");
        printf("\nThe secret word was: %s\n", secretWord);
        printf("==============================\n");
    }

    return 0;
}