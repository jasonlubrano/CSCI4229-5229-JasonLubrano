/*  Jason Lubrano
 *  Homework 2: Lorenz Atractor
 *  transfered code form ex6, ex7, ex8, lorenz.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* global vars taken from various exs */
int th = 0; // Azimuth of view angle
int ph = 0; // Elevation of view angle
double zh = 0;      //  Rotation of teapot
double len = 8; // length of axis
double dim = 20; // dimension of ortho box
int axes = 1; // Display axes
int mode = 7; // set the mode to 7

/* colors */
int red = 0;
int green = 0;
int blue = 1;

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

/* Cosine and Sine in degrees (ex8) */
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string (ex8)
void Print(const char* format , ...){
	char    buf[LEN];
	char*   ch=buf;
	va_list args;
	//  Turn the parameters into a character string
	va_start(args,format);
	vsnprintf(buf,LEN,format,args);
	va_end(args);
	//  Display the characters one at a time at the current raster position
	while (*ch)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*  Going to try and make the airplane fly
 *  Draw solid airplane
 *    at (x,y,z)
 *    nose towards (dx,dy,dz)
 *    up towards (ux,uy,uz)
 */
static void SolidPlane(double x, double y, double z,
						double dx, double dy, double dz,
						double ux, double uy, double uz)
{
	// Dimensions used to size airplane
	const double wid=0.05;
	const double nose=+0.50;
	const double cone= 0.20;
	const double wing= 0.00;
	const double strk=-0.20;
	const double tail=-0.50;
	//  Unit vector in direction of flght
	double D0 = sqrt(dx*dx+dy*dy+dz*dz);
	double X0 = dx/D0;
	double Y0 = dy/D0;
	double Z0 = dz/D0;
	//  Unit vector in "up" direction
	double D1 = sqrt(ux*ux+uy*uy+uz*uz);
	double X1 = ux/D1;
	double Y1 = uy/D1;
	double Z1 = uz/D1;
	//  Cross product gives the third vector
	double X2 = Y0*Z1-Y1*Z0;
	double Y2 = Z0*X1-Z1*X0;
	double Z2 = X0*Y1-X1*Y0;
	//  Rotation matrix
	double mat[16];
	mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
	mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
	mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
	mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

	//  Save current transforms
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x,y,z);
	glMultMatrixd(mat);
	//  Nose (4 sided)
	glColor3f(0,0,1);
	glBegin(GL_TRIANGLES);
	glVertex3d(nose, 0.0, 0.0);
	glVertex3d(cone, wid, wid);
	glVertex3d(cone,-wid, wid);

	glVertex3d(nose, 0.0, 0.0);
	glVertex3d(cone, wid,-wid);
	glVertex3d(cone,-wid,-wid);

	glVertex3d(nose, 0.0, 0.0);
	glVertex3d(cone, wid, wid);
	glVertex3d(cone, wid,-wid);

	glVertex3d(nose, 0.0, 0.0);
	glVertex3d(cone,-wid, wid);
	glVertex3d(cone,-wid,-wid);
	glEnd();
	//  Fuselage (square tube)
	glBegin(GL_QUADS);
	glVertex3d(cone, wid, wid);
	glVertex3d(cone,-wid, wid);
	glVertex3d(tail,-wid, wid);
	glVertex3d(tail, wid, wid);

	glVertex3d(cone, wid,-wid);
	glVertex3d(cone,-wid,-wid);
	glVertex3d(tail,-wid,-wid);
	glVertex3d(tail, wid,-wid);

	glVertex3d(cone, wid, wid);
	glVertex3d(cone, wid,-wid);
	glVertex3d(tail, wid,-wid);
	glVertex3d(tail, wid, wid);

	glVertex3d(cone,-wid, wid);
	glVertex3d(cone,-wid,-wid);
	glVertex3d(tail,-wid,-wid);
	glVertex3d(tail,-wid, wid);

	glVertex3d(tail,-wid, wid);
	glVertex3d(tail, wid, wid);
	glVertex3d(tail, wid,-wid);
	glVertex3d(tail,-wid,-wid);
	glEnd();
	//  Wings (plane triangles)
	glColor3f(1,1,0);
	glBegin(GL_TRIANGLES);
	glVertex3d(wing, 0.0, wid);
	glVertex3d(tail, 0.0, wid);
	glVertex3d(tail, 0.0, 0.5);

	glVertex3d(wing, 0.0,-wid);
	glVertex3d(tail, 0.0,-wid);
	glVertex3d(tail, 0.0,-0.5);
	glEnd();
	//  Vertical tail (plane triangle)
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	glVertex3d(strk, 0.0, 0.0);
	glVertex3d(tail, 0.3, 0.0);
	glVertex3d(tail, 0.0, 0.0);
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*
 * Z component of projection (ex7) ok
 */
double Zp(double x,double y,double z) {
   return -Sin(th)*Cos(ph)*x + Sin(ph)*y + Cos(th)*Cos(ph)*z;
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 *  glut will display lorenz and plane
 */
void display() {
	//  Clear the image and z buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Reset previous transforms
	glLoadIdentity();
	//  Set view angle
	glRotated(ph,1,0,0);
	glRotated(th,0,1,0);
	
	glEnable(GL_DEPTH_TEST);
	
	//lorenz attractor
	int i;
	/*  Coordinates  */
	double x = 1;
	double y = 1;
	double z = 1;
	/*  Time step  */
	double dt = 0.001;
	
	double dx = 0;
	double dy = 0;
	double dz = 0;

	switch(mode){
		case 7:
			glBegin(GL_LINES);
			for (i = 0; i < 50000; i++){
				dx = s*(y-x);
				dy = x*(r-z)-y;
				dz = x*y - b*z;
				x += dt*dx;
				y += dt*dy;
				z += dt*dz;
				glColor3f(red,green,blue);
				glVertex3d(x/3, y/3, z/3);
			}
			glEnd();
			break;
		case 8:
			glPushMatrix();
			// translate
			glTranslatef(x, 0, 0);
			glTranslatef(0, y, 0);
			glTranslatef(0, 0, z);
			// rotate
			glRotatef(Cos(x), x, 0, 0);
			glRotatef(Cos(y), 0, y, 0);
			glRotatef(Cos(z), 0, 0, z);
			// plane
			SolidPlane(x/3, y/3, z/3,
					dx/3, dy/3, dz/3,
					x*dx/3, y*dy/3, z*dz/3);
			//SolidPlane(Cos(zh), Sin(zh), 0, -Sin(zh), Cos(zh), 0, Cos(4*zh), 0, Sin(4*zh));
			glPopMatrix();
			glBegin(GL_LINES);
			for (i = 0; i < 50000; i++){
				dx = s*(y-x);
				dy = x*(r-z)-y;
				dz = x*y - b*z;
				x += dt*dx;
				y += dt*dy;
				z += dt*dz;
				glColor3f(x/zh, y/zh, z/zh);
				glVertex3d(x/3, y/3, z/3);
			}
			glEnd();
			break;
		case 9:
			glPushMatrix();
			for(i = 1; i < 6; i++){
				glTranslatef(i,0,-i);
				glRotatef(zh,0,i,0);
				glColor3f(Cos(zh)*Cos(zh),Cos(zh)*Sin(zh),Sin(zh)*Sin(zh));
				glutSolidTeapot(i);
			}
			glPopMatrix();
			glEnd();
			break;
		default:
			break;
	}
	//create axes taken from ex6
	//  Draw axes in white
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(len,0,0);
	glVertex3d(0,0,0);
	glVertex3d(0,len,0);
	glVertex3d(0,0,0);
	glVertex3d(0,0,len);
	glEnd();
	//  Label axes
	glRasterPos3d(len,0,0);
	Print("X");
	glRasterPos3d(0,len,0);
	Print("Y");
	glRasterPos3d(0,0,len);
	Print("Z");

	// Print and dislay the text
	glWindowPos2i(2,2);
	Print("B: %.3f S: %.3f  R: %.3f |\n"
			" X: %.3f Y: %.3f  Z: %.3f",
			b, s, r, x, y, z);

	//  Flush and swap
	glFlush();
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed (ex6) ok
 */
void special(int key,int x,int y){
	//  Right arrow key - increase azimuth by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		th += 5;
	//  Left arrow key - decrease azimuth by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		th -= 5;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		ph += 5;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN)
		ph -= 5;
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed ok
 */
void key(unsigned char ch,int x,int y){
	// professor shredder wrote this with if else, can i use a switch?
	switch(ch){
		case 27: // esc exits prog
			exit(0);
			break;
		case '0': // reset view angle
			th = ph = 0;
			break;
		case '1': // reset params to original lorenz
			s  = 10;
			b  = 2.6666;
			r  = 28;
			break;
		case '2': // change color to red
			red = 1;
			green = 0;
			blue = 0;
			break;
		case '3': //change color to green
			red = 0;
			green = 1;
			blue = 0;
			break;
		case '4': //change color to blue
			red = 0;
			green = 0;
			blue = 1;
			break;
		case '7':
			mode = 7;
			break;
		case '8':
			mode = 8;
			break;
		case '9':
			mode = 9;
			break;
		case 's': // increase s val
			s += 0.5;
			break;
		case 'S': // decrease s val
			s -= 0.5;
			break;
		case 'r': // increase r val
			r += 0.5;
			break;
		case 'R': // decrease r val
			r -= 0.5;
			break;
		case 'b': // increasee b val
			b += 0.5;
			break;
		case 'B': // decrease b val
			b -= 0.5;
			break;
		default:
			break;
	}
	// redisplay the scene
	glutPostRedisplay();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized (ex8) ok
 */
void reshape(int width,int height){
	//  Ratio of the width to the height of the window
	double w2h = (height>0) ? (double)width/height : 1;
	//  Set the viewport to the entire window
	glViewport(0,0, width,height);
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Orthogonal projection box adjusted for the
	//  aspect ratio of the window
	glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}

/*
 *  GLUT calls this toutine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do ok
 */
int main(int argc,char* argv[]){
	//  Initialize GLUT and process user parameters
	glutInit(&argc,argv);
	//  Request double buffered, true color window, Z-buffering
	glutInitDisplayMode(GLUT_RGB |GLUT_DEPTH | GLUT_DOUBLE);
	//  Request 500 x 500 pixel window
	glutInitWindowSize(600,600);
	//  Create the window
	glutCreateWindow("Jason Lubrano hw2");
	//  Tell GLUT to call "display" when the scene should be drawn
	glutIdleFunc(idle);
	//  Tell GLUT to call "reshape" when the window is resized
	glutDisplayFunc(display);
	//  Tell GLUT to call "idle" when there is nothing else to do
	glutReshapeFunc(reshape);
	//  Tell GLUT to call "special" when an arrow key is pressed
	glutSpecialFunc(special);
	//  Tell GLUT to call "key" when a key is pressed
	glutKeyboardFunc(key);
	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();
	//  Return code
	return 0;
}
