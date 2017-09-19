#include "Cylinder.h"
#include "Math.h"

namespace T3D {

	Cylinder::Cylinder(float radius, float height, int density) {
		initArrays(density*4 + 2, density * 2, density); //For the sides

		int i;
		float theta;
		
		//Set the edge vertices 
		for (i = 0; i<density; i++) {
			theta = i * (Math::TWO_PI / density);

			setVertex(i, radius*cos(theta), height, radius*sin(theta)); 
			setVertex(density + i, radius*cos(theta), -height, radius*sin(theta));

			//Duplicates for the top and bottom faces
			setVertex(density*2 + i, radius*cos(theta), height, radius*sin(theta));
			setVertex(density*3 + i, radius*cos(theta), -height, radius*sin(theta));
		}

		//Set the top and bottom center vertices
		setVertex(density*4, 0, height, 0);
		setVertex(density*4 + 1, 0, -height, 0);

		//Set the side faces
		for (i = 0; i<density; i++) {

			//Set the side face
			setFace(i,
				i,         // current top vertex
				(i + 1) % density,   // next top vertex (with wrapping)
				density + (i + 1) % density, // next bottom vertex (with wrapping) 
				density + i        // current bottom vertex
			);

			//Set the top and bottom triangles attached to the current side face
			setFace(i, density * 4, (i + 1) % density + (density * 2), (density * 2) + i);
			setFace(density + i, density * 4 + 1, density * 3 + i, (i + 1) % density + (density * 3));
		}

		checkArrays();
		calcNormals();
	}

	Cylinder::~Cylinder(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}