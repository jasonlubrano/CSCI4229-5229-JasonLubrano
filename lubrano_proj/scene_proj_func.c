#include "jason_funcs.h"
#include "CSCIx229.h"

void grassfloor_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
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

void scene_proj(double x, double y, double z, double dx, double dy, double dz, double th){
	glPushMatrix();
		//  Offset, scale and rotate
		glTranslated(x, y, z);
		glRotated(ro, 0, 1, 0);
		glScaled(dx, dy, dz);
		grassfloor_proj(20, -1, -20, 1, 1, 1, 0);
	glPopMatrix();
}