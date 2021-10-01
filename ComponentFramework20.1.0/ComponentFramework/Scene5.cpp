#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene5.h"
#include "Camera.h"
#include "Tetrahedron.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene5::Scene5() : camera(nullptr), tetrahedron(nullptr), tetrahedron2(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene5::~Scene5() {}

bool Scene5::OnCreate() {
	camera = new Camera();
	lightSource = Vec3(0.0, 10.0, -10.0);


	if (ObjLoader::loadOBJ("meshes/Tetrahedron.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("phongVert.glsl", "phongFrag.glsl");
	texturePtr = new Texture();
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	/*if (texturePtr->LoadImage("textures/imperius_diff.png") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}*/
	

	tetrahedron = new Tetrahedron(meshPtr, shaderPtr, texturePtr);
	if (tetrahedron == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	tetrahedron->setPos(Vec3(-5.0, 0.0, 0.0));
	tetrahedron->setModelMatrix(MMath::translate(tetrahedron->getPos()));

	tetrahedron2 = new Tetrahedron(meshPtr, shaderPtr, texturePtr);
	if (tetrahedron2 == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	tetrahedron2->setPos(Vec3(5.0, 0.0, 0.0));
	tetrahedron2->setModelMatrix(MMath::translate(tetrahedron->getPos()));


	return true;
}

void Scene5::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene5::Update(const float deltaTime) {
	tetrahedron->Update(deltaTime);
	tetrahedron2->Update2(deltaTime);
}

void Scene5::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = tetrahedron->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(tetrahedron->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(tetrahedron->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(tetrahedron->getShader()->getUniformID("lightPos"), 1, lightSource);

	tetrahedron->Render();
	tetrahedron2->Render();

	glUseProgram(0);
}


void Scene5::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (tetrahedron) delete tetrahedron, tetrahedron = nullptr;
	if (tetrahedron2) delete tetrahedron2, tetrahedron2 = nullptr;
}