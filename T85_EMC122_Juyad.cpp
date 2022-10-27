#include <iostream>
#include <gl\glut.h>

using namespace std;

void display();
void reshape(int, int);
void update(int);

float _angle = -70.0f;

//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 60.0 };

GLfloat mat_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess1[] = { 60.0 };

GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess2[] = { 60.0 };


//set world light
GLfloat light_position[] = { 0.0, 5.0, 0.0 };
GLfloat light[] = { 1.0, 1.0, 1.0 };
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

GLfloat light_position1[] = {-5.0, 0.0, 0.0 };
GLfloat light1[] = { 1.0, 0.0, 1.0};
GLfloat lmodel_ambient1[] = { 0.2, 0.2, 0.2, 1.0 };

GLfloat light_position2[] = { 5.0, 0.0, 0.0,};
GLfloat light2[] = { 1.0, 1.0, 0.0 };
GLfloat lmodel_ambient2[] = { 0.2, 0.2, 0.2, 1.0 };

//Initializes 3D rendering
void initRendering() {

	glClearColor(1.0, 0.0, 0.0, 1.0); //set background to white

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);//Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}




int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	//Create the window
	glutCreateWindow("Trophy-Juyad-M3A1");
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


	//setting world lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient2);//add ambient lighting

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light); //add diffuse specular lighting
	glLightfv(GL_LIGHT0, GL_SPECULAR, light); //add specular lighting

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);//set light position
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1); //add diffuse specular lighting
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1); //add specular lighting

	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);//set light position
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2); //add diffuse specular lighting
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2); //add specular lighting
	

	//setting object materials
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);// set shininess

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2); //set object specular mateial
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);// set shininess


	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display
	
	glRotatef(_angle, 0, 1, 0);
	
	//ball
	glPushMatrix();
	glColor3f(1.0f, 0.5f, 0.0f);//add color material to object 
	glTranslatef(0.0f, 0.5f, 0.0f); //location
	glutSolidSphere(0.9, 100, 100);
	glPopMatrix(); 

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);//add color material to object 
	glTranslatef(0.0f, 0.5f, 0.0f); //location
	glutWireSphere(1.1, 12, 4);
	glPopMatrix();


	//cone
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);//add color material to object 
	glTranslatef(0.0f, -1.0f, 0.0f); //location
	glRotatef(90, 1, 0, 0);
	glutSolidCone(1, 4, 10, 100);
	glPopMatrix();

	//body of trophy
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, -2.5f, 0.0f);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -3.5f, 0.0f);
	glutSolidCube(2.5);
	glPopMatrix();

	//Circle for the ball
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidTorus(0.5, 1, 12, 24);
	glPopMatrix();

	glutSwapBuffers();
}


//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}
