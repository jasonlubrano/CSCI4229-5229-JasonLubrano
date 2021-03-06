#include "jason_funcs.h"
#include "CSCIx229.h"

/* draw a shack and everything about it */

/*
 *  Draw the wall
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void bldg_apt1_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 25, ht = 40, dp = 25;
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
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[20]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[20]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[20]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[20]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[23]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[20]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
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

void bldg_apt2_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 30, ht = 30, dp = 30;
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
	glColor3f(1.0, 1.0, 1.0);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[21]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[21]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[21]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[21]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[23]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[21]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
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

void bldg_apt3_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 15, ht = 45, dp = 15;
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
	glColor3f(1.0, 1.0, 1.0);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[22]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[22]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[22]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[22]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[23]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[22]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
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

void bldg_off1_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 20, ht = 75, dp = 20;
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
	glColor3f(1.0, 1.0, 1.0);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[16]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[16]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[16]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[16]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[23]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[16]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
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

void bldg_off2_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 20, ht = 80, dp = 20;
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
	glColor3f(1.0, 1.0, 1.0);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[17]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[17]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[17]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[17]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[23]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[17]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
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

void bldg_off3_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 30, ht = 90, dp = 30;
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
	glColor3f(1.0, 1.0, 1.0);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[23]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
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

void bldg_off4_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 25, ht = 40, dp = 25;
	//  Set speular color to white
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
	glColor3f(1.0, 1.0, 1.0);
	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//  exterior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[19]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[19]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[19]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[19]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[23]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep,	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep,	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[19]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
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
void fountain_proj(double x, double y, double z, double r, double d, double th){
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

void draw_fountain_proj(double x, double y, double z, double r, double d, double th){
   	//  Save transformation
   	glPushMatrix();
   	//  Offset and scale
   	glTranslated(x, y ,z);
   	glRotated(th, 1, 0, 0);
  	glScaled(r, r, d);
	fountain_proj(0, 1, 0, 9, 1, 90);
	fountain_proj(0, 2, 0, 6, 1, 90);
	fountain_proj(0, 3, 0, 3, 1, 90);
	glPopMatrix();
}


void mississippi_river_proj(double x, double y, double z, double dx, double dy, double dz, double th){
	int wd = 1000, ht = 1, dp = 200, trep = 4;
	glPushMatrix();
   	// zOffset and scale
   	glTranslated(x, y ,z);
   	glRotated(th, 0, 1, 0);
  	glScaled(dx, dy, dz);
  	glColor3f(0.0, 0.80, 0.80);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[7]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(trep, 	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(trep, 	trep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	trep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	glPopMatrix();
}



void draw_road_proj(double x, double y, double z, double ds, double th){
	int wd = 500, ht = 1, dp = 50, trep=8;
	glPushMatrix();
   	// zOffset and scale
   	glTranslated(x, y ,z);
   	glRotated(th, 0, 1, 0);
  	glScaled(ds, ds, ds);
  	glColor3f(0.50, 0.50, 0.50);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[25]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(trep, 	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(trep, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	glPopMatrix();
}

void draw_roads_proj(double x, double y, double z, double ds, double th){
	glPushMatrix();
   	// zOffset and scale
   	glTranslated(x, y ,z);
   	glRotated(th, 0, 1, 0);
  	glScaled(ds, ds, ds);
	draw_road_proj(0, -10, 0, 1, 0);
	draw_road_proj(0, -10, 240, 1, 0);
	draw_road_proj(0, -10, -240, 1, 0);
	draw_road_proj(0, -9.8, 480, 1, 0);
	draw_road_proj(0, -9.8, -480, 1, 0);
	draw_road_proj(0, -9.9, 0, 1, 90);
	draw_road_proj(240, -9.9, 0, 1, 90);
	draw_road_proj(-240, -9.9, 0, 1, 90);
	draw_road_proj(-480, -9.9, 0, 1, 90);
	draw_road_proj(480, -9.9, 0, 1, 90);
	glPopMatrix();
}
/*
 * creating the ferry
 * I drew a schematic for it labling points
 */
