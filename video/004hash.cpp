//字符串的hash函数

#include <iostream>
using namespace std;

int32_t BKDRHash(const string &str)
{
	int32_t hash = 0, seed = 131;//seed是种子
	for(uint32_t i=0; i<str.length(); i++)
	{
		hash = hash * seed + str[i];	
		//将2进制映射到131进制
	}
	return (hash & 0x7fffffff);//去掉最高位的1
}

int32_t APHash(const string &str)
{
	int32_t hash = 0;
	for(uint32_t i=0; i<str.length(); i++)
	{
		if(i % 2)//奇数位
		{
			hash ^= ~((hash << 11) ^ (str[i]) ^ (hash >> 5));//异或
		}
		else//偶数位
		{
			hash ^= ((hash << 7) ^ (str[i]) ^ (hash >> 3));	
		}
	}
	return (hash & 0x7ffff);
}

int main()
{
	cout << "AOA:" << BKDRHash("AOA") << endl;
	cout << "xiaoxiang:" << BKDRHash("xiaoxiang") << endl;
	cout << "XD:" << APHash("XD") << endl;
	cout << "HH:" << APHash("HH") << endl;


	return 0;	
}


