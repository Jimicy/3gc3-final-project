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

/* Rotations on the 3 axes */
float xyzRotation[] = {-11, 40, 0};

/* The 6 direction vectors */
PVector3f forward(0,0,-1);
PVector3f back = -forward;
PVector3f up(0,1,0);
PVector3f down = -up;
PVector3f left = up * forward;
PVector3f right = -left;

/* Camera Vector for translations */
PVector3f cam(0.0f, 0.0f, 15.0f);

const float cameraSpeed = 0.75f;
const float shapeSpeed = 0.5f;

enum LightControl {LIGHT0, LIGHT1};
LightControl lightControl = LIGHT0;
enum ShapeControl {SHAPES, SCENE};
ShapeControl shapeControl = SCENE;

/* LIGHTING */
float light_pos0 [3] = {0, 3, 3};
float amb0[4]  = {1, 1, 1, 1};
float diff0[4] = {0, 0, 0, 1};
float spec0[4] = {1, 1, 1, 1};

float light_pos1 [3] =  {3 , 3, 0};
float amb1[4]  = {1, 1, 1, 1};
float diff1[4] = {0, 0, 0, 1};
float spec1[4] = {1, 1, 1, 1};

/* MATERIALS */
float m_amb[3] = {0.05375, 0.05, 0.06625};
float m_diff[3] = {0.18275, 0.17, 0.22525};
float m_spec[3] = {0.332741, 0.328634, 0.346435};
float shiny = 0.3f;

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

int selectedShapeID;

/* Shape trasnformation vectors */
Vector3D shapeTransformations;

GLUquadricObj *sphere=NULL;
int mysphereID;



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

void drawAxis()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0,0,0);
	glVertex3f(500,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0,500,0);
	glVertex3f(0,0,0);
	glVertex3f(0,0,500);
	glEnd();
	glEnable(GL_LIGHTING);
}

void drawLight()
{
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslatef(light_pos0[0], light_pos0[1], light_pos0[2]);
	glutSolidSphere(0.1, 12, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(light_pos1[0], light_pos1[1], light_pos1[2]);
	glutSolidSphere(0.1, 12, 10);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void lockCamera()
{
	/* Lock Rotation */
	if (xyzRotation[0] > -5.0f)
		xyzRotation[0] = -5.0f;
	if (xyzRotation[0] < -45.0f)
		xyzRotation[0] = -45.0f;

	if (xyzRotation[1] < 10.0f)
		xyzRotation[1] = 10.0f;
	if (xyzRotation[1] > 80.0f)
		xyzRotation[1] = 80.0f;

	if (xyzRotation[2] > 30.0f)
		xyzRotation[2] = 30.0f;
	if (xyzRotation[2] < -45.0f)
		xyzRotation[2] = -45.0f;

	/* Lock Translation */

	if (cam.x < -5)
		cam.x = -5;
	if (cam.x >  5)
		cam.x =  5;

	if (cam.y < -1)
		cam.y = -1;
	if (cam.y >  3)
		cam.y =  3;

	if (cam.z > 20)
		cam.z = 20;
	if (cam.z < 12)
		cam.z = 12;

}

/* Moves camera positions along a vector*/
void moveCamera(PVector3f dirVector, float amt)
{
	cam = cam + (dirVector*amt);
	//lockCamera();
}

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

//callbacks
void keyboard(unsigned char key, int x, int y)
{
	/*Esc to exit the program*/
	if(key == 27)
	{
		exit(0);
	}

	/*CAMERA CONTROL AND SHAPE CONTROL*/
	/*WASD+Space+z to control the camera*/
	else if (key == 'w')
	{
		if (shapeControl == SCENE)
		{
			moveCamera(forward, cameraSpeed);
		}
	} else if (key == 'a')
	{
		if (shapeControl == SCENE)
		{
			moveCamera(left, cameraSpeed);
		}
	} else if (key == 's')
	{
		if (shapeControl == SCENE)
		{
			moveCamera(back, cameraSpeed);
		}
	} else if (key == 'd')
	{
		if (shapeControl == SCENE)
		{
			moveCamera(right, cameraSpeed);
		}
		/* Space bar */
	}  else if (key == 32)
	{
		if (shapeControl == SCENE)
		{
			moveCamera(up, cameraSpeed);
		}
	} else if (key == 'c')
	{
		if (shapeControl == SCENE)
		{
			moveCamera(down, cameraSpeed);
		}
	}

	/*Z to toggle between moving light sources */
	else if (key == 'z')
	{
		switch(lightControl)
		{
			case LIGHT0:
				lightControl = LIGHT1;
				break;
			case LIGHT1:
				lightControl = LIGHT0;
				break;
			default:
				break;
		}
	}

	/* Move Lights */
	else if (key == 'f')
	{
		if (lightControl == LIGHT0)
		{
			light_pos0[0]--;
		} else if (lightControl == LIGHT1)
		{
			light_pos1[0]--;
		}
	} else if (key == 'h')
	{
		if (lightControl == LIGHT0)
		{
			light_pos0[0]++;
		} else if (lightControl == LIGHT1)
		{
			light_pos1[0]++;
		}
	} else if (key == 't')
	{
		if (lightControl == LIGHT0)
		{
			light_pos0[2]++;
			light_pos0[0]++;
		} else if (lightControl == LIGHT1)
		{
			light_pos1[2]++;
			light_pos1[0]++;
		}
	} else if (key == 'g')
	{
		if (lightControl == LIGHT0)
		{
			light_pos0[2]--;
			light_pos0[0]--;
		} else if (lightControl == LIGHT1)
		{
			light_pos1[2]--;
			light_pos1[0]--;
		}
	}

	glutPostRedisplay();
}

void special(int key, int x, int y)
{

	/* arrow key presses move the camera */
	switch(key){
		/* Rotate Camera*/
     	case GLUT_KEY_LEFT:
	        xyzRotation[1]--;
	        break;
      	case GLUT_KEY_RIGHT:
       		xyzRotation[1]++;
        	break;
      	case GLUT_KEY_UP:
       		xyzRotation[0]--;
        	break;
      	case GLUT_KEY_DOWN:
	        xyzRotation[0]++;
	        break;
 	}
  	// lockCamera();

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		// Intersect(x,y);
	}
}

void init(void)
{
	 /* LIGHTING */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLuint id = 1;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glClearColor(0.934, 0.898, 0.211, 1);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	//initializing our world
	initGraph();
}

void makeSphere() {
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	//Making a display list
	mysphereID = glGenLists(1);
	glNewList(mysphereID, GL_COMPILE);
	gluSphere(sphere, 1.0, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);
}

void loadTextures() {
	// load Textures
	std::vector<std::string> files;
	files.push_back("images/earth.png");

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

void drawGlobe() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glCallList(mysphereID);
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	/* Clear the Screen */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*6 DOF camera controls*/
	glTranslatef(-cam.x,-cam.y,-cam.z);

	glRotatef(-xyzRotation[0],1,0,0);
	glRotatef(-xyzRotation[1],0,1,0);
	glRotatef(-xyzRotation[2],0,0,1);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);

	 /* MATERIALS */
  	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  m_diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,  shiny);

	drawAxis();
	drawLight();

	drawGlobe();

	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("SimpleSceneGraph");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	init();
	loadTextures();
	makeSphere();

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}
