#include <iostream>
#include <random>
#include <fstream>
#include "Vector.h"
#include "Cube.h"
#include "Sphere.h"
#include "Ray.h"
#include "RandomDirection.h"
#include "RussianRoulette.h"
#include "Collider.h"
#include "PathTracing.h"
#include <stdlib.h>
#include <ctime>
using namespace std;
//用于生成俄罗斯轮盘的随机数和蒙特卡洛积分的随机采样。
std::default_random_engine e;
std::uniform_real_distribution<double> rand1(0, 1);
std::uniform_real_distribution<double> rand2(0, 2 * pi);
std::uniform_int_distribution<unsigned> rand3(1, 10);
//存储场景里的所有几何形体。
Collider* geometry[100];
int num;
void Create(int xLength, int yLength, int depth);
void DrawPixel();
void limit();
long int* nowTimeP, * startTimeP;
int main()
{
	ifstream scene;
	scene.open("Scene.txt", ios::in);
	int cubeNum;
	scene >> cubeNum;
	int i = 0;
	for (;i < cubeNum;i++)
	{
		Cube* cubeP = new Cube();
		int type = 0;
		geometry[i] = cubeP;
		scene >> ((Cube*)geometry[i])->xMax >> ((Cube*)geometry[i])->xMin >> ((Cube*)geometry[i])->yMax >> ((Cube*)geometry[i])->yMin >> ((Cube*)geometry[i])->zMax >> ((Cube*)geometry[i])->zMin;
		scene >> ((Cube*)geometry[i])->color.x >> ((Cube*)geometry[i])->color.y >> ((Cube*)geometry[i])->color.z;
		scene >> type;
		switch (type)
		{
		case 0:
			(((Cube*)geometry[i])->material) = "DIFF";
			break;
		case 1:
			(((Cube*)geometry[i])->material) = "REFL";
			break;
		default:
			(((Cube*)geometry[i])->material) = "DIFF";
			break;
		}
	}
	int sphereNum;
	scene >> sphereNum;
	for (;i < cubeNum + sphereNum;i++)
	{
		geometry[i] = new Sphere();
		int type = 0;
		scene >> (((Sphere*)geometry[i])->center.x) >> (((Sphere*)geometry[i])->center.y) >> (((Sphere*)geometry[i])->center.z) >> (((Sphere*)geometry[i])->radius);
		scene >> (((Sphere*)geometry[i])->color.x) >> (((Sphere*)geometry[i])->color.y) >> (((Sphere*)geometry[i])->color.z);
		scene >> type;
		switch (type)
		{
		case 0:
			(((Sphere*)geometry[i])->material) = "DIFF";
			break;
		case 1:
			(((Sphere*)geometry[i])->material) = "REFL";
			break;
		default:
			(((Sphere*)geometry[i])->material) = "DIFF";
			break;
		}
	}
	int lightNum;
	scene >> lightNum;
	for (;i < cubeNum + sphereNum + lightNum;i++)
	{
		geometry[i] = new CubicLight();
		scene >> ((Cube*)geometry[i])->xMax >> ((Cube*)geometry[i])->xMin >> ((Cube*)geometry[i])->yMax >> ((Cube*)geometry[i])->yMin >> ((Cube*)geometry[i])->zMax >> ((Cube*)geometry[i])->zMin;
		//printf("%f\n", ((Cube*)geometry[i])->xMax);
		//printf("%f\n", ((CubicLight*)geometry[i])->Cube::xMax);

	}
	num = i;
	//Vector testNorm, testColor;
	//const char* sTest;
	//double tTest = Ray(Vector(0, 0, 0), Vector::Normalize(Vector(200, -125, -400))).Ray::CollideSphere(*(Sphere*)(geometry[7]), testNorm, testColor,sTest);
	//Vector test = Trace(Ray(Vector(0, 0, 0), Vector::Normalize(Vector(200, -200, -400))));
	DrawPixel();
	//limit();
	return 0;
}
void DrawPixel()
{
	int sqrt_ssp,xLength,yLength;
	printf("sqrt_ssp = ");
	scanf_s("%d", &sqrt_ssp);
	printf("x_length , y_length = ");
	scanf_s("%d %d", &xLength, &yLength);
	system("cls");
	FILE* fImage;
	fopen_s(&fImage, "image_1.ppm", "w");
	fprintf(fImage, "P3\n");
	fprintf(fImage, "%d %d\n%d\n", xLength, yLength, 255);
	for (int j = 0;j < yLength; j++)
	{
		for (int i = 0;i < xLength;i++)
		{
			double centerX = -xLength/2 + i + 0.5;
			double centerY = yLength/2 - j - 0.5;
			Vector NRGB(0, 0, 0);
			for (int k = -sqrt_ssp/2;k <= sqrt_ssp/2;k++)
			{
				for (int l = -sqrt_ssp/2;l <= sqrt_ssp/2;l++)
				{
					double eachX = centerX + k / (sqrt_ssp*1.0);
					double eachY = centerY + l / (sqrt_ssp*1.0);
					Vector startPos = Vector(centerX / xLength * 550, centerY / xLength * 550, 0);
					Ray ray = Ray(startPos, Vector::Normalize(Vector(eachX, eachY, -600.0*yLength/360)));
					NRGB = NRGB + Trace(ray);
				}
			}
			Vector RGB = NRGB / (sqrt_ssp*sqrt_ssp*1.0);
			fprintf(fImage, "%d %d %d ", (int)(pow(RGB.x > 1 ? 1 : RGB.x,1/2.2)*255+.5), (int)(pow(RGB.y > 1 ? 1 : RGB.y,1/2.2)*255+.5), (int)(pow(RGB.z > 1 ? 1 : RGB.z,1/2.2)*255+.5));
			fprintf(stderr, "\rRendering ssp = %d res = %dx%d   %5.3f%%",sqrt_ssp*sqrt_ssp,xLength,yLength, (j * xLength + i) / (yLength * xLength * 1.0) * 100);
			//*nowTimeP = clock();
			//printf("Estimated time left: %ld", (720 * 1280 - j * 1280 - i) * (*nowTimeP-*startTimeP)/ CLOCKS_PER_SEC / (j * 1280 + i + 1));
		}
		fprintf(fImage, "\n");

	}
	fclose(fImage);

}
void Create(int xLength, int yLength, int depth)
{
	ofstream image;
	image.open("image_1.ppm", ios::out | ios::trunc);
	image << "P3" << endl;
	image << xLength << " " << yLength << endl;
	image << 255 << endl;
	image.close();

}

void limit()
{
	FILE* f1, * f2;
	fopen_s(&f1, "image_1.ppm", "r");
	fopen_s(&f2, "image_modified.ppm", "w");
	char c1[3];int c2, c3, c4;
	fscanf_s(f1, "%s %d %d %d", c1, 3, &c2, &c3, &c4);
	fprintf(f2, "%s\n%d %d\n%d\n", c1, c2, c3, c4);
	int temp;
	for (int i = 0;i < 360;i++)
	{
		for (int j = 0;j < 640 * 3;j++)
		{
			if (!fscanf_s(f1, "%d", &temp))
				return;
			fprintf(f2, "%d ", temp > 255 ? 255 : (temp < 0 ? 255 : temp));
		}
		fprintf(f2, "\n ");

	}
}