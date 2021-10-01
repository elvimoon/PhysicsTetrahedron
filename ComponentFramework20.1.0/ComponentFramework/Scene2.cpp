#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene2.h"
#include "Camera.h"
#include "Planet.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene2::Scene2() : camera(nullptr), Earth(nullptr), meshPtr(nullptr), shaderPtr(nullptr), earthTexturePtr(nullptr), moonTexturePtr(nullptr) {
	Debug::Info("Created Scene2: ", __FILE__, __LINE__);
}

Scene2::~Scene2() {}

bool Scene2::OnCreate() {
	camera = new Camera();
	lightSource = Vec3(10.0, 0.0, -10.0);


	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	earthTexturePtr = new Texture();
	moonTexturePtr = new Texture();
	if (meshPtr == nullptr || shaderPtr == nullptr || earthTexturePtr == nullptr || moonTexturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (earthTexturePtr->LoadImage("textures/earthclouds.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	if (moonTexturePtr->LoadImage("textures/moon.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	Earth = new Planet(meshPtr, shaderPtr, earthTexturePtr);
	if (Earth == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	Earth->setScale(1.0f);
	Earth->setAngularVel(6.0f);
	Earth->setPos(Vec3(0.0, 0.0, 0.0));
	Earth->setModelMatrix(MMath::translate(Earth->getPos()));

	Moon = new Planet(meshPtr, shaderPtr, moonTexturePtr);
	Moon->setScale(0.5);
	Moon->setAngularVel(2.0f);
	Moon->setPos(Vec3(5.0, 0.0, 0.0));
	Moon->setModelMatrix(MMath::translate(Moon->getPos()));

	return true;
}

void Scene2::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene2::Update(const float deltaTime) {
	Earth->Update(deltaTime);
	Moon->Update(deltaTime);
}

void Scene2::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = Earth->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(Earth->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(Earth->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(Earth->getShader()->getUniformID("lightPos"), 1, lightSource);

	Earth->Render();
	Moon->Render();

	glUseProgram(0);
}


void Scene2::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (earthTexturePtr) delete earthTexturePtr, earthTexturePtr = nullptr;
	if (moonTexturePtr) delete moonTexturePtr, moonTexturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (Earth) delete Earth, Earth = nullptr;
	if (Moon) delete Moon, Moon = nullptr;
}