#include "Entity.h"
#include <vector>

bool Entity::Move(Point vec, const vector<vector<char> >& map) {
  if (this->Collide(this->pos, vec, map)) {
    return false;
  }
  this->pos += vec;
  return true;
}


bool Entity::Collide(Point curPos, Point vec, const vector<vector<char> >& map) {
  Point target = curPos + vec;
  if ( map[target.y][target.x] != '.' ) {
    return true;
  }

  return false;
}