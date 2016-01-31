//UVa11054
#include <iostream>
using namespace std;

int main()
{
	int n;
	while(cin>>n && n)
	{
		long long a, sum=0, last=0;
		for(int i=0; i<n; i++)
		{
			cin>>a;//酒的量
			sum += last>0 ? last : -last;
			last = last + a;
		}
		cout<<sum<<endl;
	}

    return 0;
}




