#include "Header.h"
#include "Camera.h"

#define CAMERA_SPEED 0.75f

Camera::Camera(PVector3f pos, PVector3f rotation) {
	this->position = pos; // Camera Position Vector
	this->rotation = rotation; // Camera Rotation Vector
}

void Camera::look() {
	glTranslatef(-position.x, -position.y, -position.z);
	glRotatef(-rotation.x, 1, 0, 0);
	glRotatef(-rotation.y, 0, 1, 0);
	glRotatef(-rotation.z, 0, 0, 1);
}

void Camera::moveCamera(CameraMovement movement) {

	// Direction Vectors 
	PVector3f forward(0,0,-1);
	PVector3f back = -forward;
	PVector3f up(0,1,0);
	PVector3f down = -up;
	PVector3f left = up * forward;
	PVector3f right = -left;

	PVector3f direction;
	switch (movement) {
		case FORWARD:	direction = forward; break;
		case BACK:	  direction = back;    break;
		case UP:	    direction = up;      break;
		case DOWN:	  direction = down;    break;
		case LEFT:	  direction = left;    break;
		case RIGHT:	  direction = right;   break;
	}
	position = position + (direction * CAMERA_SPEED);
}

void Camera::rotateCamera(CameraMovement movement) {
	switch (movement) {
		case UP:    rotation.x--; break;
		case DOWN:  rotation.x++; break;
		case LEFT:  rotation.y--; break;
		case RIGHT:	rotation.y++; break;
	}
}

void Camera::lockCamera() {
	// Lock Rotation
	if (rotation.x > -5.0f)  rotation.x = -5.0f;
	if (rotation.x < -45.0f) rotation.x = -45.0f;
	if (rotation.y < 10.0f) rotation.y = 10.0f;
	if (rotation.y > 80.0f) rotation.y = 80.0f;
	if (rotation.z > 30.0f)  rotation.z = 30.0f;
	if (rotation.z < -45.0f) rotation.z = -45.0f;

	/* Lock Translation */
	if (position.x < -5) position.x = -5;
	if (position.x >  5) position.x =  5;
	if (position.y < -1) position.y = -1;
	if (position.y >  3) position.y =  3;
	if (position.z > 20) position.z = 20;
	if (position.z < 12) position.z = 12;
}