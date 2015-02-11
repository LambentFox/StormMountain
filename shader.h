#include "glraphics.h"

class shader
{
  private:
	int* shaders;
	unsigned int size;
	int compile(GLenum type, char* file); // Creates and compiles the shader
  public:
	shader(unsigned int n);	//	Initializes and Allocates the amount of shaders that can be loaded in
	void load(char* VertFile,char* FragFile, unsigned int n); // Loads in files and creates shader program
	void load(char* VertFile, char* GeoFile, char* FragFile, unsigned int n);
	void load(char* VertFile, char* TCFile, char* TEFile, char* GeoFile, char* FragFile,unsigned int n);
	void loadLocation(char* VertFile, char* FragFile, char* Names[], unsigned int n);
	void execute(unsigned int x);	//	Runs selected Shader
	int id(unsigned int n, char* name);	//	Returns Shader Proram Address
};

char* ReadText(char* file); // Temporary function to allow the ability to load in outside files
