/*
Will Krzastek
Lab 8
Crossword Functions File
*/

#define WORDS 20
#define LETTERS 16
#define BOARD 15

#include "words.h"

void print_board(char board[BOARD][BOARD], FILE *out)
{
    for (int x = -1; x <= BOARD; x++)
    {
        for (int y = -1; y <= BOARD; y++)
        {
            // if horizontal edge, print -
            if (x == -1 || x == BOARD)
                fprintf(out, "-");
            // if vertical edge, print |
            else if (y == -1 || y == BOARD)
                fprintf(out, "|");
            // not edge, so print X or ' ' respectively
            else
                fprintf(out, "%c", board[x][y]);
        }
        fprintf(out, "\n");
    }
}


// return number of words in file and update words array
int read_file(FILE *fp, Word words[WORDS])
{
    int num_words = 0;
    char curr_word[LETTERS];

    while (fgets(curr_word, sizeof(curr_word), fp) != NULL && num_words < 20)
    {
        curr_word[strcspn(curr_word, "\n")] = '\0'; // remove newline char if present
        if (curr_word[0] == '.')
        {
            break;
        }
        int valid = 1;
        // make sure every char is a letter
        for (int i = 0; i < strlen(curr_word); i++)
        {
            if (!isalpha(curr_word[i]))
            {
                valid = 0;
                break;
            }
        }
        // make sure it's between 2-15 letters
        if (strlen(curr_word) < 2 || strlen(curr_word) > 15)
        {
            valid = 0;
        }

        // update word and length if it's valid
        if (valid == 1)
        {
            uppercase(curr_word);
            strcpy(words[num_words].word, curr_word);
            words[num_words].length = strlen(curr_word);
            num_words++;
            
        }
    }

    return num_words;
}

// make every word in a char array uppercase
void uppercase(char word[LETTERS])
{
    int i = 0;
    while (word[i] != '\0')
    {
        word[i] = toupper(word[i]);
        i++;
    }
}

// Compare function we'll use for qsort
// Returns positive value if the first element should go after the second (desc. order) and 0 if equal
int compare(const void *a, const void *b)
{
    // makes a and b words (so we can look at their length)
    const Word *wordA = (const Word *)a;
    const Word *wordB = (const Word *)b;
    // return positive if wordB.length > wordA.length and vice versa
    return wordB->length - wordA->length;
}

// places the first word in the center of the board
void place_center(char board[BOARD][BOARD], Word *word)
{
    // get the starting position relative to board and length of word
    int start_col = (BOARD - word->length) / 2;
    int row = BOARD / 2;

    // place it on board
    for (int i = 0; word->word[i] != '\0'; i++)
    {
        board[row][start_col + i] = word->word[i];
    }
    // update the word struct accordingly
    word->x = row;
    word->y = start_col;
    word->direction = 0;
    word->placed = 1;
    scramble_word(word);
}

