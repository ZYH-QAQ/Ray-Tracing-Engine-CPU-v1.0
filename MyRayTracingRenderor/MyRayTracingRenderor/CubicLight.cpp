#include "CubicLight.h"
#include "Cube.h"
const char* CubicLight::Distinguish()
{
	const char* ori = "CubicLight";
	return ori;
}
//void CubicLight::InitializeParent()
//{
//	this->Cube::xMax = this->xMax;
//	this->Cube::xMin = this->xMin;
//	this->Cube::yMax = this->yMax;
//	this->Cube::yMin = this->yMin;
//	this->Cube::zMax = this->zMax;
//	this->Cube::zMin = this->zMin;
//}