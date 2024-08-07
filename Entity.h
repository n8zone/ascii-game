#ifndef ENTITY_H // ENSURES ENTITY_H ISN'T ALREADY DEFINED
#define ENTITY_H

#include <iostream>

using namespace std;

struct Point {
  int x;
  int y;

  Point operator+(const Point& other) const {
    return {x + other.x, y + other.y};
  }

  Point& operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Point operator*(int scalar) const {
    return { x * scalar, y * scalar };
  }

  friend Point operator*(int scalar, const Point& point) {
    return { point.x * scalar, point.y * scalar };
  }

  friend ostream& operator<<(ostream& os, const Point& point) {
    os << "( " << point.x << ", " << point.y << " )";
    return os;
  }

};





class Entity {
  public:
  string tag;
  char sprite;
  Point pos;
  bool Move(Point vec, const vector<vector<char> >& map);
  bool Collide(Point curPos, Point vec, const vector<vector<char> >& map);
};

#endif