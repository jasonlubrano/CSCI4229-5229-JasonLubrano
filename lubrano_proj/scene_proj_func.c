#include "jason_funcs.h"
#include "CSCIx229.h"

/* draw a shack and everything about it */

/*
 *  Draw the wall
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void wall_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
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
void corner_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
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
void woodfloor_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
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


void draw_scene_proj(double x, double y, double z, double dx, double dy, double dz, double ro){
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(ro, 0, 1, 0);
	glScaled(dx, dy, dz);
	wall_proj(-1, 8, -9, 1, 1, 1, 180);
	wall_proj(9, 8, 1, 1, 1, 1, 90);
	corner_proj(9, 8, -9, 1, 1, 1, 0);
	woodfloor_proj(0, -1, 0, 1, 1, 1, 0);
	grassfloor_proj(20, -1, 0, 1, 1, 1, 0);
	grassfloor_proj(0, -1, -20, 1, 1, 1, 0);
	grassfloor_proj(20, -1, -20, 1, 1, 1, 0);
	fountain_proj(20, 1, -20, 9, 1, 90);
	fountain_proj(20, 2, -20, 6, 1, 90);
	fountain_proj(20, 3, -20, 3, 1, 90);
	glPopMatrix();
}