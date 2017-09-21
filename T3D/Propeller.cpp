#include "Propeller.h"
#include "Math.h"
#include <iostream>
namespace T3D {

	Propeller::Propeller(float radius, float hubRadius, float height, float attackAngle, int blades, int density) {
		initArrays((density * 4 + 2) /*Hub vertices*/ + (blades * 3)/*+ (blades * 4 * 6) Blade vertices*/, 
			density * 2 /*Cap triangles*/ + (density * 2) /*Hub sides as triangles*/ + (blades), 
			0/*density Hub quads*/ /*+  (6 * blades)Blade quads*/); 
		printf("tris %d \n", density * 2 /*Cap triangles*/ + (density * 2) /*Hub sides as triangles*/ + (blades * 2));
		int i;
		float theta;
		/***
		* Cylinder code - For the hub
		***/
		
		//Set the edge vertices 
		for (i = 0; i<density; i++) {
			theta = i * (Math::TWO_PI / density);

			setVertex(i, hubRadius*cos(theta+ attackAngle), height, hubRadius*sin(theta + attackAngle)); //Top
			setVertex(density + i, hubRadius*cos(theta), -height, hubRadius*sin(theta)); //Bottom

			//Duplicates vertices for the caps so that the connection between caps and the sides doesn't look smooth 
			setVertex(density * 2 + i, hubRadius*cos(theta + attackAngle), height, hubRadius*sin(theta + attackAngle)); //Top
			setVertex(density * 3 + i, hubRadius*cos(theta), -height, hubRadius*sin(theta)); //Bottom
		}

		//Set the top and bottom center vertices
		setVertex(density * 4, 0, height, 0);
		setVertex(density * 4 + 1, 0, -height, 0); 

		int step = (density / blades);
		float bladeLength = radius - hubRadius;
		int bladeVertexStartIndex = (density * 4) + 2;
		int bladeIndex = 0;
		
		//Set the blade vertices 
		for (i = 0; i < density; i += step) {
			theta = (Math::TWO_PI / density);
			printf("blade vertice:%d \n", bladeVertexStartIndex + (i/step));
			//End of blade
			setVertex(bladeVertexStartIndex + bladeIndex, bladeLength*cos((i + 1) * theta), -height, bladeLength*sin((i + 1) * theta)); //SW
			setVertex(bladeVertexStartIndex + bladeIndex + 1, bladeLength*cos((i) * theta), -height, bladeLength*sin((i) * theta)); //S
			setVertex(bladeVertexStartIndex + bladeIndex + 2, bladeLength*cos((i * theta) + attackAngle), height, bladeLength*sin((i * theta) + attackAngle)); //N

			bladeIndex++;
		}

		//Set the side faces
		for (i = 0; i<density; i++) {
			/***
			* Hub sides as triangles
			***/
			setFace(i, 
				(i + 1) % density + density, //south west
				i + density, //south 
				i); //north
			
			setFace(i+density, 
				(i + 1) % density, //north west
				(i + 1) % density + density, //south west
				i); //north


			//Create the triangles attached to the current side face to form the caps
			setFace(i + (density*2), density * 4, (i + 1) % density + (density * 2), (density * 2) + i);
			setFace(i + (density*3), density * 4 + 1, density * 3 + i, (i + 1) % density + (density * 3));
			
		}

		printf("bvert %d \n", bladeVertexStartIndex);
		int bladeFaceStartIndex = density*4;

		for (i = 0; i < blades; i ++) {
			setFace(bladeFaceStartIndex + i,
				bladeVertexStartIndex + i, //south west
				bladeVertexStartIndex + i + 1, //south 
				bladeVertexStartIndex + i + 2); //north

			/*setFace(bladeFaceStartIndex + i + 1,
				((2 * i) + 1) % density, //north west
				((2 * i) + 1) % density + density, //south west
				(2 * i)); //north*/
		}

		checkArrays();
		calcNormals();
	}

	Propeller::~Propeller(void) {

	}
}