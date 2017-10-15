#include "AnimationTest.h"

namespace T3D {

	float elapsedTime;

	AnimationTest::AnimationTest(T3DApplication *app) : Task(app)
	{
		elapsedTime = 0;
		lamp = NULL;
	}

	AnimationTest::~AnimationTest(void) {}

	void AnimationTest::update(float dt) {
		elapsedTime += dt;
		if (elapsedTime < 5) {
			lamp->setLocalPosition(Vector3(Math::smoothedLerp(0, 1, elapsedTime / 5.0, 0.2), 0, 0));
			//lamp->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(1, 0, 0), elapsedTime / 5.0));
		}
		else {
			//lamp->setLocalPosition(Vector3::lerp(Vector3(1, 0, 0), Vector3(0, 1, 0), elapsedTime / 10.0));
			lamp->setLocalPosition(Vector3(
				Math::smoothedLerp(1, 0, elapsedTime / 10.0, 0.2), 
				Math::smoothedLerp(0, 1, elapsedTime / 10.0, 0.2), 
				0
			));
		}
	}
}