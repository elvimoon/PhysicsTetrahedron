#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class Planet;
class Mesh;
class Shader;
class Texture;

class Scene2 : public Scene {
private:
	Camera* camera;
	Planet* Earth;
	Planet* Moon;
	Vec3 lightSource;
	Vec3 lightSource2;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* earthTexturePtr;
	Texture* moonTexturePtr;
public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE2_H