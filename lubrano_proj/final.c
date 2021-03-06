/* Jason Lubrano
 * CSCI4229 - Graphics
 * final project */
#include "CSCIx229.h"
#include "jason_funcs.h"
//#include <irrKlang.h>


int axes=0;       //  Display axes
int mode=1;       //  Projection mode
int move=1;       //  Move light
int th=270;         //  Azimuth of view angle
int ph=30;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=100.0;   //  Size of world
// Light values
int ntex = 0;
int rep = 1;
int one       =   1;  // Unit value
int distance  =   80;  // Light distance
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
float ylight  =  20;  // Elevation of light
double bnc = 0;
int print = 0, pis = 1, spin = 0, win = 0;
int vpi = 1; // view for the piston; 1 for full length, 0 for one of them
int disp = 0; //fix the display for debugging purposes
int x_st=-650, y_st=-20, z_st=-650, ro_st=180; // start for the ferry to travel around the map


unsigned int texture[26]; // Texture names


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

	switch(disp){
		case 0:
			/*outside the city*/
			skybox_proj(0, 140, 0, 2, 2, 2, 0);
			draw_superdome_proj(0, 0, 0, 1, 1, 1, 0);
			draw_scene_proj(0, 20, 0, 1, 1, 1, 0);
			mississippi_river_proj(0, -10, 800, 1, 1, 1, 0);
			mississippi_river_proj(0, -10, -800, 1, 1, 1, 0);
			mississippi_river_proj(800, -10, 0, 1, 1, 1, 90);
			mississippi_river_proj(-800, -10, 0, 1, 1, 1, 90);
			draw_ferry_proj(x_st, y_st+bnc, z_st, 1, ro_st);
			draw_roads_proj(0, 0, 0, 1, 0);
			break;
		case 1:
			/* draw the inside of the superdome */
			draw_stand1_proj(0, -4, 0, 0.25, 0.25, 0.25, 0);
			draw_superdome_proj(0, 0, 0, 1, 1, 1, 0);
			break;
		case 2:
			draw_ferry_proj(x_st, y_st+bnc, z_st, 1, ro_st);
			skybox_proj(0, 140, 0, 2, 2, 2, 0);
			mississippi_river_proj(0, -10+0.1, 800, 1, 1, 1, 0);
			mississippi_river_proj(0, -10+0.1, -800, 1, 1, 1, 0);
			mississippi_river_proj(800, -10, 0, 1, 1, 1, 90);
			mississippi_river_proj(-800, -10, 0, 1, 1, 1, 90);
			break;
		case 3:
			draw_ferry_proj(0, 0, 0, 1, 0);
			break;
		case 4:
			draw_superdome_proj(0, 0, 0, 1, 1, 1, 0);
			break;
		case 5:
			draw_scene_proj(0, 0, 0, 1, 1, 1, 0);
			break;
		default: break;
	}

	if(win == 1){
		draw_firework1_proj(0, 250, 0, 40);
	} else if (win == 2){
		draw_firework2_proj(0, 250, 0, 40);
	} else if (win == 3){
		draw_firework3_proj(0, 250, 0, 40);
	}




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
	if(print){
		Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"On":"Off",mode?"Replace":"Modulate");
		if (light) {
			glWindowPos2i(5,25);
			Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f", 
				ambient, diffuse, specular, emission, shiny);
		}
		//  Render the scene and make it visible
	}
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
	if(pis){
		spin += 2;
		if(spin > 360.0) spin = spin - 360.0;
		bnc = 2.5*Cos(spin) - 2.5*Sin(spin);
	}

	//moving the ferry around the map
	if(z_st >= -650 && x_st == -650){
		ro_st=-90;z_st += 1;
	}
	if(z_st == 650 && x_st >= -650){
		ro_st=0; x_st+=1;
	}
	if(z_st <= 650 && x_st == 650){
		ro_st=90; z_st-=1;
	}
	if(z_st == -650 && x_st <= 650){
		ro_st=180; x_st-=1;
	}

	//z_pos -= 2;
	//z_pos -= 2;

	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y){
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT) th += 1;
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT) th -= 1;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP) ph += 1;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN) ph -= 1;
	//  PageUp key - increase dim
	else if (key == GLUT_KEY_PAGE_DOWN) dim += 1;
	//  PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_UP && dim>1) dim -= 1;
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
	//toggle display
	else if (ch == 'f') if(disp > 0){disp--;} else {disp = 5 - disp;}
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
	else if (ch=='p') print = 1-print;
	//  Repitition
	else if (ch=='+') rep++;
	else if (ch=='-' && rep>1) rep--;
	else if (ch == 'h')if(win>0){win--;} else {win = 3 - win;}
	// look inside of the superdome
	else if (ch == 'k'){disp=1; dim = 28.3; th = 270; ph = 30; distance = 2; mode = 0;
		ambient = 0; diffuse = 100; specular = 0; emission = 0;shininess = 7; ylight = 14;}
	// look outside at the superdome, drawn by itself
	else if (ch == 'K'){disp = 4; dim = 160.0; th = 0; ph = 20; distance = 50;}
	//draw the ferry stand alone
	else if (ch == 'i'){disp = 3; dim = 100; th = 0; ph = 20; distance = 700;}
	//look at the superdome from the ground floor
	else if (ch == 'I'){disp=1; dim = 5; th = 270; ph = 30; distance = 2; mode = 0; 
		ambient = 0; diffuse = 100; specular = 0; emission = 0;shininess = 7; ylight = 14;}
	//get a good view of the city
	else if (ch == 'o'){disp = 0; dim = 500; th = -90; ph = 15; distance = 50; mode = 0;
		ambient = bnc; diffuse = 100; specular = 0; emission = 0;shininess = 7; distance = 60; ylight = 220;}
	//view the skybox and the boat without any buildings
	else if (ch == 'u'){disp = 2; dim = 500; th = -90; ph = 15; distance = 50; mode = 0;
		ambient = bnc; diffuse = 100; specular = 25; emission = 0;shininess = 7; ylight = 30;}
	//  Translate shininess power to value (-1 => 0)
	shiny = shininess<0 ? 0 : pow(2.0,shininess);
	//  Reprojectmake
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









