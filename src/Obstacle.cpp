#include "Obstacle.h"

Obstacle::Obstacle(): GameAsset()
{
  Obstacle(0, 0, 0);
}

Obstacle::Obstacle(float x, float y, float z) {
  // thinner cube for the gates
  num_vertices = 8;
  num_triangles = 12;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

//x     y    z
-2.5, -0.5,  0.125, //F - 0
 2.5, -0.5,  0.125, //F - 1
-2.5,  0.5,  0.125, //F - 2
 2.5,  0.5,  0.125, //F - 3
-2.5, -0.5, -0.125, //B - 4
 2.5, -0.5, -0.125, //B - 5
-2.5,  0.5, -0.125, //B - 6
 2.5,  0.5, -0.125  //B - 7
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
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 0.25));

  make_resources();
}

Obstacle::~Obstacle() {
  // TODO: do something nice and fun here.
}

void Obstacle::update() {
}

void Obstacle::draw() {
  GameAsset::draw();
}

void Obstacle::clean() { } 