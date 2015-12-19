#ifndef CAMERA_H
#define CAMERA_H

#include "PMath/PVector.h"

typedef enum { 
	CAMERA_FORWARD, CAMERA_BACK,
	CAMERA_UP, CAMERA_DOWN,
	CAMERA_LEFT, CAMERA_RIGHT
} CameraMovement;

class Camera {
	public:

		Camera(PVector3f pos, PVector3f rotation);
		void look();
		void lockCamera();
		void moveCamera(CameraMovement movement);
		void rotateCamera(CameraMovement rotation);

		PVector3f position, rotation;
};

#endif /* CAMERA_H */
