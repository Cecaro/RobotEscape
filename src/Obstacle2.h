#include "GameAsset.h"

#ifndef OBSTACLE2_H_
#define OBSTACLE2_H_

class Obstacle2 : public GameAsset {
 public:
  Obstacle2();
  Obstacle2(float x, float y, float z);
    ~Obstacle2();

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
F0, F1, F2, F3, R1, R2, R3 , R4, };

 private:
};

#endif // OBSTACLE2_H_