void draw_ferry_proj(double x, double y, double z, double ds, double th){
	/* create arrays so it helps with the cad drawing I did
	-----------	0		1		2		3		4		5	*/
	int xs[] = {0, 		10, 	30, 	40, 	60, 	70	};
	int ys[] = {0, 		20, 	30, 	40 					};
	int zs[] = {0, 		5, 		10, 	20, 	25, 	30	};
	glPushMatrix();
	// zOffset and scale
	glTranslated(x, y ,z);
	glRotated(th, 0, 1, 0);
	glScaled(ds, ds, ds);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
	//star board
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[1], zs[0]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[1], ys[0], zs[2]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[4], ys[0], zs[2]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[5], ys[1], zs[0]); // top left
	glEnd();
	// portside
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[1], zs[5]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[1], ys[0], zs[3]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[4], ys[0], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[5], ys[1], zs[5]); // top left
	glEnd();
	// bow
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[5], ys[1], zs[0]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[4], ys[0], zs[2]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[4], ys[0], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[5], ys[1], zs[5]); // top left
	glEnd();
	// stern
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[1], zs[0]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[1], ys[0], zs[2]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[1], ys[0], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[0], ys[1], zs[5]); // top left
	glEnd();
	//undercarriage
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[1], ys[0], zs[2]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[4], ys[0], zs[2]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[4], ys[0], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[1], ys[0], zs[3]); // top left
	glEnd();
	//deck
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[24]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[1], zs[0]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[5], ys[1], zs[0]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[5], ys[1], zs[5]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[0], ys[1], zs[5]); // top left
	glEnd();
	

	//cabin
	//starboard
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[2], zs[1]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[0], ys[1], zs[1]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[1], zs[1]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[3], ys[2], zs[1]); // top left
	glEnd();
	//portside
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[2], zs[4]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[0], ys[1], zs[4]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[1], zs[4]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[3], ys[2], zs[4]); // top left
	glEnd();
	//stern
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[2], zs[1]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[0], ys[1], zs[1]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[0], ys[1], zs[4]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[0], ys[2], zs[4]); // top left
	glEnd();
	//bow
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[3], ys[2], zs[1]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[3], ys[1], zs[1]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[1], zs[4]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[3], ys[2], zs[4]); // top left
	glEnd();
	//deck
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[24]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[0], ys[2], zs[1]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[3], ys[2], zs[1]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[2], zs[4]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[0], ys[2], zs[4]); // top left
	glEnd();
	//top floor
	//starboard
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[2], ys[3], zs[2]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[2], ys[2], zs[2]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[2], zs[2]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[3], ys[3], zs[2]); // top left
	glEnd();
	// portside
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[2], ys[3], zs[3]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[2], ys[2], zs[3]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[2], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[3], ys[3], zs[3]); // top left
	glEnd();
	// bow
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[3], ys[3], zs[2]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[3], ys[2], zs[2]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[2], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[3], ys[3], zs[3]); // top left
	glEnd();
	// stern
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[18]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[2], ys[3], zs[2]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[2], ys[2], zs[2]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[2], ys[2], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[2], ys[3], zs[3]); // top left
	glEnd();
	// roof
	glColor3f(1.0, 1.0, 1.0);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[24]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(xs[2], ys[3], zs[2]); // top right
	glTexCoord2f(rep, 	0); 	glVertex3f(xs[2], ys[3], zs[3]); // bottom right
	glTexCoord2f(rep, 	rep); 	glVertex3f(xs[3], ys[3], zs[3]); // bottom left
	glTexCoord2f(0, 	rep); 	glVertex3f(xs[3], ys[3], zs[2]); // top left
	glEnd();


	glPopMatrix();
}




