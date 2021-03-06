#ifndef jason_funcs
#define jason_funcs

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>


#include <AL/al.h>
#include <AL/alc.h>


#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
#define DEF_D 5

#ifdef __cplusplus
extern "C" {
#endif
int axes;       //  Display axes
int mode;       //  Projection mode
int move;       //  Move light
int th;         //  Azimuth of view angle
int ph;         //  Elevation of view angle
int fov;       //  Field of view (for perspective)
int light;      //  Lighting
double asp;     //  Aspect ratio
double dim;   //  Size of world
// Light values
int ntex;
int rep;
int one       ;  // Unit value
int distance  ;  // Light distance
int inc       ;  // Ball increment
int smooth    ;  // Smooth/Flat shading
int local     ;  // Local Viewer Model
int emission  ;  // Emission intensity (%)
int ambient   ;  // Ambient intensity (%)
int diffuse   ;  // Diffuse intensity (%)
int specular  ;  // Specular intensity (%)
int shininess ;  // Shininess (power of two)
float shiny   ;  // Shininess (value)
int zh        ;  // Light azimuth
float ylight  ;  // Elevation of light
double bnc;
int pis;
int spin;
int vpi; // view for the piston; 1 for full length, 0 for one of them

unsigned int texture[26]; // Texture names

/*
 *  Skybox Funcs
 */
void skybox_proj(double x, double y, double z, double dx, double dy, double dz, double th);

/*
 *	Scene Funcs
 */

void draw_scene_proj(double x, double y, double z, double dx, double dy, double dz, double ro);

void fountain_proj(double x, double y, double z, double r, double d, double th);

void draw_fountain_proj(double x, double y, double z, double r, double d, double th);

void bldg_apt1_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void bldg_apt2_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void bldg_apt3_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void bldg_office1_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void bldg_office2_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void bldg_office3_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void bldg_office4_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void mississippi_river_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void draw_ferry_proj(double x, double y, double z, double ds, double th);

void draw_road_proj(double x, double y, double z, double ds, double th);

void draw_roads_proj(double x, double y, double z, double ds, double th);

/*
 *  Superdome Funcs
 */
void superdome_proj(double x, double y, double z, double r, double d, double th);

void bottomfloor_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void field_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void Vertex(int th, int ph);

void topdome_proj(double x, double y, double z, double r, double th);

void draw_superdome_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void floor0_proj(double x, double y, double z, double r, double d, double th);

void jumbotron_proj(double x, double y, double z, double dx, double dy, double dz, double th);

/*
 *  Stands Funcs
 */

void buttseat_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void backseat_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void legseat_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void draw_stand0_proj(double x, double y, double z, double dx, double dy, double dz, double th);

void draw_stand1_proj(double x, double y, double z, double dx, double dy, double dz, double th);

/*
 *  Fireworks Funcs
 */

void draw_firework1_proj(double x, double y, double z, double ds);

void draw_firework2_proj(double x, double y, double z, double ds);

void draw_firework3_proj(double x, double y, double z, double ds);

void init_fireworks_proj(int pause);


#ifdef __cplusplus
}
#endif

#endif