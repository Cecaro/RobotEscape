#include "Floor.h"

Floor::Floor(): GameAsset()
{
  Floor(0, 0, 0);
}

Floor::Floor(float x, float y, float z) :GameAsset(
  string("shaders/hello-gl.v.glsl"),
  string("shaders/ground_green-shader.f.glsl")){
  //this->li = nullptr;

  // A plane as a floor
  num_vertices = 4;
  num_triangles = 2;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

//x     y    z
  100, -30,  100, //F1
 -100, -30,  100, //F2
 -100, -30, -100, //F3
  100, -30, -100  //F4
}; 
// three points per vertex
  g_element_buffer_data = new GLushort[num_triangles * 3]{

	F1, F2, F3, 
	F1, F4, F3

}; // three vertices per triangle

  //bbox.reset();
  //bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

Floor::~Floor() {
  // TODO: do something nice and fun here.
}

void Floor::update() {
}

void Floor::draw() {
  GameAsset::draw();
}

void Floor::clean() { } 