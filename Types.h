
#ifndef COSC_ASS_ONE_TYPES
#define COSC_ASS_ONE_TYPES

// Ensures all of the relevant classes can utilise strings.
#include <string>

// Orientation codes
#define WALL        '='
#define OPEN        '.'
#define ROUTE       '*'

// Defining the symbols in the maze
#define START_SYMBOL 'S'
#define END_SYMBOL   'E'

#define NEWLINE     '\n'

#define MAZE_DIM                20
#define TRAIL_ARRAY_MAX_SIZE    (MAZE_DIM * MAZE_DIM)

/* A 2D array to represent the maze or observations
 * REMEMBER: in a maze, the location (x,y) is found by maze[y][x]!
 * typedef char Maze[MAZE_DIM][MAZE_DIM];
 */
typedef char** Maze;


#endif // COSC_ASS_ONE_TYPES
