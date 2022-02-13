#pragma once
class Vector
{
public:
	double x, y, z;
	const static Vector defaultVector;
	static double Dot(const Vector& v1, const Vector& v2);
	static Vector Cross(const Vector& v1, const Vector& v2);
	static Vector Normalize(const Vector&);
	static double Module(const Vector&);
	Vector(double x, double y, double z);
	Vector();

};

Vector operator*(const Vector& v1, double lambda);
Vector operator*(double lambda, const Vector& v1);
double operator*(const Vector& v1, const Vector& v2);
Vector operator%(const Vector& v1, const Vector& v2);
Vector operator/(const Vector& v1, double lambda);
Vector operator+(const Vector& v1, const Vector v2);
Vector operator-(const Vector& v1, const Vector v2);



