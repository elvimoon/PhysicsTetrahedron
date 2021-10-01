#ifndef SCENE3_H
#define SCENE3_H
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

class Scene3 : public Scene {
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
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE3_H