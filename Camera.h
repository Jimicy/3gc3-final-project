#ifndef CAMERA_H
#define CAMERA_H

#include "PMath/PVector.h"

typedef enum { 
	FORWARD, BACK,
	UP, DOWN,
	LEFT, RIGHT
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
