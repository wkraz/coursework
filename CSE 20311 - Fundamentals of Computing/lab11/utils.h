#define SIZE 3
#define EMPTY '-'
#define X 'X'
#define O 'O'

// ANSI color codes
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

typedef struct {
    char board[SIZE][SIZE];
    char currentPlayer;
} GameState;

// Function prototypes
void initializeGame(GameState *game);
void displayBoard(GameState *game);
int checkWinner(GameState *game);
int isTerminal(GameState *game);
void getPlayerMove(GameState *game, char player);
void getAIMoveEasy(GameState *game, char aiPlayer);
void getAIMoveMedium(GameState *game, char aiPlayer);
void getAIMoveHard(GameState *game, char aiPlayer);
int minimax(GameState *game, int depth, int isMaximizing, char aiPlayer);