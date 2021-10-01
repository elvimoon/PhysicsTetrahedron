#ifndef SCENE5_H
#define SCENE5_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class Tetrahedron;
class Mesh;
class Shader;
class Texture;

class Scene5 : public Scene {
private:
	Camera* camera;
	Tetrahedron* tetrahedron;
	Tetrahedron* tetrahedron2;
	Vec3 lightSource;
	Vec3 lightSource2;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
public:
	explicit Scene5();
	virtual ~Scene5();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE0_H