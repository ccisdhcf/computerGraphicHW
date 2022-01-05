// ConsoleApplication1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <GL/glut.h>
#include <GL/gl.h>
#include<iostream>
#include <list>
#include "ConsoleApplication1.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>     
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include<math.h>
#include <tuple>
#include <iomanip>

using namespace std;

class point
{
private:
	int x = 0;
	int y = 0;
	int color = 0;
public:
	point(int _x, int _y,int _color=0) {
		x = _x;
		y = _y;
		color = _color;
	};
	int getX() {
		return x;
	};
	int getY() {
		return y;
	}
	int getColor() {
		return color;
	}
	void setX(int new_x) {
		x = new_x;
	}
	void setY(int new_y) {
		y = new_y;
	}
	void setColor(int new_color) {
		color = new_color;
	}

};
class pointInDouble
{
private:
	double x;
	double y;
public:
	pointInDouble
	(double _x, double _y) {
		x = _x;
		y = _y;
	};
	double getX() {
		return x;
	};
	double getY() {
		return y;
	}
	void setX(double new_x) {
		x = new_x;
	}
	void setY(double new_y) {
		y = new_y;
	}

};
class point3D {
private:
	int x = 0;
	int y = 0;
	int z = 0;
public:
	point3D(int _x, int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	};
	int getX() {
		return x;
	};
	int getY() {
		return y;
	}
	int getZ() {
		return z;
	}
	void setX(int new_x) {
		x = new_x;
	}
	void setY(int new_y) {
		y = new_y;
	}
	void setZ(int new_z) {
		z = new_z;
	}
};
class point3DInDouble
{
private:
	double x;
	double y;
	double z;
	double w;

public:
	point3DInDouble(double _x, double _y, double _z, double _w = 1.0) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	};
	double getX() {
		return x;
	};
	double getY() {
		return y;
	}
	double getZ() {
		return z;
	}
	double getW() {
		return w;
	}
	void setX(double new_x) {
		x = new_x;
	}
	void setY(double new_y) {
		y = new_y;
	}
	void setZ(double new_z) {
		z = new_z;
	}
	void setW(double new_w) {
		w = new_w;
	}
};
class poly {
public:
	int n;//n-sides
	bool visible;
	vector<point3DInDouble> pointInPoly;  //after clipping use
	poly() {
		n = 0;
		visible = true;

		pointInPoly.clear();
	};
};
class objectBase {
public:
	vector<point3DInDouble> pList;
	vector<poly> plane;
	objectBase() {
		pList.clear();
		plane.clear();
	}
};

ifstream inputFile;
ifstream objectFile;
//vector<pair<pointInDouble, pointInDouble>> windowSidePair;
//vector<pair<point, point>> viewSidePair;
list<point> pointList;

//list<point3DInDouble> pointList3D;
//list<point> clippingPointList;
//list<point> pointListBackUp;
vector<objectBase> objs;
point lineTemp = point(NULL, NULL);
//point circleTemp = point(NULL, NULL);
//point polygonSrc = point(NULL, NULL);
//point polygontemp = point(NULL, NULL);
//int circleCounter = 0;
int lineCounter = 0;
int squareCounter = 0;
int triangleCounter = 0;
bool nobackfaces = false;
//int mode = 0; //  d,l,p,o,c,r,q
string fileName = "";
int windowH = 0;
int windowW = 0;
//static double defaultMatrix[3][3] = { 1.0, 0.0, 0.0,
//									  0.0, 1.0, 0.0,
//									  0.0, 0.0, 1.0, };
//static double transformationMatrix[3][3] = { 1.0, 0.0, 0.0,
//									         0.0, 1.0, 0.0,
//									         0.0, 0.0, 1.0, };
static double defaultMatrix3D[4][4] = { 1.0, 0.0, 0.0, 0.0,
									  0.0, 1.0, 0.0, 0.0,
									  0.0, 0.0, 1.0, 0.0,
									  0.0, 0.0, 0.0, 1.0 };

//static double mulResultTemp[4][4] = { 1.0, 0.0, 0.0, 0.0,
//									  0.0, 1.0, 0.0, 0.0,
//									  0.0, 0.0, 1.0, 0.0,
//									  0.0, 0.0, 0.0, 1.0 };
static double transformationMatrix3D[4][4] = { 1.0, 0.0, 0.0, 0.0,
											 0.0, 1.0, 0.0, 0.0,
											 0.0, 0.0, 1.0 ,0.0,
											 0.0, 0.0, 0.0, 1.0 };
static double tempMatrix0[4][4] = { 1.0, 0.0, 0.0, 0.0,
											 0.0, 1.0, 0.0, 0.0,
											 0.0, 0.0, 1.0 ,0.0,
											 0.0, 0.0, 0.0, 1.0 };
static double tempMatrix1[4][4] = { 1.0, 0.0, 0.0, 0.0,
											 0.0, 1.0, 0.0, 0.0,
											 0.0, 0.0, 1.0 ,0.0,
											 0.0, 0.0, 0.0, 1.0 };
static double PMMulEM[4][4] = { 1.0, 0.0, 0.0, 0.0,
											 0.0, 1.0, 0.0, 0.0,
											 0.0, 0.0, 1.0 ,0.0,
											 0.0, 0.0, 0.0, 1.0 };
static double PM[4][4] = { 1.0, 0.0, 0.0, 0.0,
							 0.0, 1.0, 0.0, 0.0,
							 0.0, 0.0, 1.0 ,0.0,
							 0.0, 0.0, 0.0, 1.0 };
static double EM[4][4] = { 1.0, 0.0, 0.0, 0.0,
							 0.0, 1.0, 0.0, 0.0,
							 0.0, 0.0, 1.0 ,0.0,
							 0.0, 0.0, 0.0, 1.0 };
double wvm[4][4];
//static double squareMatrix[3][4] = { -1.0,-1.0, 1.0, 1.0,
//									   -1.0, 1.0, 1.0,-1.0,
//										1.0, 1.0 ,1.0, 1.0 };
//static double triangleMatrix[3][3] = { 0.0,-1.0, 1.0,
//									   1.0,-1.0,-1.0,
//									   1.0, 1.0, 1.0};
// 

////clipping use
//typedef int OutCode;
//const int INSIDE = 0; // 0000
//const int LEFT = 1;   // 0001
//const int RIGHT = 2;  // 0010
//const int BOTTOM = 4; // 0100
//const int TOP = 8;    // 1000
//OutCode computeOutCode(double x, double y, double vxl, double vxr, double vyb, double vyt)
//{
//	OutCode code;
//
//	code = INSIDE;          // initialised as being inside of [[clip window]]
//
//	if (x < vxl)           // to the left of clip window
//		code |= LEFT;
//	else if (x > vxr)      // to the right of clip window
//		code |= RIGHT;
//	if (y < vyb)           // below the clip window
//		code |= BOTTOM;
//	else if (y > vyt)      // above the clip window
//		code |= TOP;
//
//	return code;
//}

