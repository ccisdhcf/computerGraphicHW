// ConsoleApplication1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <GL/glut.h>
#include <GL/gl.h>
#include<iostream>
#include <list>
#include "ConsoleApplication1.h"
#include<math.h>
using namespace std;


int forLoopOptimize = 1;
int mode = 0;
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
list<point> pointList;
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
void clear() {

}

void drawSquare(int x, int y) {
	glPointSize(3);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	glEnd();

}
void drawCycle(point centre, point cyclePoint) {  //超出邊界(?
	//float x_2 = pow((cyclePoint.getX() - centre.getX()), 2);
	//float y_2 = pow((cyclePoint.getY() - centre.getY()), 2);
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

void drawLine(point src,point des) {
	int dx = des.getX() - src.getX();

	if (dx < 0) {   // des.x < src.x then switch if needed?
		point temp = point(des.getX(), des.getY());
		des.setX(src.getX());
		des.setY(src.getY());
		src.setX(temp.getX());
		src.setY(temp.getY());
		cout << "switch   \n\n";
	}
	//switch end
	//cout << src.getX() << " " << src.getY() << " " << des.getX() << " " << des.getY() << "\n\n";  //debug
	int dy = des.getY() - src.getY();
	dx = des.getX() - src.getX();
	int x = src.getX();
	int y = src.getY();
	float slope = dy / (float)dx;
	cout<<slope<<" " << dx << " " << dy << " " << "\n";  //debug
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
		float d_init = dy + (float)dx / 2;
		int incE = dy;
		int incNE = dy - dx;
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
				y += 1;
				//cout << x <<" " << y << "\n";  //debug
				d += incNE;
			}
		}
	}

	else if (slope > 1) //slope>1 then switch (y,x)
	{
		float d_init = dx + (float)dy / 2;
		int incE = dx;
		int incNE = dx - dy;
		float d = d_init;
		
		pointList.push_back(point(x, y));
		while (y <= des.getY())
		{
			cout << d << "\n\n";  //debug
			if (d <= 0) {
				pointList.push_back(point(x, y));
				y += 1;
				//cout << x <<" " << y << "\n";  //debug
				d += incE;
			}
			else
			{
				pointList.push_back(point(x, y));
				x += 1;
				y += 1;
				//cout << x <<" " << y << "\n";  //debug
				d += incNE;
			}
		}
	}
	else if (slope<0 && slope>-1) {
		float d_init = -dy + (float)dx / 2;  //y*-1
		int incE = -dy ; //y*-1
		int incNE = -dy-dx;//y*-1
		float d = d_init;
		pointList.push_back(point(x, y));
		while (x <= des.getX())
		{
			
			//cout << d <<" "<<incE<<" "<<incNE << "\n\n";  //debug
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
				y -= 1;  //y*-1
				//cout << x <<" " << y << "\n";  //debug
				d += incNE;
			}
		}
	}
	else if (slope < -1) {
		float d_init = dx - (float)dy / 2;   //y*-1
		int incE = dx;
		int incNE = dx + dy;   //y*-1
		float d = d_init;

		pointList.push_back(point(x, y));
		while (y >= des.getY())   //<=  ->  >=
		{
			cout << d << "\n\n";  //debug
			if (d <= 0) {
				pointList.push_back(point(x, y));
				y -= 1;  //y*-1
				cout << x <<" " << y << "\n";  //debug
				d += incE;
			}
			else
			{
				pointList.push_back(point(x, y));
				x += 1;
				y -= 1;   //y*-1
				cout << x <<" " << y << "\n";  //debug
				d += incNE;
			}
		}
	}

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

void mouse(int bin, int state, int x, int y) {
	point temp=point(x ,y);
	if (state == GLUT_DOWN) {
		pointList.push_back(temp);
	}
	list<point> ::iterator point;
	for (point = pointList.begin(); point != pointList.end();point++) {
		drawSquare(point->getX(), point->getY());
	}
	glutSwapBuffers();

	//if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) drawSquare(x, y);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	gluOrtho2D(0, 500, 0, 500);
	glutCreateWindow("Your First GLUT  Window!");
	//drawCycle(point(250, 250), point(250,200)); //debug
	drawLine(point(0, 500), point(250,50));  //debug
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
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
