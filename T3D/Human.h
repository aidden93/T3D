#pragma once
#include "GameObject.h"

namespace T3D {
	class Human : public GameObject
	{
	public:Human(T3DApplication *app);
		   virtual ~Human(void);

		   GameObject *leftFoot;
		   GameObject *leftAnkleJoint;

		   GameObject *rightFoot;
		   GameObject *rightAnkleJoint;

		   GameObject *leftLowerLeg;
		   GameObject *leftKneeJoint;
		   GameObject *leftUpperLeg;

		   GameObject *rightLowerLeg;
		   GameObject *rightKneeJoint;
		   GameObject *rightUpperLeg;

		   GameObject *leftHipJoint;
		   GameObject *rightHipJoint;

		   GameObject *torso;
		   GameObject *neckJoint;
		   GameObject *head;
	};
}