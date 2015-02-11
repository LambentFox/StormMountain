#version 400

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec4 vertexNormal;

uniform mat4 projectionMatrix, modleViewMatrix;

void main()
{
	gl_Position = projectionMatrix * modleViewMatrix * vertexPosition;
}
