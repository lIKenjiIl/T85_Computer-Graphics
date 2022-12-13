#include <iostream>
#include <gl/glut.h>
#include "imageloader.h"
#include <irrKlang.h> 

using namespace irrklang;

ISoundEngine* engine = createIrrKlangDevice();

using namespace std;

void display();
void reshape(int, int);
void update(int);
GLuint loadTexture(Image* Image);
void processNormalKeys(unsigned char, int, int);
void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	const char *string);

GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 60.0 };

//light positions
GLfloat xlight1 = -5.0f, ylight1 = 20.0f, zlight1 = -50.0f;

GLfloat xlight2 = -5.0f, ylight2 = -20.0f, zlight2 = -40.0f;

GLfloat xlight3 = 0.0f, ylight3 = 5.0f, zlight3 = -20.0f;

//set Light #1
GLfloat light_position1[] = { xlight1, ylight1, zlight1, 1.0 };
GLfloat light1[] = { 1.0, 0.5, 0.0 };

//set Light #2
GLfloat light_position2[] = { xlight2, ylight2, zlight2, 1.0 };
GLfloat light2[] = { 0.0, 0.5, 1.0 };

//set Light #3
GLfloat light_position3[] = { xlight3, ylight3, zlight3, 1.0 };
GLfloat light3[] = { 1.0, .8, 0.0 };

//Emissions
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_emissionRed[] = { 1.0, 0.5, 0.0, 1.0 };
GLfloat mat_emissionSkyB[] = { 0.0, 0.5, 1.0, 1.0 };
GLfloat mat_emissionYell[] = { 1.0, 0.8, 0.0, 1.0 };

float angle = 0.0; // angle of rotation for the camera direction
float lx = 0.0f, lz = -1.0f; // actual vector representing the camera's direction
float cameraX = 0.0f, cameraZ = 5.0f; // XZ position of the camera
float _angle = 0.0f; // objects angle
long count = 0;

GLuint Pyramid;  //The id of the texture
GLuint Sand;
GLuint _Sun;
GLuint _Moon;
GLuint _Space;

GLUquadric* Sun; //pointer quadric shape for the planets
GLUquadric* Moon;
GLUquadric* Space;


