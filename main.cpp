#include "glraphics.h"
#include "shader.h"
#include "bufferDraw.h"

//  Camera
float speed = 1.0f;
int ph = 0.0f;
int th = 0.0f;
float dim = 30.0f;
vec3 cam_pos(10.0f, 10.0f, 3.0f);
mat4 proj_mat = perspective(55.0f,1.0f,0.1f,1000);

//  Light
glight light0;
float yrot = 0.0f;
float zh = 0.0f;
unsigned int lightMove = 1;

//  Vertex Array Object
unsigned int vao[4];
unsigned int screen;
unsigned int terrain;
unsigned int effects;
int len = 256;
int flagDetail = 24;
unsigned int terrainTexture[6];
unsigned int infoTexture;

//  Shaders
shader objectShader(4);
shader effectShader(1);
shader ImageShader(1);
shader ter(1);

//  Frame Buffer
unsigned int fb;
unsigned int color_tex;
unsigned int depth_tex;
unsigned int rb;
//glGenFramebuffers (1, &fb);

int window_width = 800;
int window_height = 600;

void initFrameBuffer()
{
    //glGenFramebuffers (1, &fb);
    //RGBA8 2D texture, 24 bit depth texture, 256x256
    glGenTextures(1, &color_tex);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //NULL means reserve texture memory, but texels are undefined
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, window_width, window_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

    glGenTextures(1, &depth_tex);
    glBindTexture(GL_TEXTURE_2D, depth_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    //NULL means reserve texture memory, but texels are undefined
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, window_width, window_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    //-------------------------
    glGenFramebuffersEXT(1, &fb);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
    //Attach 2D texture to this FBO
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color_tex, 0);
    //-------------------------
    //Attach depth texture to FBO
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth_tex, 0);
    //-------------------------
    //Does the GPU support current FBO configuration?
    //GLenum status;

    GLenum status = glCheckFramebufferStatus (GL_FRAMEBUFFER);
    if (GL_FRAMEBUFFER_COMPLETE != status) {
        fprintf (stderr, "ERROR: incomplete framebuffer\n");
    }

    glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

/*
 * Init
 */
void init(void)
{
    
    
    light0.values(0.1f,0.7f,0.6f,1.0f);
    light0.position(vec3(2.0f,2.0f,2.0f));
    ter.load((char*)"shaders/terrain.vert", (char*)"shaders/terrain.frag",0);
    terrainTexture[0] = LoadTexBMP("textures/height.bmp");
    terrainTexture[1] = LoadTexBMP("textures/layout.bmp");
    terrainTexture[2] = LoadTexBMP("textures/dirt.bmp");
    terrainTexture[3] = LoadTexBMP("textures/stone.bmp");
    terrainTexture[4] = LoadTexBMP("textures/grass.bmp");
    terrainTexture[5] = LoadTexBMP("textures/dirt_normal.bmp");
    infoTexture = LoadTexBMP("textures/info.bmp");
    objectShader.load((char*)"shaders/triangles.vert", (char*)"shaders/triangles.frag",0);
    objectShader.load((char*)"shaders/triangles2.vert", (char*)"shaders/triangles2.frag",1);
    objectShader.load((char*)"shaders/skybox.vert", (char*)"shaders/skybox.frag",2);
    objectShader.load((char*)"shaders/flag.vert", (char*)"shaders/flag.frag",3);

    ImageShader.load((char*)"shaders/image.vert", (char*)"shaders/image.frag",0);

    effectShader.load((char*)"shaders/rain.vert", (char*)"shaders/rain.geo", (char*)"shaders/rain.frag",0);
    effects = gen_particles();
    vao[0] = drawTriangle();
    vao[1] = drawCube();
    vao[2] = drawSkybox();
    vao[3] = drawFlag(flagDetail);
    screen = drawQuad();
    terrain = drawTerrain(len);
}

/*
 * Reshape
 */
void reshape(int width, int height)
{
    float asp = (height>0) ? (float)width/height : 1.0f;
    glViewport(0,0, width, height);
    proj_mat = perspective(55.0f,asp,0.1f,1000);

    window_height = height;
    window_width = width;
    initFrameBuffer();
}