/* doing music */












/* end music */
	

int main(int argc,char* argv[]) {
	//  Initialize GLUT
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1000,600);
	glutCreateWindow("Jason Lubrano, Final Project");
	//alutLoadWAVFile("down_in_new_orleans.wav",&alFormatBuffer, (void **) &alBuffer,(unsigned int *)&alBufferLen, &alFreqBuffer, &alLoop);
	//PlaySound("down_in_new_orleans.wav",NULL, SND_SYNC);
	//sndPlaySound("down_in_new_orleans.wav",SND_ASYNC);
	//engine->play2D("down_in_new_orleans.wav", true);
	//PlaySound(TEXT("down_in_new_orleans.wav"), NULL, SND_FILENAME | SND_ASYNC);
    glDepthFunc(GL_LEQUAL);    
    glShadeModel (GL_SMOOTH);
	//  Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	//  Load textures

	//play();
	texture[0] 	= 	LoadTexBMP("grass.bmp"); // for outside
	texture[1] 	= 	LoadTexBMP("illusion.bmp"); // for illusion
	texture[2] 	= 	LoadTexBMP("concrete_face.bmp"); // for top and bottom of dome
	texture[3] 	= 	LoadTexBMP("concrete_edge.bmp"); // for edge of dome
	texture[4] 	= 	LoadTexBMP("field.bmp"); // for field
	texture[5] 	= 	LoadTexBMP("concrete_logo.bmp"); // for dome
	texture[6] 	= 	LoadTexBMP("floor.bmp"); // going to be black
	texture[7] 	= 	LoadTexBMP("water.bmp"); // for water
	texture[8] 	= 	LoadTexBMP("edge.bmp"); // for edge of fountain
	texture[9] 	= 	LoadTexBMP("swamp.bmp"); // for outside box
	texture[10]	= 	LoadTexBMP("look.bmp"); // sky
	texture[11] = 	LoadTexBMP("leather.bmp"); // leather for the seats
	texture[12] = 	LoadTexBMP("canvas.bmp"); // seating material
	texture[13] =	LoadTexBMP("td_drew.bmp"); // drew td jumbotron
	texture[14] =	LoadTexBMP("td_kamara.bmp"); // kamara td jumbotron
	texture[15] =	LoadTexBMP("td_whodat.bmp"); // whodat nation jumbotron
	texture[16] = 	LoadTexBMP("office1.bmp"); // office building
	texture[17] = 	LoadTexBMP("office2.bmp"); // office building
	texture[18] = 	LoadTexBMP("office3.bmp"); // office building
	texture[19] = 	LoadTexBMP("office4.bmp"); // office building
	texture[20] = 	LoadTexBMP("apt1.bmp"); // apartment building
	texture[21] = 	LoadTexBMP("apt2.bmp"); // apartment building
	texture[22] = 	LoadTexBMP("apt3.bmp"); // apartment building
	texture[23] = 	LoadTexBMP("wall.bmp"); // wall tx that is use for roof of building
	texture[24] = 	LoadTexBMP("wood.bmp"); // wood for the deck of the ferry
	texture[25] = 	LoadTexBMP("road.bmp"); // wood for the deck of the ferry
	//  Pass control to GLUT so it can interact with the user
	ErrCheck("init");
	glutMainLoop();
	return 0;
}