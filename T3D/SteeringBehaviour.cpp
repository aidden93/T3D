#include "SteeringBehaviour.h"
#include "GameObject.h"

namespace T3D {

	SteeringBehaviour::~SteeringBehaviour() {}

	Vector3 SteeringBehaviour::getAcc() {
		Vector3 desiredVel = (target->getWorldPosition() - gameObject->getTransform()->getWorldPosition()).normalised() * MAX_VEL;
		desiredVel.y = 0.0f;

		Vector3 acc = desiredVel - velocity;
		if (acc.length() > MAX_ACC) {
			acc *= MAX_ACC / acc.length();
		}

		return acc;
	}

	void SteeringBehaviour::update(float dt) {
		Transform* t = gameObject->getTransform();

		Vector3 acc = getAcc();                                    // get the steering acceleration
		velocity += acc * dt;                                      // accelerate the character
		t->setWorldPosition(t->getWorldPosition() + velocity*dt);  // update position

																   // get a world space vector pointing forward (positive z of the character)
		Vector3 forward = t->transformPoint(Vector3(0, 0, 1)) - t->getWorldPosition();

		// now get a vector pointing right (positive x)
		Vector3 right = t->transformPoint(Vector3(1, 0, 0)) - t->getWorldPosition();

		// rotate towards direction of movement
		if (velocity.length() > 0.1f) {  // only do this if we are currently moving (may need to adjust the 0.1)
										 // find the angle between our current direction and movement direction and clamp to maximum turn speed
			float turnAngle = Math::clamp(forward.angleBetween(velocity), 0, MAX_TURN*dt);
			if (right.dot(velocity) < 0) {  // turn left or right?
				turnAngle = -turnAngle;
			}
			t->yaw(turnAngle); // do the rotation
		}
	}
}