void draw_scene_proj(double x, double y, double z, double dx, double dy, double dz, double ro){
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(ro, 0, 1, 0);
	glScaled(dx, dy, dz);

	draw_fountain_proj(80, -30, 0, 2, 2, 0);
	
	bldg_off1_proj(80, 0, 80, 1, 1, 1, 0);
	bldg_off2_proj(80, 0, 160, 1, 1, 1, 0);
	bldg_off3_proj(80, 0, 320, 1, 1, 1, 0);
	bldg_off4_proj(80, 0, 400, 1, 1, 1, 0);
	bldg_apt1_proj(160, 0, 80, 1, 1, 1, 0);
	bldg_apt2_proj(160, 0, 160, 1, 1, 1, 0);
	bldg_apt3_proj(160, 0, 320, 1, 1, 1, 0);
	bldg_off1_proj(160, 0, 400, 1, 1, 1, 0);
	bldg_off2_proj(320, 0, 80, 1, 1, 1, 0);
	bldg_off3_proj(320, 0, 160, 1, 1, 1, 0);
	bldg_off4_proj(320, 0, 320, 1, 1, 1, 0);
	bldg_apt1_proj(320, 0, 400, 1, 1, 1, 0);


	bldg_off3_proj(80, 0, -80, 1, 1, 1, 0);
	bldg_off4_proj(80, 0, -160, 1, 1, 1, 0);
	bldg_apt1_proj(80, 0, -320, 1, 1, 1, 0);
	bldg_apt2_proj(80, 0, -400, 1, 1, 1, 0);
	bldg_apt3_proj(160, 0, -80, 1, 1, 1, 0);
	bldg_off1_proj(160, 0, -160, 1, 1, 1, 0);
	bldg_off2_proj(160, 0, -320, 1, 1, 1, 0);
	bldg_off3_proj(160, 0, -400, 1, 1, 1, 0);
	bldg_off4_proj(320, 0, -80, 1, 1, 1, 0);
	bldg_apt1_proj(320, 0, -160, 1, 1, 1, 0);
	bldg_apt2_proj(320, 0, -320, 1, 1, 1, 0);
	bldg_apt3_proj(320, 0, -400, 1, 1, 1, 0);

	
	bldg_apt1_proj(-80, 0, 80, 1, 1, 1, 0);
	bldg_apt2_proj(-80, 0, 160, 1, 1, 1, 0);
	bldg_apt3_proj(-80, 0, 320, 1, 1, 1, 0);
	bldg_off1_proj(-80, 0, 400, 1, 1, 1, 0);
	bldg_off2_proj(-160, 0, 80, 1, 1, 1, 0);
	bldg_off3_proj(-160, 0, 160, 1, 1, 1, 0);
	bldg_off4_proj(-160, 0, 320, 1, 1, 1, 0);
	bldg_apt1_proj(-160, 0, 400, 1, 1, 1, 0);
	bldg_apt2_proj(-320, 0, 80, 1, 1, 1, 0);
	bldg_apt3_proj(-320, 0, 160, 1, 1, 1, 0);
	bldg_off1_proj(-320, 0, 320, 1, 1, 1, 0);


	bldg_apt3_proj(-80, 0, -80, 1, 1, 1, 0);
	bldg_off1_proj(-80, 0, -160, 1, 1, 1, 0);
	bldg_off2_proj(-80, 0, -320, 1, 1, 1, 0);
	bldg_off3_proj(-80, 0, -400, 1, 1, 1, 0);
	bldg_off4_proj(-160, 0, -80, 1, 1, 1, 0);
	bldg_apt1_proj(-160, 0, -160, 1, 1, 1, 0);
	bldg_apt2_proj(-160, 0, -320, 1, 1, 1, 0);
	bldg_apt3_proj(-160, 0, -400, 1, 1, 1, 0);
	bldg_off1_proj(-320, 0, -80, 1, 1, 1, 0);
	bldg_off2_proj(-320, 0, -160, 1, 1, 1, 0);
	bldg_off3_proj(-320, 0, -320, 1, 1, 1, 0);
	bldg_off4_proj(-320, 0, -400, 1, 1, 1, 0);

	glPopMatrix();
}