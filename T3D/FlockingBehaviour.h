#pragma once
#include "SteeringBehaviour.h"

#define SEP_WEIGHT 10.0f
#define ALIGN_WEIGHT 0.1f
#define COH_WEIGHT 0.2f
#define SEEK_WEIGHT 0.5f
#define FLOCK_RANGE 20.0f

namespace T3D {
	class FlockingBehaviour :
		public SteeringBehaviour
	{
	public:
		FlockingBehaviour(Transform *target) : SteeringBehaviour(target) {
		}

		virtual ~FlockingBehaviour();

		virtual Vector3 getAcc();
	};
}