//哈希表
//开放定址法 BKDR哈希函数 平方探测法
//最后加上了再哈希的方法
#include <iostream>
#include <string>
using namespace std;
#define ElementType string
#define minTableSize (10) //指针数组的最小尺寸

enum kindofhashNode{ Legitimate, Empty, Deleted };

typedef struct hashNode//定义哈希表中的一个节点
{
	ElementType *Element;
	enum kindofhashNode Info;
}hashNode, *pNode;//pNode只是pList的别名，程序中使用pList

typedef pNode pList;
typedef struct hashTable
{
	int tableSize;//指针数组的大小
	pList *List;//指针数组。指向hashNode结构的指针的指针
}hashTable, *phashTable;
//List是一个指针数组，数组的每一项都链接一个hashNode,入口地址相当于链表头节点

//函数声明
phashTable init(int tableSize);
bool prime(int tmp);
int nextPrime(int tableSize);
int Find(ElementType str, phashTable H);
void Insert(ElementType str, phashTable H);
int BKDRHash(const string &str);
void print(phashTable H);
void DestroyTable(phashTable H);
phashTable Rehash(phashTable H);

phashTable init(int tableSize)
{
	phashTable H;//创建一个哈希表指针

	if(tableSize < minTableSize)//数组中链表最小个数
	{
		cout << "table size is too small." << endl;
		return NULL;
	}

	H = (phashTable)malloc( sizeof(hashTable) );//分配表的指针空间
	if(NULL == H)
	{
		cout << "out of space" << endl;
		return NULL;	
	}

	H->tableSize = nextPrime(tableSize);//找到离用户输入的tableSize稍大的一个素数
	//分配指针数组空间，每个数组元素为一个指针，为数组整体分配空间
	H->List = (pList*)malloc( sizeof(pList) * H->tableSize );
	if(NULL == H->List)
	{
		cout << "out of space" << endl;
		return NULL;
	}

	//将数组空间分割成多个节点空间
	for(int i=0; i<H->tableSize; i++)
	{
		H->List[i] = (pList)malloc(sizeof(hashNode));
		H->List[i]->Info = Empty;
	}
	return H;		
}

bool prime(int tmp)//判断tmp是不是素数
{
	for(int i=2; i*i<tmp; i++)
	{
		if(0 == tmp % i)
		{
			return false;
		}
	}
	return true;
}

int nextPrime(int tableSize)
{//找到离用户输入的tableSize稍大的一个素数
	if(tableSize <= 2)
	{
		return 2;
	}
	else
	{
		while( !prime(tableSize) )
		{
			tableSize++;
		}
	}
	return tableSize;
}

int Find(ElementType str, phashTable H)//平方探测法，解决冲突问题
{
	int collisionNum = 0;//冲突次数
	int position = BKDRHash(str) % H->tableSize;//求hash位置
	while( H->List[position]->Info!=Empty && (*H->List[position]->Element)!=str )
	{//Empty证明没有下一个了，不等于str可能发生冲突下一个是
	 //若退出当前while，证明返回的位置就是当需要时，str将被插入的地方
		//以下是平方探测的快速方法，并非常用的平方
		position = position + 2 * ++collisionNum - 1;
		//平方解决函数F(i)=F(i-1)+2i-1
		if(position >= H->tableSize)
		{//新的定位越过数组，减去tableSize把它拉回到范围内
			position -= H->tableSize;
		}
	}
	return position;
}

void Insert(ElementType str, phashTable H)
{
	int position = Find(str, H);
	if(H->List[position]->Info != Legitimate)
	{//Legitimate合法的，意味着此位置有元素
		H->List[position]->Info = Legitimate;
		H->List[position]->Element = new string(str);
	}
}

int BKDRHash(const string &str)//哈希函数
{
	int hash = 0, seed = 131;
	for(int i=0; i<str.length(); i++)
	{
		hash = hash * seed + str[i];
	}
	return (hash & 0x7fffffff);//共7个f
}

void print(phashTable H)
{
	cout << "==========hash=============" << endl;
	for(int i=0; i<H->tableSize; i++)
	{
		pList L = H->List[i];
		if(L->Info != Legitimate)
		{
			continue;
		}
		cout << i << ':';
		cout << *L->Element << endl;
	}
	cout << "===========================" << endl;
}

void DestroyTable(phashTable H)
{
	for(int i=0; i<H->tableSize; i++)
	{
		if(Legitimate == H->List[i]->Info)
		{
			delete H->List[i]->Element;
			free(H->List[i]);
		}
		else
		{
			free(H->List[i]);
		}
	}
	free(H->List);
	free(H);
	cout << "destroy table success!" << endl;
}

phashTable Rehash(phashTable H)
{
	//保存旧的列表
	int oldsize = H->tableSize;
	pList* oldlist = H->List;

	//创建新的空列表
	H = init( 2 * oldsize );

	//遍历旧列表，重新插入到新的列表
	for(int i=0; i<oldsize; i++)
	{
		if(Legitimate == oldlist[i]->Info)
		{
			Insert(*oldlist[i]->Element, H);
			delete oldlist[i]->Element;
			free(oldlist[i]);
		}
		else
		{
			free(oldlist[i]);
		}
	}
	free(oldlist);
	cout << "rehash success!" << endl;
	return H;
}

int main()
{
	phashTable H;
	H = init(10000);//初始化指针数组长度为10000

	Insert("10", H);//插入一些字符
	Insert("20", H);
	Insert("30", H);
	Insert("40", H);
	Insert("50", H);
	Insert("60", H);
	Insert("abd", H);
	Insert("lot", H);
	Insert("AAA", H);
	print(H);

	//再散列的实现
	//需要将列表长度初始化为较小的数
	H = Rehash(H);
	print(H);

	DestroyTable(H);
	return 0;
}



