#include "Tetrahedron.h"
#include "Physics.h"
#include "MMath.h"
#include "VMath.h"

Tetrahedron::Tetrahedron(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_) {

	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

Tetrahedron::~Tetrahedron() {}

bool Tetrahedron::OnCreate() { return true; } /// Just a stub
void Tetrahedron::OnDestroy() {}				  /// Just a stub
void Tetrahedron::Update(float deltaTime_) {
	Physics::SimpleNewtonMotion(*this, deltaTime_);

	static float elapsedTime = 0.0f;
	elapsedTime += 0.025f;

	Vec3 shipForce(0.03, 0.0, 0.0);
	//float torque = 1.0f;

	applyForce(shipForce);
	//applyTorque(torque);

	//linear motion
	pos.x += vel.x * deltaTime_ + 0.5f * accel.x * deltaTime_ * deltaTime_;
	vel.x += accel.x * deltaTime_;

	pos.y += vel.y * deltaTime_ + 0.5f * accel.y * deltaTime_ * deltaTime_;
	vel.y += accel.y * deltaTime_;

	pos.z += vel.z * deltaTime_ + 0.5f * accel.z * deltaTime_ * deltaTime_;
	vel.z += accel.z * deltaTime_;

	//rotational motion torque
	//angularVel += angularAcc * deltaTime_;
	//angle += angularVel * deltaTime_ + 0.5f * angularAcc * deltaTime_ * deltaTime_;

	//rotational motion quaternion
	Quaternion quat(0.0f, 0.0f, 45.0f * (M_PI / 180.0f), 0.0f);
	quaternion = quaternion + (quat * deltaTime_ * 0.5f) * quaternion;
	quaternion.Normalize();
	
	modelMatrix = MMath::translate(pos) * MMath::scale(1.0f, 1.0f, 1.0f) * quaternion.ConvertMatrix();
	//modelMatrix = MMath::translate(pos) * MMath::scale(1.0, 1.0, 1.0) * MMath::rotate(angle, Vec3(0.0, 1.0, 0.0));

} /// Just a stub

void Tetrahedron::Update2(float deltaTime_) {
	Physics::SimpleNewtonMotion(*this, deltaTime_);

	static float elapsedTime = 0.0f;
	elapsedTime += 0.025f;

	Vec3 shipForce(-0.03, 0.0, 0.0);
	//float torque = 1.0f;

	applyForce(shipForce);
	//applyTorque(torque);

	//linear motion
	pos.x += vel.x * deltaTime_ + 0.5f * accel.x * deltaTime_ * deltaTime_;
	vel.x += accel.x * deltaTime_;

	pos.y += vel.y * deltaTime_ + 0.5f * accel.y * deltaTime_ * deltaTime_;
	vel.y += accel.y * deltaTime_;

	pos.z += vel.z * deltaTime_ + 0.5f * accel.z * deltaTime_ * deltaTime_;
	vel.z += accel.z * deltaTime_;

	//rotational motion torque
	//angularVel += angularAcc * deltaTime_;
	//angle += angularVel * deltaTime_ + 0.5f * angularAcc * deltaTime_ * deltaTime_;

	//rotational motion quaternion
	Quaternion quat(0.0f, 0.0f, -45.0f * (M_PI / 180.0f), 0.0f);
	quaternion = quaternion + (quat * deltaTime_ * 0.5f) * quaternion;
	quaternion.Normalize();

	modelMatrix = MMath::translate(pos) * MMath::scale(1.0f, 1.0f, 1.0f) * quaternion.ConvertMatrix();
	//modelMatrix = MMath::translate(pos) * MMath::scale(1.0, 1.0, 1.0) * MMath::rotate(angle, Vec3(0.0, 1.0, 0.0));

} /// Just a stub

void Tetrahedron::Render() const {

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

void Tetrahedron::HandleEvents(const SDL_Event& event) {} /// Just a stub

std::vector<Vec3> Tetrahedron::getShape() const
{
	std::vector<Vec3> points;
	points.reserve(mesh->vertices.size());
	for (auto v : mesh->vertices) {
		points.push_back(modelMatrix * v);
	}
	return points;
}