#include "FollowObject.h"
#include "GameObject.h"

namespace T3D {

	void FollowObject::update(float dt) {
		gameObject->getTransform()->setLocalRotation(target->getEulerAngles());
		gameObject->getTransform()->setLocalPosition(target->getLocalPosition() + offset);
	}

	FollowObject::~FollowObject() {}
}