#include "Assignment2.h"
#include "Camera.h"
#include "Track.h"
#include "Car.h"
#include "CarMovement.h"
#include "Person.h"
#include "FollowObject.h"
#include "RaiseArms.h"
#include "House.h"
#include "PlaneMesh.h"
#include "LookAtBehaviour.h"

namespace T3D {

	Assignment2::Assignment2(void) {}

	Assignment2::~Assignment2(void)
	{
	}


	bool Assignment2::init() {
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
		camObj->getTransform()->setLocalPosition(Vector3(0, 30, 10));
		camObj->getTransform()->setLocalRotation(Vector3(-Math::PI / 8, Math::PI, 0));
		camObj->setCamera(renderer->camera);

		//Track
		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0, 1, 0, 1);

		Track *track = new Track(this);
		track->setMaterial(green);
		track->getTransform()->setLocalScale(Vector3(10, 10, 10));
		track->getTransform()->setParent(root);
		track->getTransform()->setWorldPosition(Vector3(0, 0, 0));

		//Car
		Material *red = renderer->createMaterial(Renderer::PR_OPAQUE);
		red->setDiffuse(1, 0, 0, 1);
		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.662745, 0.662745, 0.662745, 1);
		


		Car *car = new Car(this);
		car->setMaterial(red);
		car->rail->setMaterial(grey);
		car->getTransform()->setLocalScale(Vector3(20, 1, 15));
		car->getTransform()->setParent(root);
		car->getTransform()->setWorldPosition(Vector3(0, 11, 15));

		CarMovement *movementTask = new CarMovement(this);
		movementTask->car = car->getTransform();
		addTask(movementTask);

		//GameObject *camContainer = new GameObject(this);
		//camObj->getTransform()->setParent(camContainer->getTransform());

		//CarMovement *movementTask2 = new CarMovement(this);
		//movementTask2->car = camContainer->getTransform();
		//addTask(movementTask2);

		//camObj->getTransform()->setLocalPosition(Vector3(0, 50, 20));

		//camObj->addComponent(new FollowObject(car->getTransform(), Vector3(40, 40, -40), Vector3(-Math::PI / 8, Math::PI, 0)));

		//Person
		Material *purple = renderer->createMaterial(Renderer::PR_OPAQUE);
		purple->setDiffuse(0.61179, 0.08627, 0.9647, 1);
		Material *blue = renderer->createMaterial(Renderer::PR_OPAQUE);
		blue->setDiffuse(0, 0, 1, 1);
		Material *yellow = renderer->createMaterial(Renderer::PR_OPAQUE);
		yellow->setDiffuse(1, 1, 0, 1);

		Person *person = new Person(this);
		person->setMaterial(purple);
		person->getTransform()->setParent(car->getTransform());
		person->getTransform()->setLocalScale(Vector3(0.05 * 3.5, 3.5, 0.06666666666666666666666666666667 * 3.5));
		person->getTransform()->setLocalPosition(Vector3(0, 9, -0.15));
		person->init(person);

		person->head->setMaterial(red);
		person->body->setMaterial(purple);
		person->leftArm->setMaterial(green);
		person->leftForearm->setMaterial(blue);
		person->leftHand->setMaterial(yellow);
		person->rightArm->setMaterial(green);
		person->rightForearm->setMaterial(blue);
		person->rightHand->setMaterial(yellow);


		camObj->getTransform()->setParent(person->head->getTransform());
		camObj->getTransform()->setLocalPosition(Vector3(-10, 30, 20));
		camObj->getTransform()->setLocalRotation(Vector3(Math::PI, 0, 0));

		LookAtBehaviour *look = new LookAtBehaviour(person->head->getTransform());
		camObj->addComponent(look);

		RaiseArms *raiseArms = new RaiseArms(this);
		raiseArms->person = person;
		addTask(raiseArms);

		/*House*/
		Texture *housetex = new Texture("Resources/house.jpg", true, true);
		renderer->loadTexture(housetex);
		Material *housemat = renderer->createMaterial(Renderer::PR_OPAQUE);
		housemat->setTexture(housetex);

		GameObject *house = new GameObject(this);
		house->setMesh(new House(5, 7, 5.5));
		house->setMaterial(housemat);
		house->getTransform()->setLocalPosition(Vector3(60, 50, 320));
		house->getTransform()->setLocalScale(Vector3(10, 10, 10));
		house->getTransform()->setParent(root);
		house->getTransform()->name = "House";

		/*PlaneMesh *plane = new PlaneMesh(100);
		GameObject *floor = new GameObject(this); 
		floor->setMesh(plane);
		floor->setMaterial(red);*/

		return true;
	}
}