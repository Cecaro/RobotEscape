#include "BoundingBox.h"

BoundingBox::BoundingBox(const Point3 & c, const float extent_x, const float extent_y, const float extent_z) {
  this->c   = shared_ptr<Point3>(new Point3(c));
  this->h_x = Vector3(extent_x/2.0, 0.0, 0.0);
  this->h_y = Vector3(0.0, extent_y/2.0, 0.0);
  this->h_z = Vector3(0.0, 0.0, extent_z/2.0);
}

bool between (const pair<float, float> & a, const pair<float, float> & b) {
  if((a.first >= b.first && a.first <= b.second)
     || (a.second >= b.first && a.second <= b.second))
    {
      return true;
    }
  return false;
}

bool BoundingBox::collidesWith(const BoundingBox & b) {

  if(between(projectOntoAxis(*this, X), projectOntoAxis(b, X))
     && between(projectOntoAxis(*this, Y), projectOntoAxis(b, Y))
     && between(projectOntoAxis(*this, Z), projectOntoAxis(b, Z))
     )
    {
      return true;
    }

  return false;
}

pair<float,float> BoundingBox::projectOntoAxis(const BoundingBox & b, enum AXIS axis) {

  float lo, hi;

  switch (axis) {
  case X:
    lo  = projection( Point3(Vector3(*(b.c)) + (-1 * b.h_x)), UNIT_X_AXIS);
    hi  = projection( Point3(Vector3(*(b.c)) + b.h_x), UNIT_X_AXIS);
    break;
  case Y:
    lo  = projection( Point3(Vector3(*(b.c)) + (-1 * b.h_y)), UNIT_Y_AXIS);
    hi  = projection( Point3(Vector3(*(b.c)) + b.h_y), UNIT_Y_AXIS);
    break;
  case Z:
    lo  = projection( Point3(Vector3(*(b.c)) + (-1 * b.h_z)), UNIT_Z_AXIS);
    hi  = projection( Point3(Vector3(*(b.c)) + b.h_z), UNIT_Z_AXIS);
    break;
  }

  return make_pair(lo, hi);
}

shared_ptr<Point3> BoundingBox::getCentre() {
  return c;
}
