#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define eps 1e-12
#define MAXN 55
#define INF 1e30
#define mem0(a) memset(a,0, sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
double MAX(double a, double b) {return a > b ? a : b;}
double MIN(double a, double b) {return a < b ? a : b;}
typedef long long LL;
/****************************************计算几何头文件**************************************************/
struct Point{
    double x,y;
    Point(double x=0, double y=0):x(x),y(y){}
};

struct Polygon
{
    Point p[MAXN];
    int Size;
};

struct Circle
{
    Point o;
    double r;
    Circle(){}
    Circle(Point _o, double _r):o(_o),r(_r){}
};

Point operator + (Point A, Point B) {return Point(A.x+B.x, A.y+B.y);}

Point operator - (Point A, Point B) {return Point(A.x-B.x, A.y-B.y);}

Point operator * (Point A, double p) {return Point(A.x*p, A.y*p);   }

Point operator / (Point A, double p) {return Point(A.x/p, A.y/p);   }

int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

bool operator == (const Point &A, const Point &B) {
    return dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0;
}

double Dot(Point A, Point B) { return A.x*B.x + A.y*B.y;}    //点积

double Length(Point A) { return sqrt(Dot(A,A));}             //向量长度

double Angle(Point A, Point B) {return acos(Dot(A,B) / Length(A) / Length(B));}//向量夹角

double cross(Point A, Point B) {return A.x*B.y - A.y*B.x;}

bool crossed(Point a, Point b, Point c, Point d)//线段ab和cd是否相交
{
    if(cross(a-c, d-c)*cross(b-c, d-c)<=0
       && cross(c-a, b-a)*cross(d-a, b-a)<=0)
    {
        return true;
    }
    return false;
}

bool isPointOnSegent(Point p, Point s, Point e)//判断点是否在线段se上
{
    double d = (p.x-s.x) * (e.x-p.x);
    double a = (p.y-s.y) / (p.x-s.x);
    double b = (e.y-p.y) / (e.x-p.x);
    if(dcmp(d)==1 && dcmp(a-b)==0)return true;
    return false;
}

int isPointInPolygon(Point p, Polygon poly)//判断点是否在多边形以内
{
    int w = 0;
    int n = poly.Size;
    for(int i=0;i<n;i++)
    {
        if(isPointOnSegent(p, poly.p[i], poly.p[(i+1)%n])) return 1;//点在边上
        int k = dcmp(cross(poly.p[(i+1)%n]-poly.p[i], p-poly.p[i]));
        int d1 = dcmp(poly.p[i].y - p.y);
        int d2 = dcmp(poly.p[(i+1)%n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) w++;
        if(k < 0 && d2 <= 0 && d1 > 0) w--;
    }
    if(w != 0) return 1;
    return 0;
}

/****************************************************************************************************/