double angleToRadian(double angle) {  //from angle to radian
	return (angle * M_PI / (double)180.0);
}
void matrixOutput(double matrix[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		cout << "{";
		for (int j = 0; j < 3; j++) {
			cout << setw(10) << matrix[i][j] << ",";
		}
		cout << setw(10) << matrix[i][3] << "}" << endl;
	}
	//cout << endl;
}
void matrixOutput(double matrix[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		cout << "{";
		for (int j = 0; j < 2; j++) {
			cout << setw(10) << matrix[i][j] << ",";
		}
		cout << setw(10) << matrix[i][2] << "}" << endl;
	}
	//cout << endl;
}
double vectorLength(point3DInDouble p0) {

	return sqrt(p0.getX() * p0.getX() + p0.getY() * p0.getY() + p0.getZ() * p0.getZ());
}
point3DInDouble cross(point3DInDouble p0, point3DInDouble p1) {
	double x, y, z;
	x = p0.getY() * p1.getZ() - p0.getZ() * p1.getY();
	y = p0.getZ() * p1.getX() - p0.getX() * p1.getZ();
	z = p0.getX() * p1.getY() - p0.getY() * p1.getX();
	return point3DInDouble(x, y, z);
}
//void matrixOutput(double matrix[3][4]) {
//	for (int i = 0; i < 3; i++)
//	{
//		cout << "{";
//		for (int j = 0; j < 3; j++) {
//			cout << setw(10) << matrix[i][j] << ",";
//		}
//		cout << setw(10) << matrix[i][3] << "}" << endl;
//	}
//	//cout << endl;
//}
void resetToIdentityMatrix(double M[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			M[i][j] = defaultMatrix3D[i][j];
		}
	}
}
void copyMatrix(double src[4][4], double des[4][4], bool resetSrc = false) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			des[i][j] = src[i][j];
		}
	}
	if (resetSrc)
	{
		resetToIdentityMatrix(src);
	}
}
void calMMulM(double M[4][4], double M2[4][4], double MResult[4][4]) {
	double mulResultTemp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mulResultTemp[i][j] = 0.0;
			for (int k = 0; k < 4; k++) {
				mulResultTemp[i][j] += M[i][k] * M2[k][j];
				//cout << i << " " << j << " " <<k<<" " << M[i][k] * M2[k][j]<<endl;
			}
		}
	}
	copyMatrix(mulResultTemp, MResult);
}
point3DInDouble calMMulP(double M[4][4], point3DInDouble p) {
	point3DInDouble result(0.0, 0.0, 0.0, 0.0);
	double pTemp[4] = { p.getX(),p.getY(),p.getZ(),p.getW() };
	double resultTemp[4];
	for (int i = 0; i < 4; i++) {
		resultTemp[i] = 0;
		for (int j = 0; j < 4; j++) {
			resultTemp[i] += M[i][j] * pTemp[j];
		}
	}
	result.setX(resultTemp[0]);
	result.setY(resultTemp[1]);
	result.setZ(resultTemp[2]);
	result.setW(resultTemp[3]);
	return result;
}
point cal2DP(double M[4][4], point3DInDouble p) {
	point result(0, 0);
	double pTemp[4] = { p.getX(),p.getY(),p.getZ(),p.getW() };
	double resultTemp[4];
	for (int i = 0; i < 4; i++) {
		resultTemp[i] = 0;
		for (int j = 0; j < 4; j++) {
			resultTemp[i] += M[i][j] * pTemp[j];
		}
	}
	//cout << "?P:" << resultTemp[0] << " " << resultTemp[1] << endl;
	result.setX(int(resultTemp[0]));
	result.setY(int(resultTemp[1]));

	return result;
}
point cal2DP(double M[4][4], pointInDouble p) {
	point result(0, 0);
	double pTemp[4] = { p.getX(),p.getY() };
	double resultTemp[4];
	for (int i = 0; i < 4; i++) {
		resultTemp[i] = 0;
		for (int j = 0; j < 2; j++) {
			resultTemp[i] += M[i][j] * pTemp[j];
		}
	}
	//cout << "?P:" << resultTemp[0] << " " << resultTemp[1] << endl;
	result.setX(int(resultTemp[0]));
	result.setY(int(resultTemp[1]));

	return result;
}
void calPM(double pmH, double pmY, double pmTheta) {
	//!!!!! PM[1][1] wait for viewport command
	PM[2][2] = pmY * tan(angleToRadian(pmTheta)) / (pmY - pmH);
	PM[3][2] = tan(angleToRadian(pmTheta));
	PM[2][3] = pmH * pmY * tan(angleToRadian(pmTheta)) / (pmH - pmY);
	PM[3][3] = 0.0;
}
vector<objectBase> clipping(vector<objectBase> objs) {
	for (int i = 0; i < objs.size(); i++)
	{
		for (int j = 0; j < objs[i].plane.size(); j++)
		{
			for (int pe = 0; pe < 6; pe++)  //plane equation
			{
				vector<point3DInDouble> pTemp;
				point3DInDouble a(0.0, 0.0, 0.0), b(0.0, 0.0, 0.0);
				double c1, c2;
				for (int k = 0; k < objs[i].plane[j].pointInPoly.size(); k++)
				{
					int bNO = 0;
					a.setX(objs[i].plane[j].pointInPoly[k].getX());
					a.setY(objs[i].plane[j].pointInPoly[k].getY());
					a.setZ(objs[i].plane[j].pointInPoly[k].getZ());
					a.setW(objs[i].plane[j].pointInPoly[k].getW());
					if (k == objs[i].plane[j].pointInPoly.size() - 1) { bNO = 0; }
					else { bNO = k + 1; }
					b.setX(objs[i].plane[j].pointInPoly[bNO].getX());
					b.setY(objs[i].plane[j].pointInPoly[bNO].getY());
					b.setZ(objs[i].plane[j].pointInPoly[bNO].getZ());
					b.setW(objs[i].plane[j].pointInPoly[bNO].getW());
					switch (pe)
					{
					case 0:
						c1 = a.getW() + a.getX();
						c2 = b.getW() + b.getX();
						break;
					case 1:
						c1 = a.getW() - a.getX();
						c2 = b.getW() - b.getX();
						break;
					case 2:
						c1 = a.getW() + a.getY();
						c2 = b.getW() + b.getY();
						break;
					case 3:
						c1 = a.getW() - a.getY();
						c2 = b.getW() - b.getY();
						break;
					case 4:
						c1 = a.getZ();
						c2 = b.getZ();
						break;
					case 5:
						c1 = a.getW() - a.getZ();
						c2 = b.getW() - b.getZ();
						break;
					default:
						break;
					}
					if (c1 < 0 && c2 < 0) {/*reject */ }
					else if (c1 >= 0 && c2 >= 0)
					{
						if (pTemp.size() != 0)
						{
							if (pTemp.back().getX() != b.getX() || pTemp.back().getY() != b.getY() || pTemp.back().getZ() != b.getZ())
							{
								pTemp.push_back(b);
							}
						}
						else
						{
							pTemp.push_back(b);
						}
					}
					else  //clip the line
					{
						double t = c1 / (c1 - c2);
						double x = a.getX() + t * (b.getX() - a.getX());
						double y = a.getY() + t * (b.getY() - a.getY());
						double z = a.getZ() + t * (b.getZ() - a.getZ());
						double w = a.getW() + t * (b.getW() - a.getW());
						point3DInDouble clippedP(x, y, z, w);
						if (c1 >= 0 && c2 < 0) //in>out
						{
							if (pTemp.size() != 0)
							{
								if (pTemp.back().getX() != clippedP.getX() || pTemp.back().getY() != clippedP.getY() || pTemp.back().getZ() != clippedP.getZ())
								{
									pTemp.push_back(clippedP);
								}
							}
							else
							{
								pTemp.push_back(clippedP);
							}
						}
						else if (c1 < 0 && c2 >= 0)  //out>in
						{
							if (pTemp.size() == 0)
							{
								pTemp.push_back(clippedP);
							}
							else
							{
								if (pTemp.back().getX() != clippedP.getX() || pTemp.back().getY() != clippedP.getY() || pTemp.back().getZ() != clippedP.getZ())
								{
									pTemp.push_back(clippedP);
								}
							}
							pTemp.push_back(b);
						}

					}

				}
				objs[i].plane[j].n = pTemp.size();
				objs[i].plane[j].pointInPoly = pTemp;
			}
		}
	}
	return objs;
}
//void calRotateTMMulTM(double angleTransformationMatrix[4][4]) {
//	double temp[4][4];
//	double temp2[4][4];
//
//	//pair<double, double> translateTemp = { transformationMatrix[0][2], transformationMatrix[1][2] };
//	/*double Tnegative[3][3] = { 1.0, 0.0, -1* translateTemp.first,
//							   0.0, 1.0, -1* translateTemp.second,
//						       0.0, 0.0, 1.0 };
//	double T[3][3] = { 1.0, 0.0, translateTemp.first,
//					   0.0, 1.0, translateTemp.second,
//					   0.0, 0.0, 1.0 };*/
//	//matrixOutput(Tnegative);
//	//matrixOutput(T);
//	//  self - rotate
//	//for (int i = 0; i < 3; i++) {
//	//	for (int j = 0; j < 3; j++) {
//	//		temp[i][j] = 0;
//	//		for (int k = 0; k < 3; k++) {
//	//			temp[i][j] += Tnegative[i][k] * transformationMatrix[k][j];
//	//		}
//	//	}
//	//}
//	//matrixOutput(temp);
//	//for (int i = 0; i < 3; i++) {
//	//	for (int j = 0; j < 3; j++) {
//	//		temp2[i][j] = 0;
//	//		for (int k = 0; k < 3; k++) {
//	//			temp2[i][j] += angleTransformationMatrix[i][k] * temp[k][j];
//	//		}
//	//	}
//	//}
//	//matrixOutput(temp2);
//	//for (int i = 0; i < 3; i++) {
//	//	for (int j = 0; j < 3; j++) {
//	//		transformationMatrix[i][j] = 0;
//	//		for (int k = 0; k < 3; k++) {
//	//			transformationMatrix[i][j] += T[i][k] * temp2[k][j];
//	//		}
//	//	}
//	//}
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			temp2[i][j] = 0;
//			for (int k = 0; k < 4; k++) {
//				temp2[i][j] += angleTransformationMatrix[i][k] * transformationMatrix[k][j];
//			}
//		}
//	}	
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			transformationMatrix[i][j] = 0;
//			transformationMatrix[i][j] = temp2[i][j];
//		}
//	}
//	//matrixOutput(transformationMatrix);
//
//
//}
void quit() {
	exit(1);
}
void drawSquare(int x, int y,int color) {
	glPointSize(1);
	if (color==1)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else {
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glBegin(GL_POINTS);
	glVertex2i(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	glEnd();
}
void drawAllPoint() {
	glClear(GL_COLOR_BUFFER_BIT);
	list<point> ::iterator p;
	for (p = pointList.begin(); p != pointList.end(); p++) {
		drawSquare(p->getX(), (windowH - (p->getY())),p->getColor());
	}
	glutSwapBuffers();
}
//void drawClippingPoint() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	list<point> ::iterator p;
//	for (p = clippingPointList.begin(); p != clippingPointList.end(); p++) {
//		drawSquare(p->getX(), (windowH - (p->getY())));
//	}
//	glutSwapBuffers();
//}

//void circle1to8(point centre, point p_0) {
//	point p_1 = point(p_0.getY(), p_0.getX());
//	point p_2 = point(p_0.getY(), (-1) * p_0.getX());
//	point p_3 = point(p_0.getX(), (-1) * p_0.getY());
//	point p_4 = point((-1) * p_0.getX(), (-1) * p_0.getY());
//	point p_5 = point((-1) * p_0.getY(), (-1) * p_0.getX());
//	point p_6 = point((-1) * p_0.getY(), p_0.getX());
//	point p_7 = point((-1) * p_0.getX(), p_0.getY());
//
//	pointList.push_back(point(centre.getX() + p_0.getX(), centre.getY() + p_0.getY()));
//	pointList.push_back(point(centre.getX() + p_1.getX(), centre.getY() + p_1.getY()));
//	pointList.push_back(point(centre.getX() + p_2.getX(), centre.getY() + p_2.getY()));
//	pointList.push_back(point(centre.getX() + p_3.getX(), centre.getY() + p_3.getY()));
//	pointList.push_back(point(centre.getX() + p_4.getX(), centre.getY() + p_4.getY()));
//	pointList.push_back(point(centre.getX() + p_5.getX(), centre.getY() + p_5.getY()));
//	pointList.push_back(point(centre.getX() + p_6.getX(), centre.getY() + p_6.getY()));
//	pointList.push_back(point(centre.getX() + p_7.getX(), centre.getY() + p_7.getY()));
//}

//void drawCircle(point centre, point circlePoint) {  //超出邊界(?
//	double radius = pow(pow((circlePoint.getX() - centre.getX()), 2) + pow((circlePoint.getY() - centre.getY()), 2), 0.5);
//	list<point> circlelist;
//	point circle = point(0, int(radius)); //init
//	circle1to8(centre, circle);
//	double d = 5 / 4 - radius;  //init
//	while (circle.getX() < circle.getY())
//	{
//		if (d < 0) {
//			d += circle.getX() * 2 + 3;
//			circle.setX(circle.getX() + 1);
//		}
//		else
//		{
//			d += (circle.getX() - circle.getY()) * 2 + 5;
//			circle.setX(circle.getX() + 1);
//			circle.setY(circle.getY() - 1);
//		}
//		circle1to8(centre, circle);
//		//cout << circleTemp.getX() << " " << circleTemp.getY()<<endl; //debug
//	}
//	//float x_2 = pow((circlePoint.getX() - centre.getX()), 2);
//	//float y_2 = pow((circlePoint.getY() - centre.getY()), 2);
//	//float radius = pow((x_2 + y_2), 0.5);
//	//pointList.push_back(point(centre.getX() + (int)radius, centre.getY()));
//	//pointList.push_back(point(centre.getX() - (int)radius, centre.getY()));
//	//for (int tempX = centre.getX() - (int)radius; tempX < centre.getX() + (int)radius; tempX+= forLoopOptimize)
//	//{
//	//	int tempY_Abs = pow(radius * radius - (tempX - centre.getX()) * (tempX - centre.getX()),0.5);
//	//	pointList.push_back(point(tempX, centre.getY()+tempY_Abs));
//	//	pointList.push_back(point(tempX, centre.getY()-tempY_Abs));
//	//}
//}

//void drawPolygon(){}    //drawLine is enough
void drawLine(point src, point des,int color=0) {
	int dx = des.getX() - src.getX();
	if (dx < 0) {   // des.x < src.x then switch if needed?
		point temp = point(des.getX(), des.getY());
		des.setX(src.getX());
		des.setY(src.getY());
		src.setX(temp.getX());
		src.setY(temp.getY());
		//cout << "switch   \n\n";
	}//switch end
	//cout << src.getX() << " " << src.getY() << " " << des.getX() << " " << des.getY() << "\n\n";  //debug
	int dy = des.getY() - src.getY();
	dx = des.getX() - src.getX();
	int x = src.getX();
	int y = src.getY();
	float slope = dy / (float)dx;
	int direction = slope > 0 ? 1 : (slope = -slope, -1);  //0<slope<∞
	//cout<<slope<<" " << dx << " " << dy << " " << "\n";  //debug
	if (dy == 0) {  //slope =0
		for (int tempX = min(src.getX(), des.getX()); tempX < max(src.getX(), des.getX()); tempX++) {
			pointList.push_back(point(tempX, des.getY(),color));
		}
	}
	else if (dx == 0) //slope=∞
	{
		for (int tempY = min(src.getY(), des.getY()); tempY < max(src.getY(), des.getY()); tempY += 1)
		{
			pointList.push_back(point(des.getX(), tempY, color));
		}
	}
	else if (0 < slope && slope <= 1) { // 0<slope<=1
		/*
		* //if (dx < 0) {   // des.x < src.x then switch
		//	point temp = point(des.getX(), des.getY());
		//	des.setX(src.getX());
		//	des.setY(src.getY());
		//	src.setX(temp.getX());
		//	src.setY(temp.getY());
		//	dy = -dy;
		//	dx = -dx;

		//	d_init = -d_init;
		//	d = -d;
		//	incE = -incE;
		//	incNE = -incNE;
		//	//d?

		//}
		*/
		float d_init = dy * direction + (float)dx / 2;
		int incE = dy * direction;
		int incNE = dy * direction - dx;
		float d = d_init;
		pointList.push_back(point(x, y, color));
		while (x <= des.getX())
		{
			//cout << d << "\n\n";  //debug
			if (d <= 0) {
				pointList.push_back(point(x, y, color));
				x += 1;
				//cout << x <<" " << y << "\n";  //debug
				d += incE;
			}
			else
			{
				pointList.push_back(point(x, y, color));
				x += 1;
				y += direction;
				//cout << x <<" " << y << "\n";  //debug
				d += incNE;
			}
		}
	}

	else if (slope > 1) //slope>1 then switch (y,x)
	{
		float d_init = dx + (float)dy * direction / 2;
		int incE = dx;
		int incNE = dx - dy * direction;
		float d = d_init;
		pointList.push_back(point(x, y, color));
		while (y * direction <= des.getY() * direction)
		{
			//cout << d << "\n\n";  //debug
			if (d <= 0) {
				pointList.push_back(point(x, y, color));
				y += direction;
				//cout << x <<" " << y << "\n";  //debug
				d += incE;
			}
			else
			{
				pointList.push_back(point(x, y, color));
				x += 1;
				y += direction;
				//cout << x <<" " << y << "\n";  //debug
				d += incNE;
			}
		}
	}

	//else if (slope < -1) {
	//	float d_init = dx - (float)dy / 2;   //y*-1
	//	int incE = dx;
	//	int incNE = dx + dy;   //y*-1
	//	float d = d_init;
	//	pointList.push_back(point(x, y));
	//	while (y >= des.getY())   //<=  ->  >=
	//	{
	//		cout << d << "\n\n";  //debug
	//		if (d <= 0) {
	//			pointList.push_back(point(x, y));
	//			y -= 1;  //y*-1
	//			cout << x <<" " << y << "\n";  //debug
	//			d += incE;
	//		}
	//		else
	//		{
	//			pointList.push_back(point(x, y));
	//			x += 1;
	//			y -= 1;   //y*-1
	//			cout << x <<" " << y << "\n";  //debug
	//			d += incNE;
	//		}
	//	}
	//}
	// 
	//else if (slope<0 && slope>-1) {
	//float d_init = -dy + (float)dx / 2;  //y*-1
	//int incE = -dy; //y*-1
	//int incNE = -dy - dx;//y*-1
	//float d = d_init;
	//pointList.push_back(point(x, y));
	//while (x <= des.getX())
	//{
	//	//cout << d <<" "<<incE<<" "<<incNE << "\n\n";  //debug
	//	if (d <= 0) {
	//		pointList.push_back(point(x, y));
	//		x += 1;
	//		//cout << x <<" " << y << "\n";  //debug
	//		d += incE;
	//	}
	//	else
	//	{
	//		pointList.push_back(point(x, y));
	//		x += 1;
	//		y -= 1;  //y*-1
	//		//cout << x <<" " << y << "\n";  //debug
	//		d += incNE;
	//	}
	//}
	//}
	//cout << pointList.back().getX()<<" "<<pointList.back().getY()<<"\n";
	//else  //有斜率or = 0
	//{
	//	for (int tempX = min(src.getX() + 1,des.getX()+1); tempX < max(des.getX(),src.getX()); tempX+= forLoopOptimize)
	//	{
	//		float tempY = (float)src.getY() + (tempX-src.getX())*(des.getY() - src.getY()) / (float)(des.getX() - src.getX());
	//		point temp=edgeCheck(tempX, tempY);
	//		pointList.push_back(temp);
	//	}
	//}

}
//void saveToSideList(double result[3][4]) {
//	pointInDouble p0(result[0][0], result[1][0]),
//		p1(result[0][1], result[1][1]),
//		p2(result[0][2], result[1][2]),
//		p3(result[0][3], result[1][3]);
//
//	windowSidePair.push_back(make_pair(p0, p1));
//
//	windowSidePair.push_back(make_pair(p1, p2));
//
//	windowSidePair.push_back(make_pair(p2, p3));
//
//	windowSidePair.push_back(make_pair(p3, p0));
//}
//void saveToSideList(double result[3][3]) {
//	pointInDouble p0(result[0][0], result[1][0]),
//		p1(result[0][1], result[1][1]),
//		p2(result[0][2], result[1][2]);
//
//	windowSidePair.push_back(make_pair(p0, p1));
//
//	windowSidePair.push_back(make_pair(p1, p2));
//
//	windowSidePair.push_back(make_pair(p2, p0));
//}
void drawBorder(double vxl, double vxr, double vyb, double vyt) {
	point3DInDouble aD(-1, 1, 1.0), bD(-1, -1, 1.0), cD(1, 1, 1.0), dD(1, -1, 1.0);   //    a-----c
	point a = cal2DP(wvm, aD);														  //    |     |
	point b = cal2DP(wvm, bD);														  //    b-----d
	point c = cal2DP(wvm, cD);
	point d = cal2DP(wvm, dD);
	/*cout << "wvm" << endl;
	matrixOutput(wvm);*/
	drawLine(a, b,1);												
	drawLine(a, c,1);											  
	drawLine(b, d,1);
	drawLine(c, d,1);
}
//pair<double, double> windowToViewport(double _Xw, double _Yw, double wxl, double wxr, double wyb, double wyt, double vxl, double vxr, double vyb, double vyt) {
//
//	double Xv, Yv, Xw = _Xw, Yw = _Yw;
//	double Sx = (vxr - vxl) / (wxr - wxl);
//	double Sy = (vyt - vyb) / (wyt - wyb);
//	Xv = (vxl + (Xw - wxl) * Sx);
//	Yv = (vyb + (Yw - wyb) * Sy);
//
//	return make_pair(Xv, Yv);
//}

//pair<point, point> clipping(double vx0, double vy0, double vx1, double vy1, double vxl, double vxr, double vyb, double vyt) {
//	OutCode code0 = computeOutCode(vx0, vy0, vxl, vxr, vyb, vyt);
//	OutCode	code1 = computeOutCode(vx1, vy1, vxl, vxr, vyb, vyt);
//
//	while (true) {
//		if (!(code0 | code1)) {
//			// bitwise OR is 0: both points inside window; trivially accept and exit loop
//			return make_pair(point(vx0, vy0), point(vx1, vy1));
//			break;
//		}
//		else if (code0 & code1) {
//			// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
//			// or BOTTOM), so both must be outside window; exit loop (accept is false)
//			return make_pair(point(NULL, NULL), point(NULL, NULL));
//			break;
//		}
//		else {
//			// failed both tests, so calculate the line segment to clip
//			// from an outside point to an intersection with clip edge
//			double x = 0.0, y = 0.0;
//
//			// At least one endpoint is outside the clip rectangle; pick it.
//			OutCode outcodeOut = code1 > code0 ? code1 : code0;
//
//			// Now find the intersection point;
//			// use formulas:
//			//   slope = (y1 - y0) / (x1 - x0)
//			//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
//			//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
//			// No need to worry about divide-by-zero because, in each case, the
//			// outcode bit being tested guarantees the denominator is non-zero
//			if (outcodeOut & TOP) {           // point is above the clip window
//				x = vx0 + (vx1 - vx0) * (vyt - vy0) / (vy1 - vy0);
//				y = vyt;
//			}
//			else if (outcodeOut & BOTTOM) { // point is below the clip window
//				x = vx0 + (vx1 - vx0) * (vyb - vy0) / (vy1 - vy0);
//				y = vyb;
//			}
//			else if (outcodeOut & RIGHT) {  // point is to the right of clip window
//				y = vy0 + (vy1 - vy0) * (vxr - vx0) / (vx1 - vx0);
//				x = vxr;
//			}
//			else if (outcodeOut & LEFT) {   // point is to the left of clip window
//				y = vy0 + (vy1 - vy0) * (vxl - vx0) / (vx1 - vx0);
//				x = vxl;
//			}
//
//			// Now we move outside point to intersection point to clip
//			// and get ready for next pass.
//			if (outcodeOut == code0) {
//				vx0 = x;
//				vy0 = y;
//				code0 = computeOutCode(vx0, vy0, vxl, vxr, vyb, vyt);
//			}
//			else {
//				vx1 = x;
//				vy1 = y;
//				code1 = computeOutCode(vx1, vy1, vxl, vxr, vyb, vyt);
//			}
//		}
//	}
//
//
//}
//void fakeClipping(double vxl, double vxr, double vyb, double vyt) {
//	list<point> ::iterator p;
//	for (p= pointList.begin(); p != pointList.end(); p++) {
//		point newP(p->getX(), p->getY());
//		if (p->getX() < vxl)
//		{
//			newP.setX(vxl);
//		}
//		if (p->getX() > vxr)
//		{
//			newP.setX(vxr);
//		}
//		if (p->getY() < vyb)
//		{
//			newP.setY(vyb);
//		}
//		if (p->getY() > vyt)
//		{
//			newP.setY(vyt);
//		}
//		clippingPointList.push_back(newP);
//	}
//}
void resetTM() {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			transformationMatrix3D[i][j] = defaultMatrix3D[i][j];
		}
	}

}
void modeSwitch(string command) {
	char space_char = ' ';
	vector<string> words{};
	istringstream iss(command);
	for (string command; iss >> command; ) {
		words.push_back(command);
	}
	//stringstream sstream(command);
	//string word;
	//while (getline(sstream, word, space_char)) {
	//	//word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
	//	//words.push_back(word);
	//}

	if (!words.empty()) {

		/*for (const auto& str : words) {
			cout << str << " ";
		}*/
		//cout << words[0] << endl;
		//mode select
		if (words[0] == "scale")
		{
			cout << "Scale" << endl;
			double x = atof(words[1].c_str());
			double y = atof(words[2].c_str());
			//3D
			double z = atof(words[3].c_str());
			//cout << x << "　" << y << endl;
			//transformationMatrix[0][0] = transformationMatrix[0][0] * x;
			//transformationMatrix[1][1] = transformationMatrix[1][1] * y;
			transformationMatrix3D[0][0] = transformationMatrix3D[0][0] * x;
			transformationMatrix3D[1][1] = transformationMatrix3D[1][1] * y;
			transformationMatrix3D[2][2] = transformationMatrix3D[2][2] * z;

			matrixOutput(transformationMatrix3D);

		}
		else if (words[0] == "rotate")
		{
			cout << "Rotate" << endl;
			double angleTransformationMatrix[4][4] = { 1.0, 0.0, 0.0, 0.0,
													   0.0, 1.0, 0.0, 0.0,
													   0.0, 0.0, 1.0, 0.0,
													   0.0, 0.0, 0.0, 1.0 };
			//double degree = atof(words[1].c_str());
			double degreeX = atof(words[1].c_str());
			double degreeY = atof(words[2].c_str());
			double degreeZ = atof(words[3].c_str());
			double cosX = cos(angleToRadian(degreeX));
			double sinX = sin(angleToRadian(degreeX));
			double cosY = cos(angleToRadian(degreeY));
			double sinY = sin(angleToRadian(degreeY));
			double cosZ = cos(angleToRadian(degreeZ));
			double sinZ = sin(angleToRadian(degreeZ));

			//cout << degree << endl;
			/*angleTransformationMatrix[0][0] = cos(angleToRadian(degree));
			angleTransformationMatrix[0][1] =-1.0*sin(angleToRadian(degree)) ;
			angleTransformationMatrix[1][0] = sin(angleToRadian(degree));
			angleTransformationMatrix[1][1] = cos(angleToRadian(degree));*/
			angleTransformationMatrix[0][0] = cosZ * cosY;
			angleTransformationMatrix[0][1] = -1.0 * sinZ * cosX + cosZ * sinY * sinX;
			angleTransformationMatrix[0][2] = sinZ * sinX + cosZ * sinY * cosX;
			angleTransformationMatrix[1][0] = sinZ * cosY;
			angleTransformationMatrix[1][1] = cosZ * cosX + sinZ * sinY * sinX;
			angleTransformationMatrix[1][2] = -1.0 * cosZ * sinX + sinZ * sinY * cosX;
			angleTransformationMatrix[2][0] = -1.0 * sinY;
			angleTransformationMatrix[2][1] = cosY * sinX;
			angleTransformationMatrix[2][2] = cosY * cosX;
			calMMulM(angleTransformationMatrix, transformationMatrix3D, transformationMatrix3D);
			//calRotateTMMulTM(angleTransformationMatrix);
			matrixOutput(transformationMatrix3D);

		}
		else if (words[0] == "translate")
		{
			cout << "Translate" << endl;
			double x = atof(words[1].c_str());
			double y = atof(words[2].c_str());
			//3D
			double z = atof(words[3].c_str());
			//cout << x << "　" << y << endl;
			//transformationMatrix[0][2] = transformationMatrix[0][2] + x;
			//transformationMatrix[1][2] = transformationMatrix[1][2] + y;
			transformationMatrix3D[0][3] = transformationMatrix3D[0][3] + x;
			transformationMatrix3D[1][3] = transformationMatrix3D[1][3] + y;
			transformationMatrix3D[2][3] = transformationMatrix3D[2][3] + z;
			matrixOutput(transformationMatrix3D);

		}
		else if (words[0] == "object") {
			cout << "object" << endl << "TM" << endl;
			matrixOutput(transformationMatrix3D);
			//transformation*point

			string lineInFile;
			char space_char = ' ';
			vector<string> s{};
			string objectFileName = words[1].c_str();

			objectFile.open(objectFileName);
			if (!objectFile.is_open()) {
				perror("Error open");
				exit(EXIT_FAILURE);
			}
			getline(objectFile, lineInFile);
			while (lineInFile == "")
			{
				getline(objectFile, lineInFile);
			}
			//cout << lineInFile << endl;

			istringstream iss(lineInFile);
			for (string command; iss >> command; ) {
				s.push_back(command);
			}
			int pointNum = atoi(s[0].c_str());
			int planeNum = atoi(s[1].c_str());
			objectBase objectTemp;
			for (int i = 0; i < pointNum; i++)
			{
				getline(objectFile, lineInFile);

				//cout << lineInFile << endl;

				s.clear();
				istringstream iss(lineInFile);
				for (string command; iss >> command; ) {
					s.push_back(command);
				}

				objectTemp.pList.push_back(point3DInDouble(atof(s[0].c_str()), atof(s[1].c_str()), atof(s[2].c_str()), 1));

			}

			for (int i = 0; i < planeNum; i++)
			{
				getline(objectFile, lineInFile);
				poly polyTemp;
				//cout << lineInFile << endl;

				s.clear();
				istringstream iss(lineInFile);
				for (string command; iss >> command; ) {
					s.push_back(command);
				}
				polyTemp.n = atoi(s[0].c_str());
				for (int i = 1; i < s.size(); i++)
				{
					polyTemp.pointInPoly.push_back(objectTemp.pList[int(atoi(s[i].c_str())) - 1]);
					//cout << s[i]<<endl;
				}
				/*for (int i = 0; i < polyTemp.pointNO.size(); i++)
				{
					cout << polyTemp.pointNO[i];
				}
				cout << endl;*/
				objectTemp.plane.push_back(polyTemp);

			}
			for (int j = 0; j < objectTemp.plane.size(); j++)
			{
				for (int k = 0; k < objectTemp.plane[j].pointInPoly.size(); k++)
				{
					//cout << i << " "<< j << " "<< k<<" " << pNO << endl;
					point3DInDouble p(objectTemp.plane[j].pointInPoly[k].getX(), objectTemp.plane[j].pointInPoly[k].getY(), objectTemp.plane[j].pointInPoly[k].getZ(), objectTemp.plane[j].pointInPoly[k].getW())
						, p_new(0.0, 0.0, 0.0);
					//cout << "p: " << p.getX() << " " << p.getY()<<" "<< p.getZ() << " " << p.getW() << endl;
					p_new = calMMulP(transformationMatrix3D, p);
					objectTemp.plane[j].pointInPoly[k].setX(p_new.getX());
					objectTemp.plane[j].pointInPoly[k].setY(p_new.getY());
					objectTemp.plane[j].pointInPoly[k].setZ(p_new.getZ());
					objectTemp.plane[j].pointInPoly[k].setW(p_new.getW());
					//cout << "p_new: " << p_new.getX() << " " << p_new.getY() << " " << p_new.getZ() << " " << p_new.getW() << endl;

				}
			}

			//resetTM();
			objs.push_back(objectTemp);
			objectFile.close();


		}
		else if (words[0] == "observer") {
			cout << "observer" << endl;
			double eX = atof(words[1].c_str());
			double eY = atof(words[2].c_str());
			double eZ = atof(words[3].c_str());
			double colX = atof(words[4].c_str());
			double colY = atof(words[5].c_str());
			double colZ = atof(words[6].c_str());
			double tilt = atof(words[7].c_str());
			double pmH = atof(words[8].c_str());
			double pmY = atof(words[9].c_str());
			double pmTheta = atof(words[10].c_str());
			//EM
			double negativeEyeMatrix[4][4] = { 1.0, 0.0, 0.0, -1.0 * eX,
													  0.0, 1.0, 0.0, -1.0 * eY,
													  0.0, 0.0, 1.0, -1.0 * eZ,
													  0.0, 0.0, 0.0, 1.0 };
			double GRM[4][4] = { 1.0, 0.0, 0.0, 0.0,
										0.0, 1.0, 0.0, 0.0,
										0.0, 0.0, 1.0, 0.0,
										0.0, 0.0, 0.0, 1.0 };
			double mirrorMatrix[4][4] = { -1.0, 0.0, 0.0, 0.0,
										0.0, 1.0, 0.0, 0.0,
										0.0, 0.0, 1.0, 0.0,
										0.0, 0.0, 0.0, 1.0 };
			double tiltMatrix[4][4] = { 1.0, 0.0, 0.0, 0.0,
										0.0, 1.0, 0.0, 0.0,
										0.0, 0.0, 1.0, 0.0,
										0.0, 0.0, 0.0, 1.0 };
			point3DInDouble v1(0.0, 0.0, 0.0), v2(0.0, 0.0, 0.0), v3(0.0, 0.0, 0.0), viewVector(0.0, 0.0, 0.0), topVector(0.0, 1.0, 0.0);
			viewVector.setX(colX - eX);
			viewVector.setY(colY - eY);
			viewVector.setZ(colZ - eZ);
			v3.setX(viewVector.getX());
			v3.setY(viewVector.getY());
			v3.setZ(viewVector.getZ());
			v1 = cross(topVector, viewVector);
			v2 = cross(v3, v1);
			double lenV3 = vectorLength(v3);
			double lenV2 = vectorLength(v2);
			double lenV1 = vectorLength(v1);
			GRM[0][0] = v1.getX() / lenV1;
			GRM[0][1] = v1.getY() / lenV1;
			GRM[0][2] = v1.getZ() / lenV1;
			GRM[1][0] = v2.getX() / lenV2;
			GRM[1][1] = v2.getY() / lenV2;
			GRM[1][2] = v2.getZ() / lenV2;
			GRM[2][0] = v3.getX() / lenV3;
			GRM[2][1] = v3.getY() / lenV3;
			GRM[2][2] = v3.getZ() / lenV3;

			tiltMatrix[0][0] = cos(angleToRadian(tilt));
			tiltMatrix[0][1] = sin(angleToRadian(tilt));
			tiltMatrix[1][0] = -1.0 * sin(angleToRadian(tilt));
			tiltMatrix[1][1] = cos(angleToRadian(tilt));

			calMMulM(tiltMatrix, mirrorMatrix, tempMatrix0);

			calMMulM(GRM, negativeEyeMatrix, tempMatrix1);

			calMMulM(tempMatrix0, tempMatrix1, EM);
			/*cout << "tiltMatrix X mirrorMatrix:" << endl;
			matrixOutput(tempMatrix0);
			cout << "GRM X negativeEyeMatrix:" << endl;
			matrixOutput(tempMatrix1);*/
			/*	cout << "GRM:" << endl;
				matrixOutput(GRM);
				cout << "mirror:" << endl;
				matrixOutput(mirrorMatrix);
				cout << "tile:" << endl;
				matrixOutput(tiltMatrix);*/
			cout << "EM" << endl;
			matrixOutput(EM);
			//PM
			calPM(pmH, pmY, pmTheta);
		}
		else if (words[0] == "viewport")
		{
			cout << "viewport" << endl << "PM" << endl;
			double vxl = atof(words[1].c_str());
			double vxr = atof(words[2].c_str());
			double vyb = atof(words[3].c_str());
			double vyt = atof(words[4].c_str());
			//aspect ratio for pm
			PM[1][1] = (vxr - vxl) / (vyt - vyb);
			matrixOutput(PM);
			//Window to Viewport Transformation
			double wxr = 1.0, wxl = -1.0, wyt = 1.0, wyb = -1.0;
			double Sx = ((vxr - vxl) / (wxr - wxl)) / (wxr - wxl) * windowW;  //(wxr - wxl)=2
			double Sy = ((vyt - vyb) / (wyt - wyb)) / (wyt - wyb) * windowH;  //(wyt - wyb)=2
			double Xratio = (vxl - wxl) / (wxr - wxl);
			double Yratio = (vyb - wyb) / (wyt - wyb);
			//Xv = (vxl + (Xw - wxl) * Sx); //wxl=-1
			//Yv = (vyb + (Yw - wyb) * Sy); //wyB=-1
			//cal wvm
			double TnegativeW[4][4] = { 1.0, 0.0, 0.0, -wxl,
										0.0, 1.0, 0.0, -wyb,
										0.0, 0.0, 1.0, 0.0,
										0.0, 0.0, 0.0, 1.0 };
			double Tv[4][4] = { 1.0, 0.0, 0.0, Xratio * windowW,
								0.0, 1.0, 0.0, Yratio * windowH,
								0.0, 0.0, 1.0, 0.0,
								0.0, 0.0, 0.0, 1.0 };
			double S[4][4] = { Sx , 0.0, 0.0, 0.0,
							   0.0, Sy , 0.0, 0.0,
							   0.0, 0.0, 1.0, 0.0,
							   0.0, 0.0, 0.0, 1.0 };
			double temp[4][4];

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					temp[i][j] = 0;
					for (int k = 0; k < 4; k++) {
						temp[i][j] += S[i][k] * TnegativeW[k][j];
					}
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					wvm[i][j] = 0;
					for (int k = 0; k < 4; k++) {
						wvm[i][j] += Tv[i][k] * temp[k][j];
					}
				}
			}
			//cout << "viewport fin" << endl;
		}
		else if (words[0] == "display") {
			pointList.clear();
			cout << "display" << endl;
			vector<objectBase> objsInDisplay;
			//cal wvm*pm*em*transformation*point?????????



			//PM*EM->PMMulEM
			calMMulM(PM, EM, PMMulEM);
			//cout << "pm*em:" << endl;
			//matrixOutput(PMMulEM);


			//pm*em*transformation*point
			//cout << "pm*em*t*p start" << endl;

			for (int i = 0; i < objs.size(); i++)
			{
				objectBase objTemp;
				for (int j = 0; j < objs[i].plane.size(); j++)
				{
					poly planeTemp;
					planeTemp.n = 0;
					for (int k = 0; k < objs[i].plane[j].pointInPoly.size(); k++)
					{

						point3DInDouble p_new(0.0, 0.0, 0.0);
						//cout << "p: " << p.getX() << " " << p.getY()<<" "<< p.getZ() << " " << p.getW() << endl;
						p_new = calMMulP(PMMulEM, objs[i].plane[j].pointInPoly[k]);
						planeTemp.pointInPoly.push_back(p_new);
						planeTemp.n += 1;

						//cout << "p_new: " << p_new.getX() << " " << p_new.getY()<<" "<< p_new.getZ() << " " << p_new.getW() << endl;

					}
					objTemp.plane.push_back(planeTemp);
				}
				objsInDisplay.push_back(objTemp);

			}
			//cout << "pm*em*t*p fin" << endl;

			//clipping
			objsInDisplay = clipping(objsInDisplay);
			//cout << "clipping fin" << endl;


			//perspective divide
			for (int i = 0; i < objsInDisplay.size(); i++)
			{
				for (int j = 0; j < objsInDisplay[i].plane.size(); j++)
				{
					for (int k = 0; k < objsInDisplay[i].plane[j].pointInPoly.size(); k++)
					{
						double wTemp = objsInDisplay[i].plane[j].pointInPoly[k].getW();
						objsInDisplay[i].plane[j].pointInPoly[k].setX(objsInDisplay[i].plane[j].pointInPoly[k].getX() / wTemp);
						objsInDisplay[i].plane[j].pointInPoly[k].setY(objsInDisplay[i].plane[j].pointInPoly[k].getY() / wTemp);
						objsInDisplay[i].plane[j].pointInPoly[k].setZ(objsInDisplay[i].plane[j].pointInPoly[k].getZ() / wTemp);
						objsInDisplay[i].plane[j].pointInPoly[k].setW(1);
					}
				}
			}
			//cout << "perspective divide fin" << endl;
			for (int i = 0; i < objsInDisplay.size(); i++)
			{
				for (int j = 0; j < objsInDisplay[i].plane.size(); j++)
				{
					//cout << i << "plane " << j << endl;
					for (int k = 0; k < objsInDisplay[i].plane[j].pointInPoly.size(); k++)
					{
						//cout << "clipped: " << objsInDisplay[i].plane[j].pointInPoly[k].getX() << " " << objsInDisplay[i].plane[j].pointInPoly[k].getY() << " " << objsInDisplay[i].plane[j].pointInPoly[k].getZ() << " " << objsInDisplay[i].plane[j].pointInPoly[k].getW() << " " << endl;
					}
				}
			}
			//nobackfaces
			if (nobackfaces)
			{
				//cout << "no back" << endl;
				for (int i = 0; i < objsInDisplay.size(); i++)
				{
					//cout << i<<" ";
					for (int j = 0; j < objsInDisplay[i].plane.size(); j++)
					{
						//cout << j<<" \n";
						if (objsInDisplay[i].plane[j].pointInPoly.empty() == false)
						{
							//get 2 point in the plane to cross ,then get the normal vector of the plane
							point3DInDouble a(0.0, 0.0, 0.0), b(0.0, 0.0, 0.0), aXb(0.0, 0.0, 0.0);
							a.setX(objsInDisplay[i].plane[j].pointInPoly[1].getX() - objsInDisplay[i].plane[j].pointInPoly[0].getX());
							a.setY(objsInDisplay[i].plane[j].pointInPoly[1].getY() - objsInDisplay[i].plane[j].pointInPoly[0].getY());
							a.setZ(objsInDisplay[i].plane[j].pointInPoly[1].getZ() - objsInDisplay[i].plane[j].pointInPoly[0].getZ());
							b.setX(objsInDisplay[i].plane[j].pointInPoly[2].getX() - objsInDisplay[i].plane[j].pointInPoly[1].getX());
							b.setY(objsInDisplay[i].plane[j].pointInPoly[2].getY() - objsInDisplay[i].plane[j].pointInPoly[1].getY());
							b.setZ(objsInDisplay[i].plane[j].pointInPoly[2].getZ() - objsInDisplay[i].plane[j].pointInPoly[1].getZ());
							aXb = cross(a, b);
							//cout << "0:" << objsInDisplay[i].plane[j].pointInPoly[0].getX() << " " << objsInDisplay[i].plane[j].pointInPoly[0].getY() << " " << objsInDisplay[i].plane[j].pointInPoly[0].getZ() << " " << objsInDisplay[i].plane[j].pointInPoly[0].getW() << endl;
							//cout << "1:" << objsInDisplay[i].plane[j].pointInPoly[1].getX() << " " << objsInDisplay[i].plane[j].pointInPoly[1].getY() << " " << objsInDisplay[i].plane[j].pointInPoly[1].getZ() << " " << objsInDisplay[i].plane[j].pointInPoly[1].getW() << endl;
							//cout << "2:" << objsInDisplay[i].plane[j].pointInPoly[2].getX() << " " << objsInDisplay[i].plane[j].pointInPoly[2].getY() << " " << objsInDisplay[i].plane[j].pointInPoly[2].getZ() << " " << objsInDisplay[i].plane[j].pointInPoly[2].getW() << endl;
							//cout << "a:" << a.getX() << " " << a.getY() << " " << a.getZ() << " " << a.getW() << endl;
							//cout << "b:" << b.getX() << " " << b.getY() << " " << b.getZ() << " " << b.getW() << endl;
							//cout << "a x b:" << aXb.getX() << " " << aXb.getY() << " " << aXb.getZ() << " " << aXb.getW() << endl;

							if (aXb.getZ() >= 0)
							{
								//cout << "unvisible" << endl;
								objsInDisplay[i].plane[j].visible = false;
							}
						}
						else
						{
							objsInDisplay[i].plane[j].visible = false;
						}
					}
				}
			}
			//cout << "nobackfaces fin" << endl;
			//matrixOutput(wvm);
			//window to view
			//matrixOutput(wvm);
			for (int i = 0; i < objsInDisplay.size(); i++)
			{
				for (int j = 0; j < objsInDisplay[i].plane.size(); j++)
				{
					for (int k = 0; k < objsInDisplay[i].plane[j].pointInPoly.size(); k++)
					{
						if (objsInDisplay[i].plane[j].visible)
						{
							int bNum;
							if (k == objsInDisplay[i].plane[j].pointInPoly.size() - 1) {
								bNum = 0;
							}
							else {
								bNum = k + 1;
							}
							point a = cal2DP(wvm, objsInDisplay[i].plane[j].pointInPoly[k]);
							point b = cal2DP(wvm, objsInDisplay[i].plane[j].pointInPoly[bNum]);
							//cout << "drawline a: " << a.getX() << " " << a.getY() << " b: " << b.getX() << " " << b.getY() << endl;
							
							drawLine(a, b);
						}


					}
				}
			}
			
			drawBorder(-1.0,1.0,-1.0,1.0);
			//cout << "WtoV fin" << endl;

			drawAllPoint();
			system("pause");
		}
		else if (words[0] == "nobackfaces") {
			nobackfaces = true;
		}
		//else if (words[0] == "square")
		//{
		//	//cout << "--square--" << endl;
		//	double result[3][4];
		//	for (int i = 0; i < 3; i++) {
		//		//cout << "{";
		//		for (int j = 0; j < 4; j++) {
		//			result[i][j] = 0;
		//			for (int k = 0; k < 3; k++) {
		//				result[i][j] += transformationMatrix[i][k] * squareMatrix[k][j];
		//			}
		//			//cout << setw(10) << result[i][j] << "";
		//		}
		//		//cout << "}" << endl;
		//	}
		//	saveToSideList(result);
		//	squareCounter += 1;
		//	cout << "You have" << setw(2) << squareCounter << " squares." << endl;
		//}
		//else if (words[0] == "triangle")
		//{
		//	double result[3][3];
		//	//cout << "Triangle" << endl;
		//	//cout << endl;
		//	for (int i = 0; i < 3; i++) {
		//		//cout << "{";
		//		for (int j = 0; j < 3; j++) {
		//			result[i][j] = 0;
		//			for (int k = 0; k < 3; k++) {
		//				result[i][j] += transformationMatrix[i][k] * triangleMatrix[k][j];
		//			}
		//			//cout << setw(10) << result[i][j] << "\t";
		//		}
		//		//cout << "}" << endl;
		//	}
		//	//matrixOutput(result);
		//	saveToSideList(result);
		//	triangleCounter += 1;
		//	cout << "You have" << setw(2) << triangleCounter << " triangles." << endl;
		//}

		//else if (words[0] == "view")
		//{
		//	
		//	cout << "view" << endl<<"WVM"<<endl;
		//	double wxl = atof(words[1].c_str());
		//	double wxr = atof(words[2].c_str());
		//	double wyb = atof(words[3].c_str());
		//	double wyt = atof(words[4].c_str());
		//	double vxl = atof(words[5].c_str());
		//	double vxr = atof(words[6].c_str());
		//	double vyb = atof(words[7].c_str());
		//	double vyt = atof(words[8].c_str());
		//	//cout << wxl << " " << wxr << " " << wyb << " " << wyt << " " << vxl << " " << vxr << " " << vyb << " " << vyt << endl;
		//	//world to view space
		//	int firstVx = 0, firstVy = 0, secondVx = 0, secondVy = 0;
		//	point clippingP0(0,0), clippingP1(0,0);
		//	for (int i=0; i<windowSidePair.size(); i++) {
		//		//cout << "----side pair NO." << i << endl <<setw(6)<<"first" << setw(4) << windowSidePair[i].first.getX() << setw(4) << windowSidePair[i].first.getY() << endl<<setw(6)<<"second" << setw(4) << windowSidePair[i].second.getX() << setw(4) << windowSidePair[i].second.getY() << endl;
		//		//world to view space
		//		tie(firstVx,firstVy) = windowToViewport(windowSidePair[i].first.getX(), windowSidePair[i].first.getY(),wxl,wxr,wyb,wyt,vxl,vxr,vyb,vyt);
		//		tie(secondVx, secondVy) = windowToViewport(windowSidePair[i].second.getX(), windowSidePair[i].second.getY(), wxl, wxr, wyb, wyt, vxl, vxr, vyb, vyt);
		//		//clipping
		//		tie(clippingP0,clippingP1)=clipping(firstVx, firstVy, secondVx, secondVy,vxl, vxr, vyb, vyt);
		//		//point viewP0(firstVx,firstVy), viewP1(secondVx,secondVy);
		//		//cout << "--after WtoV"<< endl << setw(6) << "first" << setw(4) << clippingP0.getX() << setw(4) << clippingP0 .getY()<< endl << setw(6) << "second" << setw(4) << clippingP1.getX() << setw(4) << clippingP1.getY() << endl;
		//		
		//		drawLine(clippingP0, clippingP1);
		//	}
		//	drawBorder(vxl, vxr, vyb, vyt);
		//	//fakeClipping(vxl, vxr, vyb, vyt);  //just a joke, you knowwwwwww
		//	//drawClippingPoint();
		//	drawAllPoint();
		//	//cal wvm
		//	double TnegativeW[3][3] = { 1.0, 0.0, -wxl,
		//					   0.0, 1.0, -wyb,
		//					   0.0, 0.0, 1.0 };
		//	double Tv[3][3] = { 1.0, 0.0, vxl,
		//							   0.0, 1.0, vyb,
		//							   0.0, 0.0, 1.0 };
		//	double S[3][3] = { (vxr - vxl) / (wxr - wxl), 0.0, 0.0,
		//					   0.0, (vyt - vyb) / (wyt - wyb), 0.0,
		//					   0.0, 0.0, 1.0 };
		//	double temp[3][3];
		//	double wvm[3][3];
		//	for (int i = 0; i < 3; i++) {
		//		for (int j = 0; j < 3; j++) {
		//			temp[i][j] = 0;
		//			for (int k = 0; k < 3; k++) {
		//				temp[i][j] += S[i][k] * TnegativeW[k][j];
		//			}
		//		}
		//	}
		//	for (int i = 0; i < 3; i++) {
		//		for (int j = 0; j < 3; j++) {
		//			wvm[i][j] = 0;
		//			for (int k = 0; k < 3; k++) {
		//				wvm[i][j] += Tv[i][k] * temp[k][j];
		//			}
		//		}
		//	}
		//	matrixOutput(wvm);
		//	system("pause");
		//}

		//else if (words[0] == "clearData")
		//{
		//	//cout << "--clear data--" << endl;
		//	pointList.clear();
		//	/*windowSidePair.clear();*/
		//	squareCounter = 0;
		//}

		//else if (words[0] == "clearScreen")
		//{
		//	//cout << "--clear screen--" << endl;
		//	pointList.clear();
		//	drawAllPoint();
		//	/*clippingPointList.clear();
		//	drawClippingPoint();*/
		//}
		else if (words[0] == "reset")
		{
			resetTM();
			//pointList.clear();
			//cout << "--reset--" << endl;

		}
		else if (words[0] == "end")
		{

			//cout << "end" << endl;
			//system("pause");
			quit();
		}
		else if (words[0] == "#") {
			for (int j = 0; j < words.size(); j++)
			{
				cout << words[j] << " ";
			}
			cout << endl;
		}
		/*	else if (words[0] != "")
			{
				cout << words[0] << endl;
			}*/
		else {  // "NULL" or
		//skip
			//system("pause");
			//cout << "skip" << endl;
		}
	}
}
//int rounding(double num, int index = 0)
//{
//	bool isNegative = false; // whether is negative number or not
//
//	if (num < 0) // if this number is negative, then convert to positive number
//	{
//		isNegative = true;
//		num = -num;
//	}
//
//	if (index >= 0)
//	{
//		int multiplier;
//		multiplier = pow(10, index);
//		num = (int)(num * multiplier + 0.5) / (multiplier * 1.0);
//	}
//
//	if (isNegative) // if this number is negative, then convert to negative number
//	{
//		num = -num;
//	}
//
//	return (int)num;
//}
//point edgeCheck(float _x, float _y) {
//	int x = rounding(_x);
//	int y = rounding(_y);
//	// printf("%d %d %f %f \n", x, y , _x ,_y); //debug
//	return point(x, y);
//}
void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//cout << "file name:" << fileName << endl;
	string lineInFile;

	inputFile.open(fileName);
	if (!inputFile.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}
	while (getline(inputFile, lineInFile)) {
		//cout << lineInFile << endl;
		modeSwitch(lineInFile);
	}
	inputFile.close();
	glFlush();
}
//void recover() {
//	list<point> ::iterator pointIterator;
//	for (pointIterator = pointListBackUp.begin(); pointIterator != pointListBackUp.end(); pointIterator++) {
//		pointList.push_back(point(pointIterator->getX(), pointIterator->getY()));
//	}
//	pointListBackUp.clear();
//	drawAllPoint();
//}

