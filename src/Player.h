#include "CubeAsset.h"
#include "SDL2/SDL.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player : public GameAsset {
 public:
  Player();
  Player(float x, float y, float z);
    ~Player();

  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void MoveDown();
  void MoveForward();
  void PlayerBoost();
  bool isItAlive();

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
F0, F1, F2, F3, R1, R2, R3 , R4, };

 private:
};

#endif // PLAYER_H_