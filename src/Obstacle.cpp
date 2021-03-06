#include "Obstacle.h"

Obstacle::Obstacle(): GameAsset()
{
  Obstacle(0, 0, 0);
}

Obstacle::Obstacle(float x, float y, float z) {
  // thinner cuboid for the wall
  num_vertices = 8;
  num_triangles = 12;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{
// three points per vertex
//x     y    z
-50.0, -25.0,  0.125, //F - 0
 50.0, -25.0,  0.125, //F - 1
-50.0,  25.0,  0.125, //F - 2
 50.0,  25.0,  0.125, //F - 3
-50.0, -25.0, -0.125, //B - 4
 50.0, -25.0, -0.125, //B - 5
-50.0,  25.0, -0.125, //B - 6
 50.0,  25.0, -0.125  //B - 7
}; 
//three vertices per triangle
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

}; 

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 100.0, 50.0, 0.25));

  make_resources();
}

Obstacle::~Obstacle() {
}

void Obstacle::update() {
}

void Obstacle::draw() {
  GameAsset::draw();
}

void Obstacle::clean() { } 