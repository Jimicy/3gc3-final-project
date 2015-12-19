#ifndef GLOBE_H
#define GLOBE_H

class Globe {
	public:

		Globe();
		void draw();
		void makeSphere();
		void loadTexture();

		void rotateX();
		void rotateY();
		void rotateZ();
		
		int mysphereID;
		GLUquadricObj *sphere;
		float diff[4];
		float rotation[3];
};

#endif /* GLOBE_H */
