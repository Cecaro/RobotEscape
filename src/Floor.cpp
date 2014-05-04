#include "Floor.h"

Floor::Floor(): GameAsset()
{
  Floor(0, 0, 0);
}

Floor::Floor(float x, float y, float z) :GameAsset(
  string("shaders/hello-gl.v.glsl"),
  string("shaders/ground_green-shader.f.glsl")){

  // A plane as a floor
  num_vertices = 4;
  num_triangles = 2;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{
// three points per vertex
//x     y    z
  500, -30,  500, //F1
 -500, -30,  500, //F2
 -500, -30, -500, //F3
  500, -30, -500  //F4
}; 
 // three vertices per triangle
  g_element_buffer_data = new GLushort[num_triangles * 3]{

	F1, F2, F3, 
	F1, F4, F3

};

  make_resources();
}

Floor::~Floor() {
}

void Floor::update() {
}

void Floor::draw() {
  GameAsset::draw();
}

void Floor::clean() { } 