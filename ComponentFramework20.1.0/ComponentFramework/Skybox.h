#ifndef SKYBOX_H
#define SKYBOX_H
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"
#include <glew.h>
class Skybox : public GameObject {
private:
	GLuint skyBoxTextureID;
	Mesh* meshPtr;
	Shader* shaderPtr;
	bool LoadTextures(const char* posX, const char* negX, const char* posY, const char* negY, const char* posZ, const char* negZ);
public:
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void HandleEvents(const SDL_Event& event) override;
	void Render() const override;
	inline Shader* getShader() { return shaderPtr; }
	inline GLuint getTextureID() { return skyBoxTextureID; }
};

#endif
