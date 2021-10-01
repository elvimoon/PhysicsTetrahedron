#ifndef SCENE4_H
#define SCENE4_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class DemoObject;
class Skybox;
class Mesh;
class Shader;
class Texture;

class Scene4 : public Scene {
private:
	Camera* camera;
	DemoObject* demoObject;
	Vec3 lightSource;
	Vec3 lightSource2;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Skybox* skyBox;
	//Trackball* trackBall;
public:
	explicit Scene4();
	virtual ~Scene4();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE4_H