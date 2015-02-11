#ifndef glraphics
#define glraphics

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <vector>

#ifdef USEGLEW
#include <GL/glew.h>
#include <GL/glext.h>
#endif

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "matrix.h"
//#include <SDL/SDL.h>
//#include <SDL/SDL_opengl.h>

#define Cos(th) (cos(3.1415926/180*(th)))
#define Sin(th) (sin(3.1415926/180*(th)))
#define BUFFER_OFFSET(x)  ((const void*) (x))
#define PARTICLE_COUNT 300

using namespace std;

/* General Graphics */
//void Print(const char* format, ...);
void Fatal(const char* format, ...);
unsigned int LoadTexBMP(const char* file);
//void Project(double fov, double asp, double dim);
void ErrCheck(const char* where);
//int  LoadOBJ(const char* file);
//void Fog(unsigned int mode, float density, float* color);
//void Sky(double D, unsigned int side, unsigned int topbottom);


struct glight{
	glight();
	glight(float a, float s, float d, float e);
	glight(float a, float s, float d, float e, const vec3& p);
	glight(float a, float s, float d, float e, const vec3& p, const vec3& dir);
	void values(float a, float s, float d, float e);
	void color(const vec4& val);
	void position(const vec3& val);
	void direction(const vec3& val);
	/* |ambient 	|specular 	|diffuse 	|Intesnity 	|
	 * |red			|green   	|blue		|alpha 		|
	 * |x			|y			|z			|w 			|
	 * |dir_x 		|dir_y 		|dir_z 		|spotlight	|
	 */
	mat4 mat;
};


/*class particleEmitter {
  private:
  	float Vert[];
  	float Color[];
  	float Vel[];
  	float Start[];
  	int p;
  public:
  	particleEmitter(float* position, float* velocity, float* velocityOffset, float s);
  	void display(int mode, double dim);
};
*/

#endif