/*
 * Scene
 */
 void scene(float time)
 {
    glEnable(GL_BLEND);
    int id;

    double Ex = -2*dim*Sin(th)*Cos(ph);
    double Ey = +2*dim        *Sin(ph);
    double Ez = +2*dim*Cos(th)*Cos(ph);
    int distance = 50;
    light0.position(vec3((float)(distance*Cos(zh)),70.0f,(float)(distance*Sin(zh))));

    mat4 view_mat = look_at(vec3(Ex,Ey+60.0f,Ez), vec3(0.0f,60.0f,0.0f), vec3(0.0,Cos(ph),0.0));
    //mat4 view_mat = look_at(cam_pos, cam_pos+vec3(-Cos(th),Cos(ph),-Sin(th)), vec3(0.0,Cos(ph),0.0));
	
	//	Flag Poll
    mat4 model = scale(identity4(),0.05,5.0,0.05);
    model = translate(model,vec3(1.60,66.0,0.0));
    mat4 modleView = view_mat * model;
    mat4 normal_mat = transpose(inverse(modleView));

    objectShader.execute(1);
    id = objectShader.id(1,(char*)"projectionMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, proj_mat.m);

    id = objectShader.id(1,(char*)"modleViewMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, modleView.m);

    id = objectShader.id(1,(char*)"normalMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, normal_mat.m);

    id = objectShader.id(1,(char*)"light0");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, light0.mat.m);

    glBindVertexArray(vao[1]);
    glDrawArrays (GL_TRIANGLES, 0, 36);

	//	Light Triangle
    model = rotate(identity4(),zh*5,0,1,0);
    model = translate(model,vec3(light0.mat.m[8],light0.mat.m[9],light0.mat.m[10]));
    modleView = view_mat * model;

    objectShader.execute(0);
    id = objectShader.id(0,(char*)"projectionMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, proj_mat.m);

    id = objectShader.id(0,(char*)"modleViewMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, modleView.m);

    glBindVertexArray (vao[0]);
    glDrawArrays (GL_TRIANGLES, 0, 6);
	
	//	Flag
    model = translate(identity4(),vec3(0.0,70.0,0.0));
    model = scale(model,1.5,1.0,1.0);
    normal_mat = transpose(inverse(modleView));

    modleView = view_mat * model;
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[5]);
    
    objectShader.execute(3);
    id = objectShader.id(3,(char*)"projectionMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, proj_mat.m);

    id = objectShader.id(3,(char*)"modleViewMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, modleView.m);

    id = objectShader.id(3,(char*)"time");
    if (id>=0) glUniform1f(id,time);
    
    id = objectShader.id(3,(char*)"normalMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, normal_mat.m);

    id = objectShader.id(3,(char*)"light0");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, light0.mat.m);
    id = objectShader.id(3,(char*)"fogTex");
    if (id>=0) glUniform1i(id,0);
    
    glBindVertexArray (vao[3]);
    glDrawArrays (GL_TRIANGLES, 0, 12*flagDetail);

	//	Terrian
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[1]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[2]);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[3]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[4]);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[5]);

    model = translate(identity4(),vec3(-len/2,-20,-len/2));
    float scalexz = 256/len;
    model = scale(model, scalexz, 1.0, scalexz);
    modleView = view_mat * model;
    normal_mat = transpose(inverse(modleView));

    ter.execute(0);

    id = ter.id(0,(char*)"heightMap");
    if (id>=0) glUniform1i(id,0);
    id = ter.id(0,(char*)"layoutMap");
    if (id>=0) glUniform1i(id,1);
    id = ter.id(0,(char*)"terrainTex1");
    if (id>=0) glUniform1i(id,2);
    id = ter.id(0,(char*)"terrainTex2");
    if (id>=0) glUniform1i(id,3);
    id = ter.id(0,(char*)"terrainTex3");
    if (id>=0) glUniform1i(id,4);
    id = ter.id(0,(char*)"terrainTex4");
    if (id>=0) glUniform1i(id,5);

    id = ter.id(0,(char*)"terrainLength");
    if (id>=0) glUniform1f(id,(float)len);

    id = ter.id(0,(char*)"projectionMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, proj_mat.m);

    id = ter.id(0,(char*)"modleViewMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, modleView.m);

    id = ter.id(0,(char*)"normalMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, normal_mat.m);

    id = ter.id(0,(char*)"light0");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, light0.mat.m);

    id = ter.id(0,(char*)"time");
    if (id>=0) glUniform1f(id,time);

    glBindVertexArray (terrain);
    glDrawArrays (GL_TRIANGLES, 0, len*len*6);

	//	Skybox
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,terrainTexture[4]);

    model = scale(identity4(), vec3(200.0));
    model = translate(model, vec3(0.0,80.0,0.0));
    modleView = view_mat * model;

    objectShader.execute(2);
    id = objectShader.id(2,(char*)"skyTexture0");
    if (id>=0) glUniform1i(id,0);
    id = objectShader.id(2,(char*)"projectionMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, proj_mat.m);

    id = objectShader.id(2,(char*)"modleViewMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, modleView.m);
    id = objectShader.id(2,(char*)"time");
    if (id>=0) glUniform1f(id,time);

    glBindVertexArray (vao[2]);
    glDrawArrays (GL_TRIANGLES, 0, 36);

    // Rain
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrainTexture[3]);
    effectShader.execute(0);
    id = effectShader.id(0,(char*)"projectionMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, proj_mat.m);
    id = effectShader.id(0,(char*)"viewMatrix");
    if (id>=0)glUniformMatrix4fv (id, 1, GL_FALSE, view_mat.m);
    id = effectShader.id(0,(char*)"time");
    if (id>=0) glUniform1f(id,time);
    id = effectShader.id(0,(char*)"tex");
    if (id>=0) glUniform1i(id,0);

    glBindVertexArray(effects);
    glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);

    glUseProgram(0);

    glDisable(GL_BLEND);
}
/*
 * Display
 */
void display(void)
{
    float time = 0.001*glutGet(GLUT_ELAPSED_TIME);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_PROGRAM_POINT_SIZE);

    //glViewport (0, 0, 600, 600);
    glBindFramebuffer (GL_FRAMEBUFFER, fb);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene(time);
    glBindFramebuffer (GL_FRAMEBUFFER, 0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImageShader.execute(0);
    glActiveTexture (GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glActiveTexture (GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, infoTexture);

    int id = ImageShader.id(0,(char*)"tex0");
    if (id>=0) glUniform1i(id,0);
    id = ImageShader.id(0,(char*)"tex1");
    if (id>=0) glUniform1i(id,1);
    id = ImageShader.id(0,(char*)"time");
    if (id>=0) glUniform1f(id,time);
    id = ImageShader.id(0,(char*)"resolution");
    if (id>=0) glUniform2f(id,window_width,window_height);
    glBindVertexArray (screen);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(0);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_PROGRAM_POINT_SIZE);

    glFlush();
    glutSwapBuffers();
}

/*
 *  Timer
 */
void timer(int k)
{
    //yrot += 5.0f;
    if(lightMove) zh += 8.0f;
   glutPostRedisplay();
   glutTimerFunc(60,timer,0);
}

/*
 * Keyboard
 */
void key(unsigned char ch, int x, int y)
{
    if(ch == 'w' || ch == 'W')
        cam_pos -= vec3(Cos(th)*speed,-Sin(ph)*speed,Sin(th)*speed);
    if(ch == 's' || ch == 'S')
        cam_pos += vec3(Cos(th)*speed,-Sin(ph)*speed,Sin(th)*speed);
	if(ch == 'l' || ch == 'L')
		lightMove = !lightMove;
    //if(ch == 'a' || ch == 'A')
    //if(ch == 'd' || ch == 'D')
    glutPostRedisplay();
}

/*
 * Special Key
 */
void special(int key,int xch,int ych)
{
    //  Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
      th += 5.0f;
    //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)
      th -= 5.0f;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP)
      ph += 5.0f;
    //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
      ph -= 5.0f;
    //  PageUp key - increase dim
    else if (key == GLUT_KEY_PAGE_DOWN && dim < 100.0)
    dim += 2.0;
    //  PageDown key - decrease dim
    else if (key == GLUT_KEY_PAGE_UP && dim > 10.0)
    dim -= 2.0;
    //  Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;
    //  Update projection
    //Project(proj?fov:0,asp,dim);
    //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  Main
 */
int main(int argc,char* argv[])
{


    //  Initialize GLUT
    glutInit(&argc,argv);
    //  Request double buffered, true color window with Z buffering at 600x600
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(window_width,window_height);
    glutCreateWindow("Storm");
    //glutInitContextVersion(4, 3);
    //glutInitContextProfile(GLUT_CORE_PROFILE);
    
    init();
	initFrameBuffer();


	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    timer(1);

	glutMainLoop();
    return 0;
}
