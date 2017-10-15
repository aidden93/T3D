#include "Person.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "DrawTask.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {

	Person::Person(T3DApplication *app) : GameObject(app) {
	
	}

	void Person::init(GameObject *go) {
//setMesh(new Cylinder(.1, .01, 16));
		go->getTransform()->name = "Person";
		float armRadius=0.3;
		float armLength=0.8;
		float forearmRadius = 0.2;
		float forearmLength = 0.7;
		float headRadius = 0.8;
		float bodyLength = 1.2;
		float bodyRadius = 1;
		float handRadius = 0.2;

		//Configure the body sub component
		body = new GameObject(app); 
		body->setMesh(new Cylinder(bodyRadius, bodyLength, 16));
		body->getTransform()->setParent(getTransform()); // attaching this piece to the Person object's transform
		body->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		body->getTransform()->name = "Body";

		//Configure the neck joint sub component
		neckJoint = new GameObject(app);
		neckJoint->getTransform()->setLocalPosition(Vector3(0, bodyLength, 0));
		neckJoint->getTransform()->setParent(body->getTransform());
		neckJoint->getTransform()->name = "NeckJoint";

		//Configure the head sub component
		head = new GameObject(app);
		head->setMesh(new Sphere(headRadius, 16));
		head->getTransform()->setLocalPosition(Vector3(0, headRadius, 0));
		head->getTransform()->setParent(neckJoint->getTransform());
		head->getTransform()->name = "Head";



		//Configure the left shoulder joint sub component
		leftShoulderJoint = new GameObject(app);
		leftShoulderJoint->getTransform()->setParent(body->getTransform());
		leftShoulderJoint->getTransform()->setLocalPosition(Vector3(bodyRadius, bodyLength-armLength, 0));
		leftShoulderJoint->getTransform()->name = "LeftShoulderJoint";

		//Configure the left arm sub component
		leftArm = new GameObject(app);
		leftArm->setMesh(new Cylinder(armRadius, armLength, 16));
		leftArm->getTransform()->setParent(leftShoulderJoint->getTransform());
		leftArm->getTransform()->setLocalPosition(Vector3(armRadius, 0, 0));
		leftArm->getTransform()->name = "LeftArm";

		//Configure the elbow joint sub component
		leftElbowJoint = new GameObject(app);
		leftElbowJoint->getTransform()->setLocalPosition(Vector3(0, -armLength, 0));
		leftElbowJoint->getTransform()->setParent(leftArm->getTransform());
		//leftElbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 4, 0, 0))); // this rotation is just to make a good starting pose
		leftElbowJoint->getTransform()->name = "LeftElbowJoint";

		//Configure the forearm sub component
		leftForearm = new GameObject(app);
		leftForearm->setMesh(new Cylinder(forearmRadius, forearmLength, 16));
		leftForearm->getTransform()->setLocalPosition(Vector3(0, -forearmLength, 0));
		leftForearm->getTransform()->setParent(leftElbowJoint->getTransform());
		leftForearm->getTransform()->name = "LeftForearm";

		leftWristJoint = new GameObject(app);
		leftWristJoint->getTransform()->setLocalPosition(Vector3(0, -forearmLength, 0));
		leftWristJoint->getTransform()->setParent(leftForearm->getTransform());
		leftWristJoint->getTransform()->name = "LeftWristJoint";

		//Configure the left hand sub component
		leftHand = new GameObject(app);
		leftHand->setMesh(new Sphere(handRadius, 16));
		leftHand->getTransform()->setLocalPosition(Vector3(0, -handRadius, 0));
		leftHand->getTransform()->setParent(leftWristJoint->getTransform());
		leftHand->getTransform()->name = "LeftHand";


		//Configure the right shoulder joint sub component
		rightShoulderJoint = new GameObject(app);
		rightShoulderJoint->getTransform()->setParent(body->getTransform());
		rightShoulderJoint->getTransform()->setLocalPosition(Vector3(-bodyRadius, bodyLength - armLength, 0));
		rightShoulderJoint->getTransform()->name = "RightShoulderJoint";

		//Configure the right arm sub component
		rightArm = new GameObject(app);
		rightArm->setMesh(new Cylinder(armRadius, armLength, 16));
		rightArm->getTransform()->setParent(rightShoulderJoint->getTransform());
		rightArm->getTransform()->setLocalPosition(Vector3(-armRadius, 0, 0));
		rightArm->getTransform()->name = "RightArm";

		//Configure the elbow joint sub component
		rightElbowJoint = new GameObject(app);
		rightElbowJoint->getTransform()->setLocalPosition(Vector3(0, -armLength, 0));
		rightElbowJoint->getTransform()->setParent(rightArm->getTransform());
		//rightElbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 4, 0, 0))); // this rotation is just to make a good starting pose
		rightElbowJoint->getTransform()->name = "RightElbowJoint";

		//Configure the forearm sub component
		rightForearm = new GameObject(app);
		rightForearm->setMesh(new Cylinder(forearmRadius, forearmLength, 16));
		rightForearm->getTransform()->setLocalPosition(Vector3(0, -forearmLength, 0));
		rightForearm->getTransform()->setParent(rightElbowJoint->getTransform());
		rightForearm->getTransform()->name = "RightForearm";

		rightWristJoint = new GameObject(app);
		rightWristJoint->getTransform()->setLocalPosition(Vector3(0, -forearmLength, 0));
		rightWristJoint->getTransform()->setParent(rightForearm->getTransform());
		rightWristJoint->getTransform()->name = "RightWristJoint";

		//Configure the right hand sub component
		rightHand = new GameObject(app);
		rightHand->setMesh(new Sphere(handRadius, 16));
		rightHand->getTransform()->setLocalPosition(Vector3(0, -handRadius, 0));
		rightHand->getTransform()->setParent(rightWristJoint->getTransform());
		rightHand->getTransform()->name = "RightHand";
	}

	Person::~Person() {

	}
}