#version 120

uniform vec2 resolution;
uniform sampler2DRect texture;
uniform float time;
 
varying vec2 vTexCoord;
 
float random (vec2 p) { 
    return fract(sin(dot(p, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec4 tex = texture2DRect(texture, vTexCoord);
    vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / resolution;
    gl_FragColor = tex+random(vec2(p*sin(time)));
}