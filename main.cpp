/* CS 3GC3 - Texturing sample
 * by R. Teather
 */
#include "Header.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "PMath/PVector.h"
#include "BoundedBox.h"
#include "FreeImage.h"
#include "ray.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Globe.h"


enum LightControl {LIGHT0, LIGHT1};
LightControl lightControl = LIGHT0;
enum ShapeControl {SHAPES, SCENE};
ShapeControl shapeControl = SCENE;

/* CAMERA */
Camera *cam1;
PVector3f camPosition(0.0f, 0.0f, 17.0f);
PVector3f camRotation(-29.0f, 0.0f, 0.0f);

/* LIGHTING */
Light *light0, *light1, *light2;
float light_pos0 [3] = {0, 3, 7};
float light_pos1 [3] = {1.0, 6.0, 7};
float light_pos2 [3] = {-1.0, 6.0, 7};
float amb[4]  = {1, 1, 1, 1};
float diff[4] = {0.2f, 0.2f, 0.2f, 1};
float spec[4] = {1, 1, 1, 1};

/* MATERIALS */
Material *material1;
float m_amb[3] = {0.05375f, 0.05f, 0.06625f};
float m_diff[3] = {0.18275f, 0.17, 1};
float m_spec[3] = {0.332741f, 0.328634f, 0.346435f};
float shiny = 0.3f;

/* EARTH */
Globe *earth;

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

int selectedShapeID;

/* Shape trasnformation vectors */
Vector3D shapeTransformations;


//function which will populate a sample graph
void initGraph() {

}

// std::vector<BoundedBox> calcShapeBoundedBoxes()
// {
	// std::vector<BoundedBox> boundedBoxes;
	// std::vector<Node*> translations = SG->getTransformations();
	//
	// Vector3D p1, p2;
	// for (int i = 0; i < translations.size(); i++)
	// {
	// 	p1 = translations[i]->getShapePosition();
	// 	p2 = translations[i]->getShapePosition();
	//
	// 	p1.x -= 0.5f;
	// 	p1.y += 0.5f;
	// 	p1.z -= 0.5f;
	//
	// 	p2.x += 0.5f;
	// 	p2.y -= 0.5f;
	// 	p2.z += 0.5f;
	//
	// 	int shapeId = translations[i]->ID;
	//
	// 	BoundedBox boundedBox(p1,p2,shapeId);
	// 	boundedBoxes.push_back(boundedBox);
	//
	// }

	// return boundedBoxes;
// }

/**
 * This method returns an array of intersection point. If the ray intersects the bounding box then
 * return the closest intersection point. If no intersection return empty array.
 */
// int checkCollision(std::vector<BoundedBox> shapes, Ray ray)
// {
// 	double smallestTmin = 100000;
// 	int selectedShape = -1;
//
// 	for (int i=0; i<shapes.size(); i++){
// 		BoundedBox box = shapes[i];
//
// 		//Get the bounding points of our box
// 		Vector3D min = box.min; //p1
// 		Vector3D max = box.max; //p2
//
// 	 	double tmin = (min.x - ray.orig.x) / ray.dir.x;
// 		double tmax = (max.x - ray.orig.x) / ray.dir.x;
//
// 		if (tmin > tmax){
// 			std::swap(tmin, tmax);
// 		}
//
// 		double tymin = (min.y - ray.orig.y) / ray.dir.y;
// 		double tymax = (max.y - ray.orig.y) / ray.dir.y;
//
// 		if (tymin > tymax){
// 			std::swap(tymin, tymax);
// 		}
//
// 		if ((tmin > tymax) || (tymin > tmax)) {
// 			continue; // no intersection point continue to next bounded box
// 		}
//
// 		if (tymin > tmin) {
// 			tmin = tymin;
// 		}
//
// 		if (tymax < tmax){
// 			tmax = tymax;
// 		}
//
// 		double tzmin = (min.z - ray.orig.z) / ray.dir.z;
// 		double tzmax = (max.z - ray.orig.z) / ray.dir.z;
//
// 		if (tzmin > tzmax){
// 			std::swap(tzmin, tzmax);
// 		}
//
// 		if ((tmin > tzmax) || (tzmin > tmax)){
// 			continue; // no intersection point continue to next bounded box
// 		}
//
// 		if (tzmin > tmin){
// 			tmin = tzmin;
// 		}
//
// 		if (tzmax < tmax){
// 			tmax = tzmax;
// 		}
//
// 		//There is an intersection point. Now we want to check if it is the closest intersection point to our ray.
// 		//If so then remove the previous intersection point and set it to this new intersection point.
// 		if (tmin < smallestTmin){
// 			smallestTmin = tmin;
// 			selectedShape = box.shapeId;
// 		}
// 	}
// 	//true there is an intersection. return the intersect point in array.
// 	return selectedShape;
// }

