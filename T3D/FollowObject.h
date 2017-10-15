#pragma once
#include "Component.h"
#include "Transform.h"
#include "Vector3.h"

namespace T3D {

	class FollowObject : public Component {
	public: 
		FollowObject(Transform *target, Vector3 offset, Vector3 angle) : target(target), offset(offset), angle(angle) {}
		~FollowObject();

		Transform *target;
		Vector3 offset;
		Vector3 angle;

		virtual void update(float dt);
	};
}