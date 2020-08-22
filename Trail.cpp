
#include "Trail.h"

#include <iostream>


Trail::Trail() {
   // Trail starts with 0 breadcrumbs.
   this->length = 0;
   for (int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i) {
      breadcrumbs[i] = nullptr;
   }
}

Trail::~Trail() {
   for (int i = 0; i < length; i++) {
      if (breadcrumbs[i] != nullptr) {
         delete breadcrumbs[i];
         breadcrumbs[i] = nullptr;
      }
   }
   delete[] breadcrumbs;
}

Trail::Trail(int rows, int cols) {
   this->length = 0;
   this->breadcrumbs = new Breadcrumb*[rows*cols];
   for (int i = 0; i < rows*cols; ++i) {
      breadcrumbs[i] = nullptr;
   }
}

/* 
 * DEEP copy which copies every element, including each breadcrumb.
 * So it iterates through each breadcrumb and copies them, remembering to deallocate used memory before reassigning.
 */
Trail::Trail(Trail& other) {
   this->length = other.length;
   this->breadcrumbs = new Breadcrumb*[length];
   for (int i = 0; i < length; ++i) {
      if (other.breadcrumbs[i] != nullptr) {
         Breadcrumb* newBreadcrumb = new Breadcrumb(*other.breadcrumbs[i]);
         breadcrumbs[i] = newBreadcrumb;
      }
   }
}

int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   return breadcrumbs[i];
}

// Since adding a copy, first used copy constructor of breadcrumb class.
void Trail::addCopy(Breadcrumb* t) {
   if (t != nullptr) {
      Breadcrumb* breadcrumb = new Breadcrumb(*t);
      breadcrumbs[length] = breadcrumb;
      delete t;
      ++length;
   }
}

// Finds the breadcrumb in the trail that matches the parameter and then sets the direction accordingly.
void Trail::setBreadcrumbsDirection(Breadcrumb* lastBreadcrumb, std::string direction) {
   if (lastBreadcrumb != nullptr) {
      Breadcrumb* currentBreadcrumb = nullptr;
      for (int i = 0; i < length; ++i) {
         currentBreadcrumb = breadcrumbs[i];
         if (lastBreadcrumb->getX() == currentBreadcrumb->getX() 
         && lastBreadcrumb->getY() == currentBreadcrumb->getY()) {
            currentBreadcrumb->setDirection(direction);
            return;
         }
      }
   }
}

// Iterates through every breadcrumb and returns the breadcrumb that already exists at the current location.
Breadcrumb* Trail::findCurrentBreadcrumb(int currentX, int currentY) {
   Breadcrumb* returnBreadcrumb = nullptr;
   for (int i = 0; i < length; ++i) {
      if (breadcrumbs[i]->getX() == currentX
      && breadcrumbs[i]->getY() == currentY) {
         returnBreadcrumb = breadcrumbs[i];
     }
   }
   return returnBreadcrumb;
}

void Trail::goToLastGoodBreadcrumb(int& currentX, int& currentY) {
   Breadcrumb* currentBreadcrumb = findCurrentBreadcrumb(currentX, currentY);
   currentBreadcrumb->setStale(true);

   // Iterating through every breadcrumb until finding the last 'good' one. Then go back to it using co-ordinates.
   for (int i = LAST_INDEX; i >= 0; --i) {
      currentBreadcrumb = breadcrumbs[i];
      if (!currentBreadcrumb->isStale()) {
         currentX = currentBreadcrumb->getX();
         currentY = currentBreadcrumb->getY();
         return;
      }
   }
}

bool Trail::contains(int x, int y) {
   bool found = false;
   /* Iterate through each breadcrumb in the train and check if their x and y values match with params.
    * Return true if that is the case, else return false.
    */
   for (int i = 0; i < length; ++i) {
      if(breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y) {
         found = true;
      }
   }
   return found;
}
