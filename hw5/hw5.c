/* Jason Lubrano hw5 
* Demonstrate lighting
*/
#include "CSCIx229.h"

int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=25.0;   //  Size of world
// Light values
int one       =   1;  // Unit value
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
double bnc = 0;
int pis = 1;
int spin = 0;


/*
*  Draw a cube
*     at (x,y,z)
*     dimensions (dx,dy,dz)
*     rotated th about the y axis
*/
static void plate_hw5(double x, double y, double z, double dx, double dy, double dz, double roll, double pitch, double yaw){
	//TO DO : draw the plate, top and bottom
	int i, j, k;
	float rad = 14, len = 1; // radius of the plate, length of the plate
	glPushMatrix();
		glTranslated(x, y, z);
		glRotated(roll, 0, 0, 1); // roll
		glRotated(yaw, 0, 1, 0); // yaw
		glRotated(pitch, 1, 0, 0); // pitch
		glScaled(dx, dy, dz);
		glBegin(GL_QUAD_STRIP);
			for (j = 0; j <= 360; j += DEF_D) {
				glColor3f(0.0, 0.0, 1.0);
				glVertex3f(rad*Cos(j), +len, rad*Sin(j));
				glColor3f(0.0, 1.0, 0.0);
				glVertex3f(rad*Cos(j), -len, rad*Sin(j));
			}
		glEnd();

		/* top and bottom circles */
		/* reuse the currentTexture on top and bottom) */
		for (i = len; i >= -len; i -= 1) {
			glBegin(GL_TRIANGLE_FAN);
				glColor3f(0.0, 1.0, 1.0);
				glVertex3f(0, len*i, 0);
				for (k = 0; k <= 360; k += DEF_D) {
					glColor3f(1.0, 0.0, 0.0);
					glVertex3f(rad*i*Cos(k), len*i, rad*Sin(k));
				}
			glEnd();
		}
	glPopMatrix();
}


static void bottomLeg_hw5(double x, double y, double z, double dx, double dy, double dz, double roll, double pitch, double yaw){
   //TO DO : draw the bottom part of the hydrolic leg
	int i, j, k;
	float rad = 0.5, len = 6; // radius of the plate, length of the plate
	glPushMatrix();
		glTranslated(x, y, z);
		glRotated(roll, 0, 0, 1); // roll
		glRotated(yaw, 0, 1, 0); // yaw
		glRotated(pitch, 1, 0, 0); // pitch
		glScaled(dx, dy, dz);
		glBegin(GL_QUAD_STRIP);
			for (j = 0; j <= 360; j += DEF_D) {
				glColor3f(1.0, 0.0, 1.0);
				glVertex3f(rad*Cos(j), +len, rad*Sin(j));
				glColor3f(1.0, 1.0, 0.0);
				glVertex3f(rad*Cos(j), -len, rad*Sin(j));
			}
		glEnd();

		/* top and bottom circles */
		/* reuse the currentTexture on top and bottom) */
		for (i = 1; i >= -1; i -= 1) {
			glBegin(GL_TRIANGLE_FAN);
				glColor3f(0.0, 0.0, 1.0);
				glVertex3f(0, len*i, 0);
				for (k = 0; k <= 360; k += DEF_D) {
					glColor3f(0.0, 1.0, 0.0);
					glVertex3f(rad*i*Cos(k), len*i, rad*Sin(k));
				}
			glEnd();
		}
	glPopMatrix();
}

static void upperLeg_hw5(double x, double y, double z, double dx, double dy, double dz, double roll, double pitch, double yaw){
	//TO DO : draw the upper part of the hydrolic leg
	int i, j, k;
	float rad = 0.4, len = 6; // radius of the plate, length of the plate
	glPushMatrix();
		glTranslated(x, y, z);
		glRotated(roll, 0, 0, 1); // roll
		glRotated(yaw, 0, 1, 0); // yaw
		glRotated(pitch, 1, 0, 0); // pitch		glScaled(dx, dy, dz);
		glBegin(GL_QUAD_STRIP);
			for (j = 0; j <= 360; j += DEF_D) {
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(rad*Cos(j), +len, rad*Sin(j));
				glColor3f(0.0, 0.0, 1.0);
				glVertex3f(rad*Cos(j), -len, rad*Sin(j));
			}
		glEnd();

		/* top and bottom circles */
		/* reuse the currentTexture on top and bottom) */
		for (i = 1; i >= -1; i -= 1) {
			glBegin(GL_TRIANGLE_FAN);
				glColor3f(0.0, 1.0, 0.0);
				glVertex3f(0, len*i, 0);
				for (k = 0; k <= 360; k += DEF_D) {
					glColor3f(0.0, 1.0, 1.0);
					glVertex3f(rad*i*Cos(k), len*i, rad*Sin(k));
				}
			glEnd();
		}
	glPopMatrix();
}


