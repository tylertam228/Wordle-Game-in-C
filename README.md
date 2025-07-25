# Wordle Game in C

## Overview
This project is a console-based implementation of the Wordle game written in C. The game challenges players to guess a 5-letter word within 6 attempts, providing feedback on each guess using colored indicators: green for correct letters in the correct position, yellow for correct letters in the wrong position, and red for letters not in the word. Words are randomly selected from a file named `words.txt`.

## Requirements
- **C Compiler**: GCC or any standard C compiler to build and run the program.
- **Operating System**: Compatible with any system supporting ANSI color codes (e.g., Linux, macOS, or Windows with a compatible terminal like Git Bash).
- **Input File**: A text file named `words.txt` containing a list of 5-letter words, one per line.

## Setup
1. **Prepare the Word List**:
   - Create a file named `words.txt` in the same directory as the program.
   - Populate it with valid 5-letter words, one per line (e.g., `house`, `smile`, `quick`).
2. **Compile the Program**:
   - Use a C compiler to compile the code. For example:
     ```bash
     gcc wordle.c -o wordle
     ```
3. **Run the Program**:
   - Execute the compiled program:
     ```bash
     ./wordle
     ```

## Program Functionality
- **Initialization**:
  - Sets the locale to `en_US.UTF-8` for consistent character handling.
  - Seeds the random number generator using the current time.
- **Front Page**:
  - Displays a welcome message and game rules, explaining the color-coded feedback (Green: correct letter and position, Yellow: correct letter, wrong position, Red: letter not in word).
- **Game Logic**:
  - Randomly selects a 5-letter word from `words.txt`.
  - Allows up to 6 guesses per game.
  - Validates each guess for correct length (5 letters) and existence in `words.txt`.
  - Provides color-coded feedback for each guess using ANSI escape codes.
  - Declares a win if the correct word is guessed, or a loss if all attempts are exhausted.
- **Replay Option**:
  - Prompts the user to play another round after each game.
- **Error Handling**:
  - Checks for file access errors, empty word lists, and memory allocation failures, exiting gracefully with appropriate error messages.

## How to Use
1. Ensure `words.txt` is in the same directory as the executable and contains valid 5-letter words.
2. Compile and run the program as described in the Setup section.
3. Follow the on-screen instructions to enter 5-letter guesses.
4. Observe the color-coded feedback:
   - Green (`G`): Letter is correct and in the correct position.
   - Yellow (`Y`): Letter is in the word but in the wrong position.
   - Red (`R`): Letter is not in the word.
5. After the game ends, choose to play again by entering `y` or exit with `n`.

## Notes
- The program assumes `words.txt` exists and contains valid 5-letter words. If the file is missing or empty, the program will exit with an error.
- ANSI color codes may not display correctly in some Windows terminals (e.g., Command Prompt). Use a terminal like Git Bash or Windows Subsystem for Linux (WSL) for best results.
- Guesses are case-insensitive and automatically converted to lowercase for validation.
- The program includes basic error handling for file operations and memory allocation.

## Example `words.txt`
```
house
smile
quick
world
```

## License
This project is open-source and available under the MIT License.
