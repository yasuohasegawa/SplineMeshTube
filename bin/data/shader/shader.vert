#version 120
varying vec2 vTexCoord;
 
void main() {
    vTexCoord =  gl_Vertex.xy;
    gl_Position = ftransform();
}