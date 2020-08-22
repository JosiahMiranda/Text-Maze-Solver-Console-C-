
#include "MazeSolver.h"

#include <iostream>


MazeSolver::MazeSolver() {
   solution = new Trail();
}

MazeSolver::~MazeSolver() {
   delete solution;
}

MazeSolver::MazeSolver(int rows, int cols) {
   solution = new Trail(rows, cols);
   this->rows = rows;
   this->cols = cols;
}

/* 
 * Iterating through every element in the Maze until finding that which 
 * co-ordinates matches the START Position. Thus, has symbol 'S'. Then sets currentX
 * and currentY to those co-ordinates. Does the same for END Position.
 * Also ensures that once all co-ordinates are set, no unneccessary checking is done.
 */ 
void MazeSolver::setCoordinates(Maze maze) {
   bool startFound = false;
   bool endFound = false;

   for (int y = 0; y < this->rows; ++y) {
      for (int x = 0; x < this->cols; ++x) {
         if (maze[y][x] == START_SYMBOL) {
            currentY = y;
            currentX = x;
            startFound = true;
         } else if (maze[y][x] == END_SYMBOL) {
            endY = y;
            endX = x;
            endFound = true;
         }
      }
      if (startFound && endFound) {
         return;
      }
   }
}

void MazeSolver::solve(Maze maze) {

   bool solved = false;


   setCoordinates(maze);
   
   while(!solved) {
      // If the trail doesn't have a breadcrumb in the current location, add a breadcrumb.
      Breadcrumb* breadcrumb = nullptr;
      if (!solution->contains(currentX, currentY)) {
         breadcrumb = new Breadcrumb(currentX, currentY, false);
         solution->addCopy(breadcrumb);
      }

      breadcrumb = solution->findCurrentBreadcrumb(currentX, currentY);

      // Look for the next place to go by checking adjacent co-ordinates.
      if (CHECK_NORTH >= 0 && maze[CHECK_NORTH][currentX]
         != WALL && !solution->contains(currentX, CHECK_NORTH)) {

         --currentY;
         solution->setBreadcrumbsDirection(breadcrumb, NORTH);

      } else if (CHECK_EAST < this->cols && maze[currentY][CHECK_EAST]
         != WALL && !solution->contains(CHECK_EAST, currentY)) {

         ++currentX;
         solution->setBreadcrumbsDirection(breadcrumb, EAST);

      } else if (CHECK_SOUTH < this->rows && maze[CHECK_SOUTH][currentX]
         != WALL && !solution->contains(currentX, CHECK_SOUTH)) {

         ++currentY;
         solution->setBreadcrumbsDirection(breadcrumb, SOUTH);

      } else if (CHECK_WEST >= 0 && maze[currentY][CHECK_WEST]
         != WALL && !solution->contains(CHECK_WEST, currentY)) {
            
         --currentX;
         solution->setBreadcrumbsDirection(breadcrumb, WEST);

         // If this runs, there was no new available place. So we need to backtrack.
      } else {
         solution->goToLastGoodBreadcrumb(currentX, currentY);
      }

      if (currentX == endX && currentY == endY) {
         solved = true;
      }

   }
}

// Since returning a deep copy, used copy constructor of Trail.
Trail* MazeSolver::getSolution() {
   return new Trail(*solution);
}


