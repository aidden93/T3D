// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// cube.cpp
//
// Simple cube mesh with coloured sides
// Note that faces are triangles only and that normals are repeated for each vertex
// This allows use of gl array pointers

#include "TCube.h"

namespace T3D
{
	TCube::TCube(float size)
	{
		// Init vertex and index arrays
		initArrays(4 * 6,	// num vertices
			0,		// num tris
			6);		// num quads

					// Set vertices

		int pos = 0;
		int uvpos = 0;
		//front
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, -size, size, -size);


		setUV(uvpos++, 0.48828125, 0.978515625);
		setUV(uvpos++, 0.01171875, 0.978515625);
		setUV(uvpos++, 0.01171875, 0.525390625);
		setUV(uvpos++, 0.48828125, 0.525390625);


		//back
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, -size, size, size);

		setUV(uvpos++, 0.01171875, 0.978515625);
		setUV(uvpos++, 0.48828125, 0.978515625);
		setUV(uvpos++, 0.48828125, 0.525390625);
		setUV(uvpos++, 0.01171875, 0.525390625);

		//left
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, -size, -size, size);



		setUV(uvpos++, 0.509765625, 0.978515625);
		setUV(uvpos++, 0.509765625, 0.525390625);
		setUV(uvpos++, 0.990234375, 0.525390625);
		setUV(uvpos++, 0.990234375, 0.978515625);

		//right
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, -size, size);

		setUV(uvpos++, 0.990234375, 0.978515625);
		setUV(uvpos++, 0.990234375, 0.525390625);
		setUV(uvpos++, 0.509765625, 0.525390625);
		setUV(uvpos++, 0.509765625, 0.978515625);

		//bottom
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, -size, -size);


		setUV(uvpos++, 0.5078125, 0.50390625);
		setUV(uvpos++, 0.984375, 0.50390625);
		setUV(uvpos++, 0.984375, 0.02734375);
		setUV(uvpos++, 0.5078125, 0.02734375);

		//top
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, size, -size);


		setUV(uvpos++, 0.01171875, 0.5);
		setUV(uvpos++, 0.48828125, 0.5);
		setUV(uvpos++, 0.48828125, 0.02734375);
		setUV(uvpos++, 0.01171875, 0.02734375);

		// Build quads
		pos = 0;
		//front
		setFace(pos++, 3, 2, 1, 0);
		//back
		setFace(pos++, 4, 5, 6, 7);
		//left
		setFace(pos++, 11, 10, 9, 8);
		//right
		setFace(pos++, 12, 13, 14, 15);
		//bottom
		setFace(pos++, 19, 18, 17, 16);
		//top
		setFace(pos++, 20, 21, 22, 23);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();

		// Setup other arrays		
		pos = 0;
		//front
		for (int i = 0; i<4; i++) {
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		}
		//back
		for (int i = 0; i<4; i++) {
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		}
		//left
		for (int i = 0; i<4; i++) {
			colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		}
		//right
		for (int i = 0; i<4; i++) {
			colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		}
		//bottom
		for (int i = 0; i<4; i++) {
			colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}
		//top
		for (int i = 0; i<4; i++) {
			colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}

		//uvs
		/*pos = 0;
		for (int f = 0; f<6; f++) {
			uvs[pos++] = 0; uvs[pos++] = 0;
			uvs[pos++] = 0; uvs[pos++] = 1;
			uvs[pos++] = 1; uvs[pos++] = 1;
			uvs[pos++] = 1; uvs[pos++] = 0;
		}*/
	}


	TCube::~TCube(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