// checks if a word can be placed at an intersection point (make sure every square it'll be placed in is empty or matches)
//      returns 1 if so
int can_place(char board[BOARD][BOARD], Word *word, int direction, int x, int y, int index)
{
    int len = word->length;

    // vertical
    if (direction == 1)
    {
        // gets ends of word relative to board
        int top = x - index;
        int bottom = x + (len - index - 1);

        // check that top and bottom are in bounds (return 0)
        if (top < 0 || bottom >= BOARD || y >= BOARD || y < 0)
        {
            return 0;
        }
        // Check cell above the word
        if (top > 0 && board[top - 1][y] != ' ')
        {
            return 0;
        }
        // Check cell below the word
        if (bottom < BOARD - 1 && board[bottom + 1][y] != ' ')
        {
            return 0;
        }

        for (int i = 0; i < len; i++)
        {
            int curr_x = top + i;
            int curr_y = y;
            // Check if the cell is empty or matches the word character
            if (board[curr_x][curr_y] != ' ' && board[curr_x][curr_y] != word->word[i])
            {
                
                return 0;
            }
            // check neighbors but NOT at index, because we know that at least one of those will not be empty
            if (i != index)
            {
                // Left neighbor
                if (curr_y > 0 && board[curr_x][curr_y - 1] != ' ')
                {
                    return 0;
                }
                // Right neighbor
                if (curr_y < BOARD - 1 && board[curr_x][curr_y + 1] != ' ')
                {
                    return 0;
                }
            }
        }

        return 1;
    }
    
    // across
    else if (direction == 0)
    {
        // get ends
        int left = y - index;
        int right = y + (len - index - 1);

        // make sure ends are in bounds
        if (left < 0 || right >= BOARD || x < 0 || x >= BOARD)
        {
            return 0;
        }

        // Check cell to the left of the word
        if (left > 0 && board[x][left - 1] != ' ')
        {
            return 0;
        }

        // Check cell to the right of the word
        if (right < BOARD - 1 && board[x][right + 1] != ' ')
        {
            return 0;
        }

        for (int i = 0; i < len; i++)
        {
            int curr_x = x;
            int curr_y = left + i;
            if (curr_y < 0 || curr_y >= BOARD)
            {
                return 0;
            }
            
            // Check top and bottom neighbors only if not at the intersection point
            if (i != index)
            {
                // Top neighbor
                if (curr_x > 0 && board[curr_x - 1][curr_y] != ' ')
                {
                    return 0;
                }
                // Bottom neighbor
                if (curr_x < BOARD - 1 && board[curr_x + 1][curr_y] != ' ')
                {
                    return 0;
                }
            }
        }

        return 1;
    }
    // invalid direction
    else
    {
        return 0;
    }
}

// function for actually placing a word
//      relies on having used can_place, so this assumes we're allowed to place it
void place(char board[BOARD][BOARD], Word *word, int direction, int x, int y, int index)
{
    int len = word->length;
    if (direction == 1)
    {
        // get starting index and go from there
        int top = x - index;
        for (int i = 0; i < len; i++)
        {
            int curr_x = top + i;
            int curr_y = y;
            if (board[curr_x][curr_y] == ' ' || board[curr_x][curr_y] == word->word[i])
            {
                board[curr_x][curr_y] = word->word[i];
            }
        }

        // update the word struct now that it's placed
        word->direction = 1;
        word->x = top;
        word->y = y;
        word->placed = 1;
        scramble_word(word);

    }
    else if (direction == 0)
    {
        int left = y - index;
        // if none of the checks fail, add the word
        for (int i = 0; i < len; i++)
        {
            int curr_x = x;
            int curr_y = left + i;
            if (board[curr_x][curr_y] == ' ' || board[curr_x][curr_y] == word->word[i])
            {
                board[curr_x][curr_y] = word->word[i];
            }
        }

        // update word now that it's placed
        word->x = x;
        word->y = left;
        word->direction = 0;
        word->placed = 1;
        scramble_word(word);

    }
}

// function for determining the best place to intersect word2 with word1
//      "best" means the closest to the combined center of each (I think it's best to combine words closer to the center)
// returns 1 if an intersection exists, -1 if it doesn't
// we're placing word2 into word1 (word1 already placed and initialized so we can look at word1.x, word1.direction, etc)
int best_intersection(char board[BOARD][BOARD], Word *word1, Word *word2, int *index, int *x, int *y)
{
    int len1 = strlen(word1->word);
    int len2 = strlen(word2->word);
    // index, x, y passed by value, initialize to -1 so we can easily track if an intersection is found (if it's not -1 at the end)
    *index = -1;
    *x = -1;
    *y = -1;
    int min_distance = BOARD; // large number for min function (will initially be less)

    // word 1 horizontal so we're placing vertically
    if (word1->direction == 0)
    {
        // loop through both words and look at all shared letters
        for (int i = 0; i < len1; i++)
        {
            for (int j = 0; j < len2; j++)
            {
                if ((word1->word[i] == word2->word[j]))
                {
                    // get the x, y position of the sharing
                    int x_candidate = word1->x;
                    int y_candidate = word1->y + i;

                    // if we're allowed to place it, look at the distance (how close to the combined center)
                    if (can_place(board, word2, 1, x_candidate, y_candidate, j) == 1)
                    {
                        int distance = abs(i - len1 / 2) + abs(j - len2 / 2);
                        // if we're below min distance (always true >= 1 time if there's an intersection) update x, y, index
                        if (distance < min_distance)
                        {
                            *x = x_candidate;
                            *y = y_candidate;
                            *index = j;
                            min_distance = distance;
                        }
                    }
                } 
            }
        }
    }
    // word1 vertical so we're going horizontal
    else if (word1->direction == 1)
    {
        // same logic as going vertically
        for (int i = 0; i < len1; i++)
        {
            for (int j = 0; j < len2; j++)
            {
                if ((word1->word[i] == word2->word[j]))
                {
                    int x_candidate = word1->x + i;
                    int y_candidate = word1->y;

                    if (can_place(board, word2, 0, x_candidate, y_candidate, j) == 1)
                    {
                        // calculate how far off center each index is (we want to be as central as possible)
                        int distance = abs(i - len1 / 2) + abs(j - len2 / 2);
                        if (distance < min_distance)
                        {
                            *x = x_candidate;
                            *y = y_candidate;
                            *index = j;
                            min_distance = distance;
                        }
                    }
                } 
            }
        }
    }

    // x and y are unchanged so no intersection found, return -1
    if (*x == -1 || *y == -1)
    {
        return -1;
    }

    return 1; // success, >= 1 intersection exists and x, y, index are updated
}

