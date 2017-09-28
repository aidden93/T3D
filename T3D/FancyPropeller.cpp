#include "FancyPropeller.h"
#include "Math.h"
#include <iostream>
namespace T3D {

	FancyPropeller::FancyPropeller(float radius, float hubRadius, float height, int density, float attackAngle, int blades, float *bladeProfile, int bladeDensity) {
		initArrays((density * 4 + 2) /*Hub vertices*/ + (blades * 20)/*+ (blades * 4 * 6) Blade vertices*/, 
			density * 2 /*Cap triangles*/ + (density * 2) /*Hub sides as triangles*/ + (blades*10), 
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

		float thetaNext;
		int step = (density / blades);
		int bladeVertexStartIndex = (density * 4) + 2;
		int currentBladeVertex = bladeVertexStartIndex;
		float bladeLength = radius - hubRadius;
		
		//Set the blade vertices 
		for (i = 0; i < density; i+= step) {
			theta = i * (Math::TWO_PI / density);
			thetaNext = (i+1) * (Math::TWO_PI / density);
			printf("blade vertice:%d \n", currentBladeVertex);

			float thetaMid = (i + 0.5f) * (Math::TWO_PI / density);
			Vector3 unitVector = Vector3(cos(thetaMid), 0, sin(thetaMid));
			
			Vector3 topRight = Vector3(hubRadius*cos(theta + attackAngle), height, hubRadius*sin(theta + attackAngle));
			Vector3 bottomRight = Vector3(hubRadius*cos(theta), -height, hubRadius*sin(theta));
			Vector3 topLeft = Vector3(hubRadius*cos(thetaNext + attackAngle), height, hubRadius*sin(thetaNext + attackAngle));
			Vector3 bottomLeft = Vector3(hubRadius*cos(thetaNext), -height, hubRadius*sin(thetaNext));

			Vector3 topRightExtended = Vector3(topRight + (bladeLength * unitVector));
			Vector3 bottomRightExtended = Vector3(bottomRight + (bladeLength * unitVector));
			Vector3 topLeftExtended = Vector3(topLeft + (bladeLength * unitVector));
			Vector3 bottomLeftExtended = Vector3(bottomLeft + (bladeLength * unitVector));
			
			//End face of blade
			setVertexFromVector(currentBladeVertex, topRightExtended);//currentBladeVertex, topRightExtended.x, topRightExtended.y, topRightExtended.z); //Top right ********
			setVertexFromVector(currentBladeVertex + 1, bottomRightExtended); //Bottom right ********

			setVertexFromVector(currentBladeVertex + 2, topLeftExtended); //Top left ********
			setVertexFromVector(currentBladeVertex + 3, bottomLeftExtended); //Bottom left ********

			//Right face of blade
			setVertexFromVector(currentBladeVertex + 4, topRight); //Top on hub
			setVertexFromVector(currentBladeVertex + 5, bottomRight); //Bottom on hub
			setVertexFromVector(currentBladeVertex + 6, topRightExtended); //Top  ********
			setVertexFromVector(currentBladeVertex + 7, bottomRightExtended); //Bottom  ********

			//Left face of blade
			setVertexFromVector(currentBladeVertex + 8, topLeft); //Top next on hub
			setVertexFromVector(currentBladeVertex + 9, bottomLeft); //Bottom next on hub
			setVertexFromVector(currentBladeVertex + 10, topLeftExtended); //Top next  ********
			setVertexFromVector(currentBladeVertex + 11, bottomLeftExtended); //Bottom next ********

			//Top face of blade
			setVertexFromVector(currentBladeVertex + 12, topLeftExtended); //Top next  ********
			setVertexFromVector(currentBladeVertex + 13, topRightExtended); //Top  ********
			setVertexFromVector(currentBladeVertex + 14, topRight); //Top on hub
			setVertexFromVector(currentBladeVertex + 15, topLeft); //Top next on hub

			//Bottom face of blade
			setVertexFromVector(currentBladeVertex + 16, bottomLeftExtended); //Top next  ********
			setVertexFromVector(currentBladeVertex + 17, bottomRightExtended); //Top  ********
			setVertexFromVector(currentBladeVertex + 18, bottomRight); //Top on hub
			setVertexFromVector(currentBladeVertex + 19, bottomLeft); //Top next on hub

			currentBladeVertex += 20;

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

		
		int bladeFaceStartIndex = density*4;
		currentBladeVertex = bladeVertexStartIndex;

		for (i = 0; i < blades * 10; i += 10) {

			/**
			* End of blade
			**/printf("bvert %d \n", currentBladeVertex);
			setFace(bladeFaceStartIndex + i,
				currentBladeVertex + 3, //south west
				currentBladeVertex + 1, //south 
				currentBladeVertex); //north

			setFace(bladeFaceStartIndex + i + 1,
				currentBladeVertex + 2, //north west
				currentBladeVertex + 3, //south west
				currentBladeVertex); //north

			/**
			* Right side of blade
			**/
			setFace(bladeFaceStartIndex + i + 2,
				currentBladeVertex + 7, //south west
				currentBladeVertex + 5, //south 
				currentBladeVertex + 4); //north

			setFace(bladeFaceStartIndex + i + 3,
				currentBladeVertex + 6, //north west
				currentBladeVertex + 7, //south west
				currentBladeVertex + 4); //north

			/**
			* Left side of blade
			**/
			setFace(bladeFaceStartIndex + i + 4,
				currentBladeVertex + 9, //south west
				currentBladeVertex + 11, //south 
				currentBladeVertex + 10); //north

			setFace(bladeFaceStartIndex + i + 5,
				currentBladeVertex + 8, //north west
				currentBladeVertex + 9, //south west
				currentBladeVertex + 10); //north

			/**
			* Top side of blade
			**/
			setFace(bladeFaceStartIndex + i + 6,
				currentBladeVertex + 12, //south west
				currentBladeVertex + 13, //south 
				currentBladeVertex + 14); //north

			setFace(bladeFaceStartIndex + i + 7,
				currentBladeVertex + 15, //north west
				currentBladeVertex + 12, //south west
				currentBladeVertex + 14); //north

			/**
			* Bottom side of blade
			**/
			setFace(bladeFaceStartIndex + i + 8,
				currentBladeVertex + 18, //south west
				currentBladeVertex + 17, //south 
				currentBladeVertex + 16); //north

			setFace(bladeFaceStartIndex + i + 9,
				currentBladeVertex + 18, //north west
				currentBladeVertex + 16, //south west
				currentBladeVertex + 19); //north

			currentBladeVertex += 20;
		}

		checkArrays();
		calcNormals();
	}

	void FancyPropeller::setVertexFromVector(int idx, Vector3 vector) {
		setVertex(idx, vector.x, vector.y, vector.z);
	}

	FancyPropeller::~FancyPropeller(void) {

	}

}