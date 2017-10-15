#include "TextureTute.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Cylinder.h"
#include "TCube.h"

namespace T3D{

	TextureTute::TextureTute(void) {}

	TextureTute::~TextureTute(void)
	{
	}


	bool TextureTute::init() {
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
		
		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 1, 0, 1);

		/*Cylinder*/
		GameObject *cylinder = new GameObject(this);
		cylinder->setMesh(new Cylinder(5,10, 8));
		cylinder->setMaterial(green);
		cylinder->getTransform()->setLocalPosition(Vector3(-20, 0, 0));
		cylinder->getTransform()->setParent(root);
		cylinder->getTransform()->name = "Cylinder";
		
		Texture *cratetex = new Texture("Resources/crate013jc.jpg", true, true);
		renderer->loadTexture(cratetex);
		Material *cratemat = renderer->createMaterial(Renderer::PR_OPAQUE);
		cratemat->setTexture(cratetex);

		/*Cube*/
		GameObject *tcube = new GameObject(this);
		tcube->setMesh(new TCube(5));
		tcube->setMaterial(cratemat);
		tcube->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		tcube->getTransform()->setParent(root);
		tcube->getTransform()->name = "TCube";


		return true;
	}
}