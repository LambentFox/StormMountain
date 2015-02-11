#version 400

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec2 texCoord;

uniform mat4 projectionMatrix,modleViewMatrix;

out vec2 coords;

void main () {
	coords = texCoord;
	vec4 p = modleViewMatrix * vertexPosition;

	gl_Position = projectionMatrix * p;
}
