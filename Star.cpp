#include "Header.h"
#include "Star.h"
#include <cstdlib>
#include <ctime>
#include <string.h>

#define PI 3.14159265

using namespace std;

float randomFloat(float min, float max) {
	srand (static_cast <unsigned> (time(0)));

	float random = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
	return random;
}

Star::Star(float x, float y, float z) {
	position[0] = x;
	position[1] = y;
	position[2] = z;	
}

void Star::draw() {
	glColor4f(1.0f, 1.0f, 1.0f, 0.5F);
	float zero[4] = {0.0, 0.0, 0.0, 0.0};
	float emit[4] = {1.0, 1.0, 1.0, 0.2};

	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zero);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, zero);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
		glTranslatef(position[0], position[1], position[2]);
		glutSolidSphere(0.05, 12, 10);
	glPopMatrix();
}
