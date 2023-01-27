#include"rending.h"
#include"Definitions.h"
#include"sort.h"
SUN::SUN()
{
	locat = SetZB(0, 0, 0);
	intensity = 100;
	color = RGB(255, 255, 255);
}
SUN::SUN(coordinate Locat, COLORREF Color, int Intensity)
{
	locat = Locat;
	intensity = Intensity;
	color = Color;
}
Linght::Linght()
{
	direction = SetZB(0, 0, 0);
	intensity = 100;
	color = RGB(255, 255, 255);
}
Linght::Linght(coordinate Direction, COLORREF Color, int Intensity)
{
	direction = Direction;
	intensity = Intensity;
	color = Color;
}
SUN setsun(
	coordinate locat,
	int intensity,
	COLORREF color)
{
	SUN Sun;
	Sun.locat = locat;
	Sun.intensity = intensity;
	Sun.color = color;
	return Sun;
}
Linght setlinght(
	coordinate direction,
	int intensity,
	COLORREF color)
{
	Linght Sun;
	Sun.direction = direction;
	Sun.intensity = intensity;
	Sun.color = color;
	return Sun;
}
coordinate zoomDot(Camera camera, coordinate dot)
{
	double distanse = (++(dot - camera.locat)) * (Cos((dot - camera.locat), camera.cameraLen));
	double x = (++(dot - camera.locat)) * (Cos((dot - camera.locat), camera.cameraLen & camera.cameraUP));
	double y = -(++(dot - camera.locat)) * (Cos((dot - camera.locat), (camera.cameraLen & camera.cameraUP)&camera.cameraLen));
	return SetZB(x * WndH / distanse + WndW / 2, y * WndH / distanse + WndH / 2, 0);
}
TriF zoom(Camera camera, TriF surface)
{
	surface.a = zoomDot(camera, surface.a);
	surface.b = zoomDot(camera, surface.b);
	surface.c = zoomDot(camera, surface.c);
	return surface;
}
void DrawTriangle(TriF a)
{
	POINT pts[] = { {a.a.x, a.a.y}, {a.b.x, a.b.y}, {a.c.x, a.c.y} };
	setfillcolor(a.Color);
	solidpolygon(pts, 3);
}
TriFLink* CalculateDistance(Camera camera, TriFLink* p, TriFLink* link)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo,b1;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	int num = 0,yes=0;
	printf_s("相机位置为%lf %lf %lf            \n", camera.locat.x, camera.locat.y, camera.locat.z);
	while (1)
	{
		if (num % 10000 == 0)
		{
			GetConsoleScreenBufferInfo(hOut, &b1);
			printf("已经判断%d个面了           \n",num);
			SetConsoleCursorPosition(hOut, b1.dwCursorPosition);
		}
		if (!p)
		{
			printf("判断了%d个面，%d个面进入了渲染队列          \n", num, yes);
			SetConsoleCursorPosition(hOut, bInfo.dwCursorPosition);
			return link;
		}
		p->distance = ++(((p->data.a + p->data.b + p->data.c) / 3) - camera.locat);
		coordinate T = (((p->data.a + p->data.b + p->data.c) / 3) - camera.locat);
		if (Cos(T , p->data.NVector) < 0)
		{
			if (Cos(T, camera.cameraLen) > cos(PI/3))
			{
				COLORREF TC = p->data.Color;
				p->data.Color = RGB((p->data.Color >> 0 & 0xff) * -Cos(T, p->data.NVector), (p->data.Color >> 8 & 0xff) * -Cos(T, p->data.NVector), (p->data.Color >> 16 & 0xff) * -Cos(T, p->data.NVector));
				sequentialTLink(link, p);
				p->data.Color = TC;
				yes++;
			}
		}
		num++;
		p = p->NEXT;
	}
}
void _shader(Camera camera, TriFLink* p)
{
	TriFLink* link = CreateTLink();
	FixTLink(link, 1, TriF(camera.locat, camera.locat, camera.locat, YELLOW));
	link = CalculateDistance(camera, p, link);
	cleardevice();
	shader(camera, link);
	DeleteTLink(link);
}
void shader(Camera camera, TriFLink* link)
{
	int num = 0;
	while (1)
	{
		if (!link)
		{
			return;
		}
		TriF z = zoom(camera, link->data);
		DrawTriangle(z);
		link = link->NEXT;
		num++;
	}

}