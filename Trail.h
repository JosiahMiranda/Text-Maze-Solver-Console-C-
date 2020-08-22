
#ifndef COSC_ASS_ONE_TRAIL
#define COSC_ASS_ONE_TRAIL

#include "Breadcrumb.h"
#include "Types.h"

// Defining the last index in Trail to be used in for loop.
#define LAST_INDEX   length-1

class Trail {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Constructor/Desctructor.
   Trail();
   ~Trail();

   // Copy Constructor.
   Trail(Trail& other);

   // Milestone 4 Constructor.
   Trail(int rows, int cols);

   // Number of elements in the Trail
   int size();

   // Get a pointer to the i-th trail element in the array - useful for making breadcrumbs stale.
   Breadcrumb* getPtr(int i);

   // Add a COPY trail element to the BACK of the trail.
   void addCopy(Breadcrumb* trail);

   // Check if the trail contain a breadcrumb at the location
   bool contains(int x, int y);

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Returns pointer to the breadcrumb at the current X and current Y location.
   Breadcrumb* findCurrentBreadcrumb(int currentX, int currentY);

   // Sets the last breadcrumb added's direction.
   void setBreadcrumbsDirection(Breadcrumb* lastBreadcrumb, std::string direction);

   /* 
    * Finds the last good breadcrumb in the trail and then goes
    * back to it. Also sets current breadcrumb to stale. Takes in
    * two references so that it can change the X and Y values in MazeSolver.
    */
   void goToLastGoodBreadcrumb(int& currentX, int& currentY);

private:
   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   /* Trail of breadcrumb objects
    * You may assume a fixed size for M1 & M2
    * Breadcrumb* breadcrumbs[TRAIL_ARRAY_MAX_SIZE];
    */
   Breadcrumb** breadcrumbs;

   // Number of breadcrumbs currently in the trail
   int length;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
};

#endif // COSC_ASS_ONE_TRAIL
