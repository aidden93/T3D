#include "RaiseArms.h"

namespace T3D {


	RaiseArms::RaiseArms(T3DApplication *app) : Task(app)
	{
		elapsedTime = 0;
		person = NULL;

		//setState(FIRST_DROP);
	}

	RaiseArms::~RaiseArms(void) {}

	void RaiseArms::setState(int state) {
		currentState = state;
	}

	void RaiseArms::update(float dt) {
		if (person->getTransform()->getWorldPosition().z >= 500) {
			elapsedTime += dt;
			float duration = 1;
			float elbowStartRotation = -Math::PI / 4;
			float elbowEndRotation = -0.2;
			float shoulderStartRotation = -Math::PI / 4;
			float shoulderEndRotation = -0.95*Math::PI;

			person->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(
				Math::smoothedLerp(shoulderStartRotation, shoulderEndRotation, elapsedTime / duration, 0.2),
				0,
				0
			));
			person->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(
				Math::smoothedLerp(shoulderStartRotation, shoulderEndRotation, elapsedTime / duration, 0.2),
				0,
				0
			));

			person->leftElbowJoint->getTransform()->setLocalRotation(Quaternion(
				Math::smoothedLerp(elbowStartRotation, elbowEndRotation, elapsedTime / duration, 0.2),
				0,
				0
			));
			person->rightElbowJoint->getTransform()->setLocalRotation(Quaternion(
				Math::smoothedLerp(elbowStartRotation, elbowEndRotation, elapsedTime / duration, 0.2),
				0,
				0
			));

			if (elapsedTime >= duration) {
				elapsedTime = 0;
				setFinsihed(true);
			}
		}
	}
}