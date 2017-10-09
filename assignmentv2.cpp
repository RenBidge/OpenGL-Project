// =====================================================================
// COSC363 Assignment - A Robot's World
// Author: Ben Ridgen
// Student ID: 14852010
// ---------------------------------------------------------------------
// The Following Code creates a scene with some features from the hit
// show Wipeout. There is a starting gate and a finishing gate + 2 major
// obstacles. A robot is jumping and ducking under one of the obstacles.
// =====================================================================


//------ Include statements --------------------------------------------
#include <cmath>
#include <GL/freeglut.h>
#include <iostream>
#include "loadTGA.h"
using namespace std;

//------ Globals -------------------------------------------------------
GLuint skyId[10];
float *x, *y, *z;  //vertex coordinate arrays
int *t1, *t2, *t3; //triangles
float  cam_x = 10,  cam_y = 20,  cam_z = 140;    //Initial camera position
float look_x = 0, look_y = 0, look_z = 0;    //"Look-at" point along -z direction
float  theta = 0.1;                              //Look angle
float spinnerAngle = 0;
int step = 0.1;								   //camera motion
float cam_hgt = 50;
float modelHeight = 0;
bool up = true;
bool upD = true;
float modelDHeight = 0;
int camMode = 0;

//------- Loads Given Textures/Skybox ------------------------------------------------
void loadTextures()				
{
	glGenTextures(10, skyId); 	// Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, skyId[0]);  //Use this texture
    loadTGA("front.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glBindTexture(GL_TEXTURE_2D, skyId[1]);  //Use this texture
    loadTGA("left.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, skyId[2]);  //Use this texture
    loadTGA("back.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, skyId[3]);  //Use this texture
    loadTGA("right.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, skyId[4]);  //Use this texture
    loadTGA("up.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, skyId[5]);  //Use this texture
    loadTGA("down.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glBindTexture(GL_TEXTURE_2D, skyId[6]);  //Use this texture
    loadTGA("Wall.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, skyId[7]);  //Use this texture
    loadTGA("Wipeout.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, skyId[8]);  //Use this texture
    loadTGA("Grass.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, skyId[9]);  //Use this texture
    loadTGA("Water.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

//--Function that converts the angle in degrees to radians -------------------
float toRadians(float degrees)
{
	float radians = degrees * (3.14159265359 / 180);
	return radians;
}

//---- Special Function for arrow key input ---------------------------------
void special(int key, int x, int y)
{
	step = 0;
	if(key == GLUT_KEY_LEFT) theta += toRadians(5); //Turn to left
	else if(key == GLUT_KEY_RIGHT) theta -= toRadians(5); //Turn to right
	else if(key == GLUT_KEY_DOWN) step = -1; //Move Back
	else if(key == GLUT_KEY_UP) step = 1; //Move Forward

	glutPostRedisplay();
}

//----- Used for spacebar key press ------------------------------------------
void keyboard(unsigned char Key, int x, int y)
{
	step = 0;
	if(Key == ' ') camMode = 1 - camMode; //change camMode if spacebar pressed
}

// ------ Draw Start and Finish -----------------------------------------------
void drawStartFinish()
{
	//Start
	glColor3f(0.8, 0, 0);
	glPushMatrix();
		glTranslatef(116, 0, -110);
		glRotatef(-90, 1, 0, 0);
		glutSolidCylinder(4, 40, 40, 40);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(110, 40, -110);
		glRotatef(90, 0, 1, 0);
		glutSolidCylinder(4, 40, 40, 40);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(144, 0, -110);
		glRotatef(-90, 1, 0, 0);
		glutSolidCylinder(4, 40, 40, 40);
	glPopMatrix();
	
	//Finish
	glColor3f(0.8, 0, 0);
	glPushMatrix();
		glTranslatef(-100, 0, 33);
		glRotatef(-90, 1, 0, 0);
		glutSolidCylinder(11, 3, 50, 10);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glPushMatrix();
		glTranslatef(-100, 0, 33);
		glRotatef(-90, 1, 0, 0);
		glutSolidCylinder(8, 3.01, 50, 10);
	glPopMatrix();
	glColor3f(0.8, 0, 0);
	glPushMatrix();
		glTranslatef(-100, 0, 33);
		glRotatef(-90, 1, 0, 0);
		glutSolidCylinder(5, 3.02, 50, 10);
	glPopMatrix();
	
	//Path to start from last obstacle
	glPushMatrix();
		glTranslatef(130, -0.511, -80);
		glRotatef(90, 0, 1, 0);
		glScalef(80, 1, 20);
		glutSolidCube(1);
	glPopMatrix();
	
	//Path to Finish from last obstacle
	glPushMatrix();
		glTranslatef(-75, -0.51, 33);
		glScalef(50, 1, 20);
		glutSolidCube(1);
	glPopMatrix();
	
	
}

//------- Draw SuckerPunch -----------------------------------------------
void suckerPunch()
{
	glColor3f(0.8, 0, 0);
	glPushMatrix();
		//Spinner 1
		glPushMatrix();
			glTranslatef(120, 0, -20);
			glRotatef(-spinnerAngle * 1.5, 0, 1, 0);
			glTranslatef(-120, 0, 20);
			glPushMatrix();
				glTranslatef(120, 0, -20);
				glRotatef(-90, 1, 0, 0);
				glutSolidCylinder(1.5, 12, 40, 40);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(120, 10.5, -20);
				glRotatef(-90, 0, 1, 0);
				glutSolidCylinder(1.2, 12, 40, 40);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(120, 10.5, -20);
				glRotatef(90, 0, 1, 0);
				glutSolidCylinder(1.2, 12, 40, 40);
			glPopMatrix();
		glPopMatrix();
		
		//Spinner 2
		glPushMatrix();
			glTranslatef(120, 0, 20);
			glRotatef(spinnerAngle * 1.5, 0, 1, 0);
			glTranslatef(-120, 0, -20);
			glPushMatrix();
				glTranslatef(120, 0, 20);
				glRotatef(-90, 1, 0, 0);
				glutSolidCylinder(1.5, 12, 40, 40);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(120, 10.5, 20);
				glutSolidCylinder(1.2, 12, 40, 40);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(120, 10.5, 20);
				glRotatef(180, 0, 1, 0);
				glutSolidCylinder(1.2, 12, 40, 40);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
	//Box + Platform
	glColor3f(0, 0, 1);
	glPushMatrix();
		glTranslatef(140, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(40, 40, 7);
		glutSolidCube(2);
	glPopMatrix();
	glColor3f(0.432, 0.275, 0.153);
	glPushMatrix();
		glTranslatef(135, 3, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(39.9, 2, 7);
		glutSolidCube(2);
	glPopMatrix();
	
	//Pool Boundary
	glColor3f(0.8, 0, 0);
	glPushMatrix();
		glTranslatef(117, 1, 40);
		glScalef(35, 2, 2);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(117, 1, -40);
		glScalef(35, 2, 2);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(100.5, 1, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(78, 2, 2);
		glutSolidCube(1);
	glPopMatrix();
	
	//Path
	glPushMatrix();
		glTranslatef(110, -0.511, 50);
		glScalef(60, 1, 20);
		glutSolidCube(1);
	glPopMatrix();
		
}

//------- Draw spinner ---------------------------------------------------
void drawSpinner()
{
	float lpos[4] = {80, 80, 0, 1.0};  //light's position
	float shadowMat[16] = { lpos[1],0,0,0, -lpos[0],0,-lpos[2],-1,
							0,0,lpos[1],0, 0,0,0,lpos[1] };
	glPushMatrix();
		glRotatef(spinnerAngle, 0, 1, 0);
		
		//Cylinder Base
		glColor3f(1, 0, 0);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glutSolidCylinder(4, 5, 30, 50);
		glPopMatrix();
		
		//Centre Cube
		glColor3f(1, 0, 0);
		glPushMatrix();
			glTranslatef(0, 12, 0);
			glScalef(1.2, 5, 1.2);
			glutSolidCube(3);
		glPopMatrix();
		
		//Lower Pole
		glColor3f(1, 0, 0);
		glPushMatrix();
			glTranslatef(0, 7, 0);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 1, 1);
		glPushMatrix();
			glTranslatef(0, 7, 10);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 0, 0);
		glPushMatrix();
			glTranslatef(0, 7, 20);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 1, 1);
		glPushMatrix();
			glTranslatef(0, 7, 30);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 0, 0);
		glPushMatrix();
			glTranslatef(0, 7, 40);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 1, 1);
		glPushMatrix();
			glTranslatef(0, 7, 50);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		
		//Upper Pole
		glColor3f(1, 0, 0);
		glPushMatrix();
			glTranslatef(0, 17.5, -10);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 1, 1);
		glPushMatrix();
			glTranslatef(0, 17.5, -20);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 0, 0);
		glPushMatrix();
			glTranslatef(0, 17.5, -30);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 1, 1);
		glPushMatrix();
			glTranslatef(0, 17.5, -40);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 0, 0);
		glPushMatrix();
			glTranslatef(0, 17.5, -50);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glColor3f(1, 1, 1);
		glPushMatrix();
			glTranslatef(0, 17.5, -60);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
	glPopMatrix();
	
	//Pool Boundary
	glColor3f(0.8, 0, 0);
	glPushMatrix();
		glTranslatef(20, -0.51, 33);
		glScalef(160, 1, 20);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 1, 59);
		glScalef(120, 2, 2);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 1, -59);
		glScalef(120, 2, 2);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(60, 1, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(120, 2, 2);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-60, 1, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(120, 2, 2);
		glutSolidCube(1);
	glPopMatrix();
	
	//Shadow Generation ---------------
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glMultMatrixf(shadowMat);
		glRotatef(spinnerAngle, 0, 1, 0);
		glColor4f(0.2, 0.2, 0.2, 1.0);
		
		//Cylinder Base
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glutSolidCylinder(4, 5, 30, 50);
		glPopMatrix();
		
		//Centre Cube
		glPushMatrix();
			glTranslatef(0, 12, 0);
			glScalef(1.2, 5, 1.2);
			glutSolidCube(3);
		glPopMatrix();
		
		//Lower Pole
		glPushMatrix();
			glTranslatef(0, 7, 0);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 7, 10);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 7, 20);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 7, 30);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 7, 40);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 7, 50);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		
		//Upper Pole
		glPushMatrix();
			glTranslatef(0, 17.5, -10);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 17.5, -20);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 17.5, -30);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 17.5, -40);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 17.5, -50);
			glutSolidCylinder(1.75, 10, 20, 80);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 17.5, -60);
			glutSolidCylinder(2, 10, 20, 80);
		glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING); 
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour
	float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

	loadTextures();		
	
	glEnable(GL_LIGHTING);					//Enable OpenGL states
	
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.01);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 	glEnable(GL_COLOR_MATERIAL);
 	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
 	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1., 1., 1000.); //The camera view volume  
}

