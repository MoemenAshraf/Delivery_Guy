#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <string.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
int status = 0;
int WIDTH = 800;
int cheer2 = 0;
int HEIGHT = 600;
float leftright = 0;
float forward = 0;
float leftright2 = 0;
float forward2 = 0;
float d = 0.05;
float zm = 1;
float text = 10;
int hit = 0;
int hit2 = 0;
float score = 0;
int life = 3;
float timer = 80;
int collidework = 1;
int ftimes = 0;
int collideeffect = 0;
int cheer = 0;
int timetosnd = 0;
int cameraview = 0;
int level2 = 0;

int collidework2 = 1;
int ftimes2 = 0;
int collideeffect2 = 0;
GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 1000;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(2.5, 1.2, 1);
Vector At(2.5, 1.3, -250);
Vector Up(0, 1, 0);




int cameraZoom = 0;

// Model Variables

Model_3DS player;
Model_3DS motor;
Model_3DS pizza;
Model_3DS street;
Model_3DS sink;
Model_3DS bin;
Model_3DS water;
Model_3DS house1;
Model_3DS house2;
Model_3DS car1;
Model_3DS car2;
Model_3DS stickman;
Model_3DS streetlight;
Model_3DS time;

Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_cone;
Model_3DS model_house3;
Model_3DS model_tree2;
Model_3DS model_tree5;
Model_3DS model_barrier;

Model_3DS reachhome;




// Textures
GLTexture tex_ground;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void print3d(int x, int y, int z, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	
		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	
	
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================

void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}
void drawstreet() {
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glScaled(5, 1, 200);
	glTranslated(0, 0, -1);
	drawWall(0.05);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScaled(0.1, 1, 200);
	glTranslated(23, 0.02, -1);
	drawWall(0.05);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScaled(0.1, 1, 200);
	glTranslated(25, 0.02, -1);
	drawWall(0.05);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
}

void drawstreetside(double z) {

	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	//glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);
	glPushMatrix();
	for (int i = 0; i < 100; i++) {
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslated(-0.3, 0, -z);
		glScaled(0.3, 1, 1);
		drawWall(0.3);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslated(-0.3, 0, -z - 1);
		glScaled(0.3, 1, 1);
		drawWall(0.3);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslated(5, 0, -z);
		glScaled(0.3, 1, 1);
		drawWall(0.3);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslated(5, 0, -z - 1);
		glScaled(0.3, 1, 1);
		drawWall(0.3);
		glPopMatrix();
		z += 2;
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);

}
void collision() {
	

	if (((forward<-36 && forward>-39) && (leftright > -0.95 && leftright < 0.1)) || ((forward<-42.2 && forward>-43.7) && (leftright > 0.05 && leftright < 1.15))
		|| ((forward<-51 && forward>-53) && (leftright > -1.7 && leftright < -0.7)) || ((forward<-55 && forward>-57) && (leftright > -0.25 && leftright < 2.35))
		|| ((forward<-75 && forward>-78) && (leftright > -1.85 && leftright < -0.8)) || ((forward<-85.5 && forward>-88.5) && (leftright > -0.9 && leftright < 0.1))
		|| ((forward<-95.5 && forward>-98.5) && (leftright > 0.1 && leftright < 1.15)) || ((forward<-106 && forward>-108) && (leftright > -0.6 && leftright < 0.3))
		|| ((forward<-116 && forward>-118) && (leftright > -1.67 && leftright < -0.75)) || ((forward<-115 && forward>-118) && (leftright > 1 && leftright < 2.1))
		|| ((forward<-142.4 && forward>-144) && (leftright > -0.85 && leftright < 0.1)) || ((forward<-146 && forward>-148) && (leftright > -0.25 && leftright < 2.35))
		|| ((forward<-161.2 && forward>-163.2) && (leftright > 0.4 && leftright < 1.3)) || ((forward<-171.2 && forward>-173.2) && (leftright > -0.6 && leftright < 0.3))
		|| ((forward<-175.6 && forward>-178.6) && (leftright > 0.1 && leftright < 1.1))) {
		hit += 1;
		PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		_sleep(1);
		collidework = 0;
		life -= 1;
	}
	if (((forward<-116.5 && forward>-117.5) && (leftright > 0.45 && leftright < 0.8))) {
		PlaySound(TEXT("present.wav"), NULL, SND_FILENAME | SND_ASYNC);
		_sleep(1);
		timer += 2;
		score += 10000;
	}

}
void collision1() {


	if (((forward2<-11.5 && forward2>-10.5) && (leftright2 > -0.6 && leftright2 < 2.5)) || ((forward2<-17.8 && forward2>-19.6) && (leftright2 > -0.13 && leftright2 < 0.35))
		|| ((forward2<-28 && forward2>-29.6) && (leftright2 > -1.1 && leftright2 < -0.65)) || ((forward2<-38 && forward2>-39.6) && (leftright2 > 1.3 && leftright2 < 1.8))
		 || ((forward2<-47.8 && forward2>-49.4) && (leftright2 > -1.6 && leftright2 < -1.1)) || ((forward2<-59.4 && forward2>-60.5) && (leftright2 > -0.15 && leftright2 < 0.35))
		)
		{
		hit2 += 1;
		PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		_sleep(1);
		collidework2 = 0;
		life -= 1;
	}
}

