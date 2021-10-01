#include "Planet.h"
#include "Physics.h"
#include "MMath.h"

Planet::Planet(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_), scale(1.0f) {

	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

Planet::~Planet() {}

bool Planet::OnCreate() { return true; } /// Just a stub
void Planet::OnDestroy() {}				  /// Just a stub
void Planet::Update(float deltaTime_) {
	Physics::SimpleNewtonMotion(*this, deltaTime_);
	Physics::RigidBodyRotation(*this, deltaTime_);

	modelMatrix = MMath::scale(scale, scale, scale) * 
				  MMath::rotate(angle, Vec3(0.0, 1.0, 0.0)) * 
				  MMath::translate(pos.x, pos.y, pos.z) *
				  MMath::rotate(-90, Vec3(1.0, 0.0, 0.0));
}

void Planet::Render() const {

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

void Planet::HandleEvents(const SDL_Event& event) {} /// Just a stub
