#pragma once
#include "Vector.h"
#include "Collider.h"
#include "Cube.h"
class CubicLight :public Cube
{
public:
	double xMax, xMin, yMax, yMin, zMax, zMin;
	//void InitializeParent();
	virtual const char* Distinguish();
};