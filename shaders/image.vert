#version 400
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 texCoords;

out vec2 coords;



void main () {
  // interpolate texture coordinates
  coords = texCoords;


  
  // transform vertex position to clip space (camera view and perspective)
  gl_Position = vec4 (vertexPosition, 1.0);
}