//void clear() {
//	list<point> ::iterator pointIterator;
//	for (pointIterator = pointList.begin(); pointIterator != pointList.end(); pointIterator++) {
//		pointListBackUp.push_back(point(pointIterator->getX(), pointIterator->getY()));
//	}
//	pointList.clear();
//	drawAllPoint();
//}

//void mouse(int button, int state, int x, int y) {
//	switch (mode)
//	{
//	case 1:   //point
//		if(state== GLUT_UP)
//		pointList.push_back(point(x,y));
//		break;
//	case 2:  //line
//		if (state == GLUT_UP)
//		{
//			lineCounter += 1;
//			if ((lineCounter % 2) != 0 && state == GLUT_UP)
//			{
//				lineTemp.setX(x);
//				lineTemp.setY(y);
//			}
//			else if ((lineCounter % 2) == 0 && state == GLUT_UP)
//			{
//				//cout << lineTemp.getX() << " " << lineTemp.getY() << " " << x << " " << y << endl;   //debug
//				drawLine(lineTemp, point(x, y));
//			}
//		}
//		//cout << lineCounter<<" " <<state<< endl;
//		
//		break;
//	case 3:  //polygon
//		if (state ==GLUT_UP)
//		{
//			if (button==GLUT_LEFT_BUTTON)
//			{
//				if (polygontemp.getX()==NULL &&polygontemp.getY()==NULL)
//				{
//					polygonSrc.setX(x);
//					polygonSrc.setY(y);
//					polygontemp.setX(x);
//					polygontemp.setY(y);
//				}
//				else
//				{
//					drawLine(polygontemp, point(x, y));
//					polygontemp.setX(x);
//					polygontemp.setY(y);
//				}
//			}
//			else if (button==GLUT_RIGHT_BUTTON)
//			{
//				drawLine(polygontemp, polygonSrc);
//				polygontemp.setX(NULL);
//				polygontemp.setY(NULL);
//
//			}
//		}
//		break;
//	case 4:  //circle
//		if (state==GLUT_DOWN)
//		{
//			circleTemp.setX(x);
//			circleTemp.setY(y);
//		}
//		else if (state == GLUT_UP)
//		{
//			//cout << lineTemp.getX() << " " << lineTemp.getY() << " " << x << " " << y << endl;
//			drawCircle(circleTemp, point(x, y));
//		}
//		break;
//	default:
//		break;
//	}
//	//point temp=point(x ,y);
//	//if (state == GLUT_DOWN) {
//	//	pointList.push_back(temp);
//	//}
//	drawAllPoint();
//
//	//if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) drawSquare(x, y);
//}

