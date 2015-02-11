#include "shader.h"


//
//  Print Shader Log
//
static void PrintShaderLog(int obj,const char* file)
{
   int len=0;
   glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) Fatal("Cannot allocate %d bytes of text for shader log\n",len);
      glGetShaderInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s:\n%s\n",file,buffer);
      free(buffer);
   }
   glGetShaderiv(obj,GL_COMPILE_STATUS,&len);
   if (!len) Fatal("Error compiling %s\n",file);
}

//
//  Print Program Log
//
void PrintProgramLog(int obj)
{
   int len=0;
   glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) Fatal("Cannot allocate %d bytes of text for program log\n",len);
      glGetProgramInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s\n",buffer);
   }
   glGetProgramiv(obj,GL_LINK_STATUS,&len);
   if (!len) Fatal("Error linking program\n");
}


/*
 *	Initialize the amount of shaders to be used
 */
shader::shader(unsigned int n)
{
	size = n;
	shaders = (int*)malloc(n);
}

/*
 *	Get Shader ID
 */
int shader::id(unsigned int n, char* name)
{
	return glGetUniformLocation(shaders[n],name);
}
/*
 *	Create and compile the shader
 */
int shader::compile(GLenum type, char* file)
{
	//	Create the shader
	int shader = glCreateShader(type);
	//	Load source code frome file
	char* source = ReadText(file);
	glShaderSource(shader,1,(const char**)&source,NULL);
	free(source);
	//	Compile the shader
	//fprintf(stderr, "Compile %s\n",file);
	glCompileShader(shader);
	//	Check for errors
	PrintShaderLog(shader, file);
	//	Return name
	return shader;
}

/*
 *	Loads in necessary files and creates a shader program
 */
void shader::load(char* VertFile,char* FragFile, unsigned int n)
{
	//	Create program
	int prog = glCreateProgram();
	if (VertFile) 
	{
		//	Create and compile vertex shader
		int vert = compile(GL_VERTEX_SHADER, VertFile);
		//	Attach vertex shader
		glAttachShader(prog,vert);
	}
	
	if (FragFile){
		//	Create and compile fragment shader
		int frag = compile(GL_FRAGMENT_SHADER, FragFile);
		//	Attach fragment shader
		glAttachShader(prog,frag);
	} 
	//	Link program
	glLinkProgram(prog);
	//	Check for errors
	PrintProgramLog(prog);
	//	Return name
	shaders[n] = prog;
}

void shader::load(char* VertFile, char* GeoFile, char* FragFile, unsigned int n)
{
	int prog = glCreateProgram();
	if (VertFile) 
	{
		//	Create and compile vertex shader
		int vert = compile(GL_VERTEX_SHADER, VertFile);
		//	Attach vertex shader
		glAttachShader(prog,vert);
	}
	if (GeoFile) 
	{
		//	Create and compile Geomoetry shader
		int geo = compile(GL_GEOMETRY_SHADER, GeoFile);
		//	Attach Geometry shader
		glAttachShader(prog,geo);
	}
	if (FragFile){
		//	Create and compile fragment shader
		int frag = compile(GL_FRAGMENT_SHADER, FragFile);
		//	Attach fragment shader
		glAttachShader(prog,frag);
	}
	//	Link program
	glLinkProgram(prog);
	//	Check for errors
	PrintProgramLog(prog);
	//	Return name
	shaders[n] = prog;
}

void shader::load(char* VertFile, char* TCFile, char* TEFile, char* GeoFile, char* FragFile, unsigned int n)
{
	int prog = glCreateProgram();
	if (VertFile) 
	{
		//	Create and compile vertex shader
		int vert = compile(GL_VERTEX_SHADER, VertFile);
		//	Attach vertex shader
		glAttachShader(prog,vert);
	}
	if (TCFile) 
	{
		//	Create and compile Tess Control shader
		int tc = compile(GL_VERTEX_SHADER, TCFile);
		//	Attach Tess Control shader
		glAttachShader(prog,tc);
	}
	if (TEFile) 
	{
		//	Create and compile Tess Evaluation shader
		int te = compile(GL_VERTEX_SHADER, TEFile);
		//	Attach Tess Evaluation shader
		glAttachShader(prog,te);
	}if (GeoFile) 
	{
		//	Create and compile Geomoetry shader
		int geo = compile(GL_VERTEX_SHADER, GeoFile);
		//	Attach Geometry shader
		glAttachShader(prog,geo);
	}
	if (FragFile){
		//	Create and compile fragment shader
		int frag = compile(GL_FRAGMENT_SHADER, FragFile);
		//	Attach fragment shader
		glAttachShader(prog,frag);
	}
	//	Link program
	glLinkProgram(prog);
	//	Check for errors
	PrintProgramLog(prog);
	//	Return name
	shaders[n] = prog;
}

void shader::loadLocation(char* VertFile, char* FragFile, char* Names[], unsigned int n)
{
	//	Create program
	int prog = glCreateProgram();
	
	if (VertFile) 
	{
		//	Create and compile vertex shader
		int vert = compile(GL_VERTEX_SHADER, VertFile);
		//	Attach vertex shader
		glAttachShader(prog,vert);
	}
	
	if (FragFile){
		//	Create and compile fragment shader
		int frag = compile(GL_FRAGMENT_SHADER, FragFile);
		//	Attach fragment shader
		glAttachShader(prog,frag);
	} 

	for(int i = 0; Names[i]; i++)
	{
		if (Names[i][0])
        	glBindAttribLocation(prog,i,Names[i]);
	}
	//	Link program
	glLinkProgram(prog);
	//	Check for errors
	PrintProgramLog(prog);
	//	Return name
	shaders[n] = prog;
}

/*
 *	Runs selected Shader
 */
void shader::execute(unsigned int x)
{
	if(x <= size)
		glUseProgram(shaders[x]);
}

/*
 *	Read in a text file
 */
char* ReadText(char *file)
{
	int n;
	char* buffer;
	//	Open File
	FILE* f = fopen(file,"rt");
	if (!f) Fatal("Cannot open text file %s\n",file);
	//	Seekto end to determine size,then rewind
	fseek(f,0,SEEK_END);
	n = ftell(f);
	rewind(f);
	//	Allocate memory for the whole file
	buffer = (char*)malloc(n+1);
	if (!buffer) Fatal("Cannot allocate %d btes for text file %s\n", n+1, file);
	//	Snarf the file
	if (fread(buffer,n,1,f)!=1) Fatal("Cannot read %d bytes for text file %s\n",n,file);
	buffer[n] = 0;
	//	Close and return
	fclose(f);
	return buffer;
}
