#include "Header.h"
#include "Camera.h"

#define CAMERA_SPEED 0.75f

Camera::Camera(PVector3f pos, PVector3f rotation) {
	position = pos;
	rotation = rotation;

	PVector3f forward(0.0f, 0.0f, -1.0f);
	PVector3f up(0.0f, 1.0f, 0.0f);

	PVector3f back  = -forward;
	PVector3f down  = -up;
	PVector3f left  = up * forward;
	PVector3f right = -left;
}

void Camera::look() {
	glTranslatef(-position.x, -position.y, -position.z);
	glRotatef(-rotation.x, 1, 0, 0);
	glRotatef(-rotation.y, 0, 1, 0);
	glRotatef(-rotation.z, 0, 0, 1);
}

void Camera::moveCamera(CameraMovement movement) {
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