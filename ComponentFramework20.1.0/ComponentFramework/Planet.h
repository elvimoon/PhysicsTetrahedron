#ifndef OBJECT_H
#define OBJECT_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "PhysicsObject.h"

using namespace MATH;


class Planet : public PhysicsObject, public GameObject {

private:
	Matrix4 modelMatrix;
	GLuint modelMatrixID;
	GLuint normalMatrixID;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Planet* satellite;

	float scale;
	float G;
	float sunMass;
	float earthMass;
	float moonMass;
	float FGEarthSun;
	float FGEarthMoon;
	float FGMoonEarth;
	float FGMoonSun;
	float sunEarthDistance;
	float sunMoonDistance;
	float earthMoonDistance;
	Vec3 normalSunEarth;
	Vec3 normalSunMoon;
	Vec3 normalEarthMoon;
	Vec3 sunpos;
	Vec3 earthpos;
	Vec3 moonpos;
	Vec3 fgravityMoon;
	Vec3 fgravityEarth;

public:
	Planet(Mesh* mesh_, Shader* shader_, Texture* texture_);
	~Planet();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& event);
	void gravitationalPhysics(Planet body1, Planet body2);


	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
	inline const Matrix4& getModelMatrix() { return modelMatrix; }
	inline void setScale(const float scale) { this->scale = scale; }
};

#endif