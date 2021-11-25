﻿// ConsoleApplication1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <GL/glut.h>
#include <GL/gl.h>
#include<iostream>
#include <list>
#include "ConsoleApplication1.h"
#include<math.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>     
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
ifstream inputFile;

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
static float matrix[3][3] = { 1.0, 0.0, 0.0,
							  0.0, 1.0, 0.0,
							  0.0, 0.0, 1.0 };

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
	glFlush();
}
void quit() {
	exit(1);
}

void drawSquare(int x, int y) {
	glPointSize(3);
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
void circle1to8(point centre, point p_0) {
	point p_1 = point(p_0.getY(), p_0.getX());
	point p_2 = point(p_0.getY(), (-1)*p_0.getX());
	point p_3 = point(p_0.getX(), (-1)*p_0.getY());
	point p_4 = point((-1)*p_0.getX(), (-1)*p_0.getY());
	point p_5 = point((-1)*p_0.getY(), (-1)*p_0.getX());
	point p_6 = point((-1)*p_0.getY(), p_0.getX());
	point p_7 = point((-1)*p_0.getX(), p_0.getY());

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
	while (circle.getX()<circle.getY())
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
void drawLine(point src,point des) {
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
	else if (0<slope && slope <= 1) { // 0<slope<=1
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
		float d_init = dy*direction + (float)dx / 2;
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
		float d_init = dx + (float)dy*direction / 2;
		int incE = dx;
		int incNE = dx - dy*direction;
		float d = d_init;
		
		pointList.push_back(point(x, y));
		while (y*direction <= des.getY()*direction)
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
	glutInit(&argc, argv);
	fileName = argv[1];
	cout << "file name:" << fileName << endl;

	inputFile.open(fileName);
	string line;

	if (!inputFile.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}
	while (getline(inputFile, line)) {
		cout << line << endl;
		char space_char = ' ';
		vector<string> words{};

		stringstream sstream(line);
		string word;
		while (getline(sstream, word, space_char)) {
			//word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
			words.push_back(word);
		}

		for (const auto& str : words) {
			cout << str << endl;
		}

		system("pause");

	}
	inputFile.close();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	gluOrtho2D(0, 500, 0, 500);
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
	gluOrtho2D(0, 500, 0, 500);
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
