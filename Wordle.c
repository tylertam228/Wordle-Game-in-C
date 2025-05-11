#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_CHANCES 6 
#define WORD_LENGTH 5 
#define WORD_FILE "words.txt"

#define Red "\033[31m"
#define Green "\033[32m"
#define Yellow "\033[33m"
#define Reset "\033[0m"

void displayFrontPage();
char* getRandomWord();
void playGame();
void checkGuess(const char* answer, const char* guess, char* result);
bool isValidWord(const char* guess);

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    char playAgain;

    srand(time(NULL));

    displayFrontPage();

    do {
        playGame();

        printf("One More Round？(y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Thanks for Playing and Using the code by Tiger228! Goodbye!\n");
    return 0;
}

void displayFrontPage() {
    printf("=====================================\n");
    printf("        Welcome to Wordle Game       \n");
    printf("=====================================\n");
    printf("Rules：\n");
    printf("    %sG%s：The letters are correct and in the correct position.\n", Green, Reset);
    printf("    %sY%s: The letters are correct but in the wrong position.\n", Yellow, Reset);
    printf("    %sR%s: The letters are not in the word.\n", Red, Reset);
    printf("Enter a %d-letter word and press enter.\n", WORD_LENGTH);
    printf("=======================================\n");
}

char* getRandomWord() {
    FILE* file = fopen(WORD_FILE, "r");
    if (!file) {
        printf("Error: Unable to open file: %s\n", WORD_FILE);
        exit(1);
    }

    char word[WORD_LENGTH + 2];
    int wordCount = 0;

    while (fgets(word, sizeof(word), file)) {
        wordCount++;
    }

    if (wordCount == 0) {
        printf("Error: No words found in the file.\n");
        fclose(file);
        exit(1);
    }

    // Select a random index
    int randomIndex = rand() % wordCount;

    rewind(file);
    for (int i = 0; i <= randomIndex; i++) {
        if (!fgets(word, sizeof(word), file)) {
            printf("Error: Failed to read the word from the file.\n");
            fclose(file);
            exit(1);
        }
    }

    char* newline = strchr(word, '\n');
    if (newline) {
        *newline = '\0';
    }

    char* selectedWord = malloc(strlen(word) + 1);
    if (!selectedWord) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        exit(1);
    }
    strcpy(selectedWord, word);

    fclose(file);
    return selectedWord;
}

void playGame() {
    char* answer = getRandomWord();
    char guess[WORD_LENGTH + 1];
    char result[WORD_LENGTH + 1];
    int attempts = 0;

    printf("Game Start!\n");

    while (attempts < MAX_CHANCES) {
        printf("Guess %d：", attempts + 1);
        scanf("%s", guess);

        // Convert guess to lowercase
        for (int i = 0; guess[i]; i++) {
            guess[i] = tolower(guess[i]);
        }

        if (strlen(guess) != WORD_LENGTH) {
            printf("Please enter the Correct Length(5) of the Word!\n");
            continue;
        }

        if (!isValidWord(guess)) {
            printf("The word doesn't exist!\n");
            continue;
        }

        // Check and print the result
        checkGuess(answer, guess, result);
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (result[i] == 'G') {
                printf("%s%c%s", Green, toupper(guess[i]), Reset);
            } else if (result[i] == 'Y') {
                printf("%s%c%s", Yellow, toupper(guess[i]), Reset);
            } else {
                printf("%s%c%s", Red, toupper(guess[i]), Reset);
            }
            printf(" ");
        }
        printf("\n");

        // Win
        if (strcmp(answer, guess) == 0) {
            printf("Congratulations on guessing it right! The answer is [%s]！\n", answer);
            free(answer);
            return;
        }

        attempts++;
    }

    // Lose
    printf("Sorry, you didn’t guess it! The answer is [%s].\n", answer);
    free(answer);
}

void checkGuess(const char* answer, const char* guess, char* result) {
    int answerLetterCount[26] = {0};
    int guessLetterCount[26] = {0};

    for (int i = 0; i < WORD_LENGTH; i++) {
        result[i] = 'R'; // Start with Red (R)
    }
    result[WORD_LENGTH] = '\0';

    for (int i = 0; i < WORD_LENGTH; i++) {
        answerLetterCount[answer[i] - 'a']++;
    }

    // Check Green (Correct letter and position)
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == answer[i]) {
            result[i] = 'G';
            answerLetterCount[guess[i] - 'a']--;
            guessLetterCount[guess[i] - 'a']++;
        }
    }

    // Check Yellow (Correct letter but wrong position)
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i] == 'R' && answerLetterCount[guess[i] - 'a'] > 0) {
            result[i] = 'Y';
            answerLetterCount[guess[i] - 'a']--;
            guessLetterCount[guess[i] - 'a']++;
        }
    }
}

bool isValidWord(const char* guess) {
    FILE* file = fopen(WORD_FILE, "r");
    if (!file) {
        printf("Error: Unable to open file: %s\n", WORD_FILE);
        exit(1); // Exit on file open error
    }

    char word[WORD_LENGTH + 2];
    while (fgets(word, sizeof(word), file)) {
        char* newline = strchr(word, '\n');
        if (newline) {
            *newline = '\0';
        }
        if (strcmp(word, guess) == 0) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}
