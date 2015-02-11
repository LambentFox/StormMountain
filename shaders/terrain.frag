#version 400

uniform sampler2D heightMap, layoutMap, terrainTex1, terrainTex2, terrainTex3, terrainTex4;

in vec3 light, view;

uniform mat4 light0;
vec3 ambient = vec3(light0[1]) * vec3(light0[0][0]);
vec3 specular = vec3(light0[1]) * vec3(light0[0][1]);
vec3 diffuse = vec3(light0[1]) * vec3(light0[0][2]);

uniform float time;

in vec2 coord;

in vec3 v_P;

out vec4 fragcolor;

const vec4 fogColor = vec4 (0.1, 0.1, 0.1, 1.0);

vec4 calcLight(){
	vec3 lpc = texture2D(layoutMap,coord.xy).rgb;
	vec3 bumpamount = vec3(0.0);
	bumpamount = (texture2D(terrainTex4, coord.xy*15-(lpc.g/20.0)).rgb * 2.0 - 1.0);
	//vec3 normal = normalize(texture2D(terrainTex4, coord.xy*20).rgb * 2.0 - 1.0);
	vec3 N = normalize(cross(dFdy(v_P), dFdx(v_P)))+normalize(bumpamount);
	//vec3 N = normalize(normal);
	vec3 L = normalize(light);
	vec3 R = reflect(-L,N);
	vec3 V = normalize(view);

	float Id = max(dot(L,N),0.0);

	float Is = (Id>0.0) ? pow(max(dot(R,V),0.0), 2.0) : 0.0;

	// final colour
	return vec4((ambient + Id*diffuse + Is*specular), 1.0f);// * scatteredLight;
}

vec4 terrainLayout(float rp)
{

	vec3 lpc = texture2D(layoutMap,coord.xy).rgb;
	vec4 tex1 = texture2D(terrainTex1,coord.xy*rp)*lpc.r;
	vec4 tex2 = texture2D(terrainTex2,coord.xy*rp)*lpc.b;
	vec4 tex3 = texture2D(terrainTex3,coord.xy)*lpc.g;
	return tex3+tex2+tex1;
}

float fog_factor(float min, float max)
{
	float dist = length(view);
	float fac = (dist - min)/(max - min);
	return clamp(fac, 0.0, 1.0);
}

void main()
{	
	vec2 pos = vec2(time*.04,0.0) + coord;
	vec4 color = mix(vec4(vec3(texture2D(terrainTex3,pos/2.0).g),1.0),fogColor,0.8);
	fragcolor = mix(terrainLayout(8.0)*calcLight(), color, fog_factor(3.0,100.0));
}
