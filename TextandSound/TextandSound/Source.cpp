#include <iostream>
#include <gl/glut.h>
#include <irr/irrKlang.h>
#include "imageloader.h"

using namespace irrklang;

ISoundEngine *engine = createIrrKlangDevice();

using namespace std;

void display();
void reshape(int, int);
void update(int);
void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	const char *string);

GLuint loadTexture(Image* image);

float _angle = -70.0f;
long count = 0;
//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 60.0 };


//set world light
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light[] = { 0.5, 0.5, 0.5 };
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat static_ambient[] = { 0.8, 0.8, 0.8, 1.0 };

GLuint _textureBall; //The id of the texture
GLUquadric* ball; //pointer quadric shape for the sphere

// default font




//Initializes 3D rendering
void initRendering() {

	engine->play2D("ThankYou.wav", true);

	glClearColor(0.0, 0.0, 0.0, 0.0); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	Image* image_sky = loadBMP("skybox.bmp");
	_textureBall = loadTexture(image_sky);
	delete image_sky;

	ball = gluNewQuadric(); //declared as quadric objects
}




int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	//Create the window
	glutCreateWindow("Juyad-Text&Sound");
	initRendering();

	//Set handler functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}

//Draws the 3D scene
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//---------SKYBOX-----------------------//
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBall);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, static_ambient); //add ambient lighting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1, 1, 1); // needed to make the skybox visible
	gluQuadricTexture(ball, 1);
	glRotatef(180, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	gluSphere(ball, 1000, 128, 128);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	//---------SKYBOX-----------------------//

	//setting world lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //add ambient lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light); //add diffuse specular lighting
	glLightfv(GL_LIGHT0, GL_SPECULAR, light); //add specular lighting
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess


	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display

	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	renderBitmapString(-4.0f, 3.5f, 5.0f, GLUT_BITMAP_HELVETICA_18, "King Ian Jason R. Juyad - EMC122 - T85");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glTranslatef(0.0f, -0.5f, 0.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	renderBitmapString(-4.0f, 3.5f, 5.0f, GLUT_BITMAP_HELVETICA_12, "I learned alot on this subject, how to code computer graphics, in a");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glTranslatef(0.0f, -0.5f, 0.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	renderBitmapString(-4.0f, 3.5f, 5.0f, GLUT_BITMAP_HELVETICA_12, "fun, enjoyable and engaging way. How to code in a 3d way with");
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glTranslatef(0.0f, -0.5f, 0.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	renderBitmapString(-4.0f, 3.5f, 5.0f, GLUT_BITMAP_HELVETICA_12, "with a scenery using skybox, lightings, background musics,");

	glDisable(GL_LIGHTING);
	glTranslatef(0.0f, -0.5f, 0.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	renderBitmapString(-4.0f, 3.5f, 5.0f, GLUT_BITMAP_HELVETICA_12, "and camera movements.");
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHTING);


	glutSwapBuffers();
}


//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
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

//Makes the image into a texture, and returns the id of the texture
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
