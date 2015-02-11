#version 400 core

uniform sampler2D tex; // optional. enable point-sprite coords to use
out vec4 fragcolor;

void main () {
	// using point texture coordinates which are pre-defined over the point
	fragcolor = vec4(0.6, 0.6, 0.8, 0.3);
}
