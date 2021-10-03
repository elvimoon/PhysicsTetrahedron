#include "Quaternion.h"
#include "VMath.h"

#define PI 3.141592654 //M_PI should be in <cmath>
#define DEGTORAD PI/180 //trig functions work in Radians; most external measurements are Degrees

Quaternion::Quaternion() : imaginary(0.0f, 1.0f, 0.0f), w(1.0f) {}

Quaternion::Quaternion(const Vec3& axis, const float angle) { // angle is measured in degrees
	w = cosf(angle * DEGTORAD / 2.0f);
	Vec3 a = VMath::normalize(axis);
	imaginary = a * (sinf(angle * DEGTORAD / 2.0f));
}

Quaternion::Quaternion(const float w_, const float x_, const float y_, const float z_) :
	imaginary(x_, y_, z_), w(w_) {}

Quaternion Quaternion::operator+(const Quaternion& other) const {
	Quaternion ans;

	ans.w = w + other.w;
	ans.imaginary = imaginary + other.imaginary;

	return ans;
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
	/* multiply overload */
	Quaternion ans;

	ans.w = (w * other.w) - VMath::dot(imaginary, other.imaginary);
	ans.imaginary = (other.imaginary * w) + (imaginary * other.w) + VMath::cross(imaginary, other.imaginary);

	return ans;
}

void Quaternion::Normalize() {
	float m = Magnitude();
	w /= m;
	imaginary.x /= m;
	imaginary.y /= m;
	imaginary.z /= m;
}

float Quaternion::Magnitude() const {
	return sqrtf((w * w) + VMath::mag(imaginary) * VMath::mag(imaginary));
}

float Quaternion::DotProduct(const Quaternion& other) const {
	return (w * other.w) + VMath::dot(imaginary, other.imaginary);
}

void Quaternion::Conjugate() {
	imaginary *= -1.0f;
}

void Quaternion::Inverse() {
	Conjugate();
	float m = (Magnitude() * Magnitude());

	w /= m;
	imaginary.x /= m;
	imaginary.y /= m;
	imaginary.z /= m;
}

Vec3 Quaternion::Rotate(const Vec3& vec) const {
	/* rotates a given point by the quaternion */
	Quaternion point;
	point.imaginary = (vec * w) + VMath::cross(imaginary, vec);
	point.w = VMath::dot(imaginary, vec);

	Quaternion inverse;
	inverse.imaginary = imaginary;
	inverse.w = w;
	inverse.Inverse();

	point = point * inverse;

	return point.imaginary;
}

Matrix4 Quaternion::ConvertMatrix() const {
	//Matrix4 ans;

	//ans.m[0] = (1 - (2 * imaginary.y * imaginary.y) - (2 * imaginary.z * imaginary.z));
	//ans.m[1] = ((2 * imaginary.x * imaginary.y) - (2 * imaginary.z * w));
	//ans.m[2] = ((2 * imaginary.x * imaginary.z) + (2 * imaginary.y * w));

	//ans.m[3] = ((2 * imaginary.x * imaginary.y) + (2 * imaginary.z * w));
	//ans.m[4] = (1 - (2 * imaginary.x * imaginary.x) - (2 * imaginary.z * imaginary.z));
	//ans.m[5] = ((2 * imaginary.y * imaginary.z) - (2 * imaginary.x * w));

	//ans.m[6] = ((2 * imaginary.x * imaginary.z) - (2 * imaginary.y * w));
	//ans.m[7] = ((2 * imaginary.y * imaginary.z) + (2 * imaginary.x * w));
	//ans.m[8] = (1 - (2 * imaginary.x * imaginary.x) - (2 * imaginary.y * imaginary.y));

	return Matrix4(
		(1 - (2 * imaginary.y * imaginary.y) - (2 * imaginary.z * imaginary.z)), ((2 * imaginary.x * imaginary.y) + (2 * imaginary.z * w)), ((2 * imaginary.x * imaginary.z) - (2 * imaginary.y * w)), 0.0f,
		((2 * imaginary.x * imaginary.y) - (2 * imaginary.z * w)), (1 - (2 * imaginary.x * imaginary.x) - (2 * imaginary.z * imaginary.z)), ((2 * imaginary.y * imaginary.z) + (2 * imaginary.x * w)), 0.0f,
		((2 * imaginary.x * imaginary.z) + (2 * imaginary.y * w)), ((2 * imaginary.y * imaginary.z) - (2 * imaginary.x * w)), (1 - (2 * imaginary.x * imaginary.x) - (2 * imaginary.y * imaginary.y)), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Quaternion::operator=(const Quaternion& other) {
	imaginary = other.imaginary;
	w = other.w;
}