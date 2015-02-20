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
#define INF 0x3f3f3f3f
#define mem0(a) memset(a,0,sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
#define lson k<<1, L, mid
#define rson k<<1|1, mid+1, R

//typedef long long LL;
const double eps = 1e-12;
const int MAXN = 100005;
const int MAXM = 500005;

double min(double a, double b) { return a < b ? a : b; }

struct Point
{
    double x;
    double y;
};
int numOfPoint;
Point points[MAXN], TempMerge[MAXN];
Point ansPoint1, ansPoint2;
double closest;

void initPoints()
{
    mem0(points); closest = INF;
    for(int i=0;i<numOfPoint;i++)
    {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
}

int cmp_X(Point A, Point B)
{
    if(A.x != B.x) return A.x < B.x;
    return A.y < B.y;
}

int cmp_Y(Point A, Point B)
{
    if(A.y != B.y) return A.y < B.y;
    return A.x < B.x;
}
#define distance(A, B) sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y))
//double distance(Point &A, Point &B)
//{
//    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
//}

double calculateTheClosest(int low, int high)
{
    for(int i=low;i<=high;i++)TempMerge[i-low] = points[i];
    sort(TempMerge, TempMerge+(high-low+1), cmp_Y);
    for(int i=0;i<high-low;i++)
    {
        for(int j=i+1;j<=i+6 && j<=high-low;j++)
        {
            double calc = distance(TempMerge[i], TempMerge[j]);
            if(calc < closest)
            {
                closest = calc;
                ansPoint1 = TempMerge[i];
                ansPoint2 = TempMerge[j];
            }
        }
    }
    return closest;
}

double findTheClosest(int left, int right)
{
    if(left>=right) return INF;
    int mid = (left+right)>>1;
    double leftAns = findTheClosest(left, mid);
    double rightAns = findTheClosest(mid+1, right);
    double ans = min(leftAns, rightAns);
    int low = left, high = mid+1;
    while(distance(points[low], points[mid])>ans)low++;
    while(high <= right && distance(points[high], points[mid])<=ans)high++;
    ans = min(ans, calculateTheClosest(low, high-1));
    return ans;
}

int main()
{
    while(scanf("%d", &numOfPoint) == 1 && numOfPoint)
    {
        initPoints();
        sort(points, points+numOfPoint, cmp_X);
        double ans = findTheClosest(0, numOfPoint-1);
        printf("%.2lf\n", ans/2);
        //printf("The Point(%.2lf, %.2lf) and Point(%.2lf, %.2lf) is %lf\n", ansPoint1.x,ansPoint1.y,ansPoint2.x,ansPoint2.y,ans);
    }
    return 0;
}
