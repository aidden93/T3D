#include "FlockingBehaviour.h"
#include "GameObject.h"
#include "Transform.h"
#include "math.h"

namespace T3D {

	FlockingBehaviour::~FlockingBehaviour() {}

	Vector3 FlockingBehaviour::getAcc() {
		Transform* t = gameObject->getTransform(); // just for convenience
		Transform* flock = t->getParent();         // we are going to set up the flock so that they all have the same parent
		Vector3 seek = Vector3(0, 0, 0);
		Vector3 separate = Vector3(0, 0, 0);
		Vector3 cohesion = Vector3(0, 0, 0);
		Vector3 align = Vector3(0, 0, 0);
		Vector3 pos = t->getWorldPosition();

		// SEEK

		Vector3 desiredVel = (target->getWorldPosition() - pos).normalised() * MAX_VEL;
		desiredVel.y = 0.0f;
		seek = desiredVel - velocity;
		if (seek.length() > MAX_ACC) {
			seek *= MAX_ACC / seek.length();
		}

		// SEPARATE, COHESION and ALIGNMENT
		// initialise centre and velocity sums/averages
		Vector3 centre = Vector3(0, 0, 0);
		Vector3 flockVel = Vector3(0, 0, 0);
		int count = 0;
		for (int i = 0; i < flock->children.size(); i++) {
			Transform *ot = flock->children[i];
			Vector3 dir = pos - ot->getWorldPosition();
			float dist = dir.length();

			if ((dist < FLOCK_RANGE) && (ot != t)) { // another boid in range
				count++;  // count number in range

						  // update centre
				centre += ot->getWorldPosition();

				// nasty component search and casting to get the other boids velocity
				std::vector<Component*> components = ot->gameObject->getComponents();
				for (int c = 0; c < components.size(); c++) { // looking for the flocking behaviour
					FlockingBehaviour *behaviour = dynamic_cast<FlockingBehaviour*>(components[c]);
					if (behaviour != NULL) // found the flocking behaviour
					{
						flockVel += behaviour->velocity;
					}
				}

				// SEPARATE
				if (dist > 0.0f) { // not myself
					separate += dir / sqrt(dist);
				}
			}
		}

		// calculate averages for cohesion and alignment
		if (count > 0) {
			// calc average
			centre /= count;
			flockVel /= count;
		}

		cohesion += centre - t->getWorldPosition();
		align += flockVel - velocity;

		// COMBINE	
		Vector3 acc = SEEK_WEIGHT * seek + SEP_WEIGHT * separate + COH_WEIGHT*cohesion + ALIGN_WEIGHT*align;
		if (acc.length() > MAX_ACC) {
			acc *= MAX_ACC / acc.length();
		}
		acc.y = 0.0f; // just in case

		return acc;
	}
}