
#ifndef COSC_ASS_ONE_PARTICLE_FILTER
#define COSC_ASS_ONE_PARTICLE_FILTER

#include "Breadcrumb.h"
#include "Trail.h"
#include "Types.h"

// Defining directions when checking locations
#define CHECK_NORTH  currentY-1
#define CHECK_SOUTH  currentY+1
#define CHECK_EAST   currentX+1
#define CHECK_WEST   currentX-1


class MazeSolver {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Constructor/Destructor
   MazeSolver();
   ~MazeSolver();

   // Constructor for Milestone 4.
   MazeSolver(int rows, int cols);

   // Solve the maze
   void solve(Maze maze);

   // Get a DEEP COPY of the solution
   Trail* getSolution();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

private:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Trail of breadcrumbs from the start to end
   Trail* solution;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Co-ordinates used for the current location in the maze.
   int currentX;
   int currentY;

   // Co-ordinates used for the END location in the maze.
   int endX;
   int endY;

   // Variables to store the rows and columns sizes.
   int rows;
   int cols;

   // Function that sets current location to the START position and also finds the END location in maze.
   void setCoordinates(Maze maze);


};

#endif // COSC_ASS_ONE_PARTICLE_FILTER
