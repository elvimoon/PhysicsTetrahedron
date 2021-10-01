#version 440
in vec3 textureCoords;
out vec4 fragColor;

uniform samplerCube skyBoxTexture; 

void main() { 
	fragColor =  texture(skyBoxTexture, textureCoords);	
} 

