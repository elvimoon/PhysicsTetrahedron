#include <SDL.h>
#include "PlayerController.h"
#include "Physics.h"
#include "MMath.h"

PlayerController::PlayerController(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_) {
	movementForce = Vec3(0.0, 0.0, 0.0);
	isGrounded = true;

	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

PlayerController::~PlayerController() {}

bool PlayerController::OnCreate() { return true; } /// Just a stub
void PlayerController::OnDestroy() {}				  /// Just a stub
void PlayerController::Update(float deltaTime_) 
{
	Physics::SimpleNewtonMotion(*this, deltaTime_);

	static float elapsedTime = 0.0f;
	elapsedTime += 0.025f;

	KeyboardInput();

	if (pos.y < 0.0f)
	{
		movementForce = Vec3(0.0, 0.0, 0.0);
		pos.y = 0.0f;
		vel.y = 0.0f;
		isGrounded = true;
	}

	applyForce(movementForce);


	pos.x += vel.x * deltaTime_ + 0.5f * accel.x * deltaTime_ * deltaTime_;
	vel.x += accel.x * deltaTime_;

	pos.y += vel.y * deltaTime_ + 0.5f * accel.y * deltaTime_ * deltaTime_;
	vel.y += accel.y * deltaTime_;

	pos.z += vel.z * deltaTime_ + 0.5f * accel.z * deltaTime_ * deltaTime_;
	vel.z += accel.z * deltaTime_;

	angularVel += angularAcc * deltaTime_;
	angle += angularVel * deltaTime_ + 0.5f * angularAcc * deltaTime_ * deltaTime_;

	modelMatrix = MMath::translate(pos) * MMath::scale(1.0, 1.0, 1.0) * MMath::rotate(angle, Vec3(0.0, 0.0, 1.0)) * MMath::rotate(facingAngle, Vec3(0.0, 1.0, 0.0));
}

void PlayerController::Render() const {

	/// This is some fancy code.  Assigning a 4x4 matrix to a 3x3 matrix
	/// just steals the upper 3x3 of the 4x4 and assigns thoses values 
	/// to the 3x3.  
	Matrix3 normalMatrix = MMath::transpose(MMath::inverse(modelMatrix));

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	if (texture) {
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}

	mesh->Render();

	/// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PlayerController::HandleEvents(const SDL_Event& event) 
{
	
} 

void PlayerController::KeyboardInput()
{

}
