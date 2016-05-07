//最大连续和问题
//采用分治法，O(nlogn)
#include <iostream>
using namespace std;

int maxsum(int *A, int start, int end)
{//左闭右开区间为[start,end)
	if(end-start == 1)//只剩一个元素
	{
		return A[start];		
	}
	int mid = start + (end - start)/2;
	int maxs = max(maxsum(A,start,mid), maxsum(A,mid,end));//递归

	int v = 0, L = A[mid-1];//求前半段最大
	for(int i=mid-1; i>=start; i--)
	{
		L = max(L, v = v + A[i]);
	}

	int g = 0, R = A[mid];//求后半段最大
	for(int i=mid; i<end; i++)
	{
		R = max(R, g = g + A[i]);
	}
		
	return max(maxs, L+R);
}

int maxsum2(int *A, int start, int end)
{
	int last = 0, ans = 0;
	int num = end - start;//总数
	for(int i=0; i<num; i++)
	{
		last = max(0, last) + A[i];//前i-1项和小于0则取0
		ans  = max(ans, last);
	}
	return ans;	
}

int main()
{//结果为43,序列为21,8,-9,10,-1,3,6,5
	int A[13]={0,-3,6,8,-20,21,8,-9,10,-1,3,6,5};
	cout<<maxsum(A, 0, 13)<<endl;//计算区间[0,13)
	cout<<maxsum2(A, 0, 13)<<endl;
	return 0;	
}

