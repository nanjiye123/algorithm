//线性筛法求素数
/*时间复杂度O(n)
  功能：求1到MAX中的素数
  核心：只通过最小素因数筛掉这个数
  原理:
  1. 任何一个合数都可以表示成一个质数和一个数的乘积
  2. 假设A是一个合数，且A = x * y，这里x也是一个合数，那么有:
       A = x * y; (假设y是质数，x合数)
	   x = a * b; (假设a是质数，且a < x——>>a<y)
	   ->  A = a * b * y = a * Z (Z = b * y) 
	   
即一个合数(x)与一个质数(y)的乘积可以表示成一个更大的合数(Z)与一个更小的质数(a)的乘积
这也是理解代码中 if(i%primes[j] == 0)break;的关键
例如: 如果i = 8; 那么由于i%2 == 0; 因此对于i=8就只需要检查primes[1]=2即可。
      而对于大于primes[1]的质数，像3，有:
      8*3 = 2*4*3 = 12*2
	  也就是说24(8*3=24)并不需要在8时检查，在12时才检查
	    
*/
#include <iostream>
using namespace std;
const int MAX = 100;
int num_prime = 0;
int isNotPrime[MAX] = {1,1};
int prime[MAX] = {0};

int main()
{
	for(int i=2; i<MAX; i++)//遍历所有待求数
	{
		if(isNotPrime[i] == 0)//如果是素数
		{
			prime[num_prime++] = i;	
		}
		for(int j=0; j<num_prime && i*prime[j]<MAX; j++)//遍历所有已知素数
		{
			isNotPrime[i * prime[j]] = 1;//(i*prime[j])是需要判断的数
			if((i % prime[j]) == 0)//能整除
				break;
		}
	}
	for(int i=0; i<num_prime; i++)//打印
	{
		if(i%5 == 0) cout << endl;
		cout << " " << prime[i];
	}
	cout << endl;
	return 0;
}
