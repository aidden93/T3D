#include "LightingTute.h"
#include "Sphere.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "GLShader.h"

namespace T3D {

	LightingTute::LightingTute(void) {}

	LightingTute::~LightingTute(void) {}

	bool LightingTute::init() {
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


		Material *fixedGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
		fixedGreen->setDiffuse(0.0, 0.6, 0, 1);
		fixedGreen->setShininess(20);
		Material *gouraudGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
		gouraudGreen->setDiffuse(0.0, 0.6, 0, 1);
		gouraudGreen->setShininess(20);
		Material *phongGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
		phongGreen->setDiffuse(0.0, 0.6, 0, 1);
		phongGreen->setShininess(20);

		GLShader *gouraudShader = new GLShader("Resources/vspecular.shader", "Resources/frag.shader");
		gouraudShader->compileShader();
		gouraudGreen->setShader(gouraudShader);

		GLShader *phongShader = new GLShader("Resources/phongVert.shader", "Resources/phongFrag.shader");
		phongShader->compileShader();
		phongGreen->setShader(phongShader);

		GameObject *sphereObj = new GameObject(this);
		sphereObj->setMesh(new Sphere(10, 32));
		sphereObj->setMaterial(fixedGreen);
		sphereObj->getTransform()->setLocalPosition(Vector3(-20, 0, 0));
		sphereObj->getTransform()->setParent(root);

		GameObject *sphereObj2 = new GameObject(this);
		sphereObj2->setMesh(new Sphere(10, 32));
		sphereObj2->setMaterial(gouraudGreen);
		sphereObj2->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		sphereObj2->getTransform()->setParent(root);

		GameObject *sphereObj3 = new GameObject(this);
		sphereObj3->setMesh(new Sphere(10, 32));
		sphereObj3->setMaterial(phongGreen);
		sphereObj3->getTransform()->setLocalPosition(Vector3(20, 0, 0));
		sphereObj3->getTransform()->setParent(root);

		return true;
	}
}