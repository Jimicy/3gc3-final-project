#ifndef GLOBE_H
#define GLOBE_H
#include "BoundedSphere.h"

class Globe {
	public:

		Globe();
		void draw();
		void makeSphere();
		void loadTexture();

		void rotateX();
		void rotateY();
		void rotateZ();
		Vector3D latLongtoVector3D(float latitude, float longitude);
		void drawMessages();

		int mysphereID;
		GLUquadricObj *sphere;
		float diff[4];
		float rotation[3];
		float messagesLatAndLong[5][2] = {{25.9, 118.3}, //Fujian, China
																			{21.0, 78.0}, //India
																			{51.5072, 0.1275}, //London, United Kingdom
																			{25.25, 155.8667}, //Hamilton, Ontario
																			{25.25, 155.666} //Hamilton, Ontario
																			};
		int numOfMessages = 5;
		int selectedMessageIndex = -1;
		std::vector<BoundedSphere> boundedSpheres; //Bounded boxes for our message for ray picking
};

#endif /* GLOBE_H */