//Initializes 3D rendering
void initRendering() {
	

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	Image* image = loadBMP("pyramid.bmp");
	Pyramid = loadTexture(image);
	delete image;

	Image* image1 = loadBMP("sand.bmp");
	Sand = loadTexture(image1);
	delete image1;

	Image* image2 = loadBMP("sun.bmp");
	_Sun = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("moon.bmp");
	_Moon = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("space.bmp");
	_Space = loadTexture(image4);
	delete image4;

	Sun = gluNewQuadric(); //declared as quadric objects
	Moon = gluNewQuadric();
	Space = gluNewQuadric();
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	//Create the window
	glutCreateWindow("Juyad-EMC122-PyramidProject");
	initRendering();

	//Set handler functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);//controls
	glutTimerFunc(1000/60, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//camera controls
	gluLookAt(cameraX, 0.1f, cameraZ,
		cameraX + lx, 0.1f, cameraZ + lz,
		0.0f, 0.1f, 0.0f);

	glTranslatef(0.0f, -1.0f, -5.0f); //move object in -z axis to seen in display

	// Pyramid 1
	glPushMatrix();

	glTranslatef(0.0f, -1.0f, -1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Pyramid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_TRIANGLES); // Begin drawing the pyramid with 4 triangles

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glColor3f(0.2f, 0.2f, 0.2f);

    // Front
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
    glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.57f, -0.57f, 0.57);
    glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.57f, -0.57, 0.57);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
    glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.57f, -0.57, 0.57);
    glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.57f, -0.57, -0.57);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
    glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.57f, -0.57f, -0.57);
    glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(-0.57f, -0.57f, -0.57f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
    glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.57, -0.57, -0.57);
    glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(-0.57f, -0.57, 0.57);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();   // Done drawing the pyramid
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Pyramid 2
	glPushMatrix();

	glTranslatef(2.0f, -1.0f, -6.0f);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Pyramid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_TRIANGLES); // Begin drawing the pyramid with 4 triangles

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glColor3f(0.2f, 0.2f, 0.2f);

	// Front
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.57f, -0.57f, 0.57);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.57f, -0.57, 0.57);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.57f, -0.57, 0.57);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.57f, -0.57, -0.57);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.57f, -0.57f, -0.57);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(-0.57f, -0.57f, -0.57f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.57, -0.57, -0.57);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(-0.57f, -0.57, 0.57);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();   // Done drawing the pyramid
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Pyramid 3
	glPushMatrix();

	glTranslatef(-2.0f, -1.0f, -6.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Pyramid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_TRIANGLES); // Begin drawing the pyramid with 4 triangles

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glColor3f(0.2f, 0.2f, 0.2f);

	// Front
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.57f, -0.57f, 0.57);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.57f, -0.57, 0.57);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.57f, -0.57, 0.57);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.57f, -0.57, -0.57);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.57f, -0.57f, -0.57);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(-0.57f, -0.57f, -0.57f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glTexCoord2f(0.5f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f); //normalize
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-0.57, -0.57, -0.57);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(-0.57f, -0.57, 0.57);
	glVertex3f(-1.0f, -1.0f, 1.0f);


	glEnd();   // Done drawing the pyramid
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Base Sand
	glPushMatrix();

	glTranslatef(0.0f, -1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Sand);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glColor3f(0.5f, 0.5f, 0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-1000.0f, -5.0f, -1000.0f);
	glTexCoord2f(1000, 0);
	glVertex3f(-1000.0f, -5.0f, 1000.0f);
	glTexCoord2f(1000.0f, 1000.0f);
	glVertex3f(1000.0f, -5.0f, 1000.0f);
	glTexCoord2f(0.0f, 1000.f);
	glVertex3f(1000.0f, -5.0f, -1000.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	////--------SUN---------------------------------------------------////
	glBindTexture(GL_TEXTURE_2D, _Sun);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gluQuadricTexture(Sun, 1);

	glPushMatrix();
	glRotatef(_angle, 0.0f, 1.0f, 1.0f);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);//set light position
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1); //add diffuse specular lighting
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionRed);
	glTranslatef(xlight1, ylight1, zlight1); //location
	glTranslatef(5.0f, 40.0f, -140.0f);
	gluSphere(Sun, 3.0, 24, 24);
	glPopMatrix();

	////--------MOON---------------------------------------------------////
	glBindTexture(GL_TEXTURE_2D, _Moon);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	gluQuadricTexture(Moon, 1);

	glPushMatrix();
	glRotatef(_angle, 1.0f, -1.0f, 1.0f);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionSkyB);
	glTranslatef(xlight2, ylight2, zlight2); //location
	glTranslatef(5.0f, -10.0f, -120.0f);
	gluSphere(Moon, 2.0, 24, 24);
	glPopMatrix();
	////--------MOON---------------------------------------------------////

	//---------SKYBOX-----------------------//
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _Space);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.2f, 0.02f, 0.02f); // needed to make the skybox visible
	glRotatef(90, 1.0f, 1.0f, 0.0f);
	gluQuadricTexture(Space, 1);
	gluSphere(Space, 250, 128, 128);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//---------SKYBOX-----------------------//

	//SpaceShip
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);//add color material to object //rotation animation
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);//set light position
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3); //add diffuse specular lighting
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionYell);
	glTranslatef(xlight3, ylight3, zlight3); //location
	glutSolidSphere(0.5, 100, 100);
	glPopMatrix();

	//SpaceShip
	glPushMatrix();
	glColor3f(1.0f, 0.5f, 0.0f);//add color material to object //rotation animation
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(0.0f, 5.0f, -20.0f); //location
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.5, 3, 3, 10);
	glPopMatrix();

	//Text
	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	renderBitmapString(-8.0f, 8.0f, 5.0f, GLUT_BITMAP_HELVETICA_18, "3 Pyramid, with a sun and moon rotating");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	renderBitmapString(-8.0f, 7.5f, 5.0f, GLUT_BITMAP_HELVETICA_12, "Press W to move forwad");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	renderBitmapString(-8.0f, 7.0f, 5.0f, GLUT_BITMAP_HELVETICA_12, "Press S to move Backward");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	renderBitmapString(-8.0f, 6.5f, 5.0f, GLUT_BITMAP_HELVETICA_12, "Press A&D to look left and right");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	renderBitmapString(-8.0f, 6.0f, 5.0f, GLUT_BITMAP_HELVETICA_12, "Press E to play BGM SpaceSounds");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	renderBitmapString(-8.0f, 5.5f, 5.0f, GLUT_BITMAP_HELVETICA_12, "Press R to play BGM ThankYou");
	glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
		//as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);
}

//rotation animation logic
void update(int value) {
	_angle += 1.0f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}

//keyboard controls
void processNormalKeys(unsigned char key, int x, int y) {
	float fraction = 1.5f;

	switch (key) {
	case 'w':
		cameraX += lx * fraction;
		cameraZ += lz * fraction;
		break;
	case 's':
		cameraX -= lx * fraction;
		cameraZ -= lz * fraction;
		break;
	case 'a':
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'd':
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	case 'e':
		engine->play2D("SpaceSounds.wav", false);
		break;
	case 'r':
		engine->play2D("ThankYou.wav", false);
		break;
	}
}
void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	const char *string) {
	const char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

