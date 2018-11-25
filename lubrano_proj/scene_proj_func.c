#include "jason_funcs.h"
#include "CSCIx229.h"

/* draw a shack and everything about it */











void scene_proj(double x, double y, double z, double dx, double dy, double dz, double th){
	glPushMatrix();
		//  Offset, scale and rotate
		glTranslated(x, y, z);
		glRotated(ro, 0, 1, 0);
		glScaled(dx, dy, dz);
		grassfloor_proj(20, -1, -20, 1, 1, 1, 0);
	glPopMatrix();
}