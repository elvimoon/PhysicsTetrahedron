#version 410
in  vec3 Normal;
in  vec3 Position;
out vec4 fragColor;

uniform samplerCube skyBoxTexture; 

void main() { 
	vec3 I = normalize(Position);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = vec4(texture(skyBoxTexture, R).rgb, 1.0);
} 