/*
*  GLUT calls this routine when the window is resized
*/
void idle(){
	//  Elapsed time in seconds
	double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	zh = fmod(90*t,360.0);
	if(pis){
		spin += 2;
		if(spin > 360.0) spin = spin - 360.0;
		bnc = 2.5*Cos(spin) - 2.5*Sin(spin);
	}

	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

static void leg_hw5(double x, double y, double z, double dx, double dy, double dz, double roll, double pitch, double yaw){
	glPushMatrix();
		glTranslated(x, y, z);
		glRotated(roll, 0, 0, 1); // roll
		glRotated(yaw, 0, 1, 0); // yaw
		glRotated(pitch, 1, 0, 0); // pitch
		glScaled(dx, dy, dz);
		bottomLeg_hw5(0, -6, 0, 1, 1, 1, 0, 0, 0);
		upperLeg_hw5(0, +2 + bnc, 0, 1, 1, 1, 0, 0, 0);
	glPopMatrix();
}

static void hydrolic_hw5(double x, double y, double z, double dx, double dy, double dz, double roll, double pitch, double yaw){
	plate_hw5(0, +8.5+bnc, 0, 0.5, 0.5, 0.5, 0, 0, 0); //TOP
	leg_hw5(5, 0, 0, 1, 1, 1, 0, 0, 0);
	leg_hw5(-5*Sin(30), 0, -5*Cos(30), 1, 1, 1, 0, 0, 0);
	leg_hw5(-5*Sin(30), 0, 5*Cos(30), 1, 1, 1, 0, 0, 0);
	plate_hw5(0, -12.5, 0, 0.5, 0.5, 0.5, 0, 0, 0); // BASE DOES
}

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x, double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph = -90; ph < 90; ph += inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th = 0; th <= 360; th += 2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

/*
*  OpenGL (GLUT) calls this routine to display the scene
*/
void display(){
	const double len=2.0;  //  Length of axes
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

	//  Flat or smooth shading
	glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

	//  Light switch
	if (light)	{
		//  Translate intensity to color vectors
		float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
		float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
		float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
		//  Light position
		float Position[]  = {distance*Cos(zh), ylight, distance*Sin(zh), 0.1};
		//  Draw light position as ball (still no lighting here)
		glColor3f(1,1,1);
		ball(Position[0],Position[1],Position[2] , 0.05);
		//  OpenGL should normalize normal vectors
		glEnable(GL_NORMALIZE);
		//  Enable lighting
		glEnable(GL_LIGHTING);
		//  Location of viewer for specular calculations
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
		//  glColor sets ambient and diffuse color materials
		glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		//  Enable light 0
		glEnable(GL_LIGHT0);
		//  Set ambient, diffuse, specular components and position of light 0
		glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
		glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
		glLightfv(GL_LIGHT0,GL_POSITION,Position);
	} else
		glDisable(GL_LIGHTING);

	/* scene goes here */
	/* scene goes here */
	/* scene goes here */
	/* scene goes here */
	/* scene goes here */
	hydrolic_hw5(0, 0, 0, 1, 1, 1, 0, 0, 0);
	//leg_hw5(0, 0, 0, 1, 1, 1, th);

	//  Draw axes - no lighting from here on
	glDisable(GL_LIGHTING);
	glColor3f(1,1,1);
	if (axes) {
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
	Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
	th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
	if (light) {
		glWindowPos2i(5,45);
		Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
		glWindowPos2i(5,25);
		Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
	}

	//  Render the scene and make it visible
	ErrCheck("display");
	glFlush();
	glutSwapBuffers();
}

/*
*  GLUT calls this routine when an arrow key is pressed
*/
void special(int key,int x,int y)
{
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
else if (key == GLUT_KEY_PAGE_DOWN)
dim += 0.1;
//  PageDown key - decrease dim
else if (key == GLUT_KEY_PAGE_UP && dim>1)
dim -= 0.1;
//  Smooth color model
else if (key == GLUT_KEY_F1)
smooth = 1-smooth;
//  Local Viewer
else if (key == GLUT_KEY_F2)
local = 1-local;
else if (key == GLUT_KEY_F3)
distance = (distance==1) ? 5 : 1;
//  Toggle ball increment
else if (key == GLUT_KEY_F8)
inc = (inc==10)?3:10;
//  Flip sign
else if (key == GLUT_KEY_F9)
one = -one;
//  Keep angles to +/-360 degrees
th %= 360;
ph %= 360;
//  Update projection
Project(mode?fov:0,asp,dim);
//  Tell GLUT it is necessary to redisplay the scene
glutPostRedisplay();
}

/*
*  GLUT calls this routine when a key is pressed
*/
void key(unsigned char ch,int x,int y)
{
//  Exit on ESC
if (ch == 27)
exit(0);
//  Reset view angle
else if (ch == '0')
th = ph = 0;
//  Toggle axes
else if (ch == 'x' || ch == 'X')
axes = 1-axes;
//  Toggle lighting
else if (ch == 'l' || ch == 'L')
light = 1-light;
//  Switch projection mode
else if (ch == 'p' || ch == 'P')
mode = 1-mode;
//  Toggle light movement
else if (ch == 'm' || ch == 'M')
move = 1-move;
//  Move light
else if (ch == '<')
zh += 1;
else if (ch == '>')
zh -= 1;
//  Change field of view angle
else if (ch == '-' && ch>1)
fov--;
else if (ch == '+' && ch<179)
fov++;
//  Light elevation
else if (ch=='[')
ylight -= 0.1;
else if (ch==']')
ylight += 0.1;
//  Ambient level
else if (ch=='a' && ambient>0)
ambient -= 5;
else if (ch=='A' && ambient<100)
ambient += 5;
//  Diffuse level
else if (ch=='d' && diffuse>0)
diffuse -= 5;
else if (ch=='D' && diffuse<100)
diffuse += 5;
//  Specular level
else if (ch=='s' && specular>0)
specular -= 5;
else if (ch=='S' && specular<100)
specular += 5;
//  Emission level
else if (ch=='e' && emission>0)
emission -= 5;
else if (ch=='E' && emission<100)
emission += 5;
//  Shininess level
else if (ch=='n' && shininess>-1)
shininess -= 1;
else if (ch=='N' && shininess<7)
shininess += 1;
//  Translate shininess power to value (-1 => 0)
shiny = shininess<0 ? 0 : pow(2.0,shininess);
//  Reproject
Project(mode?fov:0,asp,dim);
//  Animate if requested
glutIdleFunc(move?idle:NULL);
//  Tell GLUT it is necessary to redisplay the scene
glutPostRedisplay();
}

/*
*  GLUT calls this routine when the window is resized
*/
void reshape(int width,int height)
{
//  Ratio of the width to the height of the window
asp = (height>0) ? (double)width/height : 1;
//  Set the viewport to the entire window
glViewport(0,0, width,height);
//  Set projection
Project(mode?fov:0,asp,dim);
}

/*
*  Start up GLUT and tell it what to do
*/
int main(int argc,char* argv[])
{
//  Initialize GLUT
glutInit(&argc,argv);
//  Request double buffered, true color window with Z buffering at 600x600
glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
glutInitWindowSize(700,700);
glutCreateWindow("Jason Lubrano hw5");
//  Set callbacks
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutSpecialFunc(special);
glutKeyboardFunc(key);
glutIdleFunc(idle);
//  Pass control to GLUT so it can interact with the user
ErrCheck("init");
glutMainLoop();
return 0;
}