void drawplayer() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	if (forward > -210) {
		forward -= 0.2;
	}
	glTranslated(leftright, 0, forward);
	//Clear Model_View Matrix
	//Setup Camera with modified paramters
	if (collidework == 1) {
		collision();
	}
	glPushMatrix();
	glTranslated(0, 0, -2);
	glPushMatrix();
	glTranslated(2.65, 0.2, -0.25);
	glScaled(0.015, 0.015, 0.015);
	glRotated(180, 0, 1, 0);
	player.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(2.4, 0.4, -1);
	glScaled(0.004, 0.004, 0.004);
	glRotated(180, 0, 1, 0);
	motor.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(2.7, 0.52, -0.7);
	glScaled(0.015, 0.015, 0.015);
	pizza.Draw();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}
void drawplayer2() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	if (forward2 > -110) {
		forward2 -= 0.2;
	}
	if (collidework2 == 1) {
		collision1();
	}
	glTranslated(leftright2, 0, forward2);
	glPushMatrix();
	glTranslated(0, 0, -2);
	glPushMatrix();
	glTranslated(2.65, -0.8, 1.7);
	glScaled(0.015, 0.015, 0.015);
	glRotated(180, 0, 1, 0);
	player.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.4, -0.6, -1);
	glScaled(0.004, 0.004, 0.004);
	glRotated(180, 0, 1, 0);
	motor.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.7, -0.48, -0.7);
	glScaled(0.015, 0.015, 0.015);
	pizza.Draw();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glutPostRedisplay();
}
void drawhouses(int x) {
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 7; i++) {
		glPushMatrix();
		glTranslated(-5, 0, -x);
		glRotated(90, 0, 1, 0);
		glScaled(0.3, 0.3, 0.3);
		house1.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-5, 1.3, -(x + 12));
		glRotated(90, 0, 1, 0);
		glScaled(0.0003, 0.0003, 0.0003);
		house2.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(10, 0, -x);
		glRotated(-90, 0, 1, 0);
		glScaled(0.3, 0.3, 0.3);
		house1.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(10, 1.3, -(x + 12));
		glRotated(-90, 0, 1, 0);
		glScaled(0.0003, 0.0003, 0.0003);
		house2.Draw();
		glPopMatrix();
		x += 24;
	}
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);


}
void drawlego(int y, int z, int x) {
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glTranslated(x, 0.5, -y);
		glRotated(z, 0, 1, 0);
		glScaled(0.3, 0.3, 0.3);
		stickman.Draw();
		glPopMatrix();

		if (x == -1) {
			x += -1;
		}
		else {
			x += 1;
		}
		y += 10;
		z += 90;
	}
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}
void drawstreetlights(int x) {
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 15; i++) {
		glPushMatrix();
		glTranslated(5.5, 1, -x);
		glScaled(0.3, 0.3, 0.3);
		streetlight.Draw();
		glPopMatrix();
		x += 7;
	}
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}
void drawsink(int x) {
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslated(2.6, 0.1, -x);
		glScaled(0.0008, 0.0008, 0.0008);
		sink.Draw();
		glPopMatrix();
		x += 25;
	}
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}
void drawwater(int x, int y) {
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslated(y, 0.2, -x);
		glScaled(0.0025, 0.0025, 0.0025);
		water.Draw();
		glPopMatrix();
		glPushMatrix();
		glTranslated(y + 0.5, 0.2, -x);
		glScaled(0.0025, 0.0025, 0.0025);
		water.Draw();
		glPopMatrix();
		glPushMatrix();
		glTranslated(y + 0.25, 0.2, -x + 0.5);
		glScaled(0.0025, 0.0025, 0.0025);
		water.Draw();
		glPopMatrix();
		y += 1.2;
		x += 55;
	}
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}
void drawcars() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslated(1, 0, -80);
	glScaled(0.6, 0.6, 0.6);
	car1.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(3.5, 0.55, -60);
	glRotated(90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glScaled(0.6, 0.6, 0.6);
	car1.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(2, 0.5, -40);
	glScaled(0.015, 0.015, 0.015);
	car2.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(3, 0.5, -100);
	glScaled(0.015, 0.015, 0.015);
	car2.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(4, 0, -120);
	glScaled(0.6, 0.6, 0.6);
	car1.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(3.5, 0.55, -150);
	glRotated(90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glScaled(0.6, 0.6, 0.6);
	car1.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(2, 0.5, -90);
	glScaled(0.015, 0.015, 0.015);
	car2.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslated(3, 0.5, -180);
	glScaled(0.015, 0.015, 0.015);
	car2.Draw();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
}
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	//glRotated(90, 0.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-7, 0, 0);
	glTexCoord2f(5, 0);
	glVertex3f(7, 0, 0);
	glTexCoord2f(5, 5);
	glVertex3f(7, 0, -120);
	glTexCoord2f(0, 5);
	glVertex3f(-7, 0, -120);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
//=======================================================================
// Display Function
//=======================================================================
void drawtrees(int x) {
	for (int i = 0; i < 20; i++) {
		glPushMatrix();
		glTranslatef(6, -0.5, -x);
		glScalef(0.2, 0.2, 0.2);
		model_tree.Draw();
		glPopMatrix();
		x += 5;

	}
}
void drawtrees2(int x) {
	for (int i = 0; i < 20; i++) {
		glTranslatef(-2, 1.2, -x);
		glScaled(0.002, 0.002, 0.002);
		glRotated(-90, 1.0, 0.0, 0.0);
		model_tree5.Draw();
		glPopMatrix();
		glPushMatrix();
		x += 5;
	}
}
void myDisplay_0(void)
{
	
	
	if (status == 0) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
		GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

		// Draw Ground
		//RenderGround();

			// Draw Tree Model
		glDisable(GL_LIGHTING);
		glLoadIdentity();	//Clear Model_View Matrix

		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters


		//glRotated(45, 0, 1, 0);
		// Draw house Model
		glPushMatrix();
		drawstreet();
		glPopMatrix();
		glPushMatrix();
		drawstreetside(1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		char* p3s[20];
		sprintf((char*)p3s, "How to play?", "");
		print3d(1.8, 8, -20, (char*)p3s);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		char* p4s[20];
		sprintf((char*)p4s, "1- use J & L to avoid obstacles", "");
		print3d(-5, 6, -20, (char*)p4s);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1, 0, 0);
		char* p5s[20];
		sprintf((char*)p5s, "2- collect the clock to gain time and score", "");
		print3d(-5, 4.5, -20, (char*)p5s);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1, 0, 0);
		char* p6s[20];
		sprintf((char*)p6s, "To play as 3rd person click click P, or 1st person click O", "");
		print3d(-5, 3, -20, (char*)p6s);
		glPopMatrix();
		//glutReshapeFunc(myReshape);
		_sleep(1);
		glutPostRedisplay();
		glutSwapBuffers();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
	}
	if (status == 1) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
		GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

		// Draw Ground
		//RenderGround();

			// Draw Tree Model
		glDisable(GL_LIGHTING);
		glLoadIdentity();	//Clear Model_View Matrix
		if (forward > -210) {
			
			
				Eye.z -= 0.2;
				timer -= 0.025;
				score += 10;
			
		}
		
		if (forward < -205 && forward > -210) {
			if (cheer == 0) {
				PlaySound(TEXT("cheer.wav"), NULL, SND_FILENAME | SND_ASYNC);
				_sleep(1);
				cheer = 1;
				status = 2;
				life = 3;
				score = 0;
				timer = 80;
				if (cameraview == 1) {
					Eye.x = 2.5;
					Eye.y = 0.6;
					Eye.z = 3;
				}
				else {
					Eye.x = 2.4;
					Eye.y = 0;
					Eye.z = -0.9;
				}

			}
		}
		
		// Eye.z -= 0.3;
		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

		glPushMatrix();
		
		if (life == 0 || timer <= 0.0) {
			PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
			_sleep(1000000);
		}
		//glRotated(45, 0, 1, 0);
		// Draw house Model
		glPushMatrix();
		drawstreet();
		glPopMatrix();
		glPushMatrix();
		drawstreetside(1);
		glPopMatrix();

		glPushMatrix();
		if (collidework == 0) {
			collideeffect += 1;
			if (collideeffect % 3 == 0) {
				drawplayer();
				_sleep(1);
				forward -= 0.2;
				forward -= 0.2;

			}
			if (ftimes >= 20) {
				collidework = 1;
			}
			ftimes += 1;
		}
		else {
			drawplayer();
			ftimes = 0;
		}
		glPopMatrix();



		glPushMatrix();
		drawsink(10);
		glPopMatrix();

		glPushMatrix();
		drawwater(55, 1);
		glPopMatrix();

		glPushMatrix();
		drawwater(120, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(8, -4, -50);
		bin.Draw();
		glPopMatrix();
		
	

		glPushMatrix();
		glTranslated(7, -4, -150);
		bin.Draw();
		glPopMatrix();

		glPushMatrix();
		drawcars();
		glPopMatrix();

		glPushMatrix();
		glTranslated(3, 0.7, -120);
		glScaled(0.00007, 0.00007, 0.00007);
		time.Draw();
		glPopMatrix();



		glPushMatrix();
		glTranslated(0, 0, -120);
		glRotated(90, 0, 0, 1);
		glScaled(0.1, 0.2, 1);
		street.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(70, 0, -120);
		glRotated(90, 0, 0, 1);
		glScaled(0.1, 0.2, 1);
		street.Draw();
		glPopMatrix();




		glPushMatrix();
		drawhouses(8);
		glPopMatrix();


		glPushMatrix();
		drawlego(2, 90, -1);
		glPopMatrix();



		glPushMatrix();
		glTranslated(1, 0, -220);
		glRotated(90, 1, 0, 0);
		reachhome.Draw();
		glPopMatrix();
		glPushMatrix();
		glTranslated(2.5, 0.5, -215);

		glScaled(0.6, 0.6, 0.6);
		stickman.Draw();
		glPopMatrix();
		glPushMatrix();
		drawstreetlights(0);
		glPopMatrix();




		glPopMatrix();
		//sky box
		glPushMatrix();

		GLUquadricObj* qobj;
		qobj = gluNewQuadric();
		glTranslated(50, 0, 0);
		glRotated(90, 1, 0, 1);
		glScaled(3, 3, 3);
		glBindTexture(GL_TEXTURE_2D, tex);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 100, 100, 100);
		gluDeleteQuadric(qobj);


		glPopMatrix();
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %f", score);
		print(100, HEIGHT - 20, (char*)p0s);

		char* p1s[20];
		sprintf((char*)p1s, "Life: %d", life);
		print(350, HEIGHT - 20, (char*)p1s);

		char* p2s[20];
		sprintf((char*)p2s, "Timer: %f", timer);
		print(600, HEIGHT - 20, (char*)p2s);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);

		//glutReshapeFunc(myReshape);
		_sleep(1);
		glutPostRedisplay();
		glutSwapBuffers();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
	}
	if (status == 2) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);

		GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
		GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

		// Draw Ground
		glPushMatrix();
		glTranslated(2.5, -1, -3);
		RenderGround();
		glPopMatrix();

			// Draw Tree Model
		glDisable(GL_LIGHTING);
		glLoadIdentity();
	

		if (forward2 > -112 && forward2 < -109) {
			if (cheer2 == 0) {
				PlaySound(TEXT("cheer.wav"), NULL, SND_FILENAME | SND_ASYNC);
				_sleep(1);
				cheer2 = 1;
			}
		}
		//Clear Model_View Matrix
		if (forward2 > -110) {


			Eye.z -= 0.2;
			timer -= 0.025;
			score += 10;

		}
	
		
		// Eye.z -= 0.3;
		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

		glPushMatrix();
		
		
		if (life == 0 || timer <= 0.0) {
			PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
			_sleep(1000000);
		}
		//glRotated(45, 0, 1, 0);
		// Draw house Model
		glPushMatrix();
		if (collidework2 == 0) {
			collideeffect2 += 1;
			if (collideeffect2 % 3 == 0) {
				drawplayer2();
				_sleep(1);
				forward2 -= 0.2;
				forward2 -= 0.2;

			}
			if (ftimes2 >= 20) {
				collidework2 = 1;
			}
			ftimes2 += 1;
		}
		else {
			drawplayer2();
			ftimes2 = 0;
		}
		glPopMatrix();
		glPushMatrix();
		drawtrees(5);
	    glPopMatrix();

		glPushMatrix();
		drawtrees2(10);
		glPopMatrix();
	
		glPushMatrix();
		glTranslated(-2, -1, -8);
		glScaled(0.5, 0.5, 0.5);
		glRotated(90, 0, 1, 0);
		glRotatef(90.f, 1, 0, 0);
		model_house.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-2, -1, -30);
		glScaled(0.5, 0.5, 0.5);
		glRotated(90, 0, 1, 0);
		glRotatef(90.f, 1, 0, 0);
		model_house.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(2.5, 1, -120);
		glRotated(90, 0, 1, 0);
		glScaled(0.6, 0.6, 0.6);
		model_house3.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(3.0, -1, -10.0);
		glScaled(0.0005, 0.0005, 0.001);
		//glRotated(-90, 0.0, 1.0, 0.0);
		model_barrier.Draw();
		glPopMatrix();


		glPushMatrix();
		glTranslated(2.5, -1, -20);
		glScaled(0.001, 0.001, 0.001);
		model_cone.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(1.5, -1, -30);
		glScaled(0.001, 0.001, 0.001);
		model_cone.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(4, -1, -40);
		glScaled(0.001, 0.001, 0.001);
		model_cone.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslated(1, -1, -50);
		glScaled(0.001, 0.001, 0.001);
		model_cone.Draw();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(2.5, -0.5, -60);
		glScalef(0.2, 0.2, 0.2);
		model_tree.Draw();
		glPopMatrix();

		

		
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "score: %f", score);
		print(100, HEIGHT - 20, (char*)p0s);

		char* p1s[20];
		sprintf((char*)p1s, "life: %d", life);
		print(350, HEIGHT - 20, (char*)p1s);

		char* p2s[20];
		sprintf((char*)p2s, "Timer: %f", timer);
		print(600, HEIGHT - 20, (char*)p2s);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);

		//glutReshapeFunc(myReshape);
		_sleep(1);
		glutPostRedisplay();
		glutSwapBuffers();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
	
	}
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	y = HEIGHT - y;
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'j':
		if (status == 1) {
			if (leftright > -1.8) {
				leftright -= d;
				if (cameraview == 0) {
					Eye.x -= d;
				}
			}
		}
		if (status == 2) {
			if (leftright2 > -2.2) {
				leftright2 -= d;
				if (cameraview == 0) {
					Eye.x -= d;
				}
			}
		}
		break;
	case 'l':
		if (status == 1) {
			if (leftright < 2.3) {
				leftright += d;
				if (cameraview == 0) {
					Eye.x += d;
				}
			}
		}
		if (status == 2) {
			if (leftright2 < 2.5) {
				leftright2 += d;
				if (cameraview == 0) {
					Eye.x += d;
				}
			}
		}
		break;
	case 'i':
		if (status == 2) {
			Eye.z -= 0.2;
			forward2 -= 0.2;
		}
	
		break;
	case 'k':
		if (status == 2) {
			Eye.z += 0.2;
			forward2 += 0.2;
		}
		break;
	case 'p':
		cameraview = 1;
		status = 1;

		break;
	case 'o':
		cameraview = 0;
		status = 1;
		Eye.x -= 0.15;
		Eye.z -= 4;
		Eye.y -= 0.3;
		break;
	
	
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		//Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		//Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files


	motor.Load("Models/motor/motor.3ds");
	pizza.Load("Models/player/pizza.3ds");
	street.Load("Models/wall/floor.3ds");
	bin.Load("Models/bin/bin.3ds");
	water.Load("Models/water/water.3ds");
	car1.Load("Models/cars/car1.3ds");
	car2.Load("Models/cars/car2.3ds");
	time.Load("Models/time/time.3ds");
	house1.Load("Models/houses/house1/house1.3ds");
	house2.Load("Models/houses/house2/house2.3ds");
	stickman.Load("Models/stickman/stickman.3ds");
	streetlight.Load("Models/streetlight/light.3ds");
	sink.Load("Models/sink/sink.3ds");
	reachhome.Load("Models/house/house.3ds");

	player.Load("Models/player/player.3ds");
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_cone.Load("Models/cone/cone.3ds");
	model_house3.Load("Models/house3/house3/house3.3ds");
	model_tree2.Load("Models/tree2/tree2/tree2.3ds");
	model_tree5.Load("Models/tree5/tree5.3ds");
	model_barrier.Load("Models/barrier/barrier.3ds");
	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(50, 100);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay_0);


	glutKeyboardFunc(myKeyboard);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}