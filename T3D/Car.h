#pragma once
#include "GameObject.h"

namespace T3D {
	class Car : public GameObject {
	public: Car(T3DApplication *app);
			~Car();

			GameObject *rail;
	};
}