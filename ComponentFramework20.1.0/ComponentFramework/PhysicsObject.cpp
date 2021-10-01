#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() :pos(0.0f), vel(0.0f), accel(0.0f), mass(1.0f), boundingSphere(0.0f), force(0.0f) {
	angle = angularAcc = angularVel = 0.0f;
	rotInertia = 1.0f;
	elapsedTime = 0.0f;
	radius = 1.0f;
	facingAngle = 0.0f;;
}


PhysicsObject::~PhysicsObject(){

}

