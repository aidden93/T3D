#include "AnimationTute.h"
#include "AnimationTest.h"
#include "Lamp.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Animation.h"

namespace T3D {

	AnimationTute::AnimationTute(void) {}
	AnimationTute::~AnimationTute(void) {}

	bool AnimationTute::init() {
		WinGLApplication::init();

		//Light
		GameObject *lightObj = new GameObject(this);
		Light *light = new Light(Light::DIRECTIONAL);
		light->setAmbient(1, 1, 1);
		light->setDiffuse(1, 1, 1);
		light->setSpecular(1, 1, 1);
		lightObj->setLight(light);
		lightObj->getTransform()->setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
		lightObj->getTransform()->setParent(root);

		//Camera
		GameObject *camObj = new GameObject(this);
		renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(0, 0, 20));
		camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		camObj->addComponent(new KeyboardController()); //Allow the camera to be controlled by keyboard


		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8, 0.8, 0.9, 1);

		Lamp *lamp = new Lamp(this);
		lamp->setMaterial(grey);
		lamp->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		lamp->getTransform()->setLocalScale(Vector3(10, 10, 10));
		lamp->getTransform()->setParent(root);

		lamp->base->setMaterial(grey); //Set material of the base sub component so that it's visible
		lamp->arm1->setMaterial(grey);
		lamp->arm2->setMaterial(grey);
		lamp->shade->setMaterial(grey);

		lamp->baseJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 10, Math::PI / 4, 0)));
		lamp->elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 8, 0, 0)));
		lamp->shadeJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 1.8, 0, 0)));

		AnimationTest *animTask = new AnimationTest(this);
		animTask->lamp = lamp->getTransform();
		addTask(animTask);

		Animation *anim = new Animation(10.0);
		lamp->addComponent(anim);
		anim->addKey("ElbowJoint", 10.0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
		anim->addKey("ElbowJoint", 0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
		anim->addKey("ElbowJoint", 7.0, Quaternion(Vector3(Math::HALF_PI, 0, 0)), Vector3(0, 0.2, 0));
		anim->addKey("ElbowJoint", 5.0, Quaternion(Vector3(-Math::HALF_PI, 0, 0)), Vector3(0, 0.2, 0));
		anim->addKey("ShadeJoint", 10.0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
		anim->addKey("ShadeJoint", 0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
		anim->addKey("ShadeJoint", 7.0, Quaternion(Vector3(0, 0, Math::HALF_PI)), Vector3(0, 0.2, 0));
		anim->addKey("ShadeJoint", 5.0, Quaternion(Vector3(0, 0, -Math::HALF_PI)), Vector3(0, 0.2, 0));
		anim->loop(true);
		anim->play();

		return true;
	}
}

