#include<graphics.h>
#include<windows.h>
#include<shobjidl.h> 
#include<conio.h>
#include"rending.h"
#include"model.h"
#include"Definitions.h"
#include"LinkList.h"
int main()
{
	initgraph(WndW, WndH,1);
	setbkcolor(WHITE);
	cleardevice();
	coordinate
		sun(10, 10, -10),
		camera(0, 0, 200),
		cameraF(0, 0, -1),
		a(-1, -1, 1),
		b(1, -1, -1),
		c(1, -1, 1),
		d(1, 1, 1);
	TriFLink* DATA = CreateTLink();
	Linght sun1;
	Camera camera1(camera, cameraF);
	while (1)
	{
		system("cls");
		printf_s("这是一个3d查看器，可以通过按w a s d移动视角，通过i j k l旋转视角，空格上升，c下降，p重新选择模型\n此软件通过平面绘图绘制模型，也没有利用显卡渲染\n因此帧数较低，支持格式：obj模型\n");
		printf_s("请输入模型地址\n");
		std::string path;
		char val = 0;
		while ((val = getchar()) != '\n')
		{
			path += val;
		}
		FILE* FF = nullptr;
		fopen_s(&FF, path.c_str(), "r");
		if (!FF)continue;
		fclose(FF);
		Model J20(path.c_str());
		printf_s("正在对模型数据进行转码\n");
		for (int i = 1; i <= J20.meshes.Long(); i++)
		{
			Mesh TMesh = J20.meshes[i];
			printf_s("开始了第%d个叫做%s的模型组转码\n", i, TMesh.Name.c_str());
			for (int o = 0; o < TMesh.vertices.size(); o += 3)
			{
				Vertex Vertex1 = TMesh.vertices[o];
				Vertex Vertex2 = TMesh.vertices[o + 1];
				Vertex Vertex3 = TMesh.vertices[o + 2];
				TriF T = TriF(
					SetZB(Vertex1.Position.x, Vertex1.Position.y, Vertex1.Position.z),
					SetZB(Vertex2.Position.x, Vertex2.Position.y, Vertex2.Position.z),
					SetZB(Vertex3.Position.x, Vertex3.Position.y, Vertex3.Position.z),
					RGB(150, 140, 150));
				T.NVector = SetZB(Vertex1.Normal.x, Vertex1.Normal.y, Vertex1.Normal.z);
				InsertTNode(DATA, 1, T);
			}
		}
		float V = 10;
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO bInfo;
		GetConsoleScreenBufferInfo(hOut, &bInfo);
		printf_s("\n\n");
		_shader(camera1, DATA);
		ExMessage msg;
		clock_t start, ends;
		start = clock();
		ends = 0;
		short zheng = 0;
		time_t tm = time(NULL);
		while (1)
		{
			start = clock();
			if (tm != time(NULL))
			{
				SetConsoleCursorPosition(hOut, bInfo.dwCursorPosition);
				tm = time(NULL);
				printf_s("帧数为%d\n\n", zheng);
				zheng = 0;
			}
			peekmessage(&msg);
			BeginBatchDraw();
			switch (msg.message)
			{
			case WM_CHAR:
				if (msg.ch == 'W' || msg.ch == 'w')
				{
					camera1.locat = camera1.locat + ((camera1.cameraLen * V) * ((start - ends) / 1000.0));
				}
				else if (msg.ch == 'S' || msg.ch == 's')
				{
					camera1.locat = camera1.locat - ((camera1.cameraLen * V) * ((start - ends) / 1000.0));
				}
				else if (msg.ch == 'a' || msg.ch == 'A')
				{
					camera1.locat = camera1.locat - (((camera1.cameraLen & camera1.cameraUP) * V) * ((start - ends) / 1000.0));
				}
				else if (msg.ch == 'd' || msg.ch == 'D')
				{
					camera1.locat = camera1.locat + (((camera1.cameraLen & camera1.cameraUP) * V) * ((start - ends) / 1000.0));
				}
				else if (msg.ch == ' ')
				{
					camera1.locat.y += V * ((start - ends) / 1000.0);
				}
				else if (msg.ch == 'c')
				{
					camera1.locat.y--;
				}
				else if (msg.ch == 'i' && Sin(camera1.cameraLen, camera1.cameraUP) > sin(PI * 3 / 360) || msg.ch == 'i' && Cos(camera1.cameraLen, camera1.cameraUP) < 0)
				{
					double tx = sqrt(camera1.cameraLen.z * camera1.cameraLen.z + camera1.cameraLen.x * camera1.cameraLen.x);
					double ty = camera1.cameraLen.y;
					camera1.cameraLen.y = -tx * sin(-PI / 180) + ty * cos(-PI / 180);
					tx = tx * cos(-PI / 180) + ty * sin(-PI / 180);
					camera1.cameraLen.x = tx * Cos(SetZB(1, 0, 0), SetZB(camera1.cameraLen.x, 0, camera1.cameraLen.z));
					camera1.cameraLen.z = tx * Cos(SetZB(0, 0, 1), SetZB(camera1.cameraLen.x, 0, camera1.cameraLen.z));
				}
				else if (msg.ch == 'k' && Sin(camera1.cameraLen, camera1.cameraUP) > sin(PI * 3 / 360) || msg.ch == 'k' && Cos(camera1.cameraLen, camera1.cameraUP) > 0)
				{
					double tx = sqrt(camera1.cameraLen.z * camera1.cameraLen.z + camera1.cameraLen.x * camera1.cameraLen.x);
					double ty = camera1.cameraLen.y;
					camera1.cameraLen.y = -tx * sin(PI / 180) + ty * cos(PI / 180);
					tx = tx * cos(PI / 180) + ty * sin(PI / 180);
					camera1.cameraLen.x = tx * Cos(SetZB(1, 0, 0), SetZB(camera1.cameraLen.x, 0, camera1.cameraLen.z));
					camera1.cameraLen.z = tx * Cos(SetZB(0, 0, 1), SetZB(camera1.cameraLen.x, 0, camera1.cameraLen.z));
				}
				else if (msg.ch == 'j')
				{
					double tx = camera1.cameraLen.x;
					double ty = camera1.cameraLen.z;
					camera1.cameraLen.x = tx * cos(PI / 180) + ty * sin(PI / 180);
					camera1.cameraLen.z = -tx * sin(PI / 180) + ty * cos(PI / 180);
				}
				else if (msg.ch == 'l')
				{
					double tx = camera1.cameraLen.x;
					double ty = camera1.cameraLen.z;
					camera1.cameraLen.x = tx * cos(PI / -180) + ty * sin(PI / -180);
					camera1.cameraLen.z = -tx * sin(PI / -180) + ty * cos(PI / -180);
				}
				_shader(camera1, DATA);
				flushmessage();
				ends = start;
				zheng++;
				break;
			case WM_MOUSELAST:
				break;
			default:
				break;
			}
			if (msg.ch == 'p')break;
			FlushBatchDraw();
		}
		EndBatchDraw();
	}
	return 0;
}