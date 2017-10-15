#include "Car.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {

	Car::Car(T3DApplication *app) : GameObject(app) {
		SweepPath path;
		Transform t;
		std::vector<Vector3> profile;
		profile.push_back(Vector3(-0.5, 0, 1.0));
		profile.push_back(Vector3(-0.5, 0, 1.0));
		profile.push_back(Vector3(0.5, 0, 1.0));
		profile.push_back(Vector3(0.5, 0, 1.0));
		profile.push_back(Vector3(0.5, 0, -1));
		profile.push_back(Vector3(0.5, 0, -1));
		profile.push_back(Vector3(-0.5, 0, -1));

		/*
		* Close the bottom of the car from the outside
		*/
		t.setLocalScale(Vector3(0, 0, 0)); //scale to 0 % to seal the ends
		t.setLocalPosition(Vector3(0, 0, 0));
		path.addTransform(t);
		t.setLocalScale(Vector3(1, 1, 1));
		path.addTransform(t);


		/*
		* Path
		*/

		t.setLocalPosition(Vector3(0, 10, 0));
		path.addTransform(t); path.addTransform(t);

		t.setLocalScale(Vector3(0.9, 1, 0.9));
		path.addTransform(t); path.addTransform(t);

		t.setLocalPosition(Vector3(0, 0.1, 0));
		path.addTransform(t);
		path.addTransform(t); //Stops the bottom from rendering as 4 visible triangles

		t.setLocalScale(Vector3(0.1, 1, 0.1));
		path.addTransform(t);

		//Close the bottom of the car from the inside
		t.setLocalScale(Vector3(0, 0, 0));
		path.addTransform(t);

	
		setMesh(new Sweep(profile, path, false));
		getTransform()->setLocalPosition(Vector3(0, 0, 0));
		getTransform()->name = "Car";
	}
}