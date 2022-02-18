#pragma once
#include "Vector.h"
#include "Collider.h"
class Sphere :public Collider
{
public:
	Vector center;
	Vector color;
	double radius;
	const char* material;
	virtual const char* Distinguish();

};