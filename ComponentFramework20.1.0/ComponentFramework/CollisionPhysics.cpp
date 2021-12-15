#include "CollisionPhysics.h"
#include "VMath.h"
#include <glm/glm.hpp>

bool CollisionPhysics::GJKDetection(const std::vector<Vec3>& shapeA, const std::vector<Vec3>& shapeB)
{
	Simplex simplex;
	Vec3 centerA(0.0f, 0.0f, 0.0f);
	for (Vec3 va : shapeA) {
		centerA += va;
	}
	centerA /= shapeA.size();
	
	Vec3 centerB(0.0f, 0.0f, 0.0f);
	for (Vec3 vb : shapeB) {
		centerB += vb;
	}
	centerB /= shapeB.size();

	Vec3 d = centerB - centerA;
	Vec3 lastPoint;

	simplex.points.push_back(CollisionPhysics::GetPointInDirection(shapeA, shapeB, d)); //Simplex a
	d = -d;

	lastPoint = CollisionPhysics::GetPointInDirection(shapeA, shapeB, d); //Simplex b
	if (VMath::dot(lastPoint, d) <= 0) {
		return false;
	}
	simplex.points.push_back(lastPoint);

	Vec3 ab = simplex.points.at(1) - simplex.points.at(0);

	d = VMath::cross(ab, simplex.points.at(0));
	d = VMath::cross(d, ab);

	lastPoint = CollisionPhysics::GetPointInDirection(shapeA, shapeB, d);
	if (VMath::dot(lastPoint, d) <= 0) {
		return false;
	}
	simplex.points.push_back(lastPoint); //Simplex c

	Vec3 ac = simplex.points.at(2) - simplex.points.at(0);
	int count;
	do {
		d = VMath::cross(ab, ac);
		centerA = -((simplex.points.at(0) + simplex.points.at(1) + simplex.points.at(2)) / 3);
		d = VMath::dot(d, centerA) > 0 ? d : -d;

		lastPoint = CollisionPhysics::GetPointInDirection(shapeA, shapeB, d);
		if (VMath::dot(lastPoint, d) <= 0) {
			return false;
		}
		simplex.points.push_back(lastPoint); //simplex d
		
		int retry = 0;
		glm::mat4 matrix;

		count = 0;
		matrix[0] = glm::vec4(simplex.points[0].x, simplex.points[0].y, simplex.points[0].z, 1.0f);
		matrix[1] = glm::vec4(simplex.points[1].x, simplex.points[1].y, simplex.points[1].z, 1.0f);
		matrix[2] = glm::vec4(simplex.points[2].x, simplex.points[2].y, simplex.points[2].z, 1.0f);
		matrix[3] = glm::vec4(simplex.points[3].x, simplex.points[3].y, simplex.points[3].z, 1.0f);
		glm::mat4 detMat = glm::transpose(matrix);
		float det0 = glm::determinant(matrix);

		for (int i = 0; i < 4; i++) {
			glm::mat4 testMatrix = matrix;
			testMatrix[i] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			testMatrix = glm::transpose(testMatrix);
			if (glm::determinant(testMatrix) * det0 > 0) {
				count++;
			}
			else {
				retry = i;
			}
		}
		simplex.points.erase(simplex.points.begin() + retry);
		ab = simplex.points.at(0) - simplex.points.at(1);
		ac = simplex.points.at(0) - simplex.points.at(2);
	} while (count == 3);
	return (count > 3);
}

Vec3 CollisionPhysics::GetPointInDirection(const std::vector<Vec3>& shapeA, const std::vector<Vec3>& shapeB, const Vec3& direction)
{
	Vec3 aPoint, bPoint;
	float aDot, bDot;
	aDot = -10000.0f;
	bDot = 10000.0f;
	for (Vec3 va : shapeA) {
		float dotProd = VMath::dot(va, direction);
		if (dotProd > aDot) {
			aDot = dotProd;
			aPoint = va;
		}
	}
	for (Vec3 vb : shapeB) {
		float dotProd = VMath::dot(vb, direction);
		if (dotProd < bDot) {
			bDot = dotProd;
			bPoint = vb;
		}
	}
	return aPoint - bPoint;
}