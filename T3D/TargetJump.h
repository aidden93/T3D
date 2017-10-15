#pragma once
#include "Component.h"
#include "Vector3.h"
#include "Transform.h"

namespace T3D
{
	class TargetJump : public Component {
		public: TargetJump(float jumpTime) : jumpTime(jumpTime) {};

			virtual ~TargetJump();

			virtual void update(float dt);

		private:
			float jumpTime;
			float timer;
	};
}