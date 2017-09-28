#include "Assignment1Test.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Propeller.h"
#include "FancyPropeller.h"
#include "Jar.h"

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

		


		/***Task 1: Jar***/
		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8, 0.8, 0.9, 1);
		
		Jar *jar = new Jar(this);
		jar->setMaterial(grey); 
		jar->arm1->setMaterial(grey);
		jar->arm2->setMaterial(grey);
		jar->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		jar->getTransform()->setLocalScale(Vector3(10, 10, 10));
		jar->getTransform()->setParent(root);

		/*jar->body->setMaterial(grey); //Set material of the base sub component so that it's visible
		
		jar->baseJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 10, Math::PI / 4, 0)));
		jar->elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 8, 0, 0)));
		jar->shadeJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 1.8, 0, 0)));*/
		
		/***Task 3: Propeller***/
		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 1, 0, 1);
		
		GameObject *propeller = new GameObject(this);
		propeller->setMesh(new Propeller(8, 2, 0.5, Math::PI/6, 7, 21));
		propeller->setMaterial(green);
		propeller->getTransform()->setLocalPosition(Vector3(0, 0, -30));
		propeller->getTransform()->setParent(root);
		propeller->getTransform()->name = "Propeller";

		/**Task 4: Fancy Propeller**/
		GameObject *fancyPropeller = new GameObject(this);
		Material *red = renderer->createMaterial(Renderer::PR_OPAQUE);
		red->setDiffuse(1, 0, 0, 1);
		float bladeProfile[1] = {1.0f};
		fancyPropeller->setMesh(new FancyPropeller(8, 2, 0.5, 21, Math::PI / 6, 7, bladeProfile, 1));
		fancyPropeller->setMaterial(red);
		fancyPropeller->getTransform()->setLocalPosition(Vector3(0, 0, -60));
		fancyPropeller->getTransform()->setParent(root);
		fancyPropeller->getTransform()->name = "FancyPropeller";
		return true;
	}
}