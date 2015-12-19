#include "Header.h"
#include "Light.h"
#include <string.h>

Light::Light(int glLight, float pos[3], float amb[4], float diff[4], float spec[4]) {
	memcpy(ambient,  amb, 4*sizeof(float));
	memcpy(diffuse,  diff,4*sizeof(float));
	memcpy(specular, spec,4*sizeof(float));
	memcpy(position, pos, 3*sizeof(float));
	this->glLight = glLight;
	glEnable(glLight);
}

void Light::display() {
	glLightfv(glLight, GL_POSITION, position);
  glLightfv(glLight, GL_AMBIENT, ambient);
	glLightfv(glLight, GL_DIFFUSE, diffuse);
	glLightfv(glLight, GL_SPECULAR, specular);

	glDisable(GL_LIGHTING);

	glColor4f(1.0f, 0.0f, 1.0f, 1.0F);

	glPushMatrix();
		glTranslatef(position[0], position[1], position[2]);
		glutSolidSphere(0.1, 12, 10);
	glPopMatrix();

	glEnable(GL_LIGHTING);

}

void Light::moveLight(LightMovement movement) {
	switch(movement) {
		case LIGHT_UP:
			position[0]++;
			position[2]++;
			break;
		case LIGHT_DOWN:
			position[0]--; 
			position[2]--; 
			break;
		case LIGHT_LEFT:
			position[0]--; 
			break;
		case LIGHT_RIGHT: 
			position[0]++; 
			break;
	}
}