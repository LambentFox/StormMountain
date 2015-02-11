#include "bufferDraw.h"
;
unsigned int createVertexArray(float* points, float* colors, float* normals, unsigned int length)
{
	unsigned int vao;
    unsigned int points_vbo = 0;  
    glGenBuffers (1, &points_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * length * sizeof (float), points, GL_STATIC_DRAW);

    unsigned int colors_vbo = 0;
    glGenBuffers (1, &colors_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, colors_vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * length * sizeof (float), colors, GL_STATIC_DRAW);

    unsigned int normals_vbo = 0;
    glGenBuffers (1, &normals_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * length * sizeof (float), normals, GL_STATIC_DRAW);

    
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer (GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glEnableVertexAttribArray (2);
    return vao;
}

unsigned int createVertexArray2(float* points, float* colors, float* normals, unsigned int length)
{
    unsigned int vao;
    unsigned int points_vbo = 0;  
    glGenBuffers (1, &points_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * length * sizeof (float), points, GL_STATIC_DRAW);

    unsigned int colors_vbo = 0;
    glGenBuffers (1, &colors_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, colors_vbo);
    glBufferData (GL_ARRAY_BUFFER, 2 * length * sizeof (float), colors, GL_STATIC_DRAW);

    unsigned int normals_vbo = 0;
    glGenBuffers (1, &normals_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * length * sizeof (float), normals, GL_STATIC_DRAW);

    
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer (GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glEnableVertexAttribArray (2);
    return vao;
}

unsigned int createVertexArray(float* points, float* texCoords, unsigned int length)
{
    unsigned int vao;
    unsigned int points_vbo = 0;  
    glGenBuffers (1, &points_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * length * sizeof (float), points, GL_STATIC_DRAW);

    unsigned int texCoords_vbo = 0;
    glGenBuffers (1, &texCoords_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, texCoords_vbo);
    glBufferData (GL_ARRAY_BUFFER, 2 * length * sizeof (float), texCoords, GL_STATIC_DRAW);

    
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer (GL_ARRAY_BUFFER, texCoords_vbo);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    return vao;
}

unsigned int gen_particles() {
    float vv[PARTICLE_COUNT * 3]; // start velocities vec3
    float vt[PARTICLE_COUNT]; // start times
    float t_accum = 0.0f; // start time
    int j = 0;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        // start times
        vt[i] = t_accum;
        t_accum += 0.01f; // spacing for start times is 0.01 seconds
        // start velocities. randomly vary x and z components
        float randx = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
        float randz = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
        vv[j] = randx; // x
        vv[j + 1] = 1.0f; // y
        vv[j + 2] = randz; // z
        j+= 3;
    }

    unsigned int velocity_vbo = 0;
    glGenBuffers (1, &velocity_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, velocity_vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof (float) * PARTICLE_COUNT * 3, vv, GL_STATIC_DRAW);

    unsigned int time_vbo = 0;
    glGenBuffers (1, &time_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, time_vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof (float) * PARTICLE_COUNT, vt, GL_STATIC_DRAW);

    unsigned int vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, velocity_vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, time_vbo);
    glVertexAttribPointer (1, 1, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
  
    return vao;
}

unsigned int drawTerrain(int detail)
{
    unsigned int vao;
    if(detail <= 0)
        detail = 1;
    int length = detail * detail * 18;
    float points[length];
    unsigned int index = 0;
    for(unsigned int i = 0; i < detail; i++)
    {
        for(unsigned int j = 0; j < detail; j++)
        {
            points[index] = j; points[index+1] = 0; points[index+2] = i;
            points[index+3] = j; points[index+4] = 0; points[index+5] = i+1;
            points[index+6] = j+1; points[index+7] = 0; points[index+8] = i;

            points[index+9] = j; points[index+10] = 0; points[index+11] = i+1;
            points[index+12] = j+1; points[index+13] = 0; points[index+14] = i+1;
            points[index+15] = j+1; points[index+16] = 0; points[index+17] = i;
            index+=18;
        }
    }

    unsigned int points_vbo = 0;  
    glGenBuffers (2, &points_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glBufferData (GL_ARRAY_BUFFER, length * sizeof (float), points, GL_STATIC_DRAW);
    
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    glEnableVertexAttribArray (0);

    return vao;

}

unsigned int drawTriangle()
{
	unsigned int vao;
	float points[] = {
         0.0f, 1.0f, 0.0f,
         1.0f,-1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f,

         0.0f, 1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
    };
    float colors[] = {
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,

         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f
    };
    float normals[] = {
        0.0f, 0.0f,  1.0f,
        0.0f, 0.0f,  1.0f,
        0.0f, 0.0f,  1.0f,

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f
    };

    return createVertexArray(points, colors, normals, 6);
}

unsigned int drawCube()
{
	unsigned int vao;
	float points[] = {
		-1.0f,+1.0f,+1.0f,
		-1.0f,-1.0f,+1.0f,
		+1.0f,-1.0f,+1.0f,
		+1.0f,-1.0f,+1.0f,
		+1.0f,+1.0f,+1.0f,
		-1.0f,+1.0f,+1.0f, //face one


		-1.0f,+1.0f,-1.0f,
		+1.0f,+1.0f,-1.0f,
		+1.0f,-1.0f,-1.0f,
		+1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,+1.0f,-1.0f,//face two
		
		-1.0f,+1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,+1.0f,
		-1.0f,-1.0f,+1.0f,
		-1.0f,+1.0f,+1.0f,
		-1.0f,+1.0f,-1.0f, // face three

		+1.0f,-1.0f,+1.0f, 
		+1.0f,-1.0f,-1.0f, 
		+1.0f,+1.0f,-1.0f, 
		+1.0f,+1.0f,-1.0f,
		+1.0f,+1.0f,+1.0f,
		+1.0f,-1.0f,+1.0f, // face four

		-1.0f,+1.0f,+1.0f,
		+1.0f,+1.0f,+1.0f,
		+1.0f,+1.0f,-1.0f,
		+1.0f,+1.0f,-1.0f,
		-1.0f,+1.0f,-1.0f,
		-1.0f,+1.0f,+1.0f, // face five

		+1.0f,-1.0f,-1.0f,
		+1.0f,-1.0f,+1.0f,
		-1.0f,-1.0f,+1.0f,
		-1.0f,-1.0f,+1.0f,
		-1.0f,-1.0f,-1.0f,
		+1.0f,-1.0f,-1.0f // face six
    };
    float colors[108];
    for(unsigned int i = 0; i < 108; i++)
    	colors[i] = 1.0f;
    /*float colors[] = {
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f
    };*/
    float normals[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, //face one

        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f,
        0.0f, 0.0f,-1.0f, //face two

       -1.0f, 0.0f, 0.0f,
       -1.0f, 0.0f, 0.0f,
       -1.0f, 0.0f, 0.0f,
       -1.0f, 0.0f, 0.0f,
       -1.0f, 0.0f, 0.0f,
       -1.0f, 0.0f, 0.0f, //face two

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, //face two

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, //face two

        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f,
        0.0f,-1.0f, 0.0f //face two
    };

    return createVertexArray(points, colors, normals, 36);
}

unsigned int drawQuad()
{
    float points[] = {
        -1.0, -1.0, 0.0,
        1.0, -1.0, 0.0,
        1.0,  1.0, 0.0,
        1.0,  1.0, 0.0,
        -1.0,  1.0, 0.0,
        -1.0, -1.0, 0.0
    };

    float texCoords[] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0
    };

    return createVertexArray(points, texCoords, 6);
}

unsigned int drawFlag(int detail)
{
    /*float points[] = {
        -1.0f,+1.0f,+0.0f,
        -1.0f,-1.0f,+0.0f,
        -0.5f,-1.0f,+0.0f,
        -0.5f,-1.0f,+0.0f,
        -0.5f,+1.0f,+0.0f,
        -1.0f,+1.0f,+0.0f, //face one

        -0.5f,+1.0f,+0.0f,
        -0.5f,-1.0f,+0.0f,
        -0.0f,-1.0f,+0.0f,
        -0.0f,-1.0f,+0.0f,
        -0.0f,+1.0f,+0.0f,
        -0.5f,+1.0f,+0.0f, //face one

        -0.0f,+1.0f,+0.0f,
        -0.0f,-1.0f,+0.0f,
        +0.5f,-1.0f,+0.0f,
        +0.5f,-1.0f,+0.0f,
        +0.5f,+1.0f,+0.0f,
        -0.0f,+1.0f,+0.0f, //face one

        +0.5f,+1.0f,+0.0f,
        +0.5f,-1.0f,+0.0f,
        +1.0f,-1.0f,+0.0f,
        +1.0f,-1.0f,+0.0f,
        +1.0f,+1.0f,+0.0f,
        +0.5f,+1.0f,+0.0f, //face one

       /* -1.0f,+1.0f,-0.0f,
        +1.0f,+1.0f,-0.0f,
        +1.0f,-1.0f,-0.0f,
        +1.0f,-1.0f,-0.0f,
        -1.0f,-1.0f,-0.0f,
        -1.0f,+1.0f,-0.0f,//face two*/


    //};
    float points[detail*36];
    float normals[detail*36];
    double j = 0;
    for(unsigned int i = 0; i < detail*36; i+=36)
    {
        points[i] = -1+(j/detail*2); points[i+1] = 1.0; points[i+2] = 0;
        points[i+3] = -1+(j/detail*2); points[i+4] =-1.0; points[i+5] = 0;
        points[i+6] = -1+((j+1)/detail*2); points[i+7] =-1.0; points[i+8] = 0;
        points[i+9] = -1+((j+1)/detail*2); points[i+10] =-1.0; points[i+11] = 0;
        points[i+12] = -1+((j+1)/detail*2); points[i+13] = 1.0; points[i+14] = 0;
        points[i+15] = -1+(j/detail*2); points[i+16] = 1.0; points[i+17] = 0;

        for(unsigned int k = 0; k < 18; k++)
            normals[k] = ((k+1)%3 == 0)? 1.0: 0.0;

        points[i+18] = -1+(j/detail*2); points[i+19] = 1.0; points[i+20] = 0;
        points[i+21] = -1+((j+1)/detail*2); points[i+22] =-1.0; points[i+23] = 0;
        points[i+24] = -1+(j/detail*2); points[i+25] =-1.0; points[i+26] = 0;
        points[i+27] = -1+((j+1)/detail*2); points[i+28] =-1.0; points[i+29] = 0;
        points[i+30] = -1+(j/detail*2); points[i+31] = 1.0; points[i+32] = 0;
        points[i+33] = -1+((j+1)/detail*2); points[i+34] = 1.0; points[i+35] = 0;

        for(unsigned int k = 0; k < 18; k++)
            normals[k+18] = ((k+1)%3 == 0)? -1.0: 0.0;
        
        j++;
    }

    float texCoords[] = {
        0.0, 0.0,
        .25, 0.0,
        .25, 1.0,
        .25, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        0.25, 0.0,
        0.5, 0.0,
        0.5, 1.0,
        0.5, 1.0,
        0.25, 1.0,
        0.25, 0.0,

        0.5, 0.0,
        0.75, 0.0,
        0.75, 1.0,
        0.75, 1.0,
        0.5, 1.0,
        0.5, 0.0,

        0.75, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.75, 1.0,
        0.75, 0.0,

        /*0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0*/
    };

    return createVertexArray2(points, texCoords, normals, 12*detail);
}

unsigned int drawSkybox()
{
    unsigned int vao;
    float points[] = {
        -1.0f,+1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        +1.0f,-1.0f,-1.0f,
        +1.0f,-1.0f,-1.0f,
        +1.0f,+1.0f,-1.0f,
        -1.0f,+1.0f,-1.0f, //face one


        -1.0f,+1.0f,+1.0f,
        +1.0f,+1.0f,+1.0f,
        +1.0f,-1.0f,+1.0f,
        +1.0f,-1.0f,+1.0f,
        -1.0f,-1.0f,+1.0f,
        -1.0f,+1.0f,+1.0f,//face two
        
        +1.0f,+1.0f,-1.0f,
        +1.0f,-1.0f,-1.0f,
        +1.0f,-1.0f,+1.0f,
        +1.0f,-1.0f,+1.0f,
        +1.0f,+1.0f,+1.0f,
        +1.0f,+1.0f,-1.0f, // face three

        -1.0f,-1.0f,+1.0f, 
        -1.0f,-1.0f,-1.0f, 
        -1.0f,+1.0f,-1.0f, 
        -1.0f,+1.0f,-1.0f,
        -1.0f,+1.0f,+1.0f,
        -1.0f,-1.0f,+1.0f, // face four

        -1.0f,-1.0f,+1.0f,
        +1.0f,-1.0f,+1.0f,
        +1.0f,-1.0f,-1.0f,
        +1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,+1.0f, // face five

        +1.0f,+1.0f,-1.0f,
        +1.0f,+1.0f,+1.0f,
        -1.0f,+1.0f,+1.0f,
        -1.0f,+1.0f,+1.0f,
        -1.0f,+1.0f,-1.0f,
        +1.0f,+1.0f,-1.0f // face six
    };

    float texCoord[] ={
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    //return 0;
    return createVertexArray(points, texCoord, 36);
}
