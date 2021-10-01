#include <glew.h>
#include "Camera.h"
#include "Trackball.h"


Camera::Camera() {
	setProjectionMatrix(MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f));
	//setViewMatrix(MMath::lookAt(Vec3(0.0, 0.0, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)));
	//view.print();

	rotate = MMath::rotate(0.0, Vec3(0.0, 1.0, 0.0));
	translate = MMath::translate(0.0, 0.0, -10.0);
	view = rotate * translate;
}

Camera::~Camera() 
{
	delete trackballPTR;
}

bool Camera::OnCreate()
{
	trackballPTR = new Trackball();
	return true;
}

void Camera::OnDestroy(){}

void Camera::Update(const float deltaTime){}

void Camera::HandleEvents(const SDL_Event& event)
{
	if (trackballPTR)
	{
		trackballPTR->HandleEvents(event);
	}
}

void Camera::Render() const {
	if (skyBox) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glUseProgram(skyBox->getShader()->getProgram());
		glUniformMatrix4fv(skyBox->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projection);
		glUniformMatrix4fv(skyBox->getShader()->getUniformID("cameraRotationMatrix"), 1, GL_FALSE, trackballPTR->getMatrix4());
		skyBox->Render();
		glUseProgram(0);
	}
}
