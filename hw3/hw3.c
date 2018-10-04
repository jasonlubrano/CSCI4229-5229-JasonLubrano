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

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))
#define DEGREES_TO_RADIANS 3.14159/180.0

/* create a mech warrior */

// global vars
int axes=0;			//  Display axes
int mode=0; 		//  Projection mode
int th=0;			//  Azimuth of view angle
int ph=0;			//  Elevation of view angle
int fov=55;			//  Field of view (for perspective)
double asp=1;		//  Aspect ratio
static double dim = 20; //  Size of world
int viewMech = 4; 	// view 1 for small mech, 2 for mid mech, 3 for big mech, 4 for army
int turn = 1;


/* coloring the mechs */
double marr = 0.69; double marg = 0.19; double marb = 0.37; // maroon coloring
double navr = 0.00; double navg = 0.00; double navb = 0.50; // navy blue coloring
double orgr = 0.99; double orgg = 0.40; double orgb = 0.00; // orange stripe
double armr = 0.29; double armg = 0.32; double armb = 0.09; // army green
double darg = 0.20; // dark green everythign else 0;
double glar = 0.66; double glag = 0.80; double glab = 0.84; // glass color
double dglr = 0.45; double dglg = 0.67; double dglb = 0.75; // glass color

 
static GLfloat spin = 0.0;
GLfloat x, y;


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
 *  Draw mech feet silver
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechFeet_1(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(0.66, 0.66, 0.66);
	glVertex3f(0, wid, 0);
	glVertex3f(len, wid, 0);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(0.65, 0.65, 0.65);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(0, 0, dep);
	//  Right
	glColor3f(0.76, 0.76, 0.76);
	glVertex3f(len, wid, 0);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	//  Left
	glColor3f(0.75, 0.75, 0.75);
	glVertex3f(0, wid, dep);
	glVertex3f(0, wid, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, dep);
	//  Top
	glColor3f(0.82, 0.82, 0.82);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, wid, 0);
	glVertex3f(0, wid, 0);
	//  Bottom
	glColor3f(0.50, 0.50, 0.50);
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
 *  Draw mech turrent silver
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechTurrent_1(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(0.65, 0.65, 0.65);
	glVertex3f(0, wid, 0);
	glVertex3f(len, wid, 0);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(0.64, 0.64, 0.64);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(0, 0, dep);
	//  Right
	glColor3f(0.73, 0.73, 0.73);
	glVertex3f(len, wid, 0);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	//  Left
	glColor3f(0.75, 0.75, 0.75);
	glVertex3f(0, wid, dep);
	glVertex3f(0, wid, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, dep);
	//  Top
	glColor3f(0.83, 0.83, 0.83);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, wid, 0);
	glVertex3f(0, wid, 0);
	//  Bottom
	glColor3f(0.51, 0.51, 0.51);
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
 *  Draw mech right leg silver
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechRightLeg_1(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(0.68, 0.68, 0.68);
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
	glColor3f(0.73, 0.73, 0.73);
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
	glColor3f(0.69, 0.69, 0.69);
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
	glColor3f(0.74, 0.74, 0.74);
	glVertex3f(0, 4, 0);
	glVertex3f(0, 4, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 2, 0);
	//  Inseam
	glColor3f(0.75, 0.75, 0.75);
	glVertex3f(0, 3, 0);
	glVertex3f(0, 3, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 2, 0);
	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech left leg silver
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechLeftLeg_1(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(0.68, 0.68, 0.68);
	glVertex3f(0, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(0.65, 0.65, 0.65);
	glVertex3f(0, 2, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(0, 0, 2);
	//  Right
	glColor3f(0.74, 0.74, 0.74);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	//  Left
	glColor3f(0.73, 0.73, 0.73);
	glVertex3f(0, 2, 0);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, 0);
	//  Top not needed
	//  Bottom
	glColor3f(0.52, 0.52, 0.52);
	glVertex3f(0, 0, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	// UPPER LEG
	//  Front
	glColor3f(0.66, 0.66, 0.66);
	glVertex3f(2, 4, 0);
	glVertex3f(2, 3, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 2, 0);
	//  Back
	glColor3f(0.65, 0.65, 0.65);
	glVertex3f(2, 4, 2);
	glVertex3f(2, 3, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(0, 2, 2);
	//  Outseam
	glColor3f(0.77, 0.77, 0.77);
	glVertex3f(2, 4, 0);
	glVertex3f(2, 4, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, 0);
	//  Inseam
	glColor3f(0.75, 0.75, 0.75);
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
 *  Draw mech body 1 maroon stripped
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechBody_1(double x, double y, double z, double dx, double dy, double dz, double th) {
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	//  Front top
	glColor3f(0.66, 0.8, 0.84); // front glass
	glVertex3f(0, 4, 2);
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 2, 0);
	//	Front face
	glColor3f(0.66, 0.8, 0.84); // front glass
	glVertex3f(0, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	//  Front under
	glColor3f(0.65, 0.65, 0.65);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	//	Undercarriage
	glColor3f(0.50, 0.50, 0.50);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 0, 4);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	//  Back undercarrage
	glColor3f(0.68, 0.68, 0.68);
	glVertex3f(0, 2, 6);
	glVertex3f(1, 2, 6);
	glVertex3f(1, 0, 4);
	glVertex3f(0, 0, 4);
	//  Back
	glColor3f(0.64, 0.64, 0.64);
	glVertex3f(0, 4, 6);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 2, 6);
	glVertex3f(0, 2, 6);
	//  Top
	glColor3f(0.82, 0.82, 0.82);
	glVertex3f(0, 4, 6);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 4, 2);
	glVertex3f(0, 4, 2);
	//  Right
	glColor3f(0.75, 0.75, 0.75);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 2, 6);
	glColor3f(dglr, dglg, dglb); // right glass
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 2);
	glColor3f(0.76, 0.76, 0.76);
	glVertex3f(1, 1, 5);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 4);
	glColor3f(marr, marg, marb); // maroon stripe
	glVertex3f(1, 2, 6);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 1, 2);
	glVertex3f(1, 1, 5);
	//	Left
	glColor3f(marr, marg, marb); // maroon stripe
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, 6);
	glVertex3f(0, 1, 5);
	glVertex3f(0, 1, 2);
	glColor3f(0.76, 0.76, 0.76);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 5);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 0, 1);
	glColor3f(dglr, dglg, dglb); // right glass
	glVertex3f(0, 2, 0);
	glVertex3f(0, 4, 2);
	glVertex3f(0, 1, 2);
	glVertex3f(0, 1, 0);
	glColor3f(0.74, 0.74, 0.74);
	glVertex3f(0, 4, 2);
	glVertex3f(0, 4, 6);
	glVertex3f(0, 2, 6);
	glVertex3f(0, 2, 2);
	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech body 2 blue stripped
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechBody_2(double x, double y, double z, double dx, double dy, double dz, double th) {
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	//  Front top
	glColor3f(glar, glag, glab); // front glass
	glVertex3f(0, 4, 2);
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 2, 0);
	//	Front face
	glColor3f(glar, glag, glab); // front glass
	glVertex3f(0, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	//  Front under
	glColor3f(0.65, 0.65, 0.65);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	//	Undercarriage
	glColor3f(0.50, 0.50, 0.50);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 0, 4);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	//  Back undercarrage
	glColor3f(0.68, 0.68, 0.68);
	glVertex3f(0, 2, 6);
	glVertex3f(1, 2, 6);
	glVertex3f(1, 0, 4);
	glVertex3f(0, 0, 4);
	//  Back
	glColor3f(0.64, 0.64, 0.64);
	glVertex3f(0, 4, 6);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 2, 6);
	glVertex3f(0, 2, 6);
	//  Top
	glColor3f(0.82, 0.82, 0.82);
	glVertex3f(0, 4, 6);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 4, 2);
	glVertex3f(0, 4, 2);
	//  Right
	glColor3f(0.75, 0.75, 0.75);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 2, 6);
	glColor3f(dglr, dglg, dglb); // right glass
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 2);
	glColor3f(0.76, 0.76, 0.76);
	glVertex3f(1, 1, 5);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 4);
	glColor3f(navr, navg, navb); // navy stripe
	glVertex3f(1, 2, 6);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 1, 2);
	glVertex3f(1, 1, 5);
	//	Left
	glColor3f(navr, navg, navb); // navy stripe
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, 6);
	glVertex3f(0, 1, 5);
	glVertex3f(0, 1, 2);
	glColor3f(0.76, 0.76, 0.76);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 5);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 0, 1);
	glColor3f(dglr, dglg, dglb); // right glass
	glVertex3f(0, 2, 0);
	glVertex3f(0, 4, 2);
	glVertex3f(0, 1, 2);
	glVertex3f(0, 1, 0);
	glColor3f(0.74, 0.74, 0.74);
	glVertex3f(0, 4, 2);
	glVertex3f(0, 4, 6);
	glVertex3f(0, 2, 6);
	glVertex3f(0, 2, 2);
	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}


