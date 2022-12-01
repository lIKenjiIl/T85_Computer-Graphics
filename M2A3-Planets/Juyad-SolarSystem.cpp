
#include <iostream>
#include <gl\glut.h>


#include "imageloader.h"

void update(int);
GLuint loadTexture(Image* image);
void reshape(int, int);
void display();

GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat directedLightPos[] = { 0.0f, 0.0f, 1.0f, 0.0f };

//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 60.0 };

//set world light
GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };

//light positions
GLfloat xlight0 = -5.0f, ylight0 = 0.0f, zlight0 = -10.0f;


//set Light #0
GLfloat light_position[] = { xlight0, ylight0, zlight0, 1.0 };
GLfloat light[] = { 1.0, 1.0, 0.0 };

//Emissions
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_emissionRed[] = { 1.0, 0.5, 0.0, 1.0 };

float angle = 0; //rotation angle

GLuint _textureSun; //The id of the texture
GLuint _textureMercury; //The id of the texture
GLuint _textureVenus;
GLuint _textureEarth;
GLuint _textureMars;


GLUquadric* Sun; //pointer quadric shape for the planets
GLUquadric* Mercury; 
GLUquadric* Venus;
GLUquadric* Earth;
GLUquadric* Mars;


void initRendering() {

	glClearColor(0.0, 0.0, 0.0, 1.0); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

	//loading texture for the ball
	Image* Img = loadBMP("Sun.bmp");
	_textureSun = loadTexture(Img);
	delete Img;
	Image* Img2 = loadBMP("Mercury.bmp");
	_textureMercury = loadTexture(Img2);
	delete Img2;
	Image* Img3 = loadBMP("Venus.bmp");
	_textureVenus = loadTexture(Img3);
	delete Img3;
	Image* Img4 = loadBMP("Earth.bmp");
	_textureEarth = loadTexture(Img4);
	delete Img4;
	Image* Img5 = loadBMP("Mars.bmp");
	_textureMars = loadTexture(Img5);
	delete Img5;

	Sun = gluNewQuadric(); //declared as quadric objects
	Mercury = gluNewQuadric(); //declared as quadric objects
	Venus = gluNewQuadric();
	Earth = gluNewQuadric();
	Mars = gluNewQuadric();

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);

	glutCreateWindow("Juyad-M2A3-SolarSystem");
	initRendering();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / 60, update, 0); //add timer
	glutMainLoop();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //add ambient lighting

	glPushMatrix();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);

	
	////--------SUN---------------------------------------------------////
	glBindTexture(GL_TEXTURE_2D, _textureSun);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluQuadricTexture(Sun, 1);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light); //add diffuse specular lighting
	glLightfv(GL_LIGHT0, GL_SPECULAR, light); //add specular lighting
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissionRed);
	glTranslatef(xlight0, ylight0, zlight0); //location
	glTranslatef(-3.0f, 0.0f, -5.0f);
	glRotatef(90, 0.0f, 1.0f, 1.0f);
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	gluSphere(Sun, 3.0, 24, 24);
	glPopMatrix();
	////--------SUN---------------------------------------------------////


	////--------MERCURY---------------------------------------------------////
	glBindTexture(GL_TEXTURE_2D, _textureMercury);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluQuadricTexture(Mercury, 1);

	glPushMatrix();
	glRotatef(90, 1.0f, 1.0f, 1.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(0.0f, 0.0f, -10.0f);
	gluSphere(Mercury, 0.2, 24, 24);
	glPopMatrix();
	////--------MERCURY---------------------------------------------------////

	////--------VENUS---------------------------------------------------////
	glBindTexture(GL_TEXTURE_2D, _textureVenus);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluQuadricTexture(Venus, 1);

	glPushMatrix();
	glRotatef(270, 1.0f, 1.0f, 0.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f); //animated rotation
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(2.0f, 11.0f, -15.0f);
	gluSphere(Venus, 0.4, 24, 24);
	glPopMatrix();
	////--------VENUS---------------------------------------------------////


	////--------EARTH---------------------------------------------------////
	glBindTexture(GL_TEXTURE_2D, _textureEarth);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluQuadricTexture(Earth, 1);

	glPushMatrix();
	glRotatef(180, 1.0f, 1.0f, 1.0f);
	glRotatef(angle, 0.0f, 1.0f, 1.0f); //animated rotation
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(4.0f, 14.0f, -18.0f);
	gluSphere(Earth, 0.7, 24, 24);
	glPopMatrix();
	////--------EARTH---------------------------------------------------////

	////--------MARS---------------------------------------------------////
	glBindTexture(GL_TEXTURE_2D, _textureMars);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluQuadricTexture(Mars, 1);

	glPushMatrix();
	glRotatef(360, 1.0f, 1.0f, 1.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f); //animated rotation
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(6.0f, 0.0f, -20.0f);
	gluSphere(Mars, 0.3, 24, 24);
	glPopMatrix();
	////--------MARS---------------------------------------------------////


	glDisable(GL_TEXTURE_2D);



	glutSwapBuffers();
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

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 200.0);
}


void update(int)
{


	//looping animation logic
	angle += 1.5;
	if (angle > 360.0f)
		angle = angle - 360.0f;

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);

}





