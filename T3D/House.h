// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// cube.h
//
// Simple cube mesh with coloured sides

#ifndef HOUSE
#define HOUSE

#include "mesh.h"

namespace T3D
{
	class House :
		public Mesh
	{
	public:
		House(float size, float roofHeight, float roofLength);
		virtual ~House(void);
		float norm(float val, float max);
	};
}

#endif

#pragma once