/*
 *  Draw mech feet green
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechFeet_2(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(armr, armg + 0.15, armb);
	glVertex3f(0, wid, 0);
	glVertex3f(len, wid, 0);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(armr, armg + 0.15, armb);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(0, 0, dep);
	//  Right
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(len, wid, 0);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	//  Left
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(0, wid, dep);
	glVertex3f(0, wid, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, dep);
	//  Top
	glColor3f(armr, armg + 0.2, armb);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, wid, 0);
	glVertex3f(0, wid, 0);
	//  Bottom
	glColor3f(armr, armg - 0.2, armb);
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
 *  Draw mech turrent green
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechTurrent_2(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(armr, armg, armb);
	glVertex3f(0, wid, 0);
	glVertex3f(len, wid, 0);
	glVertex3f(len, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(armr, armg, armb);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(0, 0, dep);
	//  Right
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(len, wid, 0);
	glVertex3f(len, wid, dep);
	glVertex3f(len, 0, dep);
	glVertex3f(len, 0, 0);
	//  Left
	glColor3f(armr, armg + 0.05, armb);
	glVertex3f(0, wid, dep);
	glVertex3f(0, wid, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, dep);
	//  Top
	glColor3f(armr, armg + 0.2, armb);
	glVertex3f(0, wid, dep);
	glVertex3f(len, wid, dep);
	glVertex3f(len, wid, 0);
	glVertex3f(0, wid, 0);
	//  Bottom
	glColor3f(armr, armg - 0.1, armb);
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
 *  Draw mech right leg green
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechRightLeg_2(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(armr, armg + 0.05, armb);
	glVertex3f(1, 2, 0);
	glVertex3f(2, 2, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(1, 0, 0);
	//  Back
	glColor3f(armr, armg + 0.05, armb);
	glVertex3f(1, 2, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(1, 0, 2);
	//  Right
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(2, 2, 0);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 0, 0);
	//  Left
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	//  Top not needed
	//  Bottom
	glColor3f(armr, armg, armb);
	glVertex3f(1, 0, 2);
	glVertex3f(2, 0, 2);
	glVertex3f(2, 0, 0);
	glVertex3f(1, 0, 0);

	// UPPER LEG
	//  Front
	glColor3f(armr, armg, armb);
	glVertex3f(0, 4, 0);
	glVertex3f(2, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 3, 0);
	//  Back
	glColor3f(armr, armg, armb);
	glVertex3f(0, 4, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(0, 3, 2);
	//  Outseam
	glColor3f(armr, armg + 0.15, armb);
	glVertex3f(0, 4, 0);
	glVertex3f(0, 4, 2);
	glVertex3f(2, 2, 2);
	glVertex3f(2, 2, 0);
	//  Inseam
	glColor3f(armr, armg + 0.15, armb);
	glVertex3f(0, 3, 0);
	glVertex3f(0, 3, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 2, 0);
	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech left leg green
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechLeftLeg_2(double x, double y, double z, double dx, double dy, double dz, double th) {
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
	glColor3f(armr, armg + 0.05, armb);
	glVertex3f(0, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	//  Back
	glColor3f(armr, armg + 0.05, armb);
	glVertex3f(0, 2, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(0, 0, 2);
	//  Right
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	//  Left
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(0, 2, 0);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, 0);
	//  Top not needed
	//  Bottom
	glColor3f(armr, armg, armb);
	glVertex3f(0, 0, 2);
	glVertex3f(1, 0, 2);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	// UPPER LEG
	//  Front
	glColor3f(armr, armg, armb);
	glVertex3f(2, 4, 0);
	glVertex3f(2, 3, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 2, 0);
	//  Back
	glColor3f(armr, armg, armb);
	glVertex3f(2, 4, 2);
	glVertex3f(2, 3, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(0, 2, 2);
	//  Outseam
	glColor3f(armr, armg + 0.15, armb);
	glVertex3f(2, 4, 0);
	glVertex3f(2, 4, 2);
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, 0);
	//  Inseam
	glColor3f(armr, armg + 0.15, armb);
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
 *  Draw mech body 3 oange strpped green body
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void mechBody_3(double x, double y, double z, double dx, double dy, double dz, double th) {
	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(dx, dy, dz);
	//  feet use quads
	glBegin(GL_QUADS);
	//  Front top
	glColor3f(glar, glag, glab); // front glass
	glVertex3f(0, 4, 2);
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 0);
	glVertex3f(0, 2, 0);
	//	Front face
	glColor3f(glar, glag, glab + 0.1); // front glass
	glVertex3f(0, 2, 0);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	//  Front under
	glColor3f(armr, armg, armb);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	//	Undercarriage
	glColor3f(armr, armg - 0.15, armb);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 0, 4);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	//  Back undercarrage
	glColor3f(armr, armg - 0.05, armb);
	glVertex3f(0, 2, 6);
	glVertex3f(1, 2, 6);
	glVertex3f(1, 0, 4);
	glVertex3f(0, 0, 4);
	//  Back
	glColor3f(armr, armg, armb);
	glVertex3f(0, 4, 6);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 2, 6);
	glVertex3f(0, 2, 6);
	//  Top
	glColor3f(armr, armg + 0.15, armb);
	glVertex3f(0, 4, 6);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 4, 2);
	glVertex3f(0, 4, 2);
	//  Right
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(1, 4, 6);
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 2, 6);
	glColor3f(glar, glag, glab - 0.2); // front glass
	glVertex3f(1, 4, 2);
	glVertex3f(1, 2, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 2);
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(1, 1, 5);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 4);
	glColor3f(orgr, orgg, orgb); // orange stripe
	glVertex3f(1, 2, 6);
	glVertex3f(1, 2, 2);
	glVertex3f(1, 1, 2);
	glVertex3f(1, 1, 5);
	//	Left
	glColor3f(orgr, orgg, orgb); // orange stripe
	glVertex3f(0, 2, 2);
	glVertex3f(0, 2, 6);
	glVertex3f(0, 1, 5);
	glVertex3f(0, 1, 2);
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 5);
	glVertex3f(0, 0, 4);
	glVertex3f(0, 0, 1);
	glColor3f(glar, glag, glab - 0.2); // front glass
	glVertex3f(0, 2, 0);
	glVertex3f(0, 4, 2);
	glVertex3f(0, 1, 2);
	glVertex3f(0, 1, 0);
	glColor3f(armr, armg + 0.1, armb);
	glVertex3f(0, 4, 2);
	glVertex3f(0, 4, 6);
	glVertex3f(0, 2, 6);
	glVertex3f(0, 2, 2);
	//  End
	glEnd();
	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech 1, maroon stripped
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void drawMech_1(double x, double y, double z, double dx, double dy, double dz, double th) {

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

	mechFeet_1(1, 1, 3, 1, 1, 1, 0); // left foot
	mechFeet_1(5, 1 , 3, 1, 1, 1, 0); // right foot
	mechLeftLeg_1(1, 2, 4, 1, 1, 1, 0); // left leg
	mechRightLeg_1(4, 2, 4, 1, 1, 1, 0); // right leg
	mechTurrent_1(1, 7, 3, 1, 1, 1, 0); // left turrent
	mechTurrent_1(4, 7, 3, 1, 1, 1, 0); // right turrent
	mechBody_1(3, 4, 1, 1, 1, 1, 0); // body

	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech 2, blue stripped
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void drawMech_2(double x, double y, double z, double dx, double dy, double dz, double th) {

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

	mechFeet_1(1, 1, 3, 1, 1, 1, 0); // left foot
	mechFeet_1(5, 1 , 3, 1, 1, 1, 0); // right foot
	mechLeftLeg_1(1, 2, 4, 1, 1, 1, 0); // left leg
	mechRightLeg_1(4, 2, 4, 1, 1, 1, 0); // right leg
	mechTurrent_1(1, 7, 3, 1, 1, 1, 0); // left turrent
	mechTurrent_1(4, 7, 3, 1, 1, 1, 0); // right turrent
	mechBody_2(3, 4, 1, 1, 1, 1, 0); // body

	//  Undo transformations
	glPopMatrix();
}

/*
 *  Draw mech 2
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void drawMech_3(double x, double y, double z, double dx, double dy, double dz, double th) {

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

	mechFeet_2(1, 1, 3, 1, 1, 1, 0); // left foot
	mechFeet_2(5, 1 , 3, 1, 1, 1, 0); // right foot
	mechLeftLeg_2(1, 2, 4, 1, 1, 1, 0); // left leg
	mechRightLeg_2(4, 2, 4, 1, 1, 1, 0); // right leg
	mechTurrent_2(1, 7, 3, 1, 1, 1, 0); // left turrent
	mechTurrent_2(4, 7, 3, 1, 1, 1, 0); // right turrent
	mechBody_3(3, 4, 1, 1, 1, 1, 0); // body

	//  Undo transformations
	glPopMatrix();
}



/*
*  OpenGL (GLUT) calls this routine to display the scene
*/
void display() {
	int i, k;
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

	//TODO: INCLUDE DRAW MECH FUNCTION
	switch(viewMech){
		case 1:
			dim = 5;
			glPushMatrix();
				if(turn) glRotatef(spin, 0, 1, 0);
				drawMech_3(1, -1, 1, 0.3, 0.3, 0.3, 0); // small mechs
			glPopMatrix();
			break;
		case 2:
			dim = 7;
			glPushMatrix();
				if(turn) glRotatef(spin, 0, 1, 0);
				drawMech_1(2, -2, 2, 0.5, 0.5, 0.5, 0); // meds mech
			glPopMatrix();
			break;
		case 3:
			dim = 10;
			glPushMatrix();
				if(turn) glRotatef(spin, 0, 1, 0);
				drawMech_2(4, -4, 4, 1, 1, 1, 0); // really big mechs
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();
				if(turn) glRotatef(spin, 0, 1, 0);
				dim = 20;
				for(i = 0; i < 10; i += 2)
					for(k = 0; k < 12; k += 3)
						drawMech_3(i, 0, k, 0.3, 0.3, 0.3, 0); // small mechs
				for(i = 0; i < 21; i += 7)
					drawMech_1(10, 0, i - 3, 0.5, 0.5, 0.5, 270);
				for(i = 0; i < 14; i += 7)
					drawMech_2(-3, 0, i + 3, 1, 1, 1, 0); // really big mechs
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
	//  Display parameters
	glWindowPos2i(5,5);
	Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s \nSpin=%.1f",th,ph,dim,fov,mode?"Perpective":"Orthogonal",spin);
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
		case '3':
			viewMech = 3;
			break;
		case '4':
			glutIdleFunc(NULL);
			viewMech = 4;
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
 
void spinDisplay () {
	spin += 0.05;
	if (spin > 360.0) spin = spin - 360.0;
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
	glutCreateWindow("Jason Lubrano hw3");
	//  Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutIdleFunc(spinDisplay);
	glutKeyboardFunc(key);
	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();
}