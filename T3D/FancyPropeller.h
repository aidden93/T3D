#pragma once
#include "Mesh.h"

namespace T3D {
	class FancyPropeller : public Mesh
	{
	public:FancyPropeller(float radius, // the outer radius of the propeller
		float hubRadius, // the radius of the propeller hub
		float height, // the z-thickness of the hub and blades	
		int density, // the density of the hub (a multiple of blades)
		float attackAngle, // the twist applied to the top hub vertices
		int blades, // the number of blades
		float *bladeProfile, // an array specifying the blade profile
		int bladeDensity // the density of each blade
	);
		   virtual ~FancyPropeller(void);
		   void setVertexFromVector(int idx, Vector3 vector);
	};
}