//素数筛法
#include <iostream>
using namespace std;
const int MAX =  100;  
  
int Mark[MAX] = {0};  
int prime[MAX];  
    
//判断是否是一个素数  Mark 标记数组 index 素数个数  
int main()
{  
	int num_prime = 0;  
	for(int i = 2; i < MAX; i++)
	{  
		//已被标记 标记为1是非素数 
		if(Mark[i] == 1)
		{  
			continue;  
		}  
		else
		{  
			//否则得到一个素数  
			prime[ num_prime++ ] = i;  
			//标记该素数的倍数为非素数  
			for(int j = i*i; j < MAX; j += i)
			{  
				Mark[j] = 1;  
			}  
		}  
	}
	for(int i=0; i < num_prime; i++)
	{
		if(i%5 == 0) cout << endl;
		cout << ' ' << prime[i];
	}
	cout << endl;
	return 0;  
}




