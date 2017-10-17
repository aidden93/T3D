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

#include "House.h"

namespace T3D
{
	House::House(float size, float roofHeight, float roofLength)
	{
		// Init vertex and index arrays
		initArrays((4 * 7) + (3 * 2),	// num vertices
			2,		// num tris
			7);		// num quads

					// Set vertices

		int pos = 0;
		int uvpos = 0;
		//front
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, -size, size, -size);

		setUV(uvpos++, 0.517578125, 0.384765625);
		setUV(uvpos++, 0.232421875, 0.384765625);
		setUV(uvpos++, 0.232421875, 0.28515625);
		setUV(uvpos++, 0.517578125, 0.28515625);
		

		//back
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, -size, size, size);

		setUV(uvpos++, 0.166015625, 0.814453125);
		setUV(uvpos++, 0.365234375, 0.814453125);
		setUV(uvpos++, 0.365234375, 0.71484375);
		setUV(uvpos++, 0.166015625, 0.71484375);


		//left
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, -size, -size, size);

		setUV(uvpos++, norm(214, 512), norm(113, 512));
		setUV(uvpos++, norm(214, 512), norm(63, 512));
		setUV(uvpos++, norm(271, 512), norm(63, 512));
		setUV(uvpos++, norm(271, 512), norm(113, 512));


		//right
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, -size, size);

		setUV(uvpos++, norm(111, 512), norm(197, 512));
		setUV(uvpos++, norm(111, 512), norm(145, 512));
		setUV(uvpos++, norm(16, 512), norm(145, 512));
		setUV(uvpos++, norm(16, 512), norm(197, 512));


		//bottom
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, -size, -size);

		setUV(uvpos++, 0, 0);
		setUV(uvpos++, 0, 0);
		setUV(uvpos++, 0, 0);
		setUV(uvpos++, 0, 0);


		//topRight roof
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, 0, roofHeight, roofLength);
		setVertex(pos++, 0, roofHeight, -roofLength);

		
		setUV(uvpos++, norm(108, 512), norm(319, 512));
		setUV(uvpos++, norm(108, 512), norm(221, 512));
		setUV(uvpos++, norm(44, 512), norm(221, 512));
		setUV(uvpos++, norm(44, 512), norm(319, 512));

		//topLeft roof
		setVertex(pos++, size, size, -size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, 0, roofHeight, roofLength);
		setVertex(pos++, 0, roofHeight, -roofLength);

		setUV(uvpos++, norm(108, 512), norm(319, 512));
		setUV(uvpos++, norm(108, 512), norm(221, 512));
		setUV(uvpos++, norm(44, 512), norm(221, 512));
		setUV(uvpos++, norm(44, 512), norm(319, 512));


		//backRoof
		setVertex(pos++, -size, size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, 0, roofHeight, roofLength);

		setUV(uvpos++, norm(13, 512), norm(449, 512));
		setUV(uvpos++, norm(120, 512), norm(449, 512));
		setUV(uvpos++, norm(66, 512), norm(420, 512));


		//frontRoof
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, 0, roofHeight, -roofLength);

		setUV(uvpos++, norm(120, 512), norm(449, 512));
		setUV(uvpos++, norm(13, 512), norm(449, 512));
		setUV(uvpos++, norm(66, 512), norm(420, 512));


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
		//topRight
		setFace(pos++, 20, 21, 22, 23);
		//topLeft
		setFace(pos++, 27, 26, 25, 24);

		//roofback
		setFace(0, 28, 29, 30);

		//roof front
		setFace(1, 33, 32, 31);

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

	}


	House::~House(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}

	float House::norm(float val, float max) {
		return val / max;
	}
}
