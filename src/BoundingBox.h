#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <utility>
#include <memory>
#include "vectormath_cpp/vectormath_aos.h"

using namespace Vectormath::Aos;
using namespace std;

static Vector3 UNIT_X_AXIS(1.0, 0.0, 0.0);
static Vector3 UNIT_Y_AXIS(0.0, 1.0, 0.0);
static Vector3 UNIT_Z_AXIS(0.0, 0.0, 1.0);

enum AXIS {X, Y, Z};

class BoundingBox {
 public:
  BoundingBox(const Point3 & c, const float extent_x, const float extent_y, const float extent_z);
  bool collidesWith(const BoundingBox & b);

  pair<float,float> projectOntoAxis(const BoundingBox & b, enum AXIS);

  shared_ptr<Point3> getCentre();

 private:
  Vector3 h_x, h_y, h_z;
  shared_ptr<Point3> c;
};

#endif
