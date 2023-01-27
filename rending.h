#pragma once
#include<easyx.h>
#include"datalink.h"
double Cos(coordinate a, coordinate b);
double Sin(coordinate a, coordinate b);
double Tan(coordinate a, coordinate b);
TriFLink* CreateTLink();
//点光源
class SUN
{
public:
	coordinate locat;
	int intensity;
	COLORREF color;
	SUN();
	SUN(coordinate Locat, COLORREF Color = RGB(255, 255, 255), int Intensity = 100);
};
//光照方向
class Linght
{
public:
	coordinate direction;
	int intensity;
	COLORREF color;
	Linght();
	Linght(coordinate Direction, COLORREF Color = RGB(255, 255, 255), int Intensity = 100);
};
//摄像头
class Camera
{
public:
	coordinate locat;
	coordinate cameraLen;
	coordinate cameraUP;
	Camera()
	{
		locat = SetZB(0, 0, 0);
		cameraLen = SetZB(0, 0, -1);
		cameraUP = SetZB(0, 1, 0);
	}
	Camera(
		coordinate Locat,
		coordinate CameraLen,
		coordinate CameraUP=SetZB(0,1,0))
	{
		locat = Locat;
		cameraLen = CameraLen;
		cameraUP = CameraUP;
	}

};
//缩放一点投影到屏幕
coordinate zoomDot(Camera camera, coordinate dot);
//缩放一个三角面投影到屏幕
TriF zoom(Camera camera, TriF surface);
//绘制三角形（使用easyx）渲染单个三角面
#ifdef WINVER
void DrawTriangle(TriF a);
#endif
//计算渲染距离
TriFLink* CalculateDistance(Camera camera, TriFLink* p, TriFLink* link);
//从前往后依次渲染
void shader(Camera camera, TriFLink* link);
//由远及近依次渲染
void _shader(Camera camera, TriFLink* p);