#include "Propeller.h"
#include "Math.h"

namespace T3D {

	Propeller::Propeller(float radius, float hubRadius, float height, float attackAngle, int blades, int density) {
		initArrays((density * 4 + 2) /*Hub vertices*/ + (blades * 4 * 6) /*Blade vertices*/, 
			density * 2 /*Only the caps use triangles*/, 
			density /*Hub quads*/ + (6 * blades)); 

		int i;
		float theta;
		/***
		* Cylinder code - For the hub
		***/
		
		//Set the edge vertices 
		for (i = 0; i<density; i++) {
			theta = i * (Math::TWO_PI / density);

			setVertex(i, hubRadius*cos(theta), height, hubRadius*sin(theta));
			setVertex(density + i, hubRadius*cos(theta), -height, hubRadius*sin(theta));

			//Duplicates for the top and bottom faces
			setVertex(density * 2 + i, hubRadius*cos(theta), height, hubRadius*sin(theta));
			setVertex(density * 3 + i, hubRadius*cos(theta), -height, hubRadius*sin(theta));
		}

		//Set the top and bottom center vertices
		setVertex(density * 4, 0, height, 0);
		setVertex(density * 4 + 1, 0, -height, 0);

		//Set the side faces
		for (i = 0; i<density; i++) {

			//Set the side face
			setFace(i,
				i,         // current top vertex
				(i + 1) % density,   // next top vertex (with wrapping)
				density + (i + 1) % density, // next bottom vertex (with wrapping) 
				density + i        // current bottom vertex
			);

			//Set the triangles attached to the current side face that form the caps
			setFace(i, density * 4, (i + 1) % density + (density * 2), (density * 2) + i);
			setFace(density + i, density * 4 + 1, density * 3 + i, (i + 1) % density + (density * 3));
		}

		/***
		* Cube code - For the blades
		***/
		//for (int i = 0; i < )
		//Blades line up with a single face on the cylinder

		checkArrays();
		calcNormals();
	}

	Propeller::~Propeller(void) {

	}
}