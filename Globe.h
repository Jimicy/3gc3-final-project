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
		std::vector<BoundedSphere> getBoundedSpheres();

		int mysphereID;
		GLUquadricObj *sphere;
		float diff[4];
		float rotation[3];
		float messagesLatAndLong[2][2] = {{25.9, 118.3},{21.0, 78.0}};
		std::vector<BoundedSphere> boundedSpheres; //Bounded boxes for our message for ray picking
};

#endif /* GLOBE_H */
