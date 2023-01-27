#pragma once
#include<stdio.h>
#include<math.h>
class coordinate
{
public:
    double x;
    double y;
    double z;
    //构造函数，未输入时赋值0
    coordinate();
    //构造函数进行赋值
    coordinate(double x1, double y1, double z1);
    //重构（），方便赋值
    coordinate operator()(double x1, double y1, double z1)
    {
        coordinate end;
        end.x = x1;
        end.y = y1;
        end.z = z1;
        return end;
    }
    //向量相加
    coordinate operator+(coordinate b)
    {
        coordinate box;
        box.x = this->x + b.x;
        box.y = this->y + b.y;
        box.z = this->z + b.z;
        return box;
    }
    //向量相减
    coordinate operator-(coordinate b)
    {
        coordinate box;
        box.x = this->x - b.x;
        box.y = this->y - b.y;
        box.z = this->z - b.z;
        return box;
    }
    //向量倍数相乘
    coordinate operator*(double b)
    {
        coordinate box;
        box.x = this->x * b;
        box.y = this->y * b;
        box.z = this->z * b;
        return box;
    }
    //向量叉乘求法向量
    coordinate operator&(coordinate b)
    {
        coordinate c;
        c.x = this->y * b.z - this->z * b.y;
        c.y = this->z * b.x - this->x * b.z;
        c.z = this->x * b.y - this->y * b.x;
        return c;
    }
    //向量倍数相除法
    coordinate operator/(double b)
    {
        coordinate box;
        box.x = this->x / b;
        box.y = this->y / b;
        box.z = this->z / b;
        return box;
    }
    //向量叉乘，返回值
    double operator%(coordinate b)
    {
        double c;
        c = this->y * b.z - this->z * b.y + this->z * b.x - this->x * b.z + this->x * b.y - this->y * b.x;
        return c;
    }
    //向量点乘
    double operator*(coordinate b)
    {
        double end = 0;
        end = this->x * b.x + this->y * b.y + this->z * b.z;
        return end;
    }
    //向量模
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
void PutCD(coordinate box);//打印坐标x，y，z