#pragma once
#include "GameObject.h"

namespace T3D {
	class Person : public GameObject
	{
	public:Person(T3DApplication *app);
		   virtual ~Person(void);
		   void init(GameObject *go);

		   GameObject *head;

		   GameObject *neckJoint;

		   GameObject *body;

		   GameObject *leftShoulderJoint;
		   GameObject *rightShoulderJoint;

		   GameObject *leftArm;
		   GameObject *rightArm;

		   GameObject *rightElbowJoint;
		   GameObject *leftElbowJoint;
		   
		   GameObject *leftForearm;
		   GameObject *rightForearm;
		   
		   GameObject *rightWristJoint;
		   GameObject *leftWristJoint;

		   GameObject *leftHand;
		   GameObject *rightHand;
	};
}