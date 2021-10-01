#ifndef CAMERA_H
#define CAMERA_H
#include "Vector.h"
#include "Matrix.h"
#include "GameObject.h"
#include "Skybox.h"
#include "MMath.h"

using namespace MATH;
class Camera : public GameObject {
private:

	Matrix4 projection;
	Matrix4 view;
	Matrix4 translate;
	Matrix4 rotate;
	Skybox* skyBox;
	class Trackball* trackballPTR;
	

public:
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void HandleEvents(const SDL_Event& event) override;
	void Render() const override;
	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return view; }
	inline void setProjectionMatrix(Matrix4 projection_) { projection = projection_; }
	inline void setViewMatrix(Matrix4 view_) { view = view_; }
	inline void setSkyBox(Skybox* skyBox_) { skyBox = skyBox_; }
	Camera();
	~Camera();
};

#endif
