#pragma once
#include "Task.h"
#include "T3DApplication.h"
#include "Person.h"

namespace T3D {

	class RaiseArms : public Task {
	public: RaiseArms(T3DApplication *app);
			virtual ~RaiseArms(void);

			void update(float dt);
			void setState(int state);

			Person *person;
			float elapsedTime;
			enum animationStates { START, FIRST_CLIMB, STRAIGHT_BEFORE_FIRST_DROP, FIRST_DROP };
			int currentState = START;
	};

}