//void keyBoard(unsigned char key, int x, int y) {
//	//cout << key <<" "<<x<<" "<<y << endl; //debug
//	switch (key)
//	{
//		case 'd': //point
//			mode = 1;
//			break;
//		case 'l': //line
//			mode = 2;
//			break;
//		case 'p': //polygon
//			mode = 3;
//			break;
//		case 'o': //circle
//			mode = 4;
//			break;
//		case 'c': //clear
//			clear();
//			break;
//		case 'r': //recover
//			recover();
//			break;
//		case 'q': //quit
//			quit();
//
//			break;
//	default:
//		break;
//	}
//}
int main(int argc, char** argv) {
	string lineInFile;
	system("pause");
	glutInit(&argc, argv);
	fileName = argv[1];
	inputFile.open(fileName);
	if (!inputFile.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}
	getline(inputFile, lineInFile);
	char space_char = ' ';
	vector<string> words{};
	istringstream iss(lineInFile);
	for (string command; iss >> command; ) {
		words.push_back(command);
	}
	windowW = atoi(words[0].c_str());
	windowH = atoi(words[1].c_str());
	//cout << "glut window size " << windowW << "x" << windowH << endl;
	inputFile.close();

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	gluOrtho2D(0, windowW, 0, windowH);
	glutCreateWindow("Your First GLUT  Window!");
	//drawCircle(point(250, 250), point(250,200)); //debug
	//drawLine(point(0, 500), point(250,50));  //debug
	//drawLine(point(0, 0), point(11, 22));
	//drawLine(point(0, 0), point(22, 11));
	//drawLine(point(50, 50), point(11, 33));
	//drawLine(point(50, 50), point(33, 11));
	glutDisplayFunc(display);
	//glutMouseFunc(mouse);
	//glutKeyboardFunc(keyBoard);
	gluOrtho2D(0, windowW, 0, windowH);
	glutSwapBuffers();
	glutMainLoop();
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
