#version 400
in vec2 coords;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float time;
uniform vec2 resolution;

out vec4 fragcolor;

float random(vec2 p)
{
  // We need irrationals for pseudo randomness.
  // Most (all?) known transcendental numbers will (generally) work.
  const vec2 r = vec2(
    23.1406926327792690,  // e^pi (Gelfond's constant)
     2.6651441426902251); // 2^sqrt(2) (Gelfond–Schneider constant)
  return fract( cos( mod(123456789., 1e-7 + 256. * dot(p,r) ) ) );  
}

void main () {

	float x = sin(gl_FragCoord.x + time);
	float y = cos(gl_FragCoord.y + time);

	vec2 seed = vec2(x,y);
	float color = random(seed)*.25;

	vec3 col = vec3(0.0,1.0,0.0);
	//if (depth <= 0.2)
	//	col = vec3(1.0,1.0,1.0);
	col = vec3(0.2, .05+0.4*(.8+sin(gl_FragCoord.y*3.14159*1.1+time*2.0)) + sin(gl_FragCoord.y*.01+time+2.5)*0.05, 0.1);
	float col2 = texture (tex1, gl_FragCoord.xy/resolution).r;
	fragcolor = mix(texture (tex0, coords)+vec4(col2*.5,col2*.4,col2*.2,1.0),vec4(col-color,1.0),0.20);
}