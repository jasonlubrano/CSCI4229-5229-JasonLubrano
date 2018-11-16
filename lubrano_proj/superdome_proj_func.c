#include "jason_funcs.h"
#include "CSCIx229.h"


int highshiny = 25;

/*
 *  Draw the edge of superdome at (x,y,z) radius r thickness 2d
 *  The resolution is fixed at 36 slices (10 degrees each)
 */
void superdome_proj(double x, double y, double z, double r, double d, double th){
   int i,k;
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,highshiny);
   glEnable(GL_TEXTURE_2D);
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x, y ,z);
   glRotated(th, 1, 0, 0);
   glScaled(r, r, d);
   //  Head & Tail
   glColor3f(1, 1, 1);
   //for (i=1;i>=-1;i-=2){
      i = 1;
      (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
      glNormal3f(0, 0, -i);
      glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5, 0.5);
      glVertex3f(0, 0, i);
      for (k = 0; k <= 360; k += 10){
         glTexCoord2f((0.5 * Cos(k) + 0.5), (0.5 * Sin(k) + 0.5));
         glVertex3f(i * Cos(k),	Sin(k), i);
      }
      glEnd();
   //}
   //  Edge
   (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[3]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
   glColor3f(1.00, 0.77, 0.36);
   glBegin(GL_QUAD_STRIP);
   for (k = 0; k <= 360; k += 10) {
      glNormal3f(Cos(k),Sin(k),0);
      glTexCoord2f(0,	0.2*k);		glVertex3f(Cos(k)*.90,	Sin(k)*.90,	0);
      glTexCoord2f(1,	0.2*k);		glVertex3f(Cos(k),	Sin(k),	-1);
   }
   glEnd();
   //  Edge
   (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[3]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
   glColor3f(1.00, 0.77, 0.36);
   glBegin(GL_QUAD_STRIP);
   for (k = 0; k <= 360; k += 10) {
      glNormal3f(Cos(k),Sin(k),0);
      glTexCoord2f(0,	0.2*k);		glVertex3f(Cos(k),	Sin(k),	1);
      glTexCoord2f(1,	0.2*k);		glVertex3f(Cos(k)*.90,	Sin(k)*.90,	0);
   }
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void bottomfloor_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 1, ht = 1, dp = 1;
	int trep = rep * 3;
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,highshiny);
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
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  interior
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(rep, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(rep, 	rep); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	rep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(trep, 	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(trep, 	trep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	trep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[2]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(trep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(trep, 	trep); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	trep); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void floor0_proj(double x, double y, double z, double r, double d, double th){
   int i,k;
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,highshiny);
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
      (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
      glNormal3f(0, 0, -i);
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
   (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
   glColor3f(1.00, 0.77, 0.36);
   glBegin(GL_QUAD_STRIP);
   for (k = 0; k <= 360; k += 10) {
      glNormal3f(Cos(k),Sin(k),0);
      glTexCoord2f(0,	0.2*k);		glVertex3f(Cos(k)*.90,	Sin(k)*.90,	0);
      glTexCoord2f(1,	0.2*k);		glVertex3f(Cos(k),	Sin(k),	-1);
   }
   glEnd();
   //  Edge
   (!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
   glColor3f(1.00, 0.77, 0.36);
   glBegin(GL_QUAD_STRIP);
   for (k = 0; k <= 360; k += 10) {
      glNormal3f(Cos(k),Sin(k),0);
      glTexCoord2f(0,	0.2*k);		glVertex3f(Cos(k),	Sin(k),	1);
      glTexCoord2f(1,	0.2*k);		glVertex3f(Cos(k)*.90,	Sin(k)*.90,	0);
   }
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}


void field_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 1, ht = 1, dp = 1;
	int trep = rep;
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
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[4]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(trep, 	0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(trep, 	trep); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	trep); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[0]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(trep, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(trep, 	trep); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	trep); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw vertex in polar coordinates
 */
void Vertex(int th,int ph)
{
   double x = -Sin(th)*Cos(ph);
   double y =  Cos(th)*Cos(ph);
   double z =          Sin(ph);
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}


void topdome_proj(double x, double y, double z, double r, double th){
	int th2, ph;
	glPushMatrix();
	//  Offset, scale and rotate
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
	glTranslated(x, y, z);
	glRotated(th, 0, 0, 1);
	glScaled(r, r, r);
	//  Set texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[5]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	//  Latitude bands
	glColor3f(1,1,1);
	for (ph =- 90; ph < 90; ph += 5){
		glBegin(GL_QUAD_STRIP);
		for (th2 = 0; th2 <= 180; th2 += 5){
			Vertex(th2, ph);
			Vertex(th2, ph+5);
		}
		glEnd();
	}
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void draw_superdome_proj(double x, double y, double z, double dx, double dy, double dz, double th){
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	superdome_proj(0, 4.1, 0, 50, 10, 90);
	bottomfloor_proj(0, -10, 0, 52, 4, 52, 90);
	field_proj(0, -5, 0, 22.5, 1, 10, 90);
	topdome_proj(0, 14, 0, 50, -90);
	floor0_proj(0, -5.001, 0, 49, 1, 90);
	glPopMatrix();
}