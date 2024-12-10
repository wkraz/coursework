# Crossword

## EXTRA CREDIT
I did the second extra credit (skipping words and trying to place them again until no more words can be placed)
The text file: more_random_stuff.txt (don't judge the name) shows this
    - It initially skips over the word ENGINEER, but on the second go around it is able to place ENGINEER, and it displays an appropriate message
Here's the contents of more_random_stuff.txt (also in the Crossword directory)
TECHNOLOGY
COMPUTER
ENGINEER
SCIENCE
PYTHON
PROGRAM
DEVELOPER
ALGORITHM
FUNCTION
VARIABLE
NETWORK
DATABASE
SYSTEM
CODE
DEBUG
.

## Logic for Program
- Create empty solution, puzzle, board arrays
    - Board used to track what's currently on the board
    - Solution and puzzle are used for printing out
- Create structs
    - word - has the word, length, direction, placed bool, starting position, and the anagram
    - node - has a word struct (value) and points to another node (need this for the linked list)
- Read input words into a Word array words[WORDS] (interactive and at command line), also get number of words
- Sort words array in desc. order (largest -> smallest) (qsort)
- Place largest word in center (horizontally)
    - Update board array with the affected squares
- Then loop through words 2:end
    - try and place each word onto each word currently on the board
        - if we can't, add this word to a skipped word linked list
- Then continuously loop through the skipped linked list until it's empty, or no words left will fit
    - if we successfully place a word, make the previous word point to the next
    - if we don't place a word, just move to the next node while having prev still point to the current node (not removing it)
    - if we don't make a single addition in an iteration, end the loop
        - once this happens, make sure we free every node (if skipped isn't empty)
- Update the solution and puzzle boards and print them out
- Generate clues for every placed word and print them out

## Comments
I know we haven't learned what a linked list is, but I've worked with them before and they felt like the most natural choice for the skipped list. 
There was probably an easier way to do it lol, but this felt the most accurate to what was being asked: a dynamic array that keeps shrinking until a condition is met (when we can't add any of the words to the crossword anymore)
My general logic though was to have an array of Word structs that I would use for the entire program and loop through it in various ways until every word has either been placed or I know it cannot be placed
more_random_stuff.txt was a txt file that demonstrates how my program can skip over a word (engineer) and place it on its second iteration