//------ Sets the location of all the textures -------------------------------
void visuals()
{
	glColor3f(0.8, 0.7, 0.3);  //Use this texture
	glEnable(GL_TEXTURE_2D);

	//Skybox Front
	glBindTexture(GL_TEXTURE_2D, skyId[0]);
 	glBegin(GL_QUADS);
		glBindTexture(GL_TEXTURE_2D, skyId[0]);
		glTexCoord2f(0, 0); glVertex3f(-200, 0, 200);
		glTexCoord2f(1, 0); glVertex3f(-200, 0, -200);
		glTexCoord2f(1, 1); glVertex3f(-200, 100, -200);
		glTexCoord2f(0, 1); glVertex3f(-200, 100, 200);
	glEnd();
	
	//Skybox Left
	glBindTexture(GL_TEXTURE_2D, skyId[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-200, 0, -200);
		glTexCoord2f(1, 0); glVertex3f(200, 0, -200);
		glTexCoord2f(1, 1); glVertex3f(200, 100, -200);
		glTexCoord2f(0, 1); glVertex3f(-200, 100, -200);
	glEnd();
	
	//Skybox Back
	glBindTexture(GL_TEXTURE_2D, skyId[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(200, 0, -200);
		glTexCoord2f(1, 0); glVertex3f(200, 0, 200);
		glTexCoord2f(1, 1); glVertex3f(200, 100, 200);
		glTexCoord2f(0, 1); glVertex3f(200, 100, -200);
	glEnd();
	
	//Skybox Right
	glBindTexture(GL_TEXTURE_2D, skyId[3]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(200, 0, 200);
		glTexCoord2f(1, 0); glVertex3f(-200, 0, 200);
		glTexCoord2f(1, 1); glVertex3f(-200, 100, 200);
		glTexCoord2f(0, 1); glVertex3f(200, 100, 200);
	glEnd();
	
	//Skybox Up
	glBindTexture(GL_TEXTURE_2D, skyId[4]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(200, 100, 200);
		glTexCoord2f(1, 0); glVertex3f(-200, 100, 200);
		glTexCoord2f(1, 1); glVertex3f(-200, 100, -200);
		glTexCoord2f(0, 1); glVertex3f(200, 100, -200);
	glEnd();
	
	//Skybox Floor
	glBindTexture(GL_TEXTURE_2D, skyId[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(200, -0.15, 200);
		glTexCoord2f(2, 0); glVertex3f(200, -0.15, -200);
		glTexCoord2f(2, 2); glVertex3f(-200, -0.15, -200);
		glTexCoord2f(0, 2); glVertex3f(-200, -0.15, 200);
	glEnd();
	
	//Perimeter Wall
	glBindTexture(GL_TEXTURE_2D, skyId[6]);
	glBegin(GL_QUADS);
		//Front Wall
		glTexCoord2f(0, 0); glVertex3f(-180, 0, 180);
		glTexCoord2f(40, 0); glVertex3f(-180, 0, -180);
		glTexCoord2f(40, 4); glVertex3f(-180, 20, -180);
		glTexCoord2f(0, 4); glVertex3f(-180, 20, 180);
		
		//Left Wall
		glTexCoord2f(0, 0); glVertex3f(-180, 0, -180);
		glTexCoord2f(40, 0); glVertex3f(180, 0, -180);
		glTexCoord2f(40, 4); glVertex3f(180, 20, -180);
		glTexCoord2f(0, 4); glVertex3f(-180, 20, -180);
		
		//Back Wall
		glTexCoord2f(0, 0); glVertex3f(180, 0, -180);
		glTexCoord2f(40, 0); glVertex3f(180, 0, 180);
		glTexCoord2f(40, 4); glVertex3f(180, 20, 180);
		glTexCoord2f(0, 4); glVertex3f(180, 20, -180);
		
		//Right Wall
		glTexCoord2f(0, 0); glVertex3f(180, 0, 180);
		glTexCoord2f(40, 0); glVertex3f(-180, 0, 180);
		glTexCoord2f(40, 4); glVertex3f(-180, 20, 180);
		glTexCoord2f(0, 4); glVertex3f(180, 20, 180);
	glEnd();
	
	//Water 1
	glBindTexture(GL_TEXTURE_2D, skyId[9]);
	glBegin(GL_QUADS);
		//Centre Pool
		glTexCoord2f(0, 0); glVertex3f(-60, -0.1, -60);
		glTexCoord2f(3, 0); glVertex3f(60, -0.1, -60);
		glTexCoord2f(3, 3); glVertex3f(60, -0.1, 60);
		glTexCoord2f(0, 3); glVertex3f(-60, -0.1, 60);
		
		//Pool near suckerpunch
		glTexCoord2f(0, 0); glVertex3f(100, 0, 40);
		glTexCoord2f(2, 0); glVertex3f(140, 0, 40);
		glTexCoord2f(2, 1); glVertex3f(140, 0, -40);
		glTexCoord2f(0, 1); glVertex3f(100, 0, -40);
	glEnd();
	
	//grass
	glBindTexture(GL_TEXTURE_2D, skyId[8]);
	glBegin(GL_QUADS);
		//Surrounding Finish
		glTexCoord2f(0, 0); glVertex3f(-60, -0.1, 65);
		glTexCoord2f(2, 0); glVertex3f(-60, -0.1, -10);
		glTexCoord2f(2, 2); glVertex3f(-140, -0.1, -10);
		glTexCoord2f(0, 2); glVertex3f(-140, -0.1, 65);
		
		//Surrounding Start
		glTexCoord2f(0, 0); glVertex3f(100, -0.1, -140);
		glTexCoord2f(2, 0); glVertex3f(100, -0.1, -40);
		glTexCoord2f(2, 2); glVertex3f(160, -0.1, -40);
		glTexCoord2f(0, 2); glVertex3f(160, -0.1, -140);
		
		//Surrounding path between two features
		glTexCoord2f(0, 0); glVertex3f(60, -0.1, 80);
		glTexCoord2f(2, 0); glVertex3f(60, -0.1, 0);
		glTexCoord2f(2, 2); glVertex3f(145, -0.1, 0);
		glTexCoord2f(0, 2); glVertex3f(145, -0.1, 80);
	glEnd();
	
	//Wipeout Sign
	glBindTexture(GL_TEXTURE_2D, skyId[7]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0.25); glVertex3f(132.95, 5, -40);
		glTexCoord2f(1, 0.25); glVertex3f(132.95, 5, 40);
		glTexCoord2f(1, 0.75); glVertex3f(132.95, 40, 40);
		glTexCoord2f(0, 0.75); glVertex3f(132.95, 40, -40);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//--Draws a Robot constructed using GLUT objects ------------------
void drawRobot()
{
	glPushMatrix();
		glTranslatef(35, 0, 35);
		glScalef(2.5, 2.5, 2.5);
		glRotatef(-45, 0, 1, 0);
		
		glColor3f(0.701, 0.701, 0.701);
		glPushMatrix();
			//glTranslatef(0, 1.77, 3.65);
			//glRotatef(-60, 1, 0, 0);
			if(modelDHeight != 0) {
				glTranslatef(0, 4.5, 0);
				glRotatef(-modelDHeight * 9, 1, 0, 0);
				glTranslatef(0, -4.5, 0);
			}	
			//Head
			glPushMatrix();
			  glTranslatef(0, 7.7, 0);
			  glutSolidSphere(1, 50, 50);
			glPopMatrix();
			
			//Eyes
			glColor3f(0.2, 0.2, 0.2);
			glPushMatrix();
				glTranslatef(0.4, 8, 0.8);
				glutSolidCube(0.3);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.4, 8, 0.80);
				glutSolidCube(0.3);
			glPopMatrix();

			//Torso
			glColor3f(1., 0., 0.);
			glPushMatrix();
			  glTranslatef(0, 5.5, 0);
			  glScalef(3, 3, 1.4);
			  glutSolidCube(1);
			glPopMatrix();
			
			//Right arm
			glColor3f(0.701, 0.701, 0.701);
			glPushMatrix();
				glTranslatef(2, 6.5, 0);
				glRotatef(-modelHeight*10, 1, 0, 0);
				glRotatef(modelDHeight*4, 1, 0, 0);
				glTranslatef(-2, -6.5, 0);
				glTranslatef(-2, 5, 0);
				glScalef(1, 4, 1);
				glutSolidCube(1);
			glPopMatrix();
			
			//Left arm
			glColor3f(0.701, 0.701, 0.701);
			glPushMatrix();
				glTranslatef(2, 6.5, 0);
				glRotatef(-modelHeight*10, 1, 0, 0);
				glRotatef(modelDHeight*4, 1, 0, 0);
				glTranslatef(-2, -6.5, 0);
				glTranslatef(2, 5, 0);
				glScalef(1, 4, 1);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();

		//Right leg
		glColor3f(0.4, 0.4, 0.4);
		glPushMatrix();
			glTranslatef(-0.8, 2.2, 0);
			glScalef(1, 4.4, 1);
			glutSolidCube(1);
		glPopMatrix();

		//Left leg
		glColor3f(0.4, 0.4, 0.4);
		glPushMatrix();
			glTranslatef(0.8, 2.2, 0);
			glScalef(1, 4.4, 1);
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
}

//-- Alters the height of the Robot during a jump to mimick Gravity --------
void modelJump()
{
	glPushMatrix();
		//Way Up
		if(up == true) {
			if(modelHeight < 6) {
				modelHeight += 0.7;
			} else if(modelHeight >= 6 && modelHeight < 8) {
				modelHeight += 0.5;
			} else if(modelHeight >= 8 && modelHeight < 9.7) {
				modelHeight += 0.2;
			} else if(modelHeight >= 9.7 && modelHeight < 10) {
				modelHeight += 0.1;
			} else {
				up = false;
			}
		//Way Down
		} else {
			if(modelHeight >= 9.7) {
				modelHeight -= 0.1;
			} else if(modelHeight >= 8 && modelHeight < 9.7) {
				modelHeight -= 0.2;
			} else if(modelHeight >= 6 && modelHeight < 8) {
				modelHeight -= 0.5;
			} else if(modelHeight > 0 && modelHeight < 6) {
				modelHeight -= 0.7;
			} else {
				modelHeight = 0;
			}
		}
		glTranslatef(0, modelHeight, 0);
		drawRobot();
	glPopMatrix();
}

//---- Rotates the model about the waist to perform a limbo----------------
void modelDuck()
{
	glPushMatrix();
		//Way Down
		if(upD == true) {
			if(modelDHeight < 6) {
				modelDHeight += 0.5;
			} else if(modelDHeight >= 6 && modelDHeight < 8) {
				modelDHeight += 0.2;
			} else if(modelDHeight >= 8 && modelDHeight < 9.7) {
				modelDHeight += 0.1;
			} else if(modelDHeight >= 9.7 && modelDHeight < 10) {
				modelDHeight += 0.05;
			} else {
				upD = false;
			}
		//Way up - slower than way down
		} else {
			if(modelDHeight >= 9.7) {
				modelDHeight -= 0.03;
			} else if(modelDHeight >= 8 && modelDHeight < 9.7) {
				modelDHeight -= 0.07;
			} else if(modelDHeight >= 6 && modelDHeight < 8) {
				modelDHeight -= 0.13;
			} else if(modelDHeight > 0 && modelDHeight < 6) {
				modelDHeight -= 0.17;
			} else {
				modelDHeight = 0;
			}
		}
		drawRobot();
	glPopMatrix();
}

//---- Performs the normal camera movements when the arrow keys are pressed ------------
void moveCamera()
{
	float prev_x, prev_z;
	float dir_x = -sin(theta), dir_y = 0,  dir_z = -cos(theta);
	
	prev_x = cam_x;
	prev_z = cam_z;
	
	cam_x = cam_x + step * dir_x;
	cam_z = cam_z + step * dir_z;
	
	if(cam_x > 160 || cam_x < -140)
	{
		cam_x = prev_x;
	}
	if(cam_z > 160 || cam_z < -160)
	{
		cam_z = prev_z;
	}

	look_x = cam_x + 2 * dir_x;
	look_y = cam_y + 2 * dir_y;
	look_z = cam_z + 2 * dir_z;
	
	gluLookAt(cam_x, cam_y, cam_z,  look_x, look_y, look_z,   0, 1, 0);
}

//-------- Changes camera to a first person view ------------------------------
void camFP()
{
	gluLookAt(32 - modelDHeight, 20.5 + modelHeight - modelDHeight, 35,   0, 6 + modelDHeight * 8, 40,   0, 1, 0);
}

//--Display: ----------------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()  
{
	float lpos[4] = {80, 80, 0, 1.0};  //light's position
	float lgt1_pos[] = {50, 30, 50, 1.0};
	float spotdir[] = {-1, -1.5, -1};
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	//Set the camera mode based on camMode
	if(camMode == 0) {
		moveCamera();
	} else {
		camFP();
	}
	
	//Reset movement step to 0
	step = 0;
	
	//Setting light parameters
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //set light position
	
	glLightfv(GL_LIGHT1, GL_POSITION, lgt1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
	
	//Draw objects
	drawStartFinish();
	suckerPunch();
	drawSpinner();
	
	//draws model based on the position of the spinner
	if(spinnerAngle > 20 && spinnerAngle < 110) { 
		modelJump();
	} else if(spinnerAngle > 190 && spinnerAngle < 359) {
		modelDuck();
	} else {
		drawRobot();
	}
	
	//resets the value of up and upD so robot can jump/duck again
	if(spinnerAngle == 111) {
		up = true;
	} else if(spinnerAngle == 360) {
		upD = true;
	}
	
	//Draws skybox/textures
	visuals();

	glFlush();
}

//----- Used for rotations of the spinners --------------------------------
void timerCallback (int value)
{
	//changes the spinner angle every 10ms
	if(spinnerAngle < 360) {
		spinnerAngle++;
	} else {
		spinnerAngle = 0;
	}
	
	glutPostRedisplay();
	glutTimerFunc(10, timerCallback, 0);
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize (1600, 1200); 
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Wipeout");
	initialize();

	glutDisplayFunc(display); 
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(10, timerCallback, 0);
	
	glutMainLoop();
	return 0;
}
