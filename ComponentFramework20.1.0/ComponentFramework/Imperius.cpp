#include "Imperius.h"
#include "Physics.h"
#include "MMath.h"

Imperius::Imperius(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_) {

	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

Imperius::~Imperius() {}

bool Imperius::OnCreate() { return true; } /// Just a stub
void Imperius::OnDestroy() {}				  /// Just a stub
void Imperius::Update(float deltaTime_) {
	Physics::SimpleNewtonMotion(*this, deltaTime_);

	static float spinAngle = 180.0f;
	spinAngle -= 0.5f;

	modelMatrix = MMath::scale(0.02, 0.02, 0.02) * MMath::rotate(spinAngle, Vec3(0.0, 1.0, 0.0)) * MMath::translate(0.0, -100.0, 0.0);
} /// Just a stub

void Imperius::Render() const {

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

void Imperius::HandleEvents(const SDL_Event& event) {} /// Just a stub
