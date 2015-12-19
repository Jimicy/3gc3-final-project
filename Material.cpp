#include "Header.h"
#include "Material.h"
#include <string.h>


Material::Material(float shininess, float amb[3], float diff[3], float spec[3]){
	this->shininess = shininess;
	memcpy(ambient, amb, 3*sizeof(float));
	memcpy(diffuse, diff, 3*sizeof(float));
	memcpy(specular, spec, 3*sizeof(float));
}

void Material::display() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}