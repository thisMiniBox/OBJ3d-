#pragma once
#include<easyx.h>
#include"datalink.h"
double Cos(coordinate a, coordinate b);
double Sin(coordinate a, coordinate b);
double Tan(coordinate a, coordinate b);
TriFLink* CreateTLink();
//���Դ
class SUN
{
public:
	coordinate locat;
	int intensity;
	COLORREF color;
	SUN();
	SUN(coordinate Locat, COLORREF Color = RGB(255, 255, 255), int Intensity = 100);
};
//���շ���
class Linght
{
public:
	coordinate direction;
	int intensity;
	COLORREF color;
	Linght();
	Linght(coordinate Direction, COLORREF Color = RGB(255, 255, 255), int Intensity = 100);
};
//����ͷ
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
//����һ��ͶӰ����Ļ
coordinate zoomDot(Camera camera, coordinate dot);
//����һ��������ͶӰ����Ļ
TriF zoom(Camera camera, TriF surface);
//���������Σ�ʹ��easyx����Ⱦ����������
#ifdef WINVER
void DrawTriangle(TriF a);
#endif
//������Ⱦ����
TriFLink* CalculateDistance(Camera camera, TriFLink* p, TriFLink* link);
//��ǰ����������Ⱦ
void shader(Camera camera, TriFLink* link);
//��Զ����������Ⱦ
void _shader(Camera camera, TriFLink* p);