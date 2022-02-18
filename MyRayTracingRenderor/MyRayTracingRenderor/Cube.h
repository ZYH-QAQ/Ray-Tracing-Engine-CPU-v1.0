#pragma once
#include "Vector.h"
#include "Collider.h"
class Cube :public Collider
{
public:
	double xMax, xMin, yMax, yMin, zMax, zMin;
	Vector color;
	const char* material;
	virtual const char* Distinguish();
};