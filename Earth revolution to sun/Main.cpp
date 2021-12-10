#include <glut.h>
#include <math.h>

GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 2;

GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
GLfloat qaSpecularLight[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat emitLight[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat Noemit[] = { 0.0, 0.0, 1.0, 1.0 };

GLfloat qaLightPosition[] = { 0, 0, 0, 1 };

void display(void);
void reshape(int x, int y);

void idleFunc(void){
	if (zRotated > 360.0) {
		zRotated -= 360.0 * floor(zRotated / 360.0);
	}
	if (yRotated > 360.0) {
		yRotated -= 360.0 * floor(yRotated / 360.0);
	}
	zRotated += 0.1;
	yRotated += 0.1;

	display();
}

void initLighting(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaSpecularLight);
}

void display(void){
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2);
	glutSolidSphere(radius, 25, 25);

	glPopMatrix();
	glPushMatrix();

	glRotatef(yRotated, 0.0, 1.0, 0.0);
	glTranslatef(5.0, 0.0, 0.0);

	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);
	glutSolidSphere(radius / 6, 25, 25);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void reshape(int x, int y){
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);

	gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Simulasi revolusi bumi ke matahari");
	initLighting();

	xRotated = yRotated = zRotated = 0.0;

	glutIdleFunc(idleFunc);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}




