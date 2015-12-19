#include "Header.h"
#include "Globe.h"
#include "FreeImage.h"
#include <string.h>

Globe::Globe() {
	loadTexture();
	makeSphere();
	rotation[0] = -90.0;
	rotation[1] = 0.0; 
	rotation[2] = 90.0;
	// diff = {0.5, 0.5, 0.5, 0.2};
}

void Globe::rotateX() { rotation[0] += 10; }
void Globe::rotateY() { rotation[1] += 10; }
void Globe::rotateZ() { rotation[2] += 10; }

void Globe::draw() {
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		glRotatef(rotation[0],1.0,0.0,0.0);
		glRotatef(rotation[1],0.0,1.0,0.0);
		glRotatef(rotation[2],0.0,0.0,1.0);
		glCallList(mysphereID);
	glPopMatrix();
	// glTranslatef(1,0,0);
	// float diff[] = {0.5, 0.5, 0.5, 0.2};
	// glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	// glutSolidSphere(0.5, 20, 20);
}

void Globe::makeSphere() {
	// Make Sphere
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	
	//Making a display list
	mysphereID = glGenLists(1);
	glNewList(mysphereID, GL_COMPILE);
	gluSphere(sphere, 5, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);
}


void Globe::loadTexture() {
	// load Textures
	std::vector<std::string> files;
	files.push_back("images/earth2.png");

	for(int i = 0; i < files.size(); i++) {
		const char* cpFilename = files.at(i).c_str();
		FIBITMAP* bitmap = FreeImage_Load(FIF_PNG, cpFilename, PNG_DEFAULT);
		bitmap = FreeImage_ConvertTo24Bits(bitmap);
		if(FreeImage_GetBPP(bitmap) != 32) {
			FIBITMAP * tempImage = bitmap;
			bitmap = FreeImage_ConvertTo32Bits(bitmap);
		}

		if(bitmap != NULL) {
			glBindTexture(GL_TEXTURE_2D, i);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			BYTE *bits = new BYTE[FreeImage_GetWidth(bitmap) * FreeImage_GetHeight(bitmap) * 4];
			BYTE *pixels = (BYTE*) FreeImage_GetBits(bitmap);

			for (int pix = 0; pix<FreeImage_GetWidth(bitmap) * FreeImage_GetHeight(bitmap); pix++) {
					bits[pix * 4 + 0] = pixels[pix * 4 + 2];
					bits[pix * 4 + 1] = pixels[pix * 4 + 1];
					bits[pix * 4 + 2] = pixels[pix * 4 + 0];
			}

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);

			FreeImage_Unload(bitmap);
			delete bits;
		}

		printf("Loaded file %s\n", files.at(i).c_str());
	}

}