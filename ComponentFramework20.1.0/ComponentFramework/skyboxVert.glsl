#version 440
layout (location = 0) in  vec4 vVertex;

out vec3 textureCoords;
uniform mat4 projectionMatrix;
uniform mat4 cameraRotationMatrix;

void main() {
	textureCoords = vec3(-vVertex.x, vVertex.y, vVertex.z);
	gl_Position = projectionMatrix * cameraRotationMatrix * vVertex;
}
