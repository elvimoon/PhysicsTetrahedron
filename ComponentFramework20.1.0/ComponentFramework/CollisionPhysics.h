#ifndef COLLISIONPHYSICS_H
#define COLLISIONPHYSICS_H

#include <vector>
#include "Vector.h"

using namespace MATH;

struct Simplex {
	std::vector<Vec3> points;
};

class CollisionPhysics {
public:
	static bool GJKDetection(const std::vector<Vec3>& shapeA, const std::vector<Vec3>& shapeB);
	static Vec3 GetPointInDirection(const std::vector<Vec3>& shapeA, const std::vector<Vec3>& shapeB, const Vec3& direction);
};

#endif //COLLISIONPHYSICS_H