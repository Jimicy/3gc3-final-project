#ifndef LIGHT_H
#define LIGHT_H

#include "PMath/PVector.h"

typedef enum { 
	LIGHT_UP, LIGHT_DOWN,
	LIGHT_LEFT, LIGHT_RIGHT
} LightMovement;

class Light {
	public:

		Light(int glLight, float pos[3], float amb[4], float diff[4], float spec[4]);
		
		void display();
		void moveLight(LightMovement movement);

		float position[3], ambient[4], diffuse[4], specular[4];
		int glLight;
};

#endif /* LIGHT_H */
