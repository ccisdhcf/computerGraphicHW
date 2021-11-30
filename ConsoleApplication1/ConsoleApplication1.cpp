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
		int x;
		int y;
	public:
		point(int _x, int _y) {
			x = _x;
			y = _y;
		};
		int getX() {
			return x;
		};
		int getY() {
			return y;
		}
		void setX(int new_x) {
			x = new_x;
		}
		void setY(int new_y) {
			y = new_y;
		}
		
};
class pointInDouble
{
private:
	double x;
	double y;
public:
	pointInDouble(double _x, double _y) {
		x = _x;
		y = _y;
	};
	double getX() {
		return x;
	};
	double getY() {
		return y;
	}
	void setX(int new_x) {
		x = new_x;
	}
	void setY(int new_y) {
		y = new_y;
	}

};
ifstream inputFile;
vector<pair<point,point>> windowSidePair;
vector<pair<point, point>> viewSidePair;
list<point> pointList;
list<point> pointListBackUp;
point lineTemp = point(NULL, NULL);
point circleTemp = point(NULL, NULL);
point polygonSrc = point(NULL, NULL);
point polygontemp = point(NULL, NULL);
int circleCounter = 0;
int lineCounter = 0;
int mode = 0; //  d,l,p,o,c,r,q
string fileName = "";

static double defaultMatrix[3][3] = { 1.0, 0.0, 0.0,
								      0.0, 1.0, 0.0,
									  0.0, 0.0, 1.0 };
static double transformationMatrix[3][3] = { 1.0, 0.0, 0.0,
						  				     0.0, 1.0, 0.0,
									         0.0, 0.0, 1.0 };
static double squareMatrix[3][4] = { -1.0,-1.0, 1.0, 1.0,
									   -1.0, 1.0, 1.0,-1.0,
										1.0, 1.0 ,1.0, 1.0 };
static double squareDefaultMatrix[3][4] = { -1.0,-1.0, 1.0, 1.0,
									   -1.0, 1.0, 1.0,-1.0,
										1.0, 1.0 ,1.0, 1.0 };
static double triangleMatrix[3][3] = { 0.0,-1.0, 1.0,
									   1.0,-1.0,-1.0,
									   1.0, 1.0, 1.0};
static double triangleDefaultMatrix[3][3] = { 0.0,-1.0, 1.0,
									   1.0,-1.0,-1.0,
									   1.0, 1.0, 1.0 };
static double angleTransformationMatrix[3][3] = { 1.0, 0.0, 0.0,
												  0.0, 1.0, 0.0,
											      0.0, 0.0, 1.0 };
static double rotateTMMulTM[3][3] = { 1.0, 0.0, 0.0,
									  0.0, 1.0, 0.0,
									  0.0, 0.0, 1.0 };
static double angle = 0.0;



