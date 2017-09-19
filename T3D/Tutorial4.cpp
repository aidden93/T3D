#include "Tutorial4.h"
#include "Camera.h"
#include "KeyboardController.h"
//#include "Pyramid.h"
//#include "Cylinder.h"
#include "Lamp.h"

namespace T3D{

	Tutorial4::Tutorial4(void) {}

	Tutorial4::~Tutorial4(void)
	{
	}


	bool Tutorial4::init() {
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
		
		//Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		//green->setDiffuse(0, 1, 0, 1);

		/*Pyramid
		GameObject *pyramid = new GameObject(this);
		pyramid->setMesh(new Pyramid(2));
		pyramid->setMaterial(green);
		pyramid->getTransform()->setLocalPosition(Vector3(15, 0, 0));
		pyramid->getTransform()->setParent(root);
		pyramid->getTransform()->name = "Pyramid";*/

		/*Cylinder
		GameObject *cylinder = new GameObject(this);
		cylinder->setMesh(new Cylinder(5,10, 8));
		cylinder->setMaterial(green);
		cylinder->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		cylinder->getTransform()->setParent(root);
		cylinder->getTransform()->name = "Cylinder";
		*/

		/*Lamp*/
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

		return true;
	}
}