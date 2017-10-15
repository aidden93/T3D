#include "CarMovement.h"

namespace T3D {


	CarMovement::CarMovement(T3DApplication *app) : Task(app)
	{
		elapsedTime = 0;
		car = NULL;

		//setState(FIRST_DROP);
	}

	CarMovement::~CarMovement(void) {}

	void CarMovement::setState(int state) {
		currentState = state;
	}

	void CarMovement::update(float dt) {
		elapsedTime += dt;
		if (currentState == START) {
			car->setWorldPosition(Vector3(
				0, 
				11, 
				Math::smoothedLerp(15, 185, elapsedTime / 5.0, 0.2)
			));

			Vector3 pos = car->getWorldPosition();
			if (pos.x == 0 && pos.y == 11 && pos.z == 185) {
				currentState = FIRST_CLIMB;
				elapsedTime = 0;
			}
		}
		else if (currentState == FIRST_CLIMB) {
			car->setWorldPosition(Vector3(
				0,
				Math::smoothedLerp(11, 106, elapsedTime / 10.0, 0.2),
				Math::smoothedLerp(185, 390, elapsedTime / 10.0, 0.2)
			));
			car->setLocalRotation(Quaternion(
				Math::smoothedLerp(0, -0.46, elapsedTime / 4.0, 0.2),
				0,
				0
			));

			Vector3 pos = car->getWorldPosition();
			if (pos.x == 0 && pos.y == 106 && pos.z == 390) {
				currentState = STRAIGHT_BEFORE_FIRST_DROP;
				elapsedTime = 0;
			}
		}
		else if (currentState == STRAIGHT_BEFORE_FIRST_DROP) {
			car->setWorldPosition(Vector3(
				0,
				Math::smoothedLerp(106, 112, elapsedTime / 2.0, 0.2),
				Math::smoothedLerp(390, 500, elapsedTime / 10.0, 0.2)
			));
			car->setLocalRotation(Quaternion(
				Math::smoothedLerp(-0.46, 0, elapsedTime / 3.0, 0.2),
				0,
				0
			));

			Vector3 pos = car->getWorldPosition();
			if (pos.x == 0 && pos.y == 112 && pos.z == 500) {
				currentState = FIRST_DROP;
				elapsedTime = 0;
			}
		}
		else if (currentState == FIRST_DROP) {
			car->setWorldPosition(Vector3(
				0,
				Math::smoothedLerp(112, -75, elapsedTime / 3.0, 0.5),
				Math::smoothedLerp(500, 594, elapsedTime / 3.0, 0.5)
			));
			car->setLocalRotation(Quaternion(
				Math::smoothedLerp(0, 1.1, elapsedTime / 0.7, 0.1),
				0,
				0
			));

			Vector3 pos = car->getWorldPosition();
			if (pos.x == 0 && pos.y == -75 && pos.z == 594) {
				//currentState = FIRST_CLIMB;
				elapsedTime = 0;
			}
		}
	}
}