//world to view
//tuple<int,int > windowToViewport(double Xw, double Yw, double wxl,double wxr	,double wyb	,double wyt	,double vxl	,double vxr	,double vyb	,double vyt){
//	double Sx = (vxr - vxl) / (wxr - wxl);
//	double Sy = (vyt - vyb) / (wyt - wyb);
//	return make_tuple((vxl + (Xw - wxl) * Sx),(vyb + (Yw - wyb) * Sy) );
//}
double angleToRadian(double angle) {  //from angle to radian
	return (angle * M_PI / (double)180.0);
}
void matrixOutput(double matrix[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		cout << "{" ;
		for (int j = 0; j < 2; j++) {
			cout << setw(10) << matrix[i][j] << ",";
		}
		cout << setw(10) << matrix[i][2] << "}" << endl;
	}
	cout << endl;
}
void matrixOutput(double matrix[3][4]) {
	for (int i = 0; i < 3; i++)
	{
		cout << "{";
		for (int j = 0; j < 3; j++) {
			cout << setw(10) << matrix[i][j] << ",";
		}
		cout << setw(10) << matrix[i][3] << "}" << endl;
	}
	cout << endl;
}
void calRotateTMMulTM() {
	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {
			rotateTMMulTM[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				rotateTMMulTM[i][j] += transformationMatrix[i][k] * angleTransformationMatrix[k][j];
			}

		}
	}
	matrixOutput(rotateTMMulTM);
}
void quit() {
	exit(1);
}
void drawSquare(int x, int y) {
	glPointSize(1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	glEnd();

}
void drawAllPoint() {
	glClear(GL_COLOR_BUFFER_BIT);
	list<point> ::iterator point;
	for (point = pointList.begin(); point != pointList.end(); point++) {
		drawSquare(point->getX(), point->getY());
	}
	glutSwapBuffers();
}
void circle1to8(point centre, point p_0) {
	point p_1 = point(p_0.getY(), p_0.getX());
	point p_2 = point(p_0.getY(), (-1) * p_0.getX());
	point p_3 = point(p_0.getX(), (-1) * p_0.getY());
	point p_4 = point((-1) * p_0.getX(), (-1) * p_0.getY());
	point p_5 = point((-1) * p_0.getY(), (-1) * p_0.getX());
	point p_6 = point((-1) * p_0.getY(), p_0.getX());
	point p_7 = point((-1) * p_0.getX(), p_0.getY());

	pointList.push_back(point(centre.getX() + p_0.getX(), centre.getY() + p_0.getY()));
	pointList.push_back(point(centre.getX() + p_1.getX(), centre.getY() + p_1.getY()));
	pointList.push_back(point(centre.getX() + p_2.getX(), centre.getY() + p_2.getY()));
	pointList.push_back(point(centre.getX() + p_3.getX(), centre.getY() + p_3.getY()));
	pointList.push_back(point(centre.getX() + p_4.getX(), centre.getY() + p_4.getY()));
	pointList.push_back(point(centre.getX() + p_5.getX(), centre.getY() + p_5.getY()));
	pointList.push_back(point(centre.getX() + p_6.getX(), centre.getY() + p_6.getY()));
	pointList.push_back(point(centre.getX() + p_7.getX(), centre.getY() + p_7.getY()));



}
void drawCircle(point centre, point circlePoint) {  //超出邊界(?
	double radius = pow(pow((circlePoint.getX() - centre.getX()), 2) + pow((circlePoint.getY() - centre.getY()), 2), 0.5);
	list<point> circlelist;
	point circle = point(0, int(radius)); //init
	circle1to8(centre, circle);
	double d = 5 / 4 - radius;  //init
	while (circle.getX() < circle.getY())
	{
		if (d < 0) {
			d += circle.getX() * 2 + 3;
			circle.setX(circle.getX() + 1);
		}
		else
		{
			d += (circle.getX() - circle.getY()) * 2 + 5;
			circle.setX(circle.getX() + 1);
			circle.setY(circle.getY() - 1);
		}
		circle1to8(centre, circle);
		//cout << circleTemp.getX() << " " << circleTemp.getY()<<endl; //debug
	}


	//float x_2 = pow((circlePoint.getX() - centre.getX()), 2);
	//float y_2 = pow((circlePoint.getY() - centre.getY()), 2);
	//float radius = pow((x_2 + y_2), 0.5);
	//pointList.push_back(point(centre.getX() + (int)radius, centre.getY()));
	//pointList.push_back(point(centre.getX() - (int)radius, centre.getY()));
	//for (int tempX = centre.getX() - (int)radius; tempX < centre.getX() + (int)radius; tempX+= forLoopOptimize)
	//{
	//	int tempY_Abs = pow(radius * radius - (tempX - centre.getX()) * (tempX - centre.getX()),0.5);
	//	pointList.push_back(point(tempX, centre.getY()+tempY_Abs));
	//	pointList.push_back(point(tempX, centre.getY()-tempY_Abs));

	//}
}
//void drawPolygon(){}    //drawLine is enough
void drawLine(point src, point des) {
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
			pointList.push_back(point(tempX, des.getY()));
		}
	}
	else if (dx == 0) //slope=∞
	{
		for (int tempY = min(src.getY(), des.getY()); tempY < max(src.getY(), des.getY()); tempY += 1)
		{
			pointList.push_back(point(des.getX(), tempY));
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
		pointList.push_back(point(x, y));
		while (x <= des.getX())
		{
			//cout << d << "\n\n";  //debug
			if (d <= 0) {
				pointList.push_back(point(x, y));
				x += 1;
				//cout << x <<" " << y << "\n";  //debug
				d += incE;
			}
			else
			{
				pointList.push_back(point(x, y));
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

		pointList.push_back(point(x, y));
		while (y * direction <= des.getY() * direction)
		{
			//cout << d << "\n\n";  //debug
			if (d <= 0) {
				pointList.push_back(point(x, y));
				y += direction;
				//cout << x <<" " << y << "\n";  //debug
				d += incE;
			}
			else
			{
				pointList.push_back(point(x, y));
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
void saveToSideList(double result[3][4]) {
	point p0(result[0][0], result[1][0]),
		p1(result[0][1], result[1][1]),
		p2(result[0][2], result[1][2]),
		p3(result[0][3], result[1][3]);

	windowSidePair.push_back(make_pair(p0, p1));

	windowSidePair.push_back(make_pair(p1, p2));

	windowSidePair.push_back(make_pair(p2, p3));

	windowSidePair.push_back(make_pair(p3, p0));
}
void saveToSideList(double result[3][3]) {
	point p0(result[0][0], result[1][0]),
		p1(result[0][1], result[1][1]),
		p2(result[0][2], result[1][2]);
		

	windowSidePair.push_back(make_pair(p0, p1));

	windowSidePair.push_back(make_pair(p1, p2));

	windowSidePair.push_back(make_pair(p2, p0));
}
void drawBorder(double vxl, double vxr, double vyb, double vyt) {
	point a(vxl, vyt), b(vxl, vyb), c(vxr, vyt), d(vxr, vyb);   //    a-----c
	drawLine(a, b);												//    |     |
	drawLine(a, c);											    //	  b-----d
	drawLine(b, d);
	drawLine(c, d);
}
pair<int,int> windowToViewport(double _Xw,double _Yw,double wxl,double wxr,double wyb,double wyt,double vxl,double vxr,double vyb,double vyt) {
	int Xv, Yv, Xw = _Xw, Yw = _Yw;
	double Sx = (vxr - vxl) / (wxr - wxl);
	double Sy = (vyt - vyb) / (wyt - wyb);
	Xv = (vxl + (Xw - wxl) * Sx);
	Yv = (vyb + (Yw - wyb) * Sy);
	return make_pair(Xv, Yv);
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
		cout << endl << words[0] << endl;
		//mode select
		if (words[0] == "scale")
		{
			double x = atof(words[1].c_str());
			double y = atof(words[2].c_str());
			cout << x << "　" << y << endl;
			transformationMatrix[0][0] = transformationMatrix[0][0] * x;
			transformationMatrix[1][1] = transformationMatrix[1][1] * y;
			//matrixOutput(transformationMatrix);
			calRotateTMMulTM();
		}
		else if (words[0] == "rotate")
		{
			double degree = atof(words[1].c_str());
			cout << degree << endl;
			angle += degree;
			angleTransformationMatrix[0][0] = cos(angleToRadian(angle));
			angleTransformationMatrix[0][1] = -1.0 * sin(angleToRadian(angle));
			angleTransformationMatrix[1][0] = sin(angleToRadian(angle));
			angleTransformationMatrix[1][1] = cos(angleToRadian(angle));
			cout <<angle<<"° rotate matrix"<<endl;
			cout << "----------------" << endl;
			matrixOutput(angleTransformationMatrix);
			cout << "----------------" << endl;
			calRotateTMMulTM();
		}
		else if (words[0] == "translate")
		{
			double x = atof(words[1].c_str());
			double y = atof(words[2].c_str());
			cout << x << "　" << y << endl;
			transformationMatrix[0][2] = transformationMatrix[0][2] + x;
			transformationMatrix[1][2] = transformationMatrix[1][2] + y;
			//matrixOutput(transformationMatrix);
			calRotateTMMulTM();
		}
		else if (words[0] == "square")
		{
			cout << "--square--" << endl;
			double rotatedResult[3][4];
			double result[3][4];
			
			
			calRotateTMMulTM();

			for (int i = 0; i < 3; i++) {
				cout << "{";

				for (int j = 0; j < 4; j++) {
					rotatedResult[i][j] = 0;
					for (int k = 0; k < 3; k++) {
						rotatedResult[i][j] += angleTransformationMatrix[i][k] * squareMatrix[k][j];
						}

					cout << setw(10) << rotatedResult[i][j] << "";
				}
				cout<<"}" << endl;
			}
			cout << endl;

			for (int i = 0; i < 3; i++) {
				cout << "{";

				for (int j = 0; j < 4; j++) {

					result[i][j] = 0;

					for (int k = 0; k < 3; k++) {
						result[i][j] += transformationMatrix[i][k] * rotatedResult[k][j];
					}

					cout << setw(10) << result[i][j] << "";
				}
				cout << "}" << endl;
			}
			saveToSideList(result);
			
		}
		else if (words[0] == "triangle")
		{
			double rotatedResult[3][3];
			double result[3][3];
		
			cout << "--triangle--" << endl;
			calRotateTMMulTM();

			for (int i = 0; i < 3; i++) {
				//cout << "{";

				for (int j = 0; j < 3; j++) {
					rotatedResult[i][j] = 0;

					for (int k = 0; k < 3; k++) {
						rotatedResult[i][j] += angleTransformationMatrix[i][k] * triangleMatrix[k][j];
					}

					//cout << setw(10) << rotatedResult[i][j] << "\t";
				}

				//cout << "}" << endl;
			}
			cout << endl;
			for (int i = 0; i < 3; i++) {
				//cout << "{";

				for (int j = 0; j < 3; j++) {
					result[i][j] = 0;

					for (int k = 0; k < 3; k++) {
						result[i][j] += transformationMatrix[i][k] * rotatedResult[k][j];
					}

					//cout << setw(10) << result[i][j] << "\t";
				}

				//cout << "}" << endl;
			}
			matrixOutput(result);
			saveToSideList(result);

		}
		else if (words[0] == "view")
		{
			//cliping?
			cout << "--view--" << endl;
			double wxl = atof(words[1].c_str());
			double wxr = atof(words[2].c_str());
			double wyb = atof(words[3].c_str());
			double wyt = atof(words[4].c_str());
			double vxl = atof(words[5].c_str());
			double vxr = atof(words[6].c_str());
			double vyb = atof(words[7].c_str());
			double vyt = atof(words[8].c_str());

			cout << wxl << " " << wxr << " " << wyb << " " << wyt << " " << vxl << " " << vxr << " " << vyb << " " << vyt << endl;

			//world to view space
			int firstVx = 0, firstVy = 0, secondVx = 0, secondVy = 0;
			for (int i=0; i<windowSidePair.size(); i++) {
			
				//cout << "----side pair NO." << i << endl <<setw(6)<<"first" << setw(4) << windowSidePair[i].first.getX() << setw(4) << windowSidePair[i].first.getY() << endl<<setw(6)<<"second" << setw(4) << windowSidePair[i].second.getX() << setw(4) << windowSidePair[i].second.getY() << endl;

				//world to view space
				tie(firstVx,firstVy) = windowToViewport(windowSidePair[i].first.getX(), windowSidePair[i].first.getY(),wxl,wxr,wyb,wyt,vxl,vxr,vyb,vyt);
				
				tie(secondVx, secondVy) = windowToViewport(windowSidePair[i].second.getX(), windowSidePair[i].second.getY(), wxl, wxr, wyb, wyt, vxl, vxr, vyb, vyt);
				point viewP0(firstVx,firstVy), viewP1(secondVx,secondVy);

				//cout << "--after WtoV"<< endl << setw(6) << "first" << setw(4) << firstVx << setw(4) << firstVy<< endl << setw(6) << "second" << setw(4) << secondVx << setw(4) << secondVy << endl;
				drawLine(viewP0, viewP1);
			}
			drawBorder(vxl, vxr, vyb, vyt);
			drawAllPoint();
			system("pause");
		}
		else if (words[0] == "clearData")
		{
			cout << "--clear data--" << endl;
			pointList.clear();
			windowSidePair.clear();

		}
		else if (words[0] == "clearScreen")
		{
			cout << "--clear screen--" << endl;
			pointList.clear();
			drawAllPoint();


		}
		else if (words[0] == "reset")
		{
			cout << "--reset--" << endl;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					transformationMatrix[i][j] = defaultMatrix[i][j];
					angleTransformationMatrix[i][j] = defaultMatrix[i][j];
					triangleMatrix[i][j] = triangleDefaultMatrix[i][j];
				}
				for (int j = 0; j < 4; j++)
				{
					squareMatrix[i][j] = squareDefaultMatrix[i][j];
				}
			}
			
		

		}
		else if (words[0] == "end")
		{
			cout << "--end--" << endl;
			quit();
		}
		else  // "NULL" or #......
		{
			cout << "--skip--" << endl;

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
	cout << "file name:" << fileName << endl;
	string lineInFile;

	inputFile.open(fileName);
	if (!inputFile.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}
	while (getline(inputFile, lineInFile)) {
		cout << lineInFile << endl;
		modeSwitch(lineInFile);
	}
	inputFile.close();
	glFlush();
}





void recover() {
	list<point> ::iterator pointIterator;
	for (pointIterator = pointListBackUp.begin(); pointIterator != pointListBackUp.end(); pointIterator++) {
		pointList.push_back(point(pointIterator->getX(), pointIterator->getY()));
	}
	pointListBackUp.clear();
	drawAllPoint();
}
void clear() {
	list<point> ::iterator pointIterator;
	for (pointIterator = pointList.begin(); pointIterator != pointList.end(); pointIterator++) {
		pointListBackUp.push_back(point(pointIterator->getX(), pointIterator->getY()));
	}
	pointList.clear();
	drawAllPoint();

}


void mouse(int button, int state, int x, int y) {
	switch (mode)
	{
	case 1:   //point
		if(state== GLUT_UP)
		pointList.push_back(point(x,y));
		break;
	case 2:  //line
		if (state == GLUT_UP)
		{
			lineCounter += 1;
			if ((lineCounter % 2) != 0 && state == GLUT_UP)
			{
				lineTemp.setX(x);
				lineTemp.setY(y);
			}
			else if ((lineCounter % 2) == 0 && state == GLUT_UP)
			{
				//cout << lineTemp.getX() << " " << lineTemp.getY() << " " << x << " " << y << endl;   //debug
				drawLine(lineTemp, point(x, y));
			}
		}
		//cout << lineCounter<<" " <<state<< endl;
		
		break;
	case 3:  //polygon
		if (state ==GLUT_UP)
		{
			if (button==GLUT_LEFT_BUTTON)
			{
				if (polygontemp.getX()==NULL &&polygontemp.getY()==NULL)
				{
					polygonSrc.setX(x);
					polygonSrc.setY(y);
					polygontemp.setX(x);
					polygontemp.setY(y);
				}
				else
				{
					drawLine(polygontemp, point(x, y));
					polygontemp.setX(x);
					polygontemp.setY(y);
				}
			}
			else if (button==GLUT_RIGHT_BUTTON)
			{
				drawLine(polygontemp, polygonSrc);
				polygontemp.setX(NULL);
				polygontemp.setY(NULL);

			}
		}
		break;
	case 4:  //circle
		if (state==GLUT_DOWN)
		{
			circleTemp.setX(x);
			circleTemp.setY(y);
		}
		else if (state == GLUT_UP)
		{
			//cout << lineTemp.getX() << " " << lineTemp.getY() << " " << x << " " << y << endl;
			drawCircle(circleTemp, point(x, y));
		}
		break;
	default:
		break;
	}
	//point temp=point(x ,y);
	//if (state == GLUT_DOWN) {
	//	pointList.push_back(temp);
	//}
	drawAllPoint();

	//if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) drawSquare(x, y);
}

void keyBoard(unsigned char key, int x, int y) {
	//cout << key <<" "<<x<<" "<<y << endl; //debug
	switch (key)
	{
		case 'd': //point
			mode = 1;
			break;
		case 'l': //line
			mode = 2;
			break;
		case 'p': //polygon
			mode = 3;
			break;
		case 'o': //circle
			mode = 4;
			break;
		case 'c': //clear
			clear();
			break;
		case 'r': //recover
			recover();
			break;
		case 'q': //quit
			quit();

			break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	system("pause");
	glutInit(&argc, argv);
	fileName = argv[1];
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(1500, 1000);
	glutInitWindowPosition(0, 0);
	gluOrtho2D(0, 1500, 0, 1000);
	glutCreateWindow("Your First GLUT  Window!");
	//drawCircle(point(250, 250), point(250,200)); //debug
	//drawLine(point(0, 500), point(250,50));  //debug
	//drawLine(point(0, 0), point(11, 22));
	//drawLine(point(0, 0), point(22, 11));
	//drawLine(point(50, 50), point(11, 33));
	//drawLine(point(50, 50), point(33, 11));
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyBoard);
	gluOrtho2D(0, 1500, 0, 1000);
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
