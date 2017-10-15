#pragma once
#include "Task.h"
#include "T3DApplication.h";

namespace T3D {

	class CarMovement : public Task {
	public: CarMovement(T3DApplication *app);
			virtual ~CarMovement(void);

			void update(float dt);
			void setState(int state);

			Transform *car;
			float elapsedTime;
			enum animationStates {START, FIRST_CLIMB, STRAIGHT_BEFORE_FIRST_DROP, FIRST_DROP};
			int currentState = START;
	};

}