#version 400

layout (location = 0) in vec3 init_vel;
layout (location = 1) in float start_time;

uniform mat4 viewMatrix, projectionMatrix;
//vec3 emitterPos = vec3(0.0);
uniform float time;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	float t = time - start_time;
	t = mod(t, 3.0);

	//opacity = 0.0;

	vec3 pos = vec3(rand(vec2(10.0,init_vel.x))*200.0-100.0,120.0,rand(vec2(10.0,init_vel.z))*200.0-100.0);

	vec3 acc = vec3(0.0, -30.0, 0.0);

	pos += init_vel * t + 0.5 * acc * t * t;

	gl_Position = projectionMatrix * viewMatrix * vec4 (pos, 1.0);
}