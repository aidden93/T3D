#include "Lamp.h"
#include "Cylinder.h"
#include "DrawTask.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {

	Lamp::Lamp(T3DApplication *app) : GameObject(app) {
		setMesh(new Cylinder(.1, .01, 16));
		getTransform()->name = "Lamp";

		//Configure the base sub component
		base = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
		base->setMesh(new Cylinder(.02, .01, 16));
		base->getTransform()->setParent(getTransform()); // attaching this piece to the Lamp object's transform
		base->getTransform()->setLocalPosition(Vector3(0, 0.02, 0));
		base->getTransform()->name = "Base";

		//Configure the base joint sub component
		baseJoint = new GameObject(app);
		baseJoint->getTransform()->setParent(base->getTransform());
		baseJoint->getTransform()->name = "BaseJoint";

		//Configure the elbow joint sub component
		elbowJoint = new GameObject(app);
		elbowJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
		elbowJoint->getTransform()->setParent(baseJoint->getTransform());
		elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0))); // this rotation is just to make a good starting pose
		elbowJoint->getTransform()->name = "ElbowJoint";

		//Configure the shade  joint sub component
		shadeJoint = new GameObject(app);
		shadeJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
		shadeJoint->getTransform()->setParent(elbowJoint->getTransform());
		shadeJoint->getTransform()->name = "ShadeJoint";

		//Configure the sweep for the bottom arm sub component
		//Sweep profile. The profile is the vertices to be moved along the path
		std::vector<Vector3> armProfile;
		armProfile.push_back(Vector3(0.0f, -0.12f, 0.0f));
		armProfile.push_back(Vector3(0.014f, -0.114f, 0.0f));
		armProfile.push_back(Vector3(0.02f, -0.1f, 0.0f));
		armProfile.push_back(Vector3(0.02f, 0.1f, 0.0f));
		armProfile.push_back(Vector3(0.014f, 0.114f, 0.0f));
		armProfile.push_back(Vector3(0.0f, 0.12f, 0.0f));
		armProfile.push_back(Vector3(-0.014f, 0.114f, 0.0f));
		armProfile.push_back(Vector3(-0.02f, 0.1f, 0.0f));
		armProfile.push_back(Vector3(-0.02f, -0.1f, 0.0f));
		armProfile.push_back(Vector3(-0.014f, -0.114f, 0.0f));

		//Sweep path
		SweepPath armsp;
		Transform t;

		t.setLocalPosition(Vector3(-0.01, 0, 0)); //position 1cm in -ve x-direction
		t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0))); //Rotate so that profile is in YZ plane (from XY plane)
		t.setLocalScale(Vector3(0, 0, 1.0)); //scale to 0 %. no need to scale the z-direction because the profile is in the XY plane
		armsp.addTransform(t);

		t.setLocalScale(Vector3(0.9, 1, 1.0)); //Scale back up to 90 %
		armsp.addTransform(t);

		t.setLocalPosition(Vector3(-0.0075, 0, 0)); //move x-position to -0.75cm
		t.setLocalScale(Vector3(1, 1, 1.0)); //Scale to 100%
		armsp.addTransform(t);

		t.setLocalPosition(Vector3(0.0075, 0, 0)); //Move x-position to +0.75cm
		armsp.addTransform(t);

		t.setLocalPosition(Vector3(0.01, 0, 0)); //move to +1cm
		t.setLocalScale(Vector3(0.9, 1, 1.0)); //Scale to 90%
		armsp.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 1.0)); //Scale to 0%
		armsp.addTransform(t);
		armsp.addTransform(t); //Duplicate to fix shading

		//Arm1
		arm1 = new GameObject(app);
		arm1->setMesh(new Sweep(armProfile, armsp, false));
		arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm1->getTransform()->setParent(baseJoint->getTransform());
		arm1->getTransform()->name = "Arm1";

		//Arm2
		arm2 = new GameObject(app);
		arm2->setMesh(new Sweep(armProfile, armsp, false));
		arm2->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm2->getTransform()->setParent(elbowJoint->getTransform());
		arm2->getTransform()->name = "Arm2";

		//Lamp shade sweep
		//Profile
		std::vector<Vector3> shadeProfile;


		//outside

		shadeProfile.push_back(Vector3(0.0f, -0.136f, 0.0f));
		shadeProfile.push_back(Vector3(0.116f, -0.086f, 0.0f));
		shadeProfile.push_back(Vector3(0.159f, 0.103f, 0.0f));
		shadeProfile.push_back(Vector3(0.240f, 0.255f, 0.0f));
		shadeProfile.push_back(Vector3(0.272f, 0.370f, 0.0f));
		shadeProfile.push_back(Vector3(0.272f, 0.370f, 0.0f));

		//inside
		shadeProfile.push_back(Vector3(0.260f, 0.378f, 0.0f));
		shadeProfile.push_back(Vector3(0.260f, 0.378f, 0.0f));
		shadeProfile.push_back(Vector3(0.222f, 0.260f, 0.0f));
		shadeProfile.push_back(Vector3(0.140f, 0.107f, 0.0f));
		shadeProfile.push_back(Vector3(0.140f, 0.107f, 0.0f));
		shadeProfile.push_back(Vector3(0.0f, 0.106f, 0.0f));

		SweepPath shadePath;
		shadePath.makeCirclePath(0, 10);
		shade = new GameObject(app);
		shade->setMesh(new Sweep(shadeProfile, shadePath, true));
		shade->getTransform()->setLocalScale(Vector3(0.4f, 0.4f, 0.4f));
		shade->getTransform()->setLocalPosition(Vector3(0, 0.01, 0));
		shade->getTransform()->setParent(shadeJoint->getTransform());
		shade->getTransform()->name = "Shade";
	}

	Lamp::~Lamp() {

	}
}