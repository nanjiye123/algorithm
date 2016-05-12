//杨辉三角
//多种方法选择 模板
//程序运行时间计算
//debug模板
#include <iostream>
#include <time.h>
#include <queue>
#define MAX_K 10000
#define DEBUG(comd, freq) if(IS_DEBUG) cout << "debug message:" << comd << ',' << freq << endl;
using namespace std;

//函数声明
int solve_one(int k, int i);
bool solve_two(int k, int y_nums[2][MAX_K]);
bool solve_three(int k, int y_nums[2][MAX_K]);

bool IS_DEBUG = true;
int solve_one(int k, int i)//递归求解方式
{//求第k层，第i个元素的值
	if( k<=0 || i<=0 || i>k )//三角形之外的空格
	{
		return 0;
	}
	else if( i==1 || i==k )//三角形边缘的格子
	{
		return 1;
	}
	return solve_one(k-1, i-1) + solve_one(k-1, i);
}

bool solve_two(int k, int y_nums[2][MAX_K])//从上层到下层求解
{
	if(k <= 0)
	{
		return false;
	}
	y_nums[1][1] = 1;//初始化第一行，只有一个元素
	for(int i=2; i<=k; i++)//从第2层到第k层循环
	{
		//i%2使得行号在0、1之间循环
		y_nums[ i%2 ][1] = 1;     //左边界
		y_nums[ i%2 ][i] = 1;     //右边界
		for(int j=2; j<=i-1; j++) //一列循环，从1到i
		{
			y_nums[ i%2 ][ j ] = y_nums[ (i-1)%2 ][ j ] + y_nums[ (i-1)%2 ][ j-1 ];
			//i%2表示当前行，(i-1)%2表示上一行
		}
	}
	return true;
}

typedef struct event
{
	int level, position;//行号和列号
}event;

bool solve_three(int k, int y_nums[2][MAX_K])//队列求解杨辉三角
{
	if(k <= 0)
	{
		return false;
	}

	queue<event> temp_queue;
	event e1, e2;
	int level, position;
	e1.level = 1; e1.position = 1;//第一行初始化
	temp_queue.push(e1);//第一行入队
	while( !temp_queue.empty() )//直到队列为空
	{
		e1 = temp_queue.front();//读队首事件
		level = e1.level; position = e1.position;

		//解决队首事件
		if(position==1 || position==level) //该行第1个元素和最后一个元素固定为1
		{
			y_nums[level%2][position] = 1;
		}
		else
		{
			y_nums[level%2][position] = y_nums[(level-1)%2][position-1] + y_nums[(level-1)%2][position];
		}

		//下一个事件
		if(level != k)//如果有下一层的事件
		{
			e2.level = level + 1;
			e2.position = position;
			temp_queue.push(e2);//入队
			if(position == level)//该层最后一个元素
			{
				e2.position = position + 1;
				temp_queue.push(e2);
			}
		}
		//关闭当前事件
		temp_queue.pop();
	}//end while
	return true;
}

int main()
{//打印第k层杨辉三角
	int k, begin;
	int chosen;
	int y_nums[2][MAX_K];
	cout << "请输入方法序号：";
	cin >> chosen;
	cout << "请输入要计算的第几层：";
	while( cin >> k )
	{
		if( k > MAX_K )
		{
			cout << "超出范围，请重新输入层数：";
			continue;
		}
		begin = clock();
		switch(chosen)
		{
		case 1: //方法1==============================
			//此种方法中下一层是这层运行时间的两倍
			//杨辉三角从下层到上层求解
			//时间复杂度高，不可用的方法
			cout << "method 1: ";
			for(int i=1; i<=k; i++)//列号循环
			{
				cout << solve_one(k, i) << " ";//打印第k层
			}
			cout << endl;
			break;

		case 2: //方法2==============================
			//杨辉三角从上层到下层求解
			//利用一个存储数组，运行时间为0ms，可用的方法
			cout << "method 2: ";
			solve_two(k, y_nums);
			for(int i=1; i<=k; i++)
			{
				cout << y_nums[k%2][i] << ' ';
			}
			cout << endl;
			break;

		case 3: //方法3==============================
			//队列解决杨辉三角问题
			cout << "method 3: ";
			solve_three(k, y_nums);
			for(int i=1; i<=k; i++)
			{
				cout << y_nums[k%2][i] << ' ';
			}
			cout << endl;
			break;

		default:
			break;
		}
		cout << (clock() - begin)/1000 << "ms" << endl;//计算时间
	}
	
	//DEBUG(k, "test1");
	return 0;
}