// function to add a word to the skipped linked list
Node* skip(Node *head, Word word, FILE *out)
{
    // create memory of size Node
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (!new_node)
    {
        fprintf(out, "Memory allocation failed.\n");
        return head;
    }
    
    // deep copy each word field (I was having issues with just doing new_node->word = word, so i copied each field manually)
    strcpy(new_node->word.word, word.word);
    strcpy(new_node->word.clue, word.clue);
    new_node->word.length = word.length;
    new_node->word.x = word.x;
    new_node->word.y = word.y;
    new_node->word.direction = word.direction;
    new_node->word.placed = word.placed;

    // this node will point to the head, meaning it's now at the front of the linked list
    //      better than appending it since access at the front is o(1) and at the end is o(n) 
    new_node->next = head;


    return new_node;
}

// function to try placing words from the skipped linked list 
// note *skipped_head is the head of the linked list
//      pass it by reference so we can update it
int place_skip(char board[BOARD][BOARD], Word placed_words[], Node **skipped_head, int *words_placed, FILE *out)
{
    // we're starting at the head, so no node points to us
    Node *prev = NULL;
    Node *current = *skipped_head; // letting current represent the head
    int num_placed = 0;

    // traverse to the end of the linked list with current 
    while (current != NULL)
    {
        int successfully_placed = 0;
        int index, x, y;
        // try to place current->word with any of the previously placed words
        for (int i = 0; i < *words_placed; i++)
        {
            // get the opposite of the placed word's direction: 1 - 0 = 1, 1 - 1 = 0
            // best to do it this way so we are looking at EVERY word on the board and not just half them if we assign this statically
            int direction = 1 - placed_words[i].direction;

            // check if an intersection exists (best_intersection calls can_place so we don't have to call it again)
            if (best_intersection(board, &placed_words[i], &current->word, &index, &x, &y) == 1)
            {
                // if we can place it, place it on the board
                place(board, &current->word, direction, x, y, index);
                fprintf(out, "Successfully placed %s even though it was initially skipped.\n", current->word.word);
                // copies current->word to placed_words[*words_placed]
                //      more reliable to copy it via memory than directly (sizeof(Word) bytes), since I was having trouble with direct assigning stuff
                memcpy(&placed_words[*words_placed], &current->word, sizeof(Word));
                (*words_placed)++;
                successfully_placed = 1;
                num_placed++;

                break; // no need to look at more words if we found one that works
            }
        }

        // if we successfully placed a word, we can remove it from the linked list
        if (successfully_placed)
        {
            Node *temp = current;
            // check if it's the head (skipped_head) - if so, set the head to the next node
            if (prev == NULL)
            {
                *skipped_head = current->next;
            }
            // if it's not the head, have the previous node just point to the next (bypassing current node essentially)
            else
            {
                prev->next = current->next;
            }
            // update current to just be the next node
            current = current->next;
            free(temp); // done with the previous memory now, so we can free it
        }
        // move to the next word if we couldn't place a word
        else
        {
            prev = current;
            current = current->next;
        }
    }

    return num_placed; // return how many we placed (important to check it's not 0 because then it's over)
}

