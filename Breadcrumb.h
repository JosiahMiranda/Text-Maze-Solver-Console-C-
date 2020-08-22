
#ifndef COSC_ASS_ONE_BREADCRUMB
#define COSC_ASS_ONE_BREADCRUMB

#include "Types.h"

#define NORTH  "north"
#define EAST   "east"
#define SOUTH  "south"
#define WEST   "west"

class Breadcrumb {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Constructor/Desctructor
   Breadcrumb(int x, int y, bool stale);
   ~Breadcrumb();

   // Copy Constructor
   Breadcrumb(Breadcrumb& other);

   // x-co-ordinate of the particle
   int getX();

   // y-co-ordinate of the particle
   int getY();

   // Get if the Breadcrumb is stale. (If false, it is good/fresh)
   bool isStale();

   // Mark this Breadcrumb as stale (or not)
   void setStale(bool stale);

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Methods to set and get the direction of the breadcrumb.
   std::string getDirection();
   void setDirection(std::string direction);


private:

   /*                                           */
   /* DO NOT MOFIFY THESE VARIABLES             */
   /*                                           */
   int x;
   int y;
   bool stale;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Stores the direction of the breadcrumb as it moves to another one.
   std::string direction;
};

#endif // COSC_ASS_ONE_BREADCRUMB
