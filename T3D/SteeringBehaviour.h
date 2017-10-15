#pragma once
#include "Component.h"
#include "Vector3.h"
#include "Transform.h"


#define MAX_VEL 10.0f
#define MAX_TURN 10.0f
#define MAX_ACC 20.0f

namespace T3D
{
	class SteeringBehaviour : public Component {
		public: SteeringBehaviour(Transform *target) : target(target) {
				velocity = Vector3(0, 0, 0);
			}
			virtual ~SteeringBehaviour();

			virtual void update(float dt);
			virtual Vector3 getAcc();
		public:
			Transform *target;
			Vector3 velocity;
	};
}