// main function to place words, and if it can't place it add it to a linked list of skipped words
void place_words(char board[BOARD][BOARD], Word words[], int num_words, FILE *out)
{
    Node *skipped_head = NULL; // initially empty linked list we'll use for skipped words
    Word placed_words[WORDS]; // array to store words we successfully place
    int words_placed = 0;
    int curr_word = 0;

    // place the first word in the center
    place_center(board, &words[0]);
    placed_words[words_placed] = words[0]; // we know it's just words[0] so no need to check
    words_placed++;
    curr_word++;

    // try placing the remaining words
    //      only going through it once because we'll add the ones we can't add to a linked list
    while (curr_word < num_words)
    {
        int index, x, y;

        // try to place word with intersections of all words on the board
        int placed = 0;
        for (int i = 0; i < words_placed; i++)
        {
            // make direction the opposite of the placed word's direction
            int direction = 1 - placed_words[i].direction;

            // if we can place it, then place it
            if (best_intersection(board, &placed_words[i], &words[curr_word], &index, &x, &y) == 1)
            {
                place(board, &words[curr_word], direction, x, y, index);
                fprintf(out, "Placing the word %s\n", words[curr_word].word);
                // add it to the placed_words array and increment the counter
                placed_words[words_placed] = words[curr_word];
                words_placed++;
                placed = 1;
                break; // we can break because we just added it
            }
        }

        // if we couldn't place the word on the board, add to the skipped linked list
        if (!placed)
        {
            fprintf(out, "Couldn't place %s, adding it to the skipped list.\n", words[curr_word].word);
            skipped_head = skip(skipped_head, words[curr_word], out);
        }

        curr_word++;
    }

    int num_places = -1; // arbitrary value that doesn't equal 0 
    // after we initially go through, loop through linked list continuously until it gives us 0
    //      when we get 0, that means no words can fit anywhere so there's no point in trying again
    while (num_places != 0)
    {
        num_places = place_skip(board, placed_words, &skipped_head, &words_placed, out);
    }

    // free any remaining nodes in the skipped list (if we didn't place everything)
    while (skipped_head != NULL)
    {
        Node *temp = skipped_head;
        skipped_head = skipped_head->next;
        free(temp);
    }
}

// generates an anagram and directly updates word->clue
void scramble_word(Word *word)
{
    // using a temp array so we don't change anything about the word struct until the end
    char temp[LETTERS];
    strcpy(temp, word->word);
    int len = strlen(temp);

    // scrambling the array
    for (int i = 0; i < len - 1; i++)
    {
        int j = i + rand() / (RAND_MAX / (len - i) + 1);
        // randomly swapping them (bubble sort basically)
        char temp_char = temp[i];
        temp[i] = temp[j];
        temp[j] = temp_char;
    }
    strcpy(word->clue, temp);
    word->clue[len] = '\0'; // ensure that the last char is a null char
}

// print out all the anagrams 
void display_clues(Word placed_words[], int words_placed, FILE *out)
{
    fprintf(out, "\nClues: \n");
    fprintf(out, "Location | Direction | Anagram\n");
    for (int i = 0; i < words_placed; i++)
    {
        Word *word = &placed_words[i];
        if (word->placed && word->x >= 0 && word->y >= 0 && (word->direction == 0 || word->direction == 1))
        {
            fprintf(out, " %4d,%2d | %8s | %-15s\n", word->x, word->y, (word->direction == 0) ? "Across" : "Down", word->clue);
        }
    }
}

// update solution and puzzle arrays to the value of board array
void update_solution_puzzle(char board[BOARD][BOARD], char solution[BOARD][BOARD], char puzzle[BOARD][BOARD])
{
    for (int i = 0; i < BOARD; i++)
    {
        for (int j = 0; j < BOARD; j++)
        {
            if (board[i][j] != ' ')
            {
                solution[i][j] = board[i][j];
                puzzle[i][j] = ' ';
            }
        }
    }
}