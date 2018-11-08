/* Jason Lubrano
 * CSCI4229 - Graphics
 * final project */
#include "CSCIx229.h"
#include "jason_funcs.h"

int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=45;         //  Azimuth of view angle
int ph=30;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=68.0;   //  Size of world
// Light values
int ntex = 0;
int rep = 1;
int one       =   1;  // Unit value
int distance  =   10;  // Light distance
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
int vpi = 1; // view for the piston; 1 for full length, 0 for one of them

unsigned int texture[11]; // Texture names

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x, double y, double z, double r){
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glScaled(r, r, r);
	glColor3f(1, 1, 1);
	glutSolidSphere(1.0, 16, 16);
	//  Undo transofrmations
	glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display(){
	//  Length of axes
	const double len=2.0;
	//  Eye position
	double Ex = -2*dim*Sin(th)*Cos(ph);
	double Ey = +2*dim        *Sin(ph);
	double Ez = +2*dim*Cos(th)*Cos(ph);
	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Set perspective
	glLoadIdentity();
	gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
	//  Light switch
	if (light)	{
		//  Translate intensity to color vectors
		float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
		float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
		float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
		//  Light position
		float Pos1[]  = {distance*Cos(zh), ylight, distance*Sin(zh), 0.5};
		//  Draw light position as ball (still no lighting here)
		glColor3f(1, 0, 0);
		ball(Pos1[0], Pos1[1], Pos1[2], 0.25);
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
		glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
		glLightfv(GL_LIGHT0, GL_POSITION, Pos1); 
	} else
		glDisable(GL_LIGHTING);


	//  Draw scene
	skybox_proj(0, 60, 0, 1, 1, 1, 0);
	draw_superdome_proj(0, 0, 0, 1, 1, 1, 0);








	//  Draw axes - no lighting from here on
	glDisable(GL_LIGHTING);
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
	Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"On":"Off",mode?"Replace":"Modulate");
	if (light) {
		glWindowPos2i(5,25);
		Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f", 
			ambient, diffuse, specular, emission, shiny);
	}
	//  Render the scene and make it visible
	ErrCheck("display");
	glFlush();
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle(){
	//  Elapsed time in seconds
	double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
	zh = fmod(90*t,360.0);
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y){
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT) th += 5;
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT) th -= 5;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP) ph += 5;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN) ph -= 5;
	//  PageUp key - increase dim
	else if (key == GLUT_KEY_PAGE_DOWN) dim += 0.1;
	//  PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_UP && dim>1) dim -= 0.1;
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Update projection
	Project(45,asp,dim);
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y){
	//  Exit on ESC
	if (ch == 27) exit(0);
	//  Reset view angle
	else if (ch == '0') th = ph = 0;
	//  Toggle texture mode
	else if (ch == 'm' || ch == 'M') mode = 1-mode;
	//  Toggle axes
	else if (ch == 'x' || ch == 'X') axes = 1-axes;
	//  Toggle lighting
	else if (ch == 'l' || ch == 'L') light = 1-light;
	//  Toggle textures mode
	else if (ch == 't') ntex = 1-ntex;
	//  Light elevation
	else if (ch=='[') ylight -= 0.1;
	else if (ch==']') ylight += 0.1;
	//  Ambient level
	else if (ch=='a' && ambient>0) ambient -= 5;
	else if (ch=='A' && ambient<100) ambient += 5;
	//  Diffuse level
	else if (ch=='d' && diffuse>0) diffuse -= 5;
	else if (ch=='D' && diffuse<100) diffuse += 5;
	//  Specular level
	else if (ch=='s' && specular>0) specular -= 5;
	else if (ch=='S' && specular<100) specular += 5;
	//  Emission level
	else if (ch=='e' && emission>0) emission -= 5;
	else if (ch=='E' && emission<100) emission += 5;
	//  Shininess level
	else if (ch=='n' && shininess>-1) shininess -= 1;
	else if (ch=='N' && shininess<7) shininess += 1;
	//  Repitition
	else if (ch=='+') rep++;
	else if (ch=='-' && rep>1) rep--;
	// easy dim
	else if (ch == 'k') dim = 10;
	else if (ch == 'K') dim = 68.0;
	//  Translate shininess power to value (-1 => 0)
	shiny = shininess<0 ? 0 : pow(2.0,shininess);
	//  Reproject
	Project(45,asp,dim);
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height){
	//  Ratio of the width to the height of the window
	asp = (height >0) ? (double)width/height : 1;
	//  Set the viewport to the entire window
	glViewport(0,0, width,height);
	//  Set projection
	Project(45,asp,dim);
}




int main(int argc,char* argv[]) {
	//  Initialize GLUT
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1000,600);
	glutCreateWindow("Jason Lubrano, hw6");

    glDepthFunc(GL_LEQUAL);    
    glShadeModel (GL_SMOOTH);
	//  Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	//  Load textures
	texture[0] 	= 	LoadTexBMP("grass.bmp"); // for outside
	texture[1] 	= 	LoadTexBMP("illusion.bmp"); // for illusion
	texture[2] 	= 	LoadTexBMP("concrete_face.bmp"); // for top and bottom of dome
	texture[3] 	= 	LoadTexBMP("concrete_edge.bmp"); // for edge of dome
	texture[4] 	= 	LoadTexBMP("field.bmp"); // for field
	texture[5] 	= 	LoadTexBMP("wallvine.bmp"); // for outside wall
	texture[6] 	= 	LoadTexBMP("insulation.bmp"); // for side of wall
	texture[7] 	= 	LoadTexBMP("water.bmp"); // for water
	texture[8] 	= 	LoadTexBMP("edge.bmp"); // for edge of fountain
	texture[9] 	= 	LoadTexBMP("swamp.bmp"); // for outside box
	texture[10]	= 	LoadTexBMP("look.bmp"); // sky
	//  Pass control to GLUT so it can interact with the user
	ErrCheck("init");
	glutMainLoop();
	return 0;
}