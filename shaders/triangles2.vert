#version 400

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec4 vertexNormal;

uniform mat4 projectionMatrix,modleViewMatrix,normalMatrix,light0;
out vec4 color;
out vec3 light, view, normal;

void main () {
	vec4 p = modleViewMatrix * vertexPosition;
	light = light0[2].xyz - p.xyz;
	color = vertexColor;
	view = -p.xyz;
	normal = vec4(normalMatrix * vertexNormal).xyz;
	gl_Position = projectionMatrix * p;
	gl_PointSize = 15.0;
}
