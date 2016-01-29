//UVa11134
//传说中的车
//运行时间0.036
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int maxn = 5000 + 5;

struct node
{
    int xl,yl,xr,yr;
    bool isusedx, isusedy;//判断此矩形框是否用过
    int nodex, nodey;//所求点的位置坐标
    int id;//矩形框的读入顺序
}rook[maxn];//车子

bool cmp_x(node a, node b)
{
    return (a.xr < b.xr);//从小到大排序
}

bool cmp_y(node a, node b)
{
    return (a.yr < b.yr);//从小到大排序
}

bool cmp_id(node a, node b)
{
    return (a.id < b.id);//从小到大排序
}

bool solve_x(int n)
{
    //x方向上的
    sort(rook, rook+n, cmp_x);
    bool isOK = false;
    for(int i=1; i<=n; i++)//一格一格看  i是格子序号
    {
        isOK = false;
        for(int j=0; j<n; j++)//j是矩形框的序号
        {
            if(!rook[j].isusedx && rook[j].xl<=i )//&& rook[j].xr>=i)//矩形框左边界 小于 点坐标
            {
                if(rook[j].xr<i)break;
                rook[j].isusedx = true;
                rook[j].nodex = i;
                isOK = true;
                break;
            }
        }
        if(!isOK) break;
    }
    return isOK;
}

bool solve_y(int n)
{
    //y方向上的
    sort(rook, rook+n, cmp_y);
    bool isOK = false;
    for(int i=1; i<=n; i++)//一格一格看  i是格子序号
    {
        isOK = false;
        for(int j=0; j<n; j++)//j是矩形框的序号
        {
            if(!rook[j].isusedy && rook[j].yl<=i && rook[j].yr>=i)//矩形框左边界 小于 点坐标
            {
                //if(rook[j].yr<i)break;
                rook[j].isusedy = true;
                rook[j].nodey = i;
                isOK = true;
                break;
            }
        }
        if(!isOK) break;
    }
    return isOK;
}

int main()
{
    int n;
    while( scanf("%d", &n) == 1&&n)//??
    {
        for(int i=0; i<n; i++)
        {
            cin>>rook[i].xl>>rook[i].yl>>rook[i].xr>>rook[i].yr;
            rook[i].isusedx = rook[i].isusedy = false;
            rook[i].id = i;
        }

        if(solve_x(n) && solve_y(n))
        {
            sort(rook, rook+n, cmp_id);
            for(int i=0; i<n; i++)
            {
                cout<<rook[i].nodex<<' '<<rook[i].nodey<<endl;
            }
        }
        else
        {
            cout<<"IMPOSSIBLE"<<endl;
        }
    }
    system("pause");
    return 0;
}




