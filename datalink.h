#pragma once
#include<windows.h>
#include"coordinate.h"
//储存坐标的链表与相关能用到的函数
typedef struct _CDLINK
{
	bool load = 0;
	coordinate data;
	struct _CDLINK* NEXT = NULL;
}CDLINK;
//创建链表头部
CDLINK* CreateLink();
//创建链表（长度为LONG）
CDLINK* CreateLink(int LONG);
//查找链表结点（从一开始）
CDLINK* SearchLink(CDLINK* p, int num);
//查找链表数据
coordinate SearchLinkData(CDLINK* p, int num);
//链表增长结点（末尾插入）
void AddLink(CDLINK* p, coordinate data);
//链表插入结点（此结点后的数据）
void InsertNode(CDLINK* p, int num, coordinate data);
//链表删除结点(此结点）
void DeleteNode(CDLINK* p, int num);
//链表修改结点
void FixLink(CDLINK* p, int num, coordinate data);
//删除链表
void DeleteLink(CDLINK* p);
//查询链表长度
int LinkLong(CDLINK* p);
//三角面
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
//三角面链表
typedef struct _TriFLink
{
	float distance = -1;
	bool load = 0;
	TriF data;
	struct _TriFLink* NEXT = NULL;
}TriFLink;
//创建链表头部
TriFLink* CreateTLink();
//创建链表（长度为LONG）
TriFLink* CreateTLink(int LONG);
//查找链表结点（从一开始）
TriFLink* SearchTLink(TriFLink* p, int num);
//查找链表数据
TriF SearchTLinkData(TriFLink* p, int num);
//链表增长结点（末尾插入）
void AddTNode(TriFLink* p, TriF data);
//链表增长结点（前端插入）返回新的头指针
TriFLink* HAddTNode(TriFLink* p, TriF data);
//链表插入结点（此结点后的数据）
void InsertTNode(TriFLink* p, int num, TriF data);
//链表删除结点(此结点）
void DeleteTNode(TriFLink* p, int num);
//链表修改结点
void FixTLink(TriFLink* p, int num, TriF data);
//删除链表
void DeleteTLink(TriFLink* p);
//查询链表长度
int TLinkLong(TriFLink* p);
//以权重顺序插入链表
void sequentialTLink(TriFLink* p, TriFLink* data);
//填充链表（寻找无数据的空链表插入，没有则添加到尾部）
void PadTLink(TriFLink* p, TriF data);