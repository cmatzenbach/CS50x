/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 * 
 * Recommended order: init, draw, move, won
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// coords bank
int user_coords[2];
int zero_coords[2];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void boardSearch(int needle, int haystack[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // find highest value for numbers on board, save in two variables - 
    // one that will be decremented as the program goes along, and one 
    // that stays to have a log of what the highest value was
    int highest_value = (d * d) - 1;
    int value = (d * d) - 1;
    
    // loop through multi-dimensional array, putting numbers in correct array locations
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            board[i][j] = value;
            value--;
        }
    }
    
    // switch board positions of 1 and 2 if odd
    if ((highest_value % 2) == 1) {
        int temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // if single, print as type %2d
    // replace 0 with an empty space character
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] < 10) {
                if (board[i][j] == 0) printf("  _ ");
                else printf(" %2d ",board[i][j]);
            }
            else printf(" %d ",board[i][j]);
        }
        printf("\n");
    }
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // use boardSearch function to update passed arrays with coords of user-selected tile and emptyx (zero) tile
    boardSearch(tile, user_coords);
    boardSearch(0, zero_coords);
    
    // big if statement translates to: if x coords are equal and u_c y is one more or one less than z_c y
    // --OR-- if y coords are equal and u_c x is one more of one less than z_c x   -- if so, then it's within
    //  one space away and is a valid move - change corrosponding values in board as a result
    if ( (user_coords[0] == zero_coords[0] && (user_coords[1] == zero_coords[1] - 1 || user_coords[1] == zero_coords[1] + 1)) ||  
    (user_coords[1] == zero_coords[1] && (user_coords[0] == zero_coords[0] - 1 || user_coords[0] == zero_coords[0] + 1)) ) {
        board[user_coords[0]][user_coords[1]] = 0;
        board[zero_coords[0]][zero_coords[1]] = tile;
        
        return true;
    }
    else {
        return false;
    }
    
    return false;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int value = 1;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] == 0 && value == (d * d)) {
                return true;
            }
            else if (board[i][j] != value) {
                return false;
            }
            else {
                value++;
            }
        }
    }
    return true;
}


void boardSearch(int needle, int haystack[])
{
    int stopper = 0;
    
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] == needle) {
                haystack[0] = i;
                haystack[1] = j;
                stopper++;
                break;
            }
        }
        if (stopper == 1) break;
    }
    
}