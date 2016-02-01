//UVa1606
//两亲性分子
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define maxn (1000+10)
typedef struct Point
{
	int x, y;
	int r;//区分黑白
	double rad;//极角
	bool operator < (const Point &a) const
	{
		return rad < a.rad;
	}
}Point;

int Cross(Point a, Point b)
{
	return (a.x * b.y - a.y * b.x) >= 0;
}

int main()
{
	int n;
	while(cin>>n && n)
	{
		Point point[maxn];//输入的绝对坐标
		for(int i=0; i<n; i++)
		{
			cin>> point[i].x >> point[i].y >> point[i].r;
		}
		if(n<=3)//点数小于3，直接得出结论，不用计算
		{
			cout<<n<<endl;
			continue;
		}

		Point tpoint[maxn];//相对坐标
		int cnt;
		int ans = 0;
		for(int basicpoint=0; basicpoint<n; basicpoint++)//枚举基准点
		{
			cnt = 0;//相对坐标点的新序号
			for(int i=0; i<n; i++)//计算所有点与基准点的相对坐标
			{
				if(i == basicpoint) continue;
				tpoint[cnt].x = point[i].x - point[basicpoint].x;//相对坐标
				tpoint[cnt].y = point[i].y - point[basicpoint].y;
				if(point[i].r)//技巧1：将黑色点以基准点为中心，进行中心对称
				{
					tpoint[cnt].x = -tpoint[cnt].x;
					tpoint[cnt].y = -tpoint[cnt].y;
				}
				tpoint[cnt].rad = atan2(tpoint[cnt].y, tpoint[cnt].x);//求极角
				cnt++;
			}
			sort(tpoint, tpoint+cnt);//极角排序，由小到大排序，几何意义是由x轴正半轴逆时针旋转
		
			int sum = 2;//计算点数累加，2是因为分隔线上的两点
			int L = 0, R = 0;
			while(L < cnt)//tpoint[L]是分隔线，tpoint[R]是扫描线
			{
				if(R == L)//空区域，暂时多计入一个点
				{
					R = (R + 1) % cnt;
					sum++;
				}
				while(L!=R && Cross(tpoint[L],tpoint[R]))//叉积小于0则两点的夹角大于180度，跳出循环
				{
					R = (R + 1) % cnt;//使R在0-cnt之间循环，省去R清零步骤
					sum++;
				}
				sum--;
				L++;//枚举新的起点
				ans = max(ans, sum);
			}//endwhile(L < cnt)
		}//endfor//枚举基准点
		cout<< ans <<endl;

	}//endwhile

    return 0;
}




