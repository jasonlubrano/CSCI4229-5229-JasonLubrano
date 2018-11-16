/* Jason Lubrano
 * CSCI4229 - Graphics
 * Homework 6
 * Textures */
#include "CSCIx229.h"
int mode=0;       //  Texture mode
int ntex=0;       //  Cube faces
int axes=1;       //  Display axes
int th=-45;         //  Azimuth of view angle
int ph=-325;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=2;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=45.0;   //  Size of world
// Light values
int emission 	= 	0;  // Emission intensity (%)
float ambient   = 	0;  // Ambient intensity (%)
float diffuse   = 	100;  // Diffuse intensity (%)
int specular  	=   0;  // Specular intensity (%)
int shininess 	=   0;  // Shininess (power of two)
float shiny   	=   1;    // Shininess (value)
int zh        	= 	90;  // Light azimuth
float ylight  	= 	0;  // Elevation of light
unsigned int texture[11]; // Texture names

/*
 *  Draw the wall
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void skybox_hw6(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 120, ht = 50, dp = 120;
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	// this one gives issues, its reversed, change x, y cords
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[9]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[9]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[9]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[9]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[10]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(1,		0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(1,		1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[7]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(3, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(3, 	3); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	3); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw the wall
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void wall_hw6(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 9, ht = 8, dp = 1;
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[5]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[3]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[6]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw the wall
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void corner_hw6(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 1, ht = 8, dp = 1;
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);	
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw the wood floor
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void woodfloor_hw6(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 10, ht = 1, dp = 10;
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

static void grassfloor_hw6(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 10, ht = 1, dp = 10;
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/*
 *  Draw a fountain at (x,y,z) radius r thickness 2d
 *  The resolution is fixed at 36 slices (10 degrees each)
 */
static void fountain_hw6(double x, double y, double z, double r, double d, double th){
   int i,k;
   glEnable(GL_TEXTURE_2D);
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x, y ,z);
   glRotated(th, 1, 0, 0);
   glScaled(r, r, d);
   //  Head & Tail
   glColor3f(1, 1, 1);
   for (i=1;i>=-1;i-=2){
      (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[7]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
      glNormal3f(0, 0, i);
      glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5, 0.5);
      glVertex3f(0, 0, i);
      for (k = 0; k <= 360; k += 10){
         glTexCoord2f((0.5 * Cos(k) + 0.5), (0.5 * Sin(k) + 0.5));
         glVertex3f(i * Cos(k),	Sin(k), i);
      }
      glEnd();
   }
   //  Edge
   (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[8]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
   glColor3f(1.00, 0.77, 0.36);
   glBegin(GL_QUAD_STRIP);
   for (k = 0; k <= 360; k += 10) {
      glNormal3f(Cos(k),Sin(k),0);
      glTexCoord2f(0,	0.5*k);		glVertex3f(Cos(k),	Sin(k),	+1);
      glTexCoord2f(1,	0.5*k);		glVertex3f(Cos(k),	Sin(k),	-1);
   }
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}