// void Intersect(int x, int y)
// {
//
// 	//allocate matricies memory
// 	double matModelView[16], matProjection[16];
// 	int viewport[4];
//
// 	//grab the matricies
// 	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
// 	glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
// 	glGetIntegerv(GL_VIEWPORT, viewport);
//
// 	//unproject the values
// 	double winX = (double)x;
// 	double winY = viewport[3] - (double)y;
//
// 	double start[] = {0,0,0};
// 	double end[] = {1,1,1};
//
// 	// get point on the 'near' plane (third param is set to 0.0)
// 	gluUnProject(winX, winY, 0.0, matModelView, matProjection,
//          viewport, &start[0], &start[1], &start[2]);
//
// 	// get point on the 'far' plane (third param is set to 1.0)
// 	gluUnProject(winX, winY, 1.0, matModelView, matProjection,
//          viewport, &end[0], &end[1], &end[2]);
//
// 	//create new ray with the origin as the mouse click start position
// 	Ray ray = Ray(start, end);
//
// 	std::vector<BoundedBox> shapes = calcShapeBoundedBoxes();
//
// 	selectedShapeID = checkCollision(shapes, ray);
// 	selectedShapeNode = SG->highlightSelectedShape(selectedShapeID);
//
//
// 	if (selectedShapeNode != 0)
// 	{
// 		printf("shapes\n");
// 		shapeControl = SHAPES;
// 	} else
// 	{
// 		printf("scene\n");
// 		shapeControl = SCENE;
// 	}
//
// 	glutPostRedisplay();
// }

// /* Moves shape along a vector */
// void moveShape(PVector3f dirVector, float amt)
// {
// 	/* Shape vector for translations */
// 	PVector3f shapeTrans = (dirVector*amt);
// 	printf("%f %f %f\n", shapeTrans.x, shapeTrans.y, shapeTrans.z);
//
// 	selectedShapeNode->amount3.x -= shapeTrans.x;
// 	selectedShapeNode->amount3.y -= shapeTrans.y;
// 	selectedShapeNode->amount3.z -= shapeTrans.z;
//
// 	selectedShapeNode->describeNode();
//
// 	Node* parent = SG->getParentOfID(selectedShapeNode->ID);
// 	parent->describeNode();
// }

void moveLight(int lightID, LightMovement movement) {
	switch (lightID) {
		case 0: light0->moveLight(movement); break;
		case 1: light1->moveLight(movement); break;
	}
}

//callbacks
void keyboard(unsigned char key, int x, int y) {
	/* ESCAPE CONTROL*/
	if(key == 27 || key == 'q') exit(0);
	/*CAMERA CONTROL*/
	else if (key == 'w') cam1->moveCamera(CAMERA_FORWARD);
	else if (key == 'a') cam1->moveCamera(CAMERA_LEFT);
	else if (key == 's') cam1->moveCamera(CAMERA_BACK);
	else if (key == 'd') cam1->moveCamera(CAMERA_RIGHT);
	else if (key == 32)  cam1->moveCamera(CAMERA_UP);
	else if (key == 'c') cam1->moveCamera(CAMERA_DOWN);
	/* LIGHT CONTROL */
	else if (key == 'f') moveLight(lightControl, LIGHT_LEFT);
	else if (key == 'h') moveLight(lightControl, LIGHT_RIGHT);
	else if (key == 't') moveLight(lightControl, LIGHT_UP);
	else if (key == 'g') moveLight(lightControl, LIGHT_DOWN);
	/* TOGGLE LIGHT SOURCE */
	else if (key == 'z') {
		lightControl = (lightControl == LIGHT0) ? LIGHT1 : LIGHT0;
	}

	glutPostRedisplay();
}

void special(int key, int x, int y) {
	switch(key){
     	case GLUT_KEY_LEFT:  cam1->rotateCamera(CAMERA_LEFT); break;
    	case GLUT_KEY_RIGHT: cam1->rotateCamera(CAMERA_RIGHT); break;
    	case GLUT_KEY_UP:    cam1->rotateCamera(CAMERA_UP); break;
    	case GLUT_KEY_DOWN:  cam1->rotateCamera(CAMERA_DOWN); break;
    	case GLUT_KEY_PAGE_UP:   earth->rotateX(); break;
    	case GLUT_KEY_PAGE_DOWN: earth->rotateY(); break;
    	case GLUT_KEY_HOME:      earth->rotateZ(); break;
 	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		// Intersect(x,y);
	}
}

void init() {
	glEnable(GL_LIGHTING);
  glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	
	cam1   = new Camera(camPosition, camRotation);
	light0 = new Light(GL_LIGHT0, light_pos0, amb, diff, spec);
	light1 = new Light(GL_LIGHT1, light_pos1, amb, diff, spec);
	light2 = new Light(GL_LIGHT2, light_pos2, amb, diff, spec);
	material1 = new Material(shiny, m_amb, m_diff, m_spec);
	earth = new Globe();

	GLuint id = 1;

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0, 0, 0, 0);

	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
  glBlendFunc(GL_ONE, GL_ONE);

	//initializing our world
	initGraph();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cam1->look();
	earth->draw();
	light0->display();
	light1->display();
	light2->display();
	material1->display();

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	glLoadIdentity();

	float aspect = width * 1.0 / (float)height;
	gluPerspective(45.0, aspect, 1.0f, 100.0f);
}

void update(int value) {
	earth->rotateZ();
	glutPostRedisplay();
	glutTimerFunc(40, update, 0);
}

/* main function - program entry point */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Global Data Visualization");

	glutTimerFunc(1000, update, 0);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	init();

	glutMainLoop();
	return(0);
}
