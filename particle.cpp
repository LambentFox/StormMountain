#include "glraphics.h"

/*                            */
/* Basic Particle Emitter     */
/*                            */

static float frand(float rng,float off)
{
   return rand()*rng/RAND_MAX+off;
}
particleEmitter::particleEmitter(float* position, float* velocity, float* velocityOffset, float s){
		//  Array Pointers
	float* vert  = Vert;
	float* color = Color;
	float* vel   = Vel;
	float* start = Start;
	//  Loop over NxN patch
	int i,j;
	p = P;
	for (i=0;i<p;i++)
		for (j=0;j<p;j++)
		{
			 //  Location x,y,z
			 *vert++ = (i+0.5)/p-0.75+position[0];
			 *vert++ = position[1];
			 *vert++ = (j+0.5)/p-0.75+position[2];
			 //  Color r,g,b (0.5-1.0)
			 *color++ = frand(0.5,0.5);
			 *color++ = frand(0.5,0.5);
			 *color++ = frand(0.5,0.5);
			 //  Velocity
			 *vel++ = frand(velocity[0],velocityOffset[0]);
			 *vel++ = frand(velocity[1],velocityOffset[1]);
			 *vel++ = frand(velocity[2],velocityOffset[2]);
			 //  Launch time
			 *start++ = frand(s,0.0);
		}
}

void particleEmitter::display(int mode, double dim){
	   //  Set particle size
   glPointSize(100/dim);
   //  Point vertex location to local array Vert
   glVertexPointer(3,GL_FLOAT,0,Vert);
   //  Point color array to local array Color
   glColorPointer(3,GL_FLOAT,0,Color);
   //  Point attribute arrays to local arrays
   glVertexAttribPointer(VELOCITY_ARRAY,3,GL_FLOAT,GL_FALSE,0,Vel);
   glVertexAttribPointer(START_ARRAY,1,GL_FLOAT,GL_FALSE,0,Start);
   //  Enable arrays used by DrawArrays
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glEnableVertexAttribArray(VELOCITY_ARRAY);
   glEnableVertexAttribArray(START_ARRAY);
   //  Set transparent large particles
   if (mode)
   {
      glEnable(GL_POINT_SPRITE);
      glTexEnvi(GL_POINT_SPRITE,GL_COORD_REPLACE,GL_TRUE);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glDepthMask(0);
   }
   //  Draw arrays
   glDrawArrays(GL_POINTS,0,p*p);
   //  Reset
   if (mode)
   {
      glDisable(GL_POINT_SPRITE);
      glDisable(GL_BLEND);
      glDepthMask(1);
   }
   //  Disable arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableVertexAttribArray(VELOCITY_ARRAY);
   glDisableVertexAttribArray(START_ARRAY);
}