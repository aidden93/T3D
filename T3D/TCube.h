// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// cube.h
//
// Simple cube mesh with coloured sides

#ifndef TCUBE_H
#define TCUBE_H

#include "mesh.h"

namespace T3D
{
	class TCube :
		public Mesh
	{
	public:
		TCube(float size);
		virtual ~TCube(void);
	};
}

#endif

#pragma once
