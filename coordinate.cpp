#include"coordinate.h"

coordinate::coordinate()
{
    x = 0;
    y = 0;
    z = 0;
}
coordinate::coordinate(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;
}
coordinate SetZB(double a, double b, double c)
{
    coordinate d;
    d.x = a;
    d.y = b;
    d.z = c;
    return d;
}
void PutCD(coordinate box)//´òÓ¡×ø±êx£¬y£¬z
{
    printf("%f,%f,%f\n", box.x, box.y, box.z);
}
double Cos(coordinate a, coordinate b)
{
    double ans = a * b / ++a / ++b;
    return ans;
}
double Sin(coordinate a, coordinate b)
{
    double ans = sqrt(1 - (Cos(a, b) * Cos(a, b)));
    return ans;
}
double Tan(coordinate a, coordinate b)
{
    double ans = Sin(a, b) / Cos(a, b);
    return ans;
}