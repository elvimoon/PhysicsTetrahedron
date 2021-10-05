#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

struct Quaternion {
	Vec3 imaginary;
	float w;

	Quaternion();
	Quaternion(const Vec3& axis, const float angle);
	Quaternion(const float w_, const float x_, const float y_, const float z_);

	Quaternion operator+(const Quaternion& other) const;
	Quaternion operator*(const Quaternion& other) const;
	Quaternion operator*(const float& scalar) const;

	void Normalize();
	float Magnitude() const;
	float DotProduct(const Quaternion& other) const;
	void Conjugate();
	void Inverse();
	Vec3 Rotate(const Vec3& vec) const;
	Matrix4 ConvertMatrix() const;

	void operator=(const Quaternion& other);
};

#endif //QUATERNION_H