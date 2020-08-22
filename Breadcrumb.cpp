
#include "Breadcrumb.h"

Breadcrumb::Breadcrumb(int x, int y, bool stale) {
   this->x = x;
   this->y = y;
   this->stale = stale;
   // Set to blank because no direction has been defined yet.
   this->direction = "";
}

Breadcrumb::~Breadcrumb() {
}

Breadcrumb::Breadcrumb(Breadcrumb& other) {
   this->x = other.x;
   this->y = other.y;
   this->stale = other.stale;
   this->direction = other.direction;
}

int Breadcrumb::getX() {
   return x;
}

int Breadcrumb::getY() {
   return y;
}

bool Breadcrumb::isStale() {
   return stale;
}

void Breadcrumb::setStale(bool stale) {
   this->stale = stale;
}

void Breadcrumb::setDirection(std::string direction) {
   this->direction = direction;
}

std::string Breadcrumb::getDirection() {
   return direction;
}


