#include "Assignment1Test.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Propeller.h"

namespace T3D {

	Assignment1Test::Assignment1Test(void) {}

	Assignment1Test::~Assignment1Test(void)
	{
	}


	bool Assignment1Test::init() {
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
		camObj->addComponent(new KeyboardController());

		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 1, 0, 1);


		GameObject *propeller = new GameObject(this);
		propeller->setMesh(new Propeller(3, 2, 0.5, /*Math::PI/8*/0, 4, 12));
		propeller->setMaterial(green);
		propeller->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		propeller->getTransform()->setParent(root);
		propeller->getTransform()->name = "Propeller";
		return true;
	}
}