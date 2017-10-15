#include "SteeringTutorial.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Sphere.h"
#include "Pyramid.h"
#include "FlockingBehaviour.h"
#include "TargetJump.h"

namespace T3D {

	SteeringTutorial::SteeringTutorial() {}
	SteeringTutorial::~SteeringTutorial() {}

	bool SteeringTutorial::init() {
		WinGLApplication::init();

		// Add a light
		GameObject *lightObj = new GameObject(this);
		Light *light = new Light(Light::DIRECTIONAL);
		light->setAmbient(1, 1, 1);
		light->setDiffuse(1, 1, 1);
		light->setSpecular(1, 1, 1);
		lightObj->setLight(light);
		lightObj->getTransform()->setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
		lightObj->getTransform()->setParent(root);

		renderer->ambient[0] = 0.2;
		renderer->ambient[1] = 0.2;
		renderer->ambient[2] = 0.2;

		// And some materials
		Material *orange = renderer->createMaterial(Renderer::PR_OPAQUE);
		orange->setDiffuse(1, 0.6, 0.1, 1);

		Material *black = renderer->createMaterial(Renderer::PR_OPAQUE);
		black->setDiffuse(0.0, 0.0, 0.0, 1);

		Material *red = renderer->createMaterial(Renderer::PR_OPAQUE);
		red->setDiffuse(1, 0.0, 0.0, 1);

		// Create a camera
		GameObject *camObj = new GameObject(this);
		renderer->camera = new Camera(Camera::PERSPECTIVE, 20.0, 500.0, 45.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(60, 100, 0));
		camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
		camObj->getTransform()->lookAt(Vector3(0, 0, 0));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		camObj->addComponent(new KeyboardController()); //Allow the camera to be controlled by keyboard
			

		//FLOCKING

		//Add a "flat sphere" to use as the target
		GameObject *target = new GameObject(this);
		target->setMesh(new Sphere(1.5, 32));
		target->setMaterial(red);
		target->getTransform()->setParent(root);
		target->getTransform()->setLocalScale(Vector3(1.0f, 0.05f, 1.0f));
		target->getTransform()->name = "target";

		GameObject *flock = new GameObject(this);
		flock->getTransform()->setParent(root);

		for (int i = 0; i < 10; i++) {

			//Add a sphere as the boid
			GameObject *boid = new GameObject(this);
			boid->setMesh(new Sphere(1, 32));
			boid->setMaterial(orange);
			boid->getTransform()->setParent(flock->getTransform());
			boid->getTransform()->setLocalPosition(Vector3(Math::randRange(-50.0f, 50.0f), 1.0f, Math::randRange(-50.0f, 50.0f)));
			boid->getTransform()->name = "boid"+i;

			//Add a pyramid mesh (so we can see which way the boid is facing)
			GameObject *pyramid = new GameObject(this);
			pyramid->setMesh(new Pyramid(0.5));
			pyramid->setMaterial(black);
			pyramid->getTransform()->setParent(boid->getTransform());
			pyramid->getTransform()->setLocalPosition(Vector3(0.0f, 0.0f, 1.05f));
			pyramid->getTransform()->setLocalScale(Vector3(1.0f, 0.75f, 1.0f));
			pyramid->getTransform()->rotate(Vector3(90 * Math::DEG2RAD, 0, 0));
			pyramid->getTransform()->name = "pyramid";

			// Add the steering behaviour
			boid->addComponent(new FlockingBehaviour(target->getTransform()));
			boid->addComponent(new TargetJump(15));
		}
		return true;
	}
}