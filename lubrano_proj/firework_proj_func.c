#include "jason_funcs.h"
#include "CSCIx229.h"

#define NUM_FIREWORKS 3000
#define GRAVITY 0.0003

struct fw_struct {
	float x, y, z, veloc_x, veloc_y, veloc_z;
	unsigned lifetime;
} fireworks[NUM_FIREWORKS];


// Initialize the firework
void init_fireworks_proj(int pause){
	int i;

	//if(pause) usleep(200000 + rand() % 2000000);

	for(i=0;i<NUM_FIREWORKS;i++) {
		float velocity = (float)(rand() % 100)/5000.0;
		int angle = rand() % 360;
		fireworks[i].veloc_x = cos( (M_PI * angle/180.0) ) * velocity;
		fireworks[i].veloc_y = sin( (M_PI * angle/180.0) ) * velocity;
		fireworks[i].veloc_z = -cos((M_PI * angle/180.0) ) * velocity;
		fireworks[i].x = 0.0;
		fireworks[i].y = 0.0;
		fireworks[i].z = 0.0;
		fireworks[i].lifetime = rand() % 100;
	}
}

void draw_firework1_proj(double x, double y, double z, double ds){
	int i, active_fireworks=0;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And The Depth Buffer
	//gloadIdentity();       // Reset The View
	glPushMatrix();
   	// zOffset and scale
   	glTranslated(x, y ,z);
  	glScaled(ds, ds, ds);
	//glColor4f(1.0f, 1.0f, 0.3f, 0.0f);//yellow
	glColor3f(1.0f, 0.6f, 0.3f);//Orange
	glBegin(GL_POINTS);
	for(i=0;i<NUM_FIREWORKS;i++) {
		if(fireworks[i].lifetime) {
			active_fireworks++;
			fireworks[i].veloc_y -= GRAVITY;
			fireworks[i].x += fireworks[i].veloc_x;
			fireworks[i].y += fireworks[i].veloc_y;
			fireworks[i].z += fireworks[i].veloc_z;
			fireworks[i].lifetime--;

			glVertex3f( fireworks[i].x, fireworks[i].y, 0.0f); // draw pixel
			glVertex3f( 0.0f, fireworks[i].y, fireworks[i].z); // draw pixel
		}
	}
	glEnd();
	glPopMatrix();
	//glutSwapBuffers();

	if(!active_fireworks) init_fireworks_proj(1); // reset particles
}

void draw_firework2_proj(double x, double y, double z, double ds){
	int i, active_fireworks=0;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And The Depth Buffer
	//gloadIdentity();       // Reset The View
	glPushMatrix();
   	// zOffset and scale
   	glTranslated(x, y ,z);
  	glScaled(ds, ds, ds);
  	glColor4f(1.0f, 0.0f, 1.0f, 0.0f);//purple
	glBegin(GL_POINTS);
	for(i=0;i<NUM_FIREWORKS;i++) {
		if(fireworks[i].lifetime) {
			active_fireworks++;
			fireworks[i].veloc_y -= GRAVITY;
			fireworks[i].x += fireworks[i].veloc_x;
			fireworks[i].y += fireworks[i].veloc_y;
			fireworks[i].z += fireworks[i].veloc_z;
			fireworks[i].lifetime--;

			glVertex3f( fireworks[i].x, fireworks[i].y, 0.0f); // draw pixel
			glVertex3f( 0.0f, fireworks[i].y, fireworks[i].z); // draw pixel
		}
	}
	glEnd();
	glPopMatrix();
	//glutSwapBuffers();

	if(!active_fireworks) init_fireworks_proj(1); // reset particles
}


void draw_firework3_proj(double x, double y, double z, double ds){
	int i, active_fireworks=0;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And The Depth Buffer
	//gloadIdentity();       // Reset The View
	glPushMatrix();
   	// zOffset and scale
   	glTranslated(x, y ,z);
  	glScaled(ds, ds, ds);
	//glColor3f(1.0f, 0.10f, 0.85f);
		glColor3f(1.0f, 1.0f, 0.2f);
	glBegin(GL_POINTS);
	for(i=0;i<NUM_FIREWORKS;i++) {
		if(fireworks[i].lifetime) {
			active_fireworks++;
			fireworks[i].veloc_y -= GRAVITY;
			fireworks[i].x += fireworks[i].veloc_x;
			fireworks[i].y += fireworks[i].veloc_y;
			fireworks[i].z += fireworks[i].veloc_z;
			fireworks[i].lifetime--;

			glVertex3f( fireworks[i].x, fireworks[i].y, 0.0f); // draw pixel
			glVertex3f( 0.0f, fireworks[i].y, fireworks[i].z); // draw pixel
		}
	}
	glEnd();
	glPopMatrix();
	//glutSwapBuffers();

	if(!active_fireworks) init_fireworks_proj(1); // reset particles
}