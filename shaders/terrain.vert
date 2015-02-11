#version 400

layout(location = 0) in vec4 vertexPosition;

uniform mat4 projectionMatrix, modleViewMatrix, normalMatrix, light0;
uniform sampler2D heightMap;
uniform float terrainLength, time;

out vec2 coord;
out vec3 light, view;//normal;

out vec3 v_P;

//out float x_coord, y_coord

float random(vec2 p)
{
  // We need irrationals for pseudo randomness.
  // Most (all?) known transcendental numbers will (generally) work.
  const vec2 r = vec2(
    23.1406926327792690,  // e^pi (Gelfond's constant)
     2.6651441426902251); // 2^sqrt(2) (Gelfond–Schneider constant)
  return fract( cos( mod(123456789., 1e-7 + 256. * dot(p,r) ) ) );  
}

void main()
{
	float max_height = 1*abs(cos(time/3.0))+81.0;

	vec4 h;
	vec4 tmp = vertexPosition;

	// For Textures;
	float x_coord = vertexPosition.x/(terrainLength);
	float z_coord = vertexPosition.z/(terrainLength);
	coord = vec2(x_coord,z_coord);

	//	The Heigh Map
	h = texture2D(heightMap,coord.xy);
	tmp.y = max_height * (h.b);

	//	Position Vertex and Model View
	v_P = vertexPosition.xyz;
	vec4 p = modleViewMatrix * tmp;

	light = light0[2].xyz - p.xyz;
	view = -p.xyz;

	gl_Position = projectionMatrix * p;
}
