#include "TargetJump.h"
#include "GameObject.h"
#include "Math.h"

namespace T3D {

	TargetJump::~TargetJump() {}

	void TargetJump::update(float dt) {
		timer -= dt;
		if (timer < 0) {
			timer = jumpTime;
			gameObject->getTransform()->setLocalPosition(Vector3(Math::randRange(-50.0f, 50.0f), 0.0f, Math::randRange(-50.0f, 50.0f)));
		}
	}
}
