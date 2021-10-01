#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "Vector.h"
#include "Sphere.h"

using namespace MATH;

class PhysicsObject {
	friend class Physics;
public:
	PhysicsObject();
	virtual ~PhysicsObject();
	

public:
	/// Untility functions so small they cane be inlined
	inline void setPos(const Vec3 &pos_) { pos = pos_; }
	inline Vec3 getPos() { return pos; }
	inline void setVel(const Vec3 &vel_) { vel = vel_; }
	inline Vec3 getVel() { return vel; }
	inline void setAccel(const Vec3 &accel_) { accel = accel_; }
	inline Vec3 getAccel() { return accel; }
	inline void applyForce(const Vec3 force) { accel = force / mass;  }
	inline void setAngularVel(const float angularVel_) { angularVel = angularVel_; }
	inline float getAngularVel() { return angularVel; }
	inline void setAngularAcc(const float angularAcc_) { angularAcc = angularAcc_; }
	inline float getAngularAcc() { return angularAcc; }
	inline void applyTorque(const float torque) { angularAcc = torque / rotInertia; }

protected:
	Vec3 pos, vel, accel, force;
	float mass;
	float angle, angularVel, angularAcc;
	float rotInertia;
	float elapsedTime;
	float radius;
	Sphere boundingSphere;
	float facingAngle;
};
#endif

