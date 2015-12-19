#ifndef GLOBE_H
#define GLOBE_H

class Globe {
	public:

		Globe();
		void draw();
		void makeSphere();
		void loadTexture();
		
		int mysphereID;
		GLUquadricObj *sphere;
		float diff[4];
};

#endif /* GLOBE_H */
