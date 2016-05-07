//哈希表示例
//分离链接哈希表 BKDR哈希函数
#include <iostream>
#include <string>
using namespace std;
#define ElementType string
#define minTableSize (10) //指针数组的最小尺寸

typedef struct hashNode//定义哈希表中的一个节点
{
	ElementType *Element;
	struct hashNode* Next;
}hashNode, *pNode;

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
int BKDRHash(const string &str);
pNode Find(ElementType str, phashTable H);
void Insert(ElementType str, phashTable H);
void print(phashTable H);
void Delete(ElementType str, phashTable H);
void DestroyTable(phashTable H);

int BKDRHash(const string &str)//哈希函数
{
	int hash = 0, seed = 131;
	for(int i=0; i<str.length(); i++)
	{
		hash = hash * seed + str[i];	
	}
	return (hash & 0x7ffffffff);
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
		if(NULL == H->List[i])
		{
			cout << "out of space" << endl;
		}
		else
		{
			H->List[i]->Next = NULL;
		}
	}
	return H;		
}

pNode Find(ElementType str, phashTable H)//查找元素是否在链表中
{
	pNode P;
	pList L;
	L = H->List[ BKDRHash(str) %  H->tableSize ];//求hash函数
	P = L->Next;
	while( P!=NULL && (*P->Element)!=str )//判断是否匹配
	{
		P = P->Next;
	}
	return P;
}

void Insert(ElementType str, phashTable H)
{
	pNode pos = Find(str, H);
	if(NULL == pos)//如果没找到
	{
		pNode newNode = (pNode)malloc( sizeof(hashNode) );
		if(NULL == newNode)
		{
			cout << "out of space" << endl;
			return;
		}
		else
		{
			pList L = H->List[ BKDRHash(str) %  H->tableSize ];
			newNode->Element = new string(str);//写入内容
			//cout << (*newNode->Element)<<endl;
			newNode->Next = L->Next;//在链表头后第一个位置插入
			L->Next = newNode;
		}//end newNode
	}//end pos
}

void print(phashTable H)
{
	cout << "======== hash ========" << endl;
	for(int i=0; i<H->tableSize; i++)
	{
		pList L = H->List[i];
		if(NULL == L->Next)
		{
			continue;
		}
		cout << i << ':';
		while(L->Next != NULL)
		{
			cout << *(L->Next->Element) << " -> ";
			L = L->Next;
		}
		cout << "end" << endl;
	}
	cout << "======================" << endl;
}

void Delete(ElementType str, phashTable H)
{
	pNode pos = Find(str, H);
	if(NULL == pos)//如果没找到
	{
		cout << "no find!" << endl;
		return;
	}
	else//找到，准备删除
	{
		pList L = H->List[ BKDRHash(str) %  H->tableSize ];
		for(pNode pre=L; pre->Next!=NULL; pre=pre->Next)
		{
			if(pre->Next == pos)
			{
				pre->Next = pos->Next;
				delete pos->Element;
				free(pos);
				cout << "delete success!" << endl;
				break;
			}
		}
	}
}

void DestroyTable(phashTable H)//销毁哈希表
{
	pList P, tmp;
	for(int i=0; i<H->tableSize; i++)
	{
		P = H->List[i];
		while(P->Next != NULL)
		{
			tmp = P->Next;
			if(tmp->Next != NULL) 
			{
				P->Next = tmp->Next;
			}
			else
			{
				P->Next = NULL;
			}
			delete tmp->Element;
			free(tmp);
		}
	}
	free(H->List);
	free(H);
	cout << "destroy table success!" << endl;
}

int main()//
{
	phashTable H;
	H = init(10000);//初始化指针数组长度为100000

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

	if(Find("30", H))//查找字符串
	{
		cout << "find!" << endl;
	}
	else
	{
		cout << "no find!" << endl;
	}

	Delete("lot", H);
	print(H);

	DestroyTable(H);

	return 0;
}



