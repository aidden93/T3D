#pragma once
#include "GameObject.h"

namespace T3D {
	class Jar : public GameObject
	{
	public:Jar(T3DApplication *app);
		   virtual ~Jar(void);

		   GameObject *body;
		   GameObject *arm1;
		   GameObject *arm2;
	};
}