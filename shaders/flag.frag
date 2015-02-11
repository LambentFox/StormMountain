#version 400

uniform mat4 light0;
uniform sampler2D fogTex;
uniform float time;

vec3 ambient = vec3(light0[1]) * vec3(light0[0][0]);
vec3 specular = vec3(light0[1]) * vec3(light0[0][1]);
vec3 diffuse = vec3(light0[1]) * vec3(light0[0][2]);

in vec3 light, view, normal;
out vec4 fragcolor;

const vec4 fogColor = vec4 (0.15, 0.15, 0.15, 1.0);

vec4 calcLight(){
	vec3 N = normalize(normal);
	//vec3 N = normalize(cross(dFdy(normal), dFdx(normal)));
	vec3 L = normalize(light);
	vec3 R = reflect(-L,N);
	vec3 V = normalize(view);

	float Id = max(dot(L,N),0.0);

	float Is = (Id>0.0) ? pow(max(dot(R,V),0.2), 5.0) : 0.0;

	// final colour
	return vec4((ambient + Id*diffuse + Is*specular), 1.0f);// * scatteredLight;
}

float fog_factor(float min, float max)
{
	float dist = length(view);
	float fac = (dist - min)/(max - min);
	return clamp(fac, 0.0, 1.0);
}

void main()
{
	//vec2 pos = vec2(time*.04,0.0) + coord;
	vec4 color = mix(vec4(0.3, 0.3 , 0.6 ,1.0),calcLight(),0.7);
	//vec4 fcolor = mix(vec4(vec3(texture2D(fogTex,pos/2.0).g),1.0),fogColor,0.8);
	fragcolor = mix(color, fogColor, fog_factor(3.0,100.0));
}