static void scene_hw6(double x, double y, double z, double dx, double dy, double dz, double ro){
	glPushMatrix();

		//  Offset, scale and rotate
		glTranslated(x, y, z);
		glRotated(ro, 0, 1, 0);
		glScaled(dx, dy, dz);
		wall_hw6(-1, 8, -9, 1, 1, 1, 180);
		wall_hw6(9, 8, 1, 1, 1, 1, 90);
		corner_hw6(9, 8, -9, 1, 1, 1, 0);
		woodfloor_hw6(0, -1, 0, 1, 1, 1, 0);
		grassfloor_hw6(20, -1, 0, 1, 1, 1, 0);
		grassfloor_hw6(0, -1, -20, 1, 1, 1, 0);
		grassfloor_hw6(20, -1, -20, 1, 1, 1, 0);
		fountain_hw6(20, 1, -20, 9, 1, 90);
		fountain_hw6(20, 2, -20, 6, 1, 90);
		fountain_hw6(20, 3, -20, 3, 1, 90);
	glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(int th, int ph)
{
   double x = -Sin(th)*Cos(ph);
   double y =  Cos(th)*Cos(ph);
   double z =          Sin(ph);
   glNormal3d(x, y, z);
   glTexCoord2d(th/360.0, ph/180.0+0.5);
   glVertex3d(x, y, z);
}

/*
 *  Draw a ball body parts
 *     at (x,y,z)
 *     radius r
 */
static void ballbody_hw6(double x, double y, double z, double r){
	int th, ph;
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glScaled(r, r, r);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	//marble head
	//  White ball
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	//  Latitude bands
	glColor3f(1, 1, 1);
	for (ph = -90; ph < 90; ph += 5){
		glBegin(GL_QUAD_STRIP);
		for (th = 0; th <= 360; th += 5){
			Vertex(th, ph);
			Vertex(th, ph + 5);
		}
		glEnd();
	}
	//  Undo transofrmations
	glPopMatrix();
}

/*
 *  Draw the man, statue
 *     at (x,y,z)
 *     radius r
 */
static void man_hw6(double x, double y, double z, double dx, double dy, double dz, double ro){
	int i;
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(ro, 0, 1, 0);
	glScaled(dx, dy, dz);
	for(i = 2; i < 12; i += 4) ballbody_hw6(0, i, 0, 2);
	glPopMatrix();
}

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
	if (light) {
		//  Translate intensity to color vectors
		float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
		float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
		float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
		//  Light direction
		float Position[]  = {dim/2 * Cos(zh), ylight+dim/2, dim/2 * Sin(zh), 1};
		//  Draw light position as ball (still no lighting here)
		glColor3f(1, 1, 1);
		ball(Position[0], Position[1], Position[2], 0.1);
		//  OpenGL should normalize normal vectors
		glEnable(GL_NORMALIZE);
		//  Enable lighting
		glEnable(GL_LIGHTING);
		//  glColor sets ambient and diffuse color materials
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		//  Enable light 0
		-lEnable(GL_LIGHT0)=
		//  Set ambient, diffuse, specular components and position of light 0
		glLightfv(GL_LIGHT0,GL_AMBIENT , Ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE , Diffuse);
		glLightfv(GL_LIGHT0,GL_SPECULAR, Specular);
		glLightfv(GL_LIGHT0,GL_POSITION, Position);
	} else {
		glDisable(GL_LIGHTING);
	}


	//  Draw scene
	scene_hw6(-10, -5, 10, 1, 1, 1, 0);
	man_hw6(-10, -5, 10, 1, 1, 1, 0);
	skybox_hw6(0, 42, 0, 1, 1, 1, 0);
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
		Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
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
	if (key == GLUT_KEY_RIGHT) // ok
		th += 5;
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT) // ok
		th -= 5;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP) // ok
		ph += 5;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN) // ok
		ph -= 5;
	//  PageUp key - increase dim
	else if (key == GLUT_KEY_PAGE_DOWN) // ok
		dim += 0.1;
	//  PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_UP && dim>1) // ok
		dim -= 0.1;
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
	if (ch == 27) // ok
		exit(0);
	//  Reset view angle
	else if (ch == '0') // ok
		th = ph = 0;
	//  Toggle texture mode
	else if (ch == 'm' || ch == 'M') // ok
		mode = 1-mode;
	//  Toggle axes
	else if (ch == 'x' || ch == 'X') // ok
		axes = 1-axes;
	//  Toggle lighting
	else if (ch == 'l' || ch == 'L') // ok
		light = 1-light;
	//  Toggle textures mode
	else if (ch == 't') // ok
		ntex = 1-ntex;
	//  Light elevation
	else if (ch=='[') // ok
		ylight -= 0.1;
	else if (ch==']') // ok
		ylight += 0.1;
	//  Ambient level
	else if (ch=='a' && ambient>0) // ok
		ambient -= 5;
	else if (ch=='A' && ambient<100) // ok
		ambient += 5;
	//  Diffuse level
	else if (ch=='d' && diffuse>0)
		diffuse -= 5;
	else if (ch=='D' && diffuse<100)
		diffuse += 5;
	//  Specular level
	else if (ch=='s' && specular>0) // ok
		specular -= 5;
	else if (ch=='S' && specular<100) // ok
		specular += 5;
	//  Emission level
	else if (ch=='e' && emission>0) // ok
		emission -= 5;
	else if (ch=='E' && emission<100) // ok
		emission += 5;
	//  Shininess level
	else if (ch=='n' && shininess>-1) // ok
		shininess -= 1;
	else if (ch=='N' && shininess<7) // ok
		shininess += 1;
	//  Repitition
	else if (ch=='+')
		rep++;
	else if (ch=='-' && rep>1)
		rep--;
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
	texture[1] 	= 	LoadTexBMP("illusion.bmp"); // for statue
	texture[2] 	= 	LoadTexBMP("marble.bmp"); // for statue
	texture[3] 	= 	LoadTexBMP("wall.bmp"); // for inside
	texture[4] 	= 	LoadTexBMP("wood.bmp"); // for floor
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