#include "Player.h"

Player::Player(): GameAsset()
{
  Player(0, 0, 0);
}

Player::Player(float x, float y, float z) {
  //this->li = nullptr;

  // A default unit cube
  num_vertices = 8;
  num_triangles = 12;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

//x     y    z
-0.5, -0.5, 0.5,  //F - 0
 0.5, -0.5, 0.5,  //F - 1
-0.5, 0.5, 0.5,   //F - 2
 0.5, 0.5, 0.5,   //F - 3
-0.5, -0.5, -0.5, //B - 4
 0.5, -0.5, -0.5, //B - 5
-0.5, 0.5, -0.5,  //B - 6
 0.5, 0.5, -0.5   //B - 7
}; // three points per vertex

  g_element_buffer_data = new GLushort[num_triangles * 3]{

F0, F1, F2, //front
F1, F3, F2,

F1, R2, F3, //right
R2, R4, F3,

R2, R1, R4, //back
R1, R3, R4,

R1, F0, R3, //left
F0, F2, R3,

F2, F3, R3, //top
F3, R4, R3,

R1, R2, F0, //bottom
R2, F1, F0

}; // three vertices per triangle

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

Player::~Player() {
}

void Player::MoveLeft() {
    shared_ptr<Point3> MvL = this->bbox->getCentre();
    *MvL = Point3((MvL->getX()) - 0.5, 0.0, 0.0);
}
void Player::MoveRight() {
  shared_ptr<Point3> MvR = this->bbox->getCentre();
    *MvR = Point3(MvR->getX() - 0.5, 0.0, 0.0);
}  
void Player::MoveUp() {
  shared_ptr<Point3> MvU = this->bbox->getCentre();
    *MvU = Point3(MvU->getX() - 0.5, 0.0, 0.0);
}
void Player::MoveDown() {
  shared_ptr<Point3> MvD = this->bbox->getCentre();
    *MvD = Point3(MvD->getX() - 0.5, 0.0, 0.0);
}

void Player::update() {
}

void Player::draw() {
  GameAsset::draw();
}

void Player::clean() { } 