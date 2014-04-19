/*
 * Camera.cpp
 *
 *  Created on: 20 Mar 2011
 *      Author: aidan
 */

#include "Camera.h"

Camera* Camera::c = 0;

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::lookAt(const Point3 &eye, const Point3 &point, const Vector3 &up) {
  camera = new Matrix4(camera->lookAt(eye, point, up));
}

void Camera::setCamera(const Matrix4 & m) {
  Matrix4 * tmp = camera;
  camera = new Matrix4(m);
  delete (tmp);
}

float* Camera::getCamera() {
	float * f = new float[16];
	f[0] = camera->getCol0().getX();
	f[4] = camera->getCol0().getY();
	f[8] = camera->getCol0().getZ();
	f[12] = camera->getCol0().getW();

	f[1] = camera->getCol1().getX();
	f[5] = camera->getCol1().getY();
	f[9] = camera->getCol1().getZ();
	f[13] = camera->getCol1().getW();

	f[2] = camera->getCol2().getX();
	f[6] = camera->getCol2().getY();
	f[10] = camera->getCol2().getZ();
	f[14] = camera->getCol2().getW();

	f[3] = camera->getCol3().getX();
	f[7] = camera->getCol3().getY();
	f[11] = camera->getCol3().getZ();
	f[15] = camera->getCol3().getW();
	return f;
}

Matrix4& Camera::getCameraM() {
  return *camera;
}

Camera& Camera::getInstance() {
	if(0 == c) {
		c = new Camera();
	}
	return (*c);
}
