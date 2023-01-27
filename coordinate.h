#pragma once
#include<stdio.h>
#include<math.h>
class coordinate
{
public:
    double x;
    double y;
    double z;
    //���캯����δ����ʱ��ֵ0
    coordinate();
    //���캯�����и�ֵ
    coordinate(double x1, double y1, double z1);
    //�ع����������㸳ֵ
    coordinate operator()(double x1, double y1, double z1)
    {
        coordinate end;
        end.x = x1;
        end.y = y1;
        end.z = z1;
        return end;
    }
    //�������
    coordinate operator+(coordinate b)
    {
        coordinate box;
        box.x = this->x + b.x;
        box.y = this->y + b.y;
        box.z = this->z + b.z;
        return box;
    }
    //�������
    coordinate operator-(coordinate b)
    {
        coordinate box;
        box.x = this->x - b.x;
        box.y = this->y - b.y;
        box.z = this->z - b.z;
        return box;
    }
    //�����������
    coordinate operator*(double b)
    {
        coordinate box;
        box.x = this->x * b;
        box.y = this->y * b;
        box.z = this->z * b;
        return box;
    }
    //�������������
    coordinate operator&(coordinate b)
    {
        coordinate c;
        c.x = this->y * b.z - this->z * b.y;
        c.y = this->z * b.x - this->x * b.z;
        c.z = this->x * b.y - this->y * b.x;
        return c;
    }
    //�������������
    coordinate operator/(double b)
    {
        coordinate box;
        box.x = this->x / b;
        box.y = this->y / b;
        box.z = this->z / b;
        return box;
    }
    //������ˣ�����ֵ
    double operator%(coordinate b)
    {
        double c;
        c = this->y * b.z - this->z * b.y + this->z * b.x - this->x * b.z + this->x * b.y - this->y * b.x;
        return c;
    }
    //�������
    double operator*(coordinate b)
    {
        double end = 0;
        end = this->x * b.x + this->y * b.y + this->z * b.z;
        return end;
    }
    //����ģ
    double operator++()
    {
        double h;
        h = this->x * this->x + this->y * this->y + this->z * this->z;
        if (h > 0)
        {
            h = sqrt(h);
        }
        else
        {
            h = 0;
        }
        return h;
    }
};
coordinate SetZB(double a, double b, double c);
double Cos(coordinate a, coordinate b);
double Sin(coordinate a, coordinate b);
double Tan(coordinate a, coordinate b);
void PutCD(coordinate box);//��ӡ����x��y��z