#version 400
 
layout (points) in;
// convert to points, line_strip, or triangle_strip
layout (triangle_strip, max_vertices = 4) out;
 
// NB: in and out pass-through vertex->fragment variables must go here if used
 
void main () {
	float size = 0.18;
  for(int i = 0; i < 4; i++) {
    // copy attributes
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
    // NB: pass-through of variables would go here
 
    gl_Position.y = gl_in[i].gl_Position.y + size*2.0;
    EmitVertex();
    gl_Position.y = gl_in[i].gl_Position.y;
    gl_Position.x = gl_in[i].gl_Position.x - size;
    EmitVertex();
    gl_Position.y = gl_in[i].gl_Position.y + size*2.0;
    gl_Position.x = gl_in[i].gl_Position.x - size;
    EmitVertex();
  }
}
