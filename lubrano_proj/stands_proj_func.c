#include "jason_funcs.h"
#include "CSCIx229.h"

/*
 *  Draw the buttseat
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
 void buttseat_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 3., ht = 0.5, dp = 3.;
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
	//  Front
	// this one gives issues, its reversed, change x, y cords
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[12]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Back
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[12]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[12]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[12]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(1,		0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(1,		1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(5, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(5, 	5); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	5); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/*
 *  Draw the backseat
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
 void backseat_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 3., ht = 3., dp = 0.5;
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
	//  Front
	// this one gives issues, its reversed, change x, y cords
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[12]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Back
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[12]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[12]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[12]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(1,		0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(1,		1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(5, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(5, 	5); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	5); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/*
 *  Draw the legs
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
 void legseat_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 3., ht = 1.5, dp = 0.5;
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
	//  Front
	// this one gives issues, its reversed, change x, y cords
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Back
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(1,		0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(1,		1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[11]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(5, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(5, 	5); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	5); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw the ground beneath stands
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
 void belowseat_proj(double x, double y, double z, double dx, double dy, double dz, double th) {
	float wd = 3, ht = 0.5, dp = 6;
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
	//  Front
	// this one gives issues, its reversed, change x, y cords
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, +1);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0);		glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Back
	(!ntex) ? glBindTexture(GL_TEXTURE_2D, texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glEnd();
	//  Right
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(+1, 0, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(1, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(1, 	1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0, 	1); 	glVertex3f(+wd, +ht, +dp);
	glEnd();
	//  Left
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(1, 	0); 	glVertex3f(-wd, -ht, +dp);
	glTexCoord2f(1, 	1); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(0, 	1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Top
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[6]): glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, +1, 0);
	glTexCoord2f(0,		0); 	glVertex3f(-wd, +ht, +dp);
	glTexCoord2f(1,		0); 	glVertex3f(+wd, +ht, +dp);
	glTexCoord2f(1,		1); 	glVertex3f(+wd, +ht, -dp);
	glTexCoord2f(0,		1); 	glVertex3f(-wd, +ht, -dp);
	glEnd();
	//  Bottom
	(!ntex) ? glBindTexture(GL_TEXTURE_2D,texture[6]) : glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 	0); 	glVertex3f(-wd, -ht, -dp);
	glTexCoord2f(5, 	0); 	glVertex3f(+wd, -ht, -dp);
	glTexCoord2f(5, 	5); 	glVertex3f(+wd, -ht, +dp);
	glTexCoord2f(0, 	5); 	glVertex3f(-wd, -ht, +dp);
	glEnd();
	//  Undo transformations and textures
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void draw_stand0_proj(double x, double y, double z, double dx, double dy, double dz, double th){
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	buttseat_proj(0, 0, 0, 1, 1, 1, 0); 
	backseat_proj(0, 3, -2.5, 1, 1, 1, 0);
	legseat_proj(0, -2, -2.5, 1, 1, 1, 0);
	belowseat_proj(0, -4, 3, 10, 1, 1, 0);
	glPopMatrix();
}

void draw_stand1_proj(double x, double y, double z, double dx, double dy, double dz, double th){
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);
	int r1 = 100, g = 0, f = 0, r2 = 50;
	
	// bottom floor
	// endzone

	for(f = 0; f < 10; f+=2){
		for(g = 70; g <= 110; g += 5){
			draw_stand0_proj(r1*Cos(g), f+1, r1*Sin(g), 0.25, 0.25, 0.25, -g-90);
		}
		for(g = -110; g <= -70; g += 5){
			draw_stand0_proj(r1*Cos(g), f+1, r1*Sin(g), 0.25, 0.25, 0.25, -g-90);
		}
		r1 += 3;
	}
	
	r2=50;
	for(f = 0; f < 10; f+=2){
		for(g = 0; g <= 60; g += 5){
			draw_stand0_proj(-r2, f+1, g, 0.25, 0.25, 0.25, 90);
			draw_stand0_proj(-r2, f+1, -g, 0.25, 0.25, 0.25, 90);
			draw_stand0_proj(r2, f+1, g, 0.25, 0.25, 0.25, -90);
			draw_stand0_proj(r2, f+1, -g, 0.25, 0.25, 0.25, -90);
		}
		r2+=3;
	}
	
	r1=60;
	for(f = 20; f <= 30; f+=2){
		for(g = 0; g <= 180; g += 5){
			glPushMatrix();
			glTranslated(0, 0, +60);
			draw_stand0_proj(r1*Cos(g), f+1, r1*Sin(g), 0.25, 0.25, 0.25, -g-90);
			glPopMatrix();
		}
		// endzone
		for(g = 180; g <= 360; g += 5){
			glPushMatrix();
			glTranslated(0, 0, -60);
			draw_stand0_proj(r1*Cos(g), f+1, r1*Sin(g), 0.25, 0.25, 0.25, -g-90);
			glPopMatrix();
		}
		r1 += 3;
	}


	// endzone
	r2=60;
	for(f = 20; f <= 30; f+=2){
		for(g = 0; g <= 60; g += 5){
			draw_stand0_proj(-r2, f+1, g, 0.25, 0.25, 0.25, 90);
			draw_stand0_proj(-r2, f+1, -g, 0.25, 0.25, 0.25, 90);
			draw_stand0_proj(r2, f+1, g, 0.25, 0.25, 0.25, -90);
			draw_stand0_proj(r2, f+1, -g, 0.25, 0.25, 0.25, -90);
		}
		r2+=3;
	}

	r1=80;
	for(f = 40; f <= 60; f+=2){
		for(g = 0; g <= 180; g += 5){
			glPushMatrix();
			glTranslated(0, 0, +60);
			draw_stand0_proj(r1*Cos(g), f+1, r1*Sin(g), 0.25, 0.25, 0.25, -g-90);
			glPopMatrix();
		}
		// endzone
		for(g = 180; g <= 360; g += 5){
			glPushMatrix();
			glTranslated(0, 0, -60);
			draw_stand0_proj(r1*Cos(g), f+1, r1*Sin(g), 0.25, 0.25, 0.25, -g-90);
			glPopMatrix();
		}
		r1 += 3;
	}

	r2=80;
	for(f = 40; f <= 60; f+=2){
		for(g = 0; g <= 60; g += 5){
			draw_stand0_proj(-r2, f+1, g, 0.25, 0.25, 0.25, 90);
			draw_stand0_proj(-r2, f+1, -g, 0.25, 0.25, 0.25, 90);
			draw_stand0_proj(r2, f+1, g, 0.25, 0.25, 0.25, -90);
			draw_stand0_proj(r2, f+1, -g, 0.25, 0.25, 0.25, -90);
		}
		r2+=3;
	}
	
	

	glPopMatrix();
}