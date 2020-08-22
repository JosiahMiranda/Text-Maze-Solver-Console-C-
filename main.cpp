
/*
 *
 *  ASSIGNMENT ONE ANALYSIS - Josiah Miranda - s3782051
 * 
 *  My Approach:
 *  I took a very step-by-step approach in trying to complete the entire implementation of this program.
 *  Instead of trying to think about the entire specification at once, I ensured that I would complete
 *  portions of the implementation at a time. This included completing the Breadcrumb and Trail implementations
 *  and testing them fully before beginning on the MazeSolver and main files. From there, it was a matter of
 *  correctly implementing the Maze Solving algorithm and creating maze tests to check all of the expected
 *  functionalities.
 * 
 *  Encountered Issues:
 *  (Milestone 2) There were many issues in getting the backtracking to work, but they were systematically dealt with.
 *  (Milestone 3) The directions of breadcrumbs that were returned to due to backtracking would not be updated
 *  originally, and so the implementation needed to change to always update the breadcrumb to be equal to the 
 *  equivalent breadcrumb in the trail so that their direction could be updated.
 *  (Milestone 4) The program would encounter a segmentation fault if the maze ended with an empty line. This
 *  was due to the way in which the maze was read in.
 *  
 *  Decisions:
 *  (Milestone 1) All of the tests were created to test different parts of the implementation. Whether that be
 *  the expected order of movement in the maze, backtracking, and direction checking too.
 *  (Milestone 2) Methods were broken up wherever possible, and were kept related to their classes. For example,
 *  the MazeSolver did not have any breadcrumb methods, it was just the Trail class.
 *  (Milestone 3) Storing the directions in the actual breadcrumb class themselves meant I didn't need to do something
 *  like store each direction in an array. Additionally it made it very easy to print the directions at the end.
 *  (Milestone 4) Adding rows and columns as variables to Maze Solver allowed easy passing of the required number
 *  in the new methods for this milestone.
 * 
 *  Efficiency:
 *  I believe that the efficiency of my implementation and its design
 *  is overall decent. However there are some positives and negatives.
 * 
 *  Positive:
 *  For all the void methods that would search through arrays to find a certain value, the method would
 *  return as soon as it had been found to ensure there were no unnecessary comparisons. Methods are split into
 *  their classes logically, with all of the breadcrumb-related methods either in the class itself or part of
 *  the Trail class.
 * 
 *  Negative:
 *  The way in which my breadcrumb class is made, and how the directions are updated, this implementation
 *  constantly iterates throughout the trail of breadcrumbs to ensure it is always pointing at the correct
 *  breadcrumb. There were probably better ways to do the directions than this.
 *  The efficiency of the Milestone 4 implementation is not very good. It dynamically increases a character array's
 *  size by incrementing it by 1 every time it needs more space to hold a new character. This means that hundreds, even
 *  thousands of new arrays are being created for every maze.
 * 
 *  Milestones: 
 *  For Milestone 3, I needed to be able to keep track of the directions that were being followed in the solution.
 *  To do this, I included a new variable for the breadcrumb called 'direction' and set it whenever the
 *  program would move from that breadcrumb's position to another.
 * 
 *  For Milestone 4, many aspects of the implementation needed to be changed. The fixed 20x20 size was no longer
 *  able to be used since the maze could be of any rectangular size. So, instead variables were created to store
 *  the number of rows and columns of any maze that was passed in. Additionally each character needed to be stored into
 *  an array of characters which would increase in size dynamically as to not waste any memory.
 * 
 * 
 */

#include <iostream>

#include "Types.h"
#include "MazeSolver.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Read a maze from standard input for Milestone 4.
void readMazeStdin(Maze& maze, int& rows, int& columns);

char* newCharacters(char* characterArray, int& arrayLength);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, int& rows, int& cols, Trail* solution);

// Print out the walking directions to standard output.
void printWalkingDirections(Trail* solution);

// Maze creation method taken from milestone4.h.
Maze make_maze(const int rows, const int cols);

// Maze deletion method taken from milestone4.h.
void delete_maze(Maze maze, int rows, int cols);

// Method to validate the number of rows and columns when empty line is present.
void validateRowsAndCols(int& rows, int& cols, int& index, char* charactersArray);

int main(int argc, char** argv) {
    /* THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
     * AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
     * AS YOU GO ALONG.
     * COMMENT THESE OUT BEFORE YOU SUBMIT!!!
     */ 

    /* std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
     * testBreadcrumb();
     * testTrail();
     * std::cout << "DONE TESTING" << std::endl << std::endl;
     */

    // variables for the rows and columns of the maze. Needed for milestone 4.
    int rows = 0;
    int cols = 0;

    // Load Maze from stdin
    Maze maze = nullptr;
    readMazeStdin(maze, rows, cols);

    /* Solve using MazeSolver
     *  THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
     */
    
    MazeSolver* solver = new MazeSolver(rows, cols);
    Trail* solution = nullptr;
    solver->solve(maze);
    solution = solver->getSolution();

    // Print Maze to stdout
    printMazeStdout(maze, rows, cols, solution);

    // Print Walking Directions
    printWalkingDirections(solution);

    delete solver;
    delete solution;

    delete_maze(maze, rows, cols);

    return EXIT_SUCCESS;
}

Maze make_maze(const int rows, const int cols) {
   Maze maze = nullptr;

   if (rows >= 0 && cols >= 0) {
      maze = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         maze[i] = new char[cols];
      }
   }

   return maze;
}

void delete_maze(Maze maze, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete maze[i];
      }
      delete maze;
   }

   return;
}

// old read method. Try to create new one for Milestone 4

void readMazeStdin(Maze maze) {
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).

    char c = 'a';

    // Nested for loop to iterate through every value in the 20x20 2D array.
    for (int y = 0; y < MAZE_DIM; ++y) {
        for (int x = 0; x < MAZE_DIM; ++x) {
            std::cin >> c;
            if (std::cin.good()) {
                maze[y][x] = c;
            }
        }
    }
}

// Milestone 4 read maze to standard input method.

/*
 * Reading in a maze of any size. First reads all of the input
 * and stores it into a character array. Counts the number of rows and columns,
 * and then creates the maze using those rows and columns values. Finally, reads in
 * all of the characters from the character array into the maze to fully read it in.
 */

void readMazeStdin(Maze& maze, int& rows, int& cols) {

    int arrayLength = 1;
    char* charactersArray = new char[arrayLength];
    char c = 'a';
    int index = 0;
    while(!std::cin.eof()) {
        while(std::cin.get(c)) {
            if (index >= arrayLength) {
                ++arrayLength;
                charactersArray = newCharacters(charactersArray, arrayLength);
            }
            if (c == NEWLINE) {
                ++rows;
                cols = 0;
            } else {
                ++cols;
            }
            charactersArray[index] = c;
            ++index;
        }
    }

    validateRowsAndCols(rows, cols, index, charactersArray);
    
    maze = make_maze(rows, cols);

    index = 0;
    for (int y = 0; y < rows; ++y) {
        // Must also include the final column value since we account for newlines.
        for (int x = 0; x <= cols; ++x) {
            if (!(charactersArray[index] == NEWLINE)) {
                maze[y][x] = charactersArray[index];
            }
            ++index;
        }
    }
}

/*
 * Since in the case where there is an empty line at the end of the maze, 
 * the columns get reset to 0, we must reset their value to the proper amount.
 * Otherwise the maze will be of incorrect dimensions. Additionally we
 * check for every row which should not be counted (in case they are empty).
 */

void validateRowsAndCols(int& rows, int& cols, int& index, char* charactersArray) {
    // Account for the next row which is not added.
    ++rows; 
    // Checking the second last value if it has an empty line, 
    // since the last value is the end of file character.
    --index;

    if (charactersArray[index] == NEWLINE) {
        int lastIndex = index;
        // For every empty line, decrement row by one.
        while(charactersArray[lastIndex] == NEWLINE) {
            --rows;
            --lastIndex;
        }

        // Increment columns by one for every character up until the first newline character.
        for (int i = 0; i < index; ++i) {
            if (charactersArray[i] != NEWLINE) {
                ++cols;
            } else {
                return;
            }
        }
    }
}

// Method for dynamically increasing the size of the character array.

char* newCharacters(char* charactersArray, int& arrayLength) {
    char* returnCharacters = new char[arrayLength];
    int lastIndex = arrayLength-1;
    for (int i = 0; i < lastIndex; ++i) {
        returnCharacters[i] = charactersArray[i];
    }
    delete[] charactersArray;
    return returnCharacters;
}

// Old print method. Try to create new one for Milestone 4.

void printMazeStdout(Maze maze, Trail* solution) {
    Breadcrumb* currentBreadcrumb = nullptr;

    int x = 0;
    int y = 0;

    for (int i = 0; i < solution->size(); ++i) {
        currentBreadcrumb = solution->getPtr(i);
        x = currentBreadcrumb->getX();
        y = currentBreadcrumb->getY();

    
        /* Don't want to replace the Start position with a breadcrumb symbol!
         * Also don't print stale breadcrumbs.
         */
        if (maze[y][x] != START_SYMBOL && !currentBreadcrumb->isStale()) {
            maze[y][x] = ROUTE;
        }
    }
    for (int y = 0; y < MAZE_DIM; ++y) {
        for (int x = 0; x < MAZE_DIM; ++x) {
            std::cout << maze[y][x];
        }
        std::cout << std::endl;
        
    }
}


// New method for printing the maze out for Milestone 4. Uses rows and cols variables.

void printMazeStdout(Maze maze, int& rows, int& cols, Trail* solution) {
    Breadcrumb* currentBreadcrumb = nullptr;

    int x = 0;
    int y = 0;

    for (int i = 0; i < solution->size(); ++i) {

        currentBreadcrumb = solution->getPtr(i);

        x = currentBreadcrumb->getX();
        y = currentBreadcrumb->getY();
        

    
        /*
         * Don't want to replace the Start position with a breadcrumb symbol!
         * Also don't print stale breadcrumbs.
         */

        if (maze[y][x] != START_SYMBOL && !currentBreadcrumb->isStale()) {
            maze[y][x] = ROUTE;
        }
    }
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::cout << maze[y][x];
        }
        std::cout << std::endl;
        
    }
}

void printWalkingDirections(Trail* solution) {
    Breadcrumb* currentBreadcrumb = nullptr;

    // Iterate through every 'good' breadcrumb and print their direction from the last breadcrumb.
    for (int i = 0; i < solution->size(); ++i) {
        currentBreadcrumb = solution->getPtr(i);
        if (!currentBreadcrumb->isStale()) {
            std::cout << currentBreadcrumb->getDirection() << std::endl;
        }

    }
}

void testBreadcrumb() {
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb* breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;
}

void testTrail() {
    std::cout << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb* b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Add second breadcrumb
    Breadcrumb* b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb* getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl;

    // Print out the trail
    std::cout << "PRINTING OUT A TRAIL IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
