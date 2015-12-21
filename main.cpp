/* CS 3GC3 - Texturing sample
 * by R. Teather
 */
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PMath/PVector.h"
#include "BoundedSphere.h"
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
													"You must be the change you wish to see in the world. - Gandhi",
													"Success is going from failure to failure without losing your enthusiasm. - Winston Churchill",
													"The final project for 3GC3 is due December 20th at Midnight - Thomas Gwosdz",
													"PK thunder - Vicky Bilbily (3GC3)"};
int selectedMessageIndex; //Selected message by mouse

/**
 * [checkCollision check is the mouse click raycast intersects a bounded sphere]
 * @param  boundedSphere [Bounded sphere to test for ray sphere intersection]
 * @param  ray           [projected ray object to do calculations with intersection]
 * @return               [an int representing the index of the message that is selected]
 */
int checkCollision(BoundedSphere boundedSphere, Ray ray)
{
	Vector3D point = boundedSphere.point;
	float radius = boundedSphere.radius;
	int selectedMessageId = -1;
  float dist = sqrt(pow(point.x-ray.orig.x,2)+pow(point.y-ray.orig.y,2)+pow(point.z-ray.orig.z,2));

  for(int i = 0; i<1000; i++){ //It will check for collisions at one point and advance to the next until it hits an object
  	if(dist > radius){
      ray.orig.x += ray.dir.x;
      ray.orig.y += ray.dir.y;
      ray.orig.z += ray.dir.z;
      dist = sqrt(pow(point.x-ray.orig.x,2)+pow(point.y-ray.orig.y,2)+pow(point.z-ray.orig.z,2));
 		}
    else if(dist<=radius){ //If the dist between current ray position and object position is less than degree then its a hit
     selectedMessageId = boundedSphere.messageId;
     return selectedMessageId;
    }
  }
  return selectedMessageId;
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

	std::vector<BoundedSphere> shapes = earth->boundedSpheres;
	BoundedSphere b1 = shapes[0];
	BoundedSphere b2 = shapes[1];

	selectedMessageIndex = -1;

	for (int index; index < shapes.size(); index++) {
		int messageIndex = checkCollision(shapes[index], ray);
		if (messageIndex!=-1) {
			selectedMessageIndex = messageIndex;
		}
	}

	earth->selectedMessageIndex = selectedMessageIndex;
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

void setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 800);
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

	//2D Raster Text GUI for our message
  setOrthographicProjection();
  glPushMatrix();
  glLoadIdentity();
  renderBitmapString(10,30, "Inspirational messages from around the world");

  glDisable(GL_LIGHTING);
  glColor3f(0.7, 0.7, 0.7);
  if (selectedMessageIndex!=-1) {
  	renderBitmapString(10,10, messages[selectedMessageIndex].c_str());
  }
  glEnable(GL_LIGHTING);

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

void printStartMenu()
{
  printf("\033[H\033[J");
  printf("==================================================\n");
  printf("==========  Yi (Jimmy), Haris, Kurt's   ==========\n");
  printf("===Inspirational Messages From Around The World===\n");
  printf("==================================================\n");
  printf("\n");
  printf("------------- CONTROLS ----------- \n");
  printf("Click on the green spheres to select a inspiration quote\n");
  printf("WASD to move up right down and left\n");
  printf("Arrow keys to rotate map\n");
  printf("Spacebar to move up, c to crouch (move down)\n");
  printf("MOVE LIGHTS: TFGH to move LIGHT up right down and left\n");
  printf("z - toggle which light source you wish to move\n");
  printf("\n");
}

/* main function - program entry point */
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Global Data Visualization");

	glutTimerFunc(1000, update, 0);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	init();
	printStartMenu();
	glutMainLoop();
	return(0);
}
