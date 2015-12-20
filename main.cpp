/* CS 3GC3 - Texturing sample
 * by R. Teather
 */
#include "Header.h"
#include <stdio.h>
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

/* CAMERA */
Camera *cam1;
PVector3f camPosition(0.0f, 0.0f, 25.0f);
PVector3f camRotation(-15.0f, 0.0f, 0.0f);

/* LIGHTING */
Light *light0, *light1, *light2;
float light_pos0 [3] = {0, 3, 25.0};
float light_pos1 [3] = {1.0, 6.0, 25.0};
float light_pos2 [3] = {-1.0, 6.0, 25.0};
float amb[4]  = {1, 1, 1, 1};
float diff[4] = {0.2f, 0.2f, 0.2f, 1};
float spec[4] = {1, 1, 1, 1};

/* MATERIALS */
Material *material1;
float m_amb[3] = {0.05375f, 0.05f, 0.06625f};
float m_diff[3] = {0.18275f, 0.17, 1};
float m_spec[3] = {0.332741f, 0.328634f, 0.346435f};
float shiny = 0.3f;

Material *material2;
float m_amb2[3] = {0.05375f, 0.05f, 0.06625f};
float m_diff2[3] = {0.18275f, 0.17, 1};
float m_spec2[3] = {0.332741f, 0.328634f, 0.346435f};
float shiny2 = 1.5f;

/* EARTH */
Globe *earth;

/* Inspirational Messages */
std::string messages[] = {"The journey of a thousand miles begins with one step. - Lao Tzu",
													"You must be the change you wish to see in the world. - Gandhi"};
float latAndLong[2][2] = {{25.9, 118.3},{21.0, 78.0}};
int selectedMessageIndex; //Selected message by mouse
std::vector<BoundedBox> boundedBoxes; //Bounded boxes for our message for ray picking

/**
 * This method returns an array of intersection point. If the ray intersects the bounding box then
 * return the closest intersection point. If no intersection return empty array.
 */
int checkCollision(std::vector<BoundedBox> shapes, Ray ray)
{
	double smallestTmin = 100000;
	int selectedShape = -1;

	for (int i=0; i<shapes.size(); i++){
		BoundedBox box = shapes[i];

		//Get the bounding points of our box
		Vector3D min = box.min; //p1
		Vector3D max = box.max; //p2

	 	double tmin = (min.x - ray.orig.x) / ray.dir.x;
		double tmax = (max.x - ray.orig.x) / ray.dir.x;

		if (tmin > tmax){
			std::swap(tmin, tmax);
		}

		double tymin = (min.y - ray.orig.y) / ray.dir.y;
		double tymax = (max.y - ray.orig.y) / ray.dir.y;

		if (tymin > tymax){
			std::swap(tymin, tymax);
		}

		if ((tmin > tymax) || (tymin > tmax)) {
			continue; // no intersection point continue to next bounded box
		}

		if (tymin > tmin) {
			tmin = tymin;
		}

		if (tymax < tmax){
			tmax = tymax;
		}

		double tzmin = (min.z - ray.orig.z) / ray.dir.z;
		double tzmax = (max.z - ray.orig.z) / ray.dir.z;

		if (tzmin > tzmax){
			std::swap(tzmin, tzmax);
		}

		if ((tmin > tzmax) || (tzmin > tmax)){
			continue; // no intersection point continue to next bounded box
		}

		if (tzmin > tmin){
			tmin = tzmin;
		}

		if (tzmax < tmax){
			tmax = tzmax;
		}

		//There is an intersection point. Now we want to check if it is the closest intersection point to our ray.
		//If so then remove the previous intersection point and set it to this new intersection point.
		if (tmin < smallestTmin){
			smallestTmin = tmin;
			selectedShape = box.shapeId;
		}
	}
	//true there is an intersection. return the intersect point in array.
	return selectedShape;
}

void Intersect(int x, int y)
{

	//allocate matricies memory
	double matModelView[16], matProjection[16];
	int viewport[4];

	//grab the matricies
	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	//unproject the values
	double winX = (double)x;
	double winY = viewport[3] - (double)y;

	double start[] = {0,0,0};
	double end[] = {1,1,1};

	// get point on the 'near' plane (third param is set to 0.0)
	gluUnProject(winX, winY, 0.0, matModelView, matProjection,
         viewport, &start[0], &start[1], &start[2]);

	// get point on the 'far' plane (third param is set to 1.0)
	gluUnProject(winX, winY, 1.0, matModelView, matProjection,
         viewport, &end[0], &end[1], &end[2]);

	//create new ray with the origin as the mouse click start position
	Ray ray = Ray(start, end);

	//boxes are defined by 2 points p1, p2
	double box2Min[] = {-2.5,-2.5,-2.5};
	double box2Max[] = {2.5,2.5,2.5};
	BoundedBox box2 = BoundedBox(box2Min, box2Max, 1);

	double box1Min[] = {-4.5, -0.5, -0.5};
	double box1Max[] = {-3.5, 0.5, 0.5};
	BoundedBox box1 = BoundedBox(box1Min, box1Max, 2);

	double box3Min[] = {-1.5,-1.5,-0.5};
	double box3Max[] = {-0.5,-0.5,0.5};
	BoundedBox box3 = BoundedBox(box3Min, box3Max, 3);

	boundedBoxes.push_back(box1);
	boundedBoxes.push_back(box2);
	boundedBoxes.push_back(box3);

	selectedMessageIndex = checkCollision(boundedBoxes, ray);

	glutPostRedisplay();
}

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
		Intersect(x,y);
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
	material2 = new Material(shiny2, m_amb2, m_diff2, m_spec2);
	earth = new Globe();

	GLuint id = 1;

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0, 0, 0, 0);

	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
  glBlendFunc(GL_ONE, GL_ONE);
}

void sphericalCoordinates() {
	/*LATITUDE LONGITUDE SPHERICAL COORDINATE MAPPING*/
	float latitude = 43.653226;
	float longitude = -79.383184;
	float radius = 5.0;

	float X = radius * cos(latitude) * cos(longitude);
	float Y = radius * cos(latitude) * sin(longitude);
	float Z = radius * sin(latitude);

	material2->display();

/*	glPushMatrix();
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(X*1.5, Y*1.5, Z*1.5);
	glEnd();
	glPopMatrix();*/
}

Vector3D latLongtoVector3D(float latitude, float longitude) {
	/*LATITUDE LONGITUDE SPHERICAL COORDINATE MAPPING*/
	float radius = 5.0;

	Vector3D point;
	point.x = radius * cos(latitude) * cos(longitude);
	point.y = radius * cos(latitude) * sin(longitude);
	point.z = radius * sin(latitude);

	return point;
}

void drawMessages() {
	for (int i=0; i<sizeof(messages); i++){
		Vector3D point = latLongtoVector3D(latAndLong[i][0], latAndLong[i][1]);
		// boundedBoxes;
		glPushMatrix(); //sets orgin as draw point
			glTranslatef(point.x, point.y, point.z);
			glDisable(GL_LIGHTING);
			glColor3f(0.5f, 1.0f, 0.0f);
			glutWireCube(0.1);
			glEnable(GL_LIGHTING);
		glPopMatrix(); //resets orgin for next object

		glPushMatrix();
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(point.x*1.5, point.y*1.5, point.z*1.5);
		glEnd();
		glPopMatrix();
	}
}

void setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}
void resetPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
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

	sphericalCoordinates();

	//3D lines on globe representing inspirational messages from around the world
	drawMessages();

	//2D Raster Text GUI for our message
  setOrthographicProjection();
  glPushMatrix();
  glLoadIdentity();
  renderBitmapString(10,30, "Inspirational messages from around the world");
  renderBitmapString(10,10, messages[1].c_str());
  glPopMatrix();
  resetPerspectiveProjection();

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
	glutTimerFunc(35, update, 0);
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
