#include <iostream>
#include <gl/glut.h>

using namespace std;

void display();
void reshape(int, int);

void init()
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("JUYAD_M1A2_T85");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	init();
	glutMainLoop();

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	//botton right
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, -12.0f);
	glVertex2f(8.0f, -10.0f);
	glVertex2f(6.0f, -7.0f);
	glVertex2f(7.0f, -6.0f);
	glVertex2f(6.0f, -4.0f);
	glVertex2f(9.0f, -6.0f);
	glVertex2f(8.0f, -7.0f);
	glVertex2f(10.0f, -9.0f);
	glVertex2f(10.0f, -7.0f);

	//upper right
	glVertex2f(12.0f, 0.0f);
	glVertex2f(10.0f, 7.0f);
	glVertex2f(10.0f, 9.0f);
	glVertex2f(8.0f, 7.0f);
	glVertex2f(9.0f, 6.0f);
	glVertex2f(6.0f, 4.0f);
	glVertex2f(7.0f, 6.0f);
	glVertex2f(6.0f, 7.0f);
	glVertex2f(8.0f, 10.0f);

	//upper left
	glVertex2f(0.0f, 12.0f);
	glVertex2f(-8.0f, 10.0f);
	glVertex2f(-6.0f, 7.0f);
	glVertex2f(-7.0f, 6.0f);
	glVertex2f(-6.0f, 4.0f);
	glVertex2f(-9.0f, 6.0f);
	glVertex2f(-8.0f, 7.0f);
	glVertex2f(-10.0f, 9.0f);
	glVertex2f(-10.0f, 7.0f);

	//bottom left
	glVertex2f(-12.0f, 0.0f);
	glVertex2f(-10.0f, -7.0f);
	glVertex2f(-10.0f, -9.0f);
	glVertex2f(-8.0f, -7.0f);
	glVertex2f(-9.0f, -6.0f);
	glVertex2f(-6.0f, -4.0f);
	glVertex2f(-7.0f, -6.0f);
	glVertex2f(-6.0f, -7.0f);
	glVertex2f(-8.0f, -10.0f);
	glEnd();
	glLineWidth(3);

	//color
	//bottom right 
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex2f(0.0f, -12.0f);
	glVertex2f(8.0f, -10.0f);
	glVertex2f(6.0f, -7.0f);
	glVertex2f(7.0f, -6.0f);
	glVertex2f(6.0f, -4.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 12.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(12.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(6.0f, -4.0f);
	glVertex2f(9.0f, -6.0f);
	glVertex2f(8.0f, -7.0f);
	glVertex2f(10.0f, -9.0f);
	glVertex2f(10.0f, -7.0f);
	glEnd();

	//upper right
	glBegin(GL_POLYGON);
	glVertex2f(12.0f, 0.0f);
	glVertex2f(10.0f, 7.0f);
	glVertex2f(10.0f, 9.0f);
	glVertex2f(8.0f, 7.0f);
	glVertex2f(9.0f, 6.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 12.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(6.0f, 4.0f);
	glVertex2f(7.0f, 6.0f);
	glVertex2f(6.0f, 7.0f);
	glVertex2f(8.0f, 10.0f);
	glEnd();

	//upper left
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 12.0f);
	glVertex2f(-8.0f, 10.0f);
	glVertex2f(-6.0f, 7.0f);
	glVertex2f(-7.0f, 6.0f);
	glVertex2f(-6.0f, 4.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-12.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-9.0f, 6.0f);
	glVertex2f(-8.0f, 7.0f);
	glVertex2f(-10.0f, 9.0f);
	glVertex2f(-10.0f, 7.0f);
	glEnd();

	//bottom left
	glBegin(GL_POLYGON);
	glVertex2f(-12.0f, 0.0f);
	glVertex2f(-10.0f, -7.0f);
	glVertex2f(-10.0f, -9.0f);
	glVertex2f(-8.0f, -7.0f);
	glVertex2f(-9.0f, -6.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, -12.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-6.0f, -4.0f);
	glVertex2f(-7.0f, -6.0f);
	glVertex2f(-6.0f, -7.0f);
	glVertex2f(-8.0f, -10.0f);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	gluOrtho2D(-12, 12, -12, 12);
	glMatrixMode(GL_MODELVIEW);
}
