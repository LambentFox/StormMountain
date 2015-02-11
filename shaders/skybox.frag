#version 400

uniform sampler2D skyTexture0;

uniform float time;

in vec2 coords;
out vec4 fragcolor;

void main () {
	vec2 pos = vec2(time*.1,-time*.01) + gl_FragCoord.xy/5000;
	vec2 pos2 = vec2(-time*.05,time*.01) + gl_FragCoord.xy/5000;
	float color = texture2D(skyTexture0,pos).g;
	float color2 = texture2D(skyTexture0,pos2).g;
	fragcolor =  mix(vec4(color,color,color,0.5),vec4(color2,color2,color2,0.5),.8);;
}
