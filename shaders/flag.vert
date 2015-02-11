#version 400

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 vertexNormal;

uniform mat4 projectionMatrix,modleViewMatrix,normalMatrix,light0;

out vec3 light, view, normal;


uniform float time;

void main()
{
	vec4 point = vertexPosition;
	vec4 norm = vertexNormal;
	norm.z = point.z;
	if(point.x != 1.0)
	{
		point.z += cos(20.0*time+sin(point.x*3.14))*.2;
		point.y += cos(0.2*time)*.2;
		norm.z = (-0.05*asin(0.05*sin(time))-0.05*sin(3.14*point.x));
		//norm.z =  min(1,-20*sin(20*time+sin(3.14*point.x)));
		//norm.z = -(20.0*sin(20.0*time+sin(point.x*3.14)));
	}
	
	norm.xy = point.xy;
	
	vec4 p = modleViewMatrix * point;
	light = light0[2].xyz - p.xyz;

	view = -p.xyz;
	normal = norm.xyz;//vec4(normalMatrix * norm).xyz;

	
	gl_Position = projectionMatrix * p;
}
