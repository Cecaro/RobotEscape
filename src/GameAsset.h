/*
 * GameObject.h
 *
 *  Created on: 03-Mar-2009
 *      Author: balor
 */
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "vectormath_cpp/vectormath_aos.h"
#include "Camera.h"
#include "BoundingBox.h"

using namespace std;
using namespace Vectormath::Aos;

#ifndef GAMEASSET_H_
#define GAMEASSET_H_

class GameAsset {
public:
	GameAsset();
	GameAsset(const string & v_shader, const string & f_shader);
	virtual ~GameAsset();

	bool collidesWith(GameAsset & a);

	virtual void draw();
	virtual void update()=0;
	virtual bool isDead() {isAlive = false;};
	virtual bool assetAlive(){return isAlive;};

	shared_ptr<BoundingBox> bbox;

protected:
	/* functions */
	int make_resources();
	GLchar* shader_file_contents(const string &filename, GLint * length);
	GLuint make_buffer(GLenum target, const void *buffer_data, GLsizei buffer_size);
	GLuint make_shader(GLenum type, const char *filename);
	GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);

	/* For keeping track of OpenGL VBOs */
	GLuint vertex_buffer, element_buffer;
	GLuint vertex_shader, fragment_shader, program;
	GLint position_attrib;
	GLint tx_uniform;

	GLfloat * g_vertex_buffer_data;
	GLushort * g_element_buffer_data;
      
	// How many vertices/triangles in this model
	int num_vertices;
	int num_triangles;


 private:
	void common_init(); // because we don't have delegating constructors yet (http://gcc.gnu.org/projects/cxx0x.html)
	string v_shader;
	string f_shader;
	bool isAlive;
};

#endif /* GAMEASSET_H_ */
