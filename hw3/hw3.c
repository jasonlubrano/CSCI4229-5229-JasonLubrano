/* Jason Lubrano hw3 */

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

/* create a mech warrior */

// global vars
int axes=0;       //  Display axes
int mode=0;       //  Projection mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=8.0;   //  Size of world


//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

/*
	lightgray	rgb(211,211,211)	0.827
	silver		gb(192,192,192)		0.752
	darkgray	rgb(169,169,169)	0.662
	gray 		srgb(128,128,128)	0.501
*/

/*
*  Convenience routine to output raster text
*  Use VARARGS to make this more flexible
*/
#define LEN 8192  //  Maximum length of text string
	void Print(const char* format , ...) {
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

/*
*  Set projection
*/
static void Project() {
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Perspective transformation
	if (mode)
		gluPerspective(fov,asp,dim/4,4*dim);
	//  Orthogonal projection
	else
		glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}

/*
 *  Draw mech feet
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechFeet(double x,double y,double z,
						double dx,double dy,double dz,
						double th) {
	// foot vars
	int wid = 1, len = 1, dep = 4;
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	//  Front
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, wid, 0);
	glVertex3f(len, wid, 0);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(0, 0, dep);
	//  Right
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(len, wid, 0);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	//  Left
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(0, wid, dep);
	glVertex3f(0, wid, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, dep);
	//  Top
	glColor3f(0.827, 0.827, 0.827);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, wid, 0);
	glVertex3f(0, wid, 0);
	//  Bottom
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(0, 0, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);

	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech turrent
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechTurrent(double x,double y,double z,
						double dx,double dy,double dz,
						double th) {
	// turrent vars
	int wid = 2, len = 2, dep = 4;
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	//  Front
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, wid, 0);
	glVertex3f(len, wid, 0);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(0, 0, dep);
	//  Right
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(len, wid, 0);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	//  Left
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(0, wid, dep);
	glVertex3f(0, wid, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, dep);
	//  Top
	glColor3f(0.827, 0.827, 0.827);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, wid, 0);
	glVertex3f(0, wid, 0);
	//  Bottom
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(0, 0, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);

	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech upper leg
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechRightLeg(double x,double y,double z,
						double dx,double dy,double dz,
						double th) {
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	// BOTTOM LEG
	//  Front
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(1, 2, 0);
	glVertex3f(2, 2, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(1, 0, 0);
	//  Back
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(1, 2, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(1, 0, 2);
	//  Right
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(2, 2, 0);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 0, 0);
	//  Left
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	//  Top not needed
	//  Bottom
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(1, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 0, 0);
	glVertex3f(1, 0, 0);

	// UPPER LEG
	//  Front
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, 4, 0);
	glVertex3f(2, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 3, 0);
	//  Back
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, 4, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(0, 3, 2);
	//  Outseam
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(0, 4, 0);
	glVertex3f(0, 4, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 2, 0);
	//  Inseam
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(0, 3, 0);
	glVertex3f(0, 3, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 2, 0);
	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

static void mechLeftLeg(double x,double y,double z,
						double dx,double dy,double dz,
						double th) {
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	// BOTTOM LEG
	//  Front
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(0, 2, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(0, 0, 2);
	//  Right
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	//  Left
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(0, 2, 0);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, 0);
	//  Top not needed
	//  Bottom
	glColor3f(0.501, 0.501, 0.501);
	glVertex3f(0, 0, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	// UPPER LEG
	//  Front
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(2, 4, 0);
	glVertex3f(2, 3, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 2, 0);
	//  Back
	glColor3f(0.662, 0.662, 0.662);
	glVertex3f(2, 4, 2);
	glVertex3f(2, 3, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(0, 2, 2);
	//  Outseam
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(2, 4, 0);
	glVertex3f(2, 4, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, 0);
	//  Inseam
	glColor3f(0.752, 0.752, 0.752);
	glVertex3f(2, 3, 0);
	glVertex3f(2, 3, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 2, 0);
	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}


/*
 *  Draw mech
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void mechDraw(double x,double y,double z,
						double dx,double dy,double dz,
						double th) {

	if(dx == 0 || dy == 0 || dz == 0){
		dx = 1;
		dy = 1;
		dz = 1;
	}

	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);

	mechFeet(1, 1, 3, 1, 1, 1, 0); // left foot
	mechFeet(5, 1 , 3, 1, 1, 1, 0); // right foot
	mechLeftLeg(1, 2, 4, 1, 1, 1, 0); // left leg
	mechRightLeg(4, 2, 4, 1, 1, 1, 0); // right leg
	mechTurrent(1, 7, 3, 1, 1, 1, 0); // left turrent
	mechTurrent(4, 7, 3, 1, 1, 1, 0); // right turrent

	//  Undo transformations
	glPopMatrix();
}


/*
*  OpenGL (GLUT) calls this routine to display the scene
*/
void display() {
	const double len=1.5;  //  Length of axes
	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations
	glLoadIdentity();
	//  Perspective - set eye position
	if (mode) {
		double Ex = -2*dim*Sin(th)*Cos(ph);
		double Ey = +2*dim        *Sin(ph);
		double Ez = +2*dim*Cos(th)*Cos(ph);
		gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
	} else {
		//  Orthogonal - set world orientation
		glRotatef(ph,1,0,0);
		glRotatef(th,0,1,0);
	}

	//TODO: INCLUDE DRAW MECH FUNCTION
	mechDraw(-4, -4, -4, 1, 1, 1, 0);
	//  Draw axes
	glColor3f(1,1,1);
	if (axes)
	{
		glBegin(GL_LINES);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(len,0.0,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,len,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,0.0,len);
		glEnd();
		//  Label axes
		glRasterPos3d(len,0.0,0.0);
		Print("X");
		glRasterPos3d(0.0,len,0.0);
		Print("Y");
		glRasterPos3d(0.0,0.0,len);
		Print("Z");
	}
	//  Display parameters
	glWindowPos2i(5,5);
	Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");
	//  Render the scene and make it visible
	glFlush();
	glutSwapBuffers();
}

/*
*  GLUT calls this routine when an arrow key is pressed
*/
void special(int key,int x,int y) {
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		th += 5;
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		th -= 5;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		ph += 5;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN)
		ph -= 5;
	//  PageUp key - increase dim
	else if (key == GLUT_KEY_PAGE_UP)
		dim += 0.1;
	//  PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
		dim -= 0.1;
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Update projection
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
*  GLUT calls this routine when a key is pressed
*/
void key(unsigned char ch,int x,int y) {
	//  Exit on ESC
	if (ch == 27)
		exit(0);
	//  Reset view angle
	else if (ch == '0')
		th = ph = 0;
	//  Toggle axes
	else if (ch == 'a' || ch == 'A')
		axes = 1-axes;
	//  Switch display mode
	else if (ch == 'm' || ch == 'M')
		mode = 1-mode;
	//  Change field of view angle
	else if (ch == '-' && ch>1)
		fov--;
	else if (ch == '+' && ch<179)
		fov++;
	//  Reproject
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
*  GLUT calls this routine when the window is resized
*/
void reshape(int width,int height) {
	//  Ratio of the width to the height of the window
	asp = (height>0) ? (double)width/height : 1;
	//  Set the viewport to the entire window
	glViewport(0,0, width,height);
	//  Set projection
	Project();
}

/*
*  Start up GLUT and tell it what to do
*/
int main(int argc,char* argv[]){
	//  Initialize GLUT
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("Projections");
	//  Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();
	return 0;
}
