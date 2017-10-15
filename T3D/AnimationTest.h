#pragma once
#include "Task.h"
#include "T3DApplication.h";

namespace T3D {

	class AnimationTest : public Task {
		public: AnimationTest(T3DApplication *app);
				virtual ~AnimationTest(void);

				void update(float dt);

				Transform *lamp;
	};

}