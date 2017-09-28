#include "Jar.h"
#include "DrawTask.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {

	Jar::Jar(T3DApplication *app) : GameObject(app) {
		//Configure the sweep for the bottom arm sub component
		//Sweep profile. The profile is the vertices to be moved along the path
		std::vector<Vector3> jarProfile;
		/*jarProfile.push_back(Vector3(0.0f, -0.12f, 0.0f));
		jarProfile.push_back(Vector3(0.014f, -0.114f, 0.0f));
		jarProfile.push_back(Vector3(0.02f, -0.1f, 0.0f));
		jarProfile.push_back(Vector3(0.02f, 0.1f, 0.0f));
		jarProfile.push_back(Vector3(0.014f, 0.114f, 0.0f));
		jarProfile.push_back(Vector3(0.0f, 0.12f, 0.0f));
		jarProfile.push_back(Vector3(-0.014f, 0.114f, 0.0f));
		jarProfile.push_back(Vector3(-0.02f, 0.1f, 0.0f));
		jarProfile.push_back(Vector3(-0.02f, -0.1f, 0.0f));
		jarProfile.push_back(Vector3(-0.014f, -0.114f, 0.0f));*/
		jarProfile.push_back(Vector3(0.0f, 0.0f, 0.0f));
		jarProfile.push_back(Vector3(0.085f, 0.0f, 0.0f));
		jarProfile.push_back(Vector3(0.126f, -0.048f, 0.0f));
		jarProfile.push_back(Vector3(0.126f, -0.100f, 0.0f));
		jarProfile.push_back(Vector3(0.085f, -0.164f, 0.0f));
		jarProfile.push_back(Vector3(0.0f, -0.164f, 0.0f));
		jarProfile.push_back(Vector3(-0.041f, -0.100f, 0.0f));
		jarProfile.push_back(Vector3(-0.041f, -0.048f, 0.0f));

		//Sweep path
		SweepPath jarPath;
		Transform t;

		t.setLocalPosition(Vector3(-0.01, 0, 0)); //position 1cm in -ve x-direction
		t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0))); //Rotate so that profile is in YZ plane (from XY plane)
		t.setLocalScale(Vector3(0, 0, 1.0)); //scale to 0 %. no need to scale the z-direction because the profile is in the XY plane
		jarPath.addTransform(t);

		t.setLocalScale(Vector3(0.9, 1, 1.0)); //Scale back up to 90 %
		jarPath.addTransform(t);

		t.setLocalPosition(Vector3(-0.0075, 0, 0)); //move x-position to -0.75cm
		t.setLocalScale(Vector3(1, 1, 1.0)); //Scale to 100%
		jarPath.addTransform(t);

		t.setLocalPosition(Vector3(0.0075, 0, 0)); //Move x-position to +0.75cm
		jarPath.addTransform(t);

		t.setLocalPosition(Vector3(0.01, 0, 0)); //move to +1cm
		t.setLocalScale(Vector3(0.9, 1, 1.0)); //Scale to 90%
		jarPath.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 1.0)); //Scale to 0%
		jarPath.addTransform(t);
		jarPath.addTransform(t); //Duplicate to fix shading

		//Arm1
		arm1 = new GameObject(app);
		arm1->setMesh(new Sweep(jarProfile, jarPath, false));
		arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm1->getTransform()->setParent(getTransform());
		arm1->getTransform()->name = "Arm1";

		//Arm2
		arm2 = new GameObject(app);
		arm2->setMesh(new Sweep(jarProfile, jarPath, false));
		arm2->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm2->getTransform()->setParent(getTransform());
		arm2->getTransform()->name = "Arm2";
	}

	Jar::~Jar() {

	}
}