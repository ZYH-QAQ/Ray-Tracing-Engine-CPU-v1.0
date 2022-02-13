#pragma once
#include "Vector.h"
#include "Collider.h"
class Sphere :public Collider
{
public:
	Vector center;
	Vector color;
	double radius;
	virtual const char* Distinguish();

};