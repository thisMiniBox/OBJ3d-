#pragma once
#include<windows.h>
#include"coordinate.h"
//���������������������õ��ĺ���
typedef struct _CDLINK
{
	bool load = 0;
	coordinate data;
	struct _CDLINK* NEXT = NULL;
}CDLINK;
//��������ͷ��
CDLINK* CreateLink();
//������������ΪLONG��
CDLINK* CreateLink(int LONG);
//���������㣨��һ��ʼ��
CDLINK* SearchLink(CDLINK* p, int num);
//������������
coordinate SearchLinkData(CDLINK* p, int num);
//����������㣨ĩβ���룩
void AddLink(CDLINK* p, coordinate data);
//��������㣨�˽�������ݣ�
void InsertNode(CDLINK* p, int num, coordinate data);
//����ɾ�����(�˽�㣩
void DeleteNode(CDLINK* p, int num);
//�����޸Ľ��
void FixLink(CDLINK* p, int num, coordinate data);
//ɾ������
void DeleteLink(CDLINK* p);
//��ѯ������
int LinkLong(CDLINK* p);
//������
class TriF
{
public:
	coordinate a;
	coordinate b;
	coordinate c;
	coordinate NVector;
	COLORREF Color;
	TriF();
	TriF(coordinate A,
		coordinate B,
		coordinate C);
	TriF(coordinate A,
		coordinate B,
		coordinate C,
		COLORREF color);
	void Setcolor(COLORREF color);
	void SetCD(coordinate A,
		coordinate B,
		coordinate C);
	TriF operator()(coordinate A,
		coordinate B,
		coordinate C)
	{
		TriF end;
		end.a = A;
		end.b = B;
		end.c = C;
		return end;
	}
};
//����������
typedef struct _TriFLink
{
	float distance = -1;
	bool load = 0;
	TriF data;
	struct _TriFLink* NEXT = NULL;
}TriFLink;
//��������ͷ��
TriFLink* CreateTLink();
//������������ΪLONG��
TriFLink* CreateTLink(int LONG);
//���������㣨��һ��ʼ��
TriFLink* SearchTLink(TriFLink* p, int num);
//������������
TriF SearchTLinkData(TriFLink* p, int num);
//����������㣨ĩβ���룩
void AddTNode(TriFLink* p, TriF data);
//����������㣨ǰ�˲��룩�����µ�ͷָ��
TriFLink* HAddTNode(TriFLink* p, TriF data);
//��������㣨�˽�������ݣ�
void InsertTNode(TriFLink* p, int num, TriF data);
//����ɾ�����(�˽�㣩
void DeleteTNode(TriFLink* p, int num);
//�����޸Ľ��
void FixTLink(TriFLink* p, int num, TriF data);
//ɾ������
void DeleteTLink(TriFLink* p);
//��ѯ������
int TLinkLong(TriFLink* p);
//��Ȩ��˳���������
void sequentialTLink(TriFLink* p, TriFLink* data);
//�������Ѱ�������ݵĿ�������룬û������ӵ�β����
void PadTLink(TriFLink* p, TriF data);