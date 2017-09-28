#include "Human.h"
#include "Cylinder.h"
#include "DrawTask.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {

	Human::Human(T3DApplication *app) : GameObject(app) {
		//setMesh(new Cylinder(.1, .01, 16));
		//getTransform()->name = "Human";

	}

	Human::~Human() {

	}
}