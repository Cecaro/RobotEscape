#include "GameAsset.h"

#ifndef FLOOR_H_
#define FLOOR_H_

class Floor : public GameAsset {
 public:
  Floor();
  Floor(float x, float y, float z);
    ~Floor();

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
F1, F2, F3, F4, };

 private:
};

#endif // FLOOR_H_