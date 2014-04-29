#include "GameAsset.h"

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

class Obstacle : public GameAsset {
 public:
  Obstacle();
  Obstacle(float x, float y, float z);
    ~Obstacle();

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
F0, F1, F2, F3, R1, R2, R3 , R4, };

 private:
};

#endif // OBSTACLE_H_