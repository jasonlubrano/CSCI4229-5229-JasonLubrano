/* Jason Lubrano hw4 */

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

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))
#define DEGREES_TO_RADIANS 3.14159/180.0

/* create a mech warrior */

// global vars
int axes = 1;			//  Display axes
int mode = 0; 			//  Projection mode
int th = 0;				//  Azimuth of view angle
int ph = 0;				//  Elevation of view angle
int fov = 55;			//  Field of view (for perspective)
double asp = 1;			//  Aspect ratio
static double dim = 20; //  Size of world
int turn = 1;			//	Turns the view of the world
static GLfloat spin = 0.0;
static int viewMech = 1;

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
 *	Set projection
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

/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/


/*	Draw mech feet silver
 *	at (x,y,z)
 *	dimensions (dx,dy,dz)
 *	rotated th about the y axis
 */
static void feet_mech1(double x, double y, double z, double dx, double dy, double dz, double th) {
	// foot vars
	double wid = 0.25, len = 0.25, dep = 1;
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	//  Front
	glColor3f(0.50, 0.50, 0.50);
	glVertex3f(-wid, +len, -dep);
	glVertex3f(+wid, +len, -dep);
	glVertex3f(+wid, -len, -dep);
	glVertex3f(-wid, -len, -dep);
	//  Back
	glColor3f(0.50, 0.50, 0.55);
	glVertex3f(-wid, +len, +dep);
	glVertex3f(+wid, +len, +dep);
	glVertex3f(+wid, -len, +dep);
	glVertex3f(-wid, -len, +dep);
	//  Right
	glColor3f(0.50, 0.50, 0.60);
	glVertex3f(+wid, +len, -dep);
	glVertex3f(+wid, +len, +dep);
	glVertex3f(+wid, -len, +dep);
	glVertex3f(+wid, -len, -dep);
	//  Left
	glColor3f(0.50, 0.50, 0.65);
	glVertex3f(-wid, +len, +dep);
	glVertex3f(-wid, +len, -dep);
	glVertex3f(-wid, -len, -dep);
	glVertex3f(-wid, -len, +dep);
	//  Top
	glColor3f(0.50, 0.50, 0.70);
	glVertex3f(-wid, +len, +dep);
	glVertex3f(+wid, +len, +dep);
	glVertex3f(+wid, +len, -dep);
	glVertex3f(-wid, +len, -dep);
	//  Bottom
	glColor3f(0.50, 0.50, 0.75);
	glVertex3f(-wid, -len, +dep);
	glVertex3f(+wid, -len, +dep);
	glVertex3f(+wid, -len, -dep);
	glVertex3f(-wid, -len, -dep);

	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*	Draw mech turrent silver
 *	at (x,y,z)
 *	dimensions (dx,dy,dz)
 *	rotated th about the y axis
 */
static void turrent_mech1(double x, double y, double z, double dx, double dy, double dz, double th) {
	// turrent vars
	double wid = 0.5, len = 0.5, dep = 1;
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	//  Front
	glColor3f(0.50, 0.55, 0.50);
	glVertex3f(-wid, +len, -dep);
	glVertex3f(+wid, +len, -dep);
	glVertex3f(+wid, -len, -dep);
	glVertex3f(-wid, -len, -dep);
	//  Back
	glColor3f(0.50, 0.55, 0.55);
	glVertex3f(-wid, +len, +dep);
	glVertex3f(+wid, +len, +dep);
	glVertex3f(+wid, -len, +dep);
	glVertex3f(-wid, -len, +dep);
	//  Right
	glColor3f(0.50, 0.55, 0.60);
	glVertex3f(+wid, +len, -dep);
	glVertex3f(+wid, +len, +dep);
	glVertex3f(+wid, -len, +dep);
	glVertex3f(+wid, -len, -dep);
	//  Left
	glColor3f(0.50, 0.55, 0.65);
	glVertex3f(-wid, +len, +dep);
	glVertex3f(-wid, +len, -dep);
	glVertex3f(-wid, -len, -dep);
	glVertex3f(-wid, -len, +dep);
	//  Top
	glColor3f(0.50, 0.55, 0.70);
	glVertex3f(-wid, +len, +dep);
	glVertex3f(+wid, +len, +dep);
	glVertex3f(+wid, +len, -dep);
	glVertex3f(-wid, +len, -dep);
	//  Bottom
	glColor3f(0.50, 0.55, 0.75);
	glVertex3f(-wid, -len, +dep);
	glVertex3f(+wid, -len, +dep);
	glVertex3f(+wid, -len, -dep);
	glVertex3f(-wid, -len, -dep);

	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*	Draw mech left leg silver
 *	at (x,y,z)
 *	dimensions (dx,dy,dz)
 * 	rotated th about the y axis
 */
static void lLeg_mech1(double x, double y, double z, double dx, double dy, double dz, double th) {
	//left leg varsa
	//top of the leg vars
	double lenO = 1.5; double lenI = 1.0; //outseam (lenO) and inseam (lenI) heights
	double wibO = 1.0; double wibI = 0.5; // width outseam , wid inseam
	double midp = 0; // where the two legs connect, Bottom of top leg is the top of the bottom leg
	double depl = 0.25; double depb = 1.0; // depth of the leg, depth of the base
	//bottom of the leg vars
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	// TOP LEG
	// Front
	glColor3f(0.50, 0.60, 0.50);
	glVertex3f(-wibO, +lenO, -depl);
	glVertex3f(+wibO, +midp, -depl);
	glVertex3f(+wibI, +midp, -depl);
	glVertex3f(-wibO, +lenI, -depl);
	// Back
	glColor3f(0.50, 0.60, 0.55);
	glVertex3f(-wibO, +lenO, +depl);
	glVertex3f(+wibO, +midp, +depl);
	glVertex3f(+wibI, +midp, +depl);
	glVertex3f(-wibO, +lenI, +depl);
	// Outseam
	glColor3f(0.50, 0.60, 0.60);
	glVertex3f(-wibO, +lenO, -depl);
	glVertex3f(-wibO, +lenO, +depl);
	glVertex3f(+wibO, +midp, +depl);
	glVertex3f(+wibO, +midp, -depl);
	// Inseam
	glColor3f(0.50, 0.60, 0.65);
	glVertex3f(-wibO, +lenI, -depl);
	glVertex3f(-wibO, +lenI, +depl);
	glVertex3f(+wibI, +midp, +depl);
	glVertex3f(+wibI, +midp, -depl);
	// Inseam

	// BOTTOM LEG
	// Front
	glColor3f(0.50, 0.60, 0.70);
	glVertex3f(+wibI, +midp, -depl);
	glVertex3f(+wibO, +midp, -depl);
	glVertex3f(+wibO, -lenO, -depl);
	glVertex3f(+wibI, -lenO, -depl);
	// Back
	glColor3f(0.50, 0.60, 0.75);
	glVertex3f(+wibI, +midp, +depl);
	glVertex3f(+wibO, +midp, +depl);
	glVertex3f(+wibO, -lenO, +depl);
	glVertex3f(+wibI, -lenO, +depl);
	// Outseam
	glColor3f(0.50, 0.65, 0.50);
	glVertex3f(+wibO, +midp, -depl);
	glVertex3f(+wibO, +midp, +depl);
	glVertex3f(+wibO, -lenO, +depl);
	glVertex3f(+wibO, -lenO, -depl);
	// Inseam
	glColor3f(0.50, 0.65, 0.55);
	glVertex3f(+wibI, +midp, -depl);
	glVertex3f(+wibI, +midp, +depl);
	glVertex3f(+wibI, -lenO, +depl);
	glVertex3f(+wibI, -lenO, -depl);
	//  End

	// BASE
	// Front
	glColor3f(0.50, 0.65, 0.60);
	glVertex3f(+wibI, -lenI, -depl);
	glVertex3f(+wibO, -lenI, -depl);
	glVertex3f(+wibO, -lenO, -depb);
	glVertex3f(+wibI, -lenO, -depb);
	// Back
	glColor3f(0.50, 0.65, 0.65);
	glVertex3f(+wibI, -lenI, +depl);
	glVertex3f(+wibO, -lenI, +depl);
	glVertex3f(+wibO, -lenO, +depb);
	glVertex3f(+wibI, -lenO, +depb);
	glEnd();

	// BASE
	glBegin(GL_TRIANGLES);
	// Base
	// Front
	// Inseam
	glColor3f(0.50, 0.65, 0.70);
	glVertex3f(+wibI, -lenI, -depl);
	glVertex3f(+wibI, -lenO, -depl);
	glVertex3f(+wibI, -lenO, -depb);
	// Outseam
	glColor3f(0.50, 0.65, 0.75);
	glVertex3f(+wibO, -lenI, -depl);
	glVertex3f(+wibO, -lenO, -depl);
	glVertex3f(+wibO, -lenO, -depb);

	// Back
	// Inseam
	glColor3f(0.50, 0.70, 0.50);
	glVertex3f(+wibI, -lenI, +depl);
	glVertex3f(+wibI, -lenO, +depl);
	glVertex3f(+wibI, -lenO, +depb);
	// Outseam
	glColor3f(0.50, 0.70, 0.55);
	glVertex3f(+wibO, -lenI, +depl);
	glVertex3f(+wibO, -lenO, +depl);
	glVertex3f(+wibO, -lenO, +depb);

	glEnd();

	//  Undo transformations
	glPopMatrix();
}

/*	Draw mech right leg silver
 *	at (x,y,z)
 *	dimensions (dx,dy,dz)
 *	rotated th about the y axis
 */
static void rLeg_mech1(double x, double y, double z, double dx, double dy, double dz, double th) {
	//left leg varsa
	//top of the leg vars
	double lenO = 1.5; double lenI = 1.0; //outseam (lenO) and inseam (lenI) heights
	double wibO = 1.0; double wibI = 0.5; // width outseam , wid inseam
	double midp = 0; // where the two legs connect, Bottom of top leg is the top of the bottom leg
	double depl = 0.25; double depb = 1.0; // depth of the leg, depth of the base
	//bottom of the leg vars
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	// TOP LEG
	// Front
	glColor3f(0.50, 0.70, 0.60);
	glVertex3f(+wibO, +lenO, -depl);
	glVertex3f(+wibO, +lenI, -depl);
	glVertex3f(-wibI, +midp, -depl);
	glVertex3f(-wibO, +midp, -depl);
	// Back
	glColor3f(0.50, 0.70, 0.65);
	glVertex3f(+wibO, +lenO, +depl);
	glVertex3f(+wibO, +lenI, +depl);
	glVertex3f(-wibI, +midp, +depl);
	glVertex3f(-wibO, +midp, +depl);
	// Outseam
	glColor3f(0.50, 0.70, 0.70);
	glVertex3f(+wibO, +lenO, -depl);
	glVertex3f(+wibO, +lenO, +depl);
	glVertex3f(-wibO, +midp, +depl);
	glVertex3f(-wibO, +midp, -depl);
	// Inseam
	glColor3f(0.50, 0.70, 0.75);
	glVertex3f(+wibO, +lenI, -depl);
	glVertex3f(+wibO, +lenI, +depl);
	glVertex3f(-wibI, +midp, +depl);
	glVertex3f(-wibI, +midp, -depl);

	// BOTTOM LEG
	// Front
	glColor3f(0.50, 0.75, 0.50);
	glVertex3f(-wibO, +midp, -depl);
	glVertex3f(-wibI, +midp, -depl);
	glVertex3f(-wibI, -lenO, -depl);
	glVertex3f(-wibO, -lenO, -depl);
	// Back
	glColor3f(0.50, 0.75, 0.55);
	glVertex3f(-wibO, +midp, +depl);
	glVertex3f(-wibI, +midp, +depl);
	glVertex3f(-wibI, -lenO, +depl);
	glVertex3f(-wibO, -lenO, +depl);
	// Outseam
	glColor3f(0.50, 0.75, 0.60);
	glVertex3f(-wibO, +midp, -depl);
	glVertex3f(-wibO, +midp, +depl);
	glVertex3f(-wibO, -lenO, +depl);
	glVertex3f(-wibO, -lenO, -depl);
	// Inseam
	glColor3f(0.50, 0.75, 0.65);
	glVertex3f(-wibI, +midp, -depl);
	glVertex3f(-wibI, +midp, +depl);
	glVertex3f(-wibI, -lenO, +depl);
	glVertex3f(-wibI, -lenO, -depl);

	// BASE
	// Front
	glColor3f(0.50, 0.75, 0.70);
	glVertex3f(-wibI, -lenI, -depl);
	glVertex3f(-wibO, -lenI, -depl);
	glVertex3f(-wibO, -lenO, -depb);
	glVertex3f(-wibI, -lenO, -depb);
	// Back
	glColor3f(0.50, 0.75, 0.75);
	glVertex3f(-wibI, -lenI, +depl);
	glVertex3f(-wibO, -lenI, +depl);
	glVertex3f(-wibO, -lenO, +depb);
	glVertex3f(-wibI, -lenO, +depb);
	glEnd();

	// BASE
	glBegin(GL_TRIANGLES);
	// Base
	// Front
	// Inseam
	glColor3f(0.55, 0.50, 0.50);
	glVertex3f(-wibI, -lenI, -depl);
	glVertex3f(-wibI, -lenO, -depl);
	glVertex3f(-wibI, -lenO, -depb);
	// Outseam
	glColor3f(0.55, 0.50, 0.55);
	glVertex3f(-wibO, -lenI, -depl);
	glVertex3f(-wibO, -lenO, -depl);
	glVertex3f(-wibO, -lenO, -depb);

	// Back
	// Inseam
	glColor3f(0.55, 0.50, 0.60);
	glVertex3f(-wibI, -lenI, +depl);
	glVertex3f(-wibI, -lenO, +depl);
	glVertex3f(-wibI, -lenO, +depb);
	// Outseam
	glColor3f(0.55, 0.50, 0.65);
	glVertex3f(-wibO, -lenI, +depl);
	glVertex3f(-wibO, -lenO, +depl);
	glVertex3f(-wibO, -lenO, +depb);

	glEnd();

	//  Undo transformations
	glPopMatrix();
}


/*	Draw mech body 1 maroon stripped
 *	at (x,y,z)
 *	dimensions (dx,dy,dz)
 *	rotated th about the y axis
 */
static void body_mech1(double x, double y, double z, double dx, double dy, double dz, double th) {
	double lenG = 0.5; double midp = 0.0; double lenF = 1.0; 
	double depC = 0.5; double depM = 1.0; double depS = 1.5; // depth close, mid, side
	double strp = 0.75;	double widg = 0.5; double depT = 0.75; double desB = 1.25;
	
	/* coloring the mechs */
	double marr = 0.69; double marg = 0.19; double marb = 0.37; // maroon coloring
	double dglr = 0.45; double dglg = 0.67; double dglb = 0.75; // glass color

	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  GLASS
	// Front - Upper
	glBegin(GL_QUADS);
	glColor3f(dglr, dglg, dglb);
	glVertex3f(-widg, +lenG, -depM);
	glVertex3f(+widg, +lenG, -depM);
	glVertex3f(+widg, +midp, -depS);
	glVertex3f(-widg, +midp, -depS);
	// Front - Face
	glColor3f(dglr, dglg, dglb);
	glVertex3f(-widg, +midp, -depS);
	glVertex3f(+widg, +midp, -depS);
	glVertex3f(+widg, -lenG, -depS);
	glVertex3f(-widg, -lenG, -depS);
	// Right
	glColor3f(dglr, dglg, dglb);
	glVertex3f(+widg, +midp, -midp);
	glVertex3f(+widg, +lenG, -depM);
	glVertex3f(+widg, +midp, -depS);
	glVertex3f(+widg, -lenG, -depS);
	// Left
	glColor3f(dglr, dglg, dglb);
	glVertex3f(-widg, +midp, -midp);
	glVertex3f(-widg, +lenG, -depM);
	glVertex3f(-widg, +midp, -depS);
	glVertex3f(-widg, -lenG, -depS);
	//	STRIPE
	// Front - Upper
	glColor3f(marr, marg, marb);
	glVertex3f(-widg, +strp, -depT);
	glVertex3f(+widg, +strp, -depT);
	glVertex3f(+widg, +lenG, -depM);
	glVertex3f(-widg, +lenG, -depM);
	// Right - Upper
	glColor3f(marr, marg, marb);
	glVertex3f(+widg, +strp, +desB);
	glVertex3f(+widg, +strp, -depT);
	glVertex3f(+widg, +lenG, -depM);
	glVertex3f(+widg, +lenG, +depS);
	// Left - Upper
	glColor3f(marr, marg, marb);
	glVertex3f(-widg, +strp, +desB);
	glVertex3f(-widg, +strp, -depT);
	glVertex3f(-widg, +lenG, -depM);
	glVertex3f(-widg, +lenG, +depS);
	// Front - Bottom
	glColor3f(marr, marg, marb);
	glVertex3f(-widg, -lenG, -depS);
	glVertex3f(+widg, -lenG, -depS);
	glVertex3f(+widg, -strp, -desB);
	glVertex3f(-widg, -strp, -desB);
	// Right - Bottom
	glColor3f(marr, marg, marb);
	glVertex3f(+widg, -lenG, -depS);
	glVertex3f(+widg, -lenG, +depM);
	glVertex3f(+widg, -strp, +depT);
	glVertex3f(+widg, -strp, -desB);
	// Left - Bottom
	glColor3f(marr, marg, marb);
	glVertex3f(-widg, -lenG, -depS);
	glVertex3f(-widg, -lenG, +depM);
	glVertex3f(-widg, -strp, +depT);
	glVertex3f(-widg, -strp, -desB);
	
	// MAIN BODY
	
	// UPPER
	// Front
	glColor3f(0.55, 0.50, 0.70);
	glVertex3f(-widg, +lenF, -depC);
	glVertex3f(+widg, +lenF, -depC);
	glVertex3f(+widg, +strp, -depT);
	glVertex3f(-widg, +strp, -depT);
	// Back
	glColor3f(0.55, 0.50, 0.75);
	glVertex3f(-widg, +lenF, +depM);
	glVertex3f(+widg, +lenF, +depM);
	glVertex3f(+widg, +lenG, +depS);
	glVertex3f(-widg, +lenG, +depS);
	// Top
	glColor3f(0.55, 0.55, 0.50);
	glVertex3f(-widg, +lenF, +depM);
	glVertex3f(+widg, +lenF, +depM);
	glVertex3f(+widg, +lenF, -depC);
	glVertex3f(-widg, +lenF, -depC);
	// Right
	glColor3f(0.55, 0.55, 0.55);
	glVertex3f(+widg, +lenF, +depM);
	glVertex3f(+widg, +lenF, -depC);
	glVertex3f(+widg, +strp, -depT);
	glVertex3f(+widg, +strp, +desB);
	// Left
	glColor3f(0.55, 0.55, 0.60);
	glVertex3f(-widg, +lenF, +depM);
	glVertex3f(-widg, +lenF, -depC);
	glVertex3f(-widg, +strp, -depT);
	glVertex3f(-widg, +strp, +desB);
	
	// SIDES
	// Right - Upper
	glColor3f(0.55, 0.55, 0.65);
	glVertex3f(+widg, +lenG, +depS);
	glVertex3f(+widg, +lenG, -depM);
	glVertex3f(+widg, +midp, -midp);
	glVertex3f(+widg, +midp, +depS);
	// Right - Lower
	glColor3f(0.55, 0.55, 0.70);
	glVertex3f(+widg, +midp, +depS);
	glVertex3f(+widg, +midp, +midp);
	glVertex3f(+widg, -lenG, -depS);
	glVertex3f(+widg, -lenG, +depM);
	// Left - Upper
	glColor3f(0.55, 0.55, 0.75);
	glVertex3f(-widg, +lenG, +depS);
	glVertex3f(-widg, +lenG, -depM);
	glVertex3f(-widg, +midp, -midp);
	glVertex3f(-widg, +midp, +depS);
	// Left - Lower
	glColor3f(0.55, 0.60, 0.50);
	glVertex3f(-widg, +midp, +depS);
	glVertex3f(-widg, +midp, +midp);
	glVertex3f(-widg, -lenG, -depS);
	glVertex3f(-widg, -lenG, +depM);

	// Bottom
	// Front
	glColor3f(0.55, 0.60, 0.55);
	glVertex3f(-widg, -strp, -desB);
	glVertex3f(+widg, -strp, -desB);
	glVertex3f(+widg, -lenF, -depM);
	glVertex3f(-widg, -lenF, -depM);
	// Back
	glColor3f(0.55, 0.60, 0.60);
	glVertex3f(-widg, -midp, +depS);
	glVertex3f(+widg, -midp, +depS);
	glVertex3f(+widg, -lenF, +depC);
	glVertex3f(-widg, -lenF, +depC);
	// Right
	glColor3f(0.55, 0.60, 0.65);
	glVertex3f(+widg, -strp, +depT);
	glVertex3f(+widg, -strp, -desB);
	glVertex3f(+widg, -lenF, -depM);
	glVertex3f(+widg, -lenF, +depC);
	// Left
	glColor3f(0.55, 0.60, 0.70);
	glVertex3f(-widg, -strp, +depT);
	glVertex3f(-widg, -strp, -desB);
	glVertex3f(-widg, -lenF, -depM);
	glVertex3f(-widg, -lenF, +depC);
	// Bottom
	glColor3f(0.55, 0.60, 0.75);
	glVertex3f(-widg, -lenF, +depC);
	glVertex3f(+widg, -lenF, +depC);
	glVertex3f(+widg, -lenF, -depM);
	glVertex3f(-widg, -lenF, -depM);

	// BACK
	glColor3f(0.55, 0.65, 0.50);
	glVertex3f(-widg, +lenG, +depS);
	glVertex3f(+widg, +lenG, +depS);
	glVertex3f(+widg, +midp, +depS);
	glVertex3f(-widg, +midp, +depS);

	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/* 	Draw mech 1, maroon stripped
 * 	at (x,y,z)
 * 	dimensions (dx,dy,dz)
 *	rotated th about the y axis
 */
void draw_mech1(double x, double y, double z, double dx, double dy, double dz, double th) {
	if(dx == 0 || dy == 0 || dz == 0){
		dx = 1;
		dy = 1;
		dz = 1;
	}

	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th + 180, 0, 1, 0);
	glScaled(dx, dy, dz);
	// DRAW MECH PARTS
	body_mech1(0, 1, 0, 1, 1, 1, 0); // mech body
	turrent_mech1(1, 2, 1, 1, 1, 1, 0); // left turrent
	turrent_mech1(-1, 2, 1, 1, 1, 1, 0); // right turrent
	lLeg_mech1(1.5, -0.5, 0, 1, 1, 1, 0); // left leg
	rLeg_mech1(-1.5, -0.5, 0, 1, 1, 1, 0); // right leg
	feet_mech1(2.25, -2.25, 0, 1, 1, 1, 0); // left foot
	feet_mech1(-2.25, -2.25, 0, 1, 1, 1, 0); // right foot

	//  Undo transformations
	glPopMatrix();
}

/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/
/*****************************************************************************************************************************************************/

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
		gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
	} else {
		//  Orthogonal - set world orientation
		glRotatef(ph,1,0,0);
		glRotatef(th,0,1,0);
	}


	int i = 0, j = 0;

	switch(viewMech){
		case 1:
			glPushMatrix();
				if(turn) glRotatef(spin, 0, 1, 0);
				for(i = 0; i <= 12; i += 6)
					for(j = 0; j <= 15; j += 5)
						draw_mech1(i, 0, j, 1, 1, 1, 0);
				draw_mech1(-6, 2.5, 0, 2, 2, 2, 90); // draws the mid mech
				draw_mech1(-6, 2.5, 12, 2, 2, 2, 90); // draws the mid mech
				draw_mech1(13.5, 5, -1.5, 3, 3, 3, -45); // draws the big mech
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
				if(turn) glRotatef(spin, 0, 1, 0);
				draw_mech1(0, 0, 0, 3, 3, 3, 0); // draws the big mech
			glPopMatrix();
			break;
		default:
			break;
	}


	//  Draw axes
	glColor3f(1,1,1);
	if (axes){
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

	//  Display prarameters
	glWindowPos2i(5,5);
	Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s\n", th, ph, dim, fov, mode?"Perpective":"Orthogonal");
	Print("Spin = %0.2f", spin);
	//  Render the scene and make it visible
	glFlush();
	glutSwapBuffers();
}

/*
*  GLUT calls this routine when an arrow key is pressed
*/
void special(int key, int x, int y) {

	switch(key){
		case GLUT_KEY_RIGHT: //  Right arrow key - increase angle by 5 degrees
			th += 5;
			break;
		case GLUT_KEY_LEFT: //  Left arrow key - decrease angle by 5 degrees
			th -= 5;
			break;
		case GLUT_KEY_UP: //  Up arrow key - increase elevation by 5 degrees
			ph += 5;
			break;
		case GLUT_KEY_DOWN: //  Down arrow key - decrease elevation by 5 degrees
			ph -= 5;
			break;
		case GLUT_KEY_PAGE_UP: //  PageUp key - increase dim
			dim += 0.1;
			break;
		case GLUT_KEY_PAGE_DOWN: //  PageDown key - decrease dim
			if(dim > 1){
				dim -= 0.1;
			}
			break;
	}
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

	switch(ch){
		case 27:
			exit(0);
			break;
		case '0': // reset view angle
			th = ph = 0;
			break;
		case 'A': //  Toggle axes
		case 'a': //  Toggle axes
			axes = (axes + 1) % 2; // fixes the axes problem
			break;
		case 'm': //  Switch display mode
		case 'M': //  Switch display mode
			mode = 1-mode;
			break;
		case '-':
			if(ch > 1){
				fov--;
			}
			break;
		case '+':
			if(ch < 179){
				fov ++;
			}
			break;
		case '1':
			viewMech = 1;
			break;
		case '2':
			viewMech = 2;
			break;
		case '9':
			turn = (turn + 1) % 2; // fixes turn
			break;
		default:
			break;
	}
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
 * Idle function that will make the view spin when not used
 * TO DO: make it able to be turned off
 */
void spinDisplay () {
	if(turn) spin += 0.05;
	if(spin > 360.0) spin = spin - 360.0;
	glutPostRedisplay();
}

/*
*  Start up GLUT and tell it what to do
*/
int main(int argc,char* argv[]){
	//  Initialize GLUT
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("mech drawings");
	//  Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutIdleFunc(spinDisplay);
	glutKeyboardFunc(key);
	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();
}