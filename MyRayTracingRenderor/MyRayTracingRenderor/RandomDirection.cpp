#include "RandomDirection.h"
#include <math.h>
#include "Vector.h"
#include <random>
#define pi 3.141592653589793238
using namespace std;
extern std::default_random_engine e;
extern std::uniform_real_distribution<double> rand1;
extern std::uniform_real_distribution<double> rand2;
;
Vector RandomDirection::Decide(Vector n)
{
	double cos_phi = rand1(e);
	double theta = rand2(e);
	Vector vx = Vector(1, 0, 0);
	Vector vy = Vector(0, 1, 0);
	Vector vRotate1x = Vector::Cross(n, vx);
	Vector vRotate1y = Vector::Cross(n, vy);
	Vector vRotate1 =Vector::Normalize(Vector::Module(vRotate1x) > Vector::Module(vRotate1y) ? vRotate1x : vRotate1y);

	Vector n1 = n * cos_phi + (n * vRotate1) * vRotate1 * (1 - cos_phi) + Vector::Cross(vRotate1, n) * sqrt(1 - cos_phi * cos_phi);
	Vector n2 = n1 * cos(theta) + (n * n1) * n * (1 - cos(theta)) + Vector::Cross(n, n1) * sin(theta);
	return n2;
}