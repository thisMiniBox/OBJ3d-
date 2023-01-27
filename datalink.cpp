#include"datalink.h"
CDLINK* CreateLink()
{
	CDLINK* p = new CDLINK;
	p->NEXT = NULL;
	p->data = SetZB(0, 0, 0);
	p->load = 0;
	return p;
}
CDLINK* CreateLink(coordinate a)
{
	CDLINK* p = new CDLINK;
	p->NEXT = NULL;
	p->data = a;
	p->load = 0;
	return p;
}
CDLINK* CreateLink(int LONG)
{
	if (LONG == 0)
		return NULL;
	LONG--;
	CDLINK* p = NULL;
	p = new CDLINK;
	p->NEXT = CreateLink(LONG);
	return p;
}
CDLINK* SearchLink(CDLINK* p, int num)
{
	if (num == 1 || p == NULL)
		return p;
	num--;
	p = p->NEXT;
	p = SearchLink(p, num);
	return p;
}
coordinate SearchLinkData(CDLINK* p, int num)
{
	p = SearchLink(p, num);
	if (p && p->load)
		return p->data;
	return SetZB(0, 0, 0);
}
void AddLink(CDLINK* p, coordinate data)
{
	while (p->NEXT)
	{
		p = p->NEXT;
	}
	p->NEXT = CreateLink();
	p->NEXT->data = data;
	p->NEXT->load = 1;
}
void FixLink(CDLINK* p, int num, coordinate data)
{
	p = SearchLink(p, num);
	p->data = data;
	p->load = 1;
}
void InsertNode(CDLINK* p, int num, coordinate data)
{
	p = SearchLink(p, num);
	CDLINK* m = CreateLink();
	m->NEXT = p->NEXT;
	p->NEXT = m;
	m->data = data;
	m->load = 1;
}
void DeleteNode(CDLINK* p, int num)
{
	CDLINK* m;
	p = SearchLink(p, num);
	if (p == NULL)
		return;
	if (p->NEXT == NULL)
	{
		delete p;
		return;
	}
	p->data = p->NEXT->data;
	p->load = p->NEXT->load;
	m = p->NEXT->NEXT;
	delete p->NEXT;
	p->NEXT = m;
}
void DeleteLink(CDLINK* p)
{
	if (p == NULL)
		return;
	CDLINK* m;
	m = p->NEXT;
	delete p;
	p = m;
	DeleteLink(p);
}
int LinkLong(CDLINK* p)
{
	int Long = 0;
	while (p)
	{
		p = p->NEXT;
		Long++;
	}
	return Long;
}
TriF::TriF()
{
	a(0, 0, 0);
	b(0, 0, 0);
	c(0, 0, 0);
	NVector(0, 0, 0);
	Color = RGB(0, 0, 0);
}
TriF::TriF(coordinate A,
	coordinate B,
	coordinate C)
{
	a = A;
	b = B;
	c = C;
	NVector = (b - a) & (c - b) * -1;
	Color = RGB(0, 0, 0);
}
TriF::TriF(coordinate A,
	coordinate B,
	coordinate C,
	COLORREF color)
{
	a = A;
	b = B;
	c = C;
	NVector = (b - a) & (c - b) * -1;
	Color = color;
}
void TriF::Setcolor(COLORREF color)
{
	Color = color;
}
void TriF::SetCD(coordinate A,
	coordinate B,
	coordinate C)
{
	a = A;
	b = B;
	c = C;
}
TriFLink* CreateTLink()
{
	TriFLink* p = new TriFLink;
	p->distance = -1;
	p->NEXT = NULL;
	p->data = TriF();
	p->load = 0;
	return p;
}
TriFLink* CreateLink(TriF a)
{
	TriFLink* p = new TriFLink;
	p->distance = -1;
	p->NEXT = NULL;
	p->data = a;
	p->load = 0;
	return p;
}
TriFLink* CreateTLink(int LONG)
{
	if (LONG == 0)
		return NULL;
	LONG--;
	TriFLink* p = NULL;
	p = new TriFLink;
	p->distance = -1;
	p->load = 0;
	p->NEXT = CreateTLink(LONG);
	return p;
}
TriFLink* SearchTLink(TriFLink* p, int num)
{
	while (1)
	{
		if (num == 1 || p == NULL)
			return p;
		num--;
		p = p->NEXT;
	}
}
TriF SearchTLinkData(TriFLink* p, int num)
{
	p = SearchTLink(p, num);
	if (p && p->load)
		return p->data;
	return TriF();
}
void AddTNode(TriFLink* p, TriF data)
{
	while (p->NEXT)
	{
		p = p->NEXT;
	}
	p->NEXT = CreateTLink();
	p = p->NEXT;
	p->data = data;
	p->load = 1;
}
TriFLink* HAddTNode(TriFLink* p, TriF data)
{
	TriFLink* m = CreateTLink();
	m->NEXT = p;
	FixTLink(m, 1, data);
	return m;
}
void InsertTNode(TriFLink* p, int num, TriF data)
{
	p = SearchTLink(p, num);
	TriFLink* m = CreateTLink();
	m->NEXT = p->NEXT;
	p->NEXT = m;
	m->data = data;
	m->load = 1;
}
void DeleteTNode(TriFLink* p, int num)
{
	TriFLink* m;
	p = SearchTLink(p, num);
	if (p->NEXT == NULL)
	{
		delete p;
		return;
	}
	p->data = p->NEXT->data;
	m = p->NEXT->NEXT;
	delete p->NEXT;
	p->NEXT = m;
}
void FixTLink(TriFLink* p, int num, TriF data)
{
	p = SearchTLink(p, num);
	p->data = data;
	p->load = 1;
}
void DeleteTLink(TriFLink* p)
{
	while (1)
	{
		if (p == NULL)
			return;
		TriFLink* m;
		m = p->NEXT;
		delete[] p;
		p = m;
	}

}
int TLinkLong(TriFLink* p)
{
	int Long = 0;
	while (p)
	{
		p = p->NEXT;
		Long++;
	}
	return Long;
}
void sequentialTLink(TriFLink* link, TriFLink* data)
{
	if (!link || data->distance == -1)
		return;
	while (1)
	{
		if (link->distance >= data->distance)
		{
			link = link->NEXT;
		}
		else
		{
			InsertTNode(link, 1, link->data);
			link->NEXT->distance = link->distance;
			FixTLink(link, 1, data->data);
			link->distance = data->distance; 
			return;
		}
	}

}
void  PadTLink(TriFLink* p, TriF data)
{
	while (p->load)
	{
		if (!p->NEXT)
		{
			AddTNode(p, data);
			return;
		}
		p = p->NEXT;
	}
	FixTLink(p, 1, data);
}