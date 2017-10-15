#include "Track.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {



	Track::Track(T3DApplication *app) : GameObject(app) {
		int uvpos = 0;
		SweepPath path;
		Transform t;
		std::vector<Vector3> profile;
		profile.push_back(Vector3(0.0, 0.0, 0.0));
		profile.push_back(Vector3(1.0, 0.0, 0.0));
		profile.push_back(Vector3(1.0, 1.0, 0.0));
		profile.push_back(Vector3(1.0, 1.0, 0.0));
		profile.push_back(Vector3(0.75, 1.0, 0.0));
		profile.push_back(Vector3(0.75, 1.0, 0.0));
		profile.push_back(Vector3(0.75, 0.5, 0.0));
		profile.push_back(Vector3(0.75, 0.5, 0.0));
		profile.push_back(Vector3(0.0, 0.5, 0.0));
		profile.push_back(Vector3(-0.75, 0.5, 0.0));
		profile.push_back(Vector3(-0.75, 0.5, 0.0));
		profile.push_back(Vector3(-0.75, 1.0, 0.0));
		profile.push_back(Vector3(-0.75, 1.0, 0.0));
		profile.push_back(Vector3(-1.0, 1.0, 0.0));
		profile.push_back(Vector3(-1.0, 1.0, 0.0));
		profile.push_back(Vector3(-1.0, 0.0, 0.0));

		/*
		* Close the ends of the track
		*/
		t.setLocalScale(Vector3(0, 0, 1.0)); //scale to 0 % to seal the ends
		t.setLocalPosition(Vector3(1, 1, 0));
		path.addTransform(t);
		t.setLocalScale(Vector3(1.0, 1.0, 1.0));


		/*
		* Path
		*/

		t.setLocalPosition(Vector3(0, 0, 0));
		path.addTransform(t);

		t.setLocalPosition(Vector3(0,0,20));
		path.addTransform(t);

		t.setLocalPosition(Vector3(0, 10, 40));
		path.addTransform(t);

		t.setLocalPosition(Vector3(0, 10, 50));
		path.addTransform(t);

		t.setLocalPosition(Vector3(0, -10, 60));
		path.addTransform(t);

		t.setLocalPosition(Vector3(-20, -10, 70));
		//t.setLocalRotation(Vector3(0, Math::PI / 2, 0));
		path.addTransform(t);

		/*
		* Close the ends of the track
		*/
		t.setLocalScale(Vector3(0, 0, 1.0)); //scale to 0 % to seal the ends
		Vector3 pos = t.getLocalPosition();
		t.setLocalPosition(Vector3(pos.x+1, pos.y+1, pos.z));
		path.addTransform(t);
		path.addTransform(t);

		Sweep *mesh = new Sweep(profile, path, false);
		setMesh(mesh);
		getTransform()->setLocalPosition(Vector3(0, 0, 0));
		getTransform()->name = "Track";
	}
}