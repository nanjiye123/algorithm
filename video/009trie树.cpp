//实现了字典树Trie树
//26叉树，只存储小写字母
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>

using namespace std;
const int num_chars = 26;

class Trie
{

public:
	Trie();
	~Trie();
	int TrieSearch(const char* word);
	int TrieInsert(const char* word);
	int TrieDelete(const char* word);

private:
	struct Trie_node
	{
		char* data;//若不为空，表示从root到此节点能构成一个单词
		Trie_node* branch[num_chars];//26叉树
		Trie_node();//构造函数
	};
	Trie_node* root;//根节点
};


Trie::Trie_node::Trie_node()//struct中的构造函数
{
	data = NULL;
	for(int i=0; i<num_chars; i++)
	{
		branch[i] = NULL;
	}
}

Trie::Trie():root(NULL) {}
Trie::~Trie() {}

int Trie::TrieSearch(const char* word)
{
	if(NULL == root)
	{
		cout << "字典树为空！" << endl;
		return -1;
	}
	int char_code;
	Trie_node *location = root;//从根节点开始查找位置
	while(location != NULL && *word != 0)
	{
		if(*word>='a' && *word<='z')
		{
			char_code = *word - 'a';
		}
		else
		{
			cout << "查找的单词不合法" << endl;
			return -1;//不合法的单词
		}

		if(location->branch[char_code] != NULL)
		{
			location = location->branch[char_code];//转入分支
			word++;
		}
		else
		{
			cout << "未找到！" << endl;
			return 0;
		}
		
	}//endwhile
	if(NULL == location->data)
	{
		cout << "未找到！" << endl;
		return 0;
	}
	else if(!strcmp(location->data, word))
	{
		cout << "已找到！" << endl;
		return 1;
	}
	else
	{
		cout << "未找到！" << endl;
		return 0;
	}
	return 0;
}

int Trie::TrieInsert(const char* word)
{
	if(NULL == root)//初始插入，根节点为空
	{
		root = new Trie_node;
	}

	int char_code;
	Trie_node *location = root;//从根节点开始查找插入位置
	while(location != NULL && *word != 0)
	{
		if(*word>='a' && *word<='z')
		{
			char_code = *word - 'a';
		}
		else
		{
			cout << "insert error" << endl;
			return -1;//不合法的单词
		}

		if(NULL == location->branch[char_code])//如果没有此分支
		{
			location->branch[char_code] = new Trie_node;
		}

		location = location->branch[char_code];//转入分支
		word++;
	}//endwhile
	if(location->data != NULL)
	{
		cout << "单词已存在" << endl;
		return -1;
	}
	else
	{
		location->data = new char[strlen(word)+1];
		strcpy(location->data, word);
	}
	return 0;
}

int Trie::TrieDelete(const char* word)
{
	if(NULL == root)
	{
		cout << "字典树为空！" << endl;
		return -1;
	}
	if(TrieSearch(word) != 1)
	{
		cout << "未找到目标！" << endl;
		return -1;
	}

	int char_code;
	Trie_node *location = root;//从根节点开始查找位置
	while(location != NULL && *word != 0)
	{
		char_code = *word - 'a';
		location = location->branch[char_code];//转入分支
		word++;
	}//endwhile
	if(!strcmp(location->data, word))
	{
		delete location->data;
		delete location->branch[char_code];
		location->data = NULL;
		cout << "删除成功！" << endl;
		return 1;
	}
	else
	{
		cout << "删除不成功！" << endl;
		return 0;
	}
	return 0;
}

int main()
{
	Trie t;
	t.TrieInsert("abdkj");
	t.TrieInsert("fhh");
	t.TrieInsert("qg");
	t.TrieInsert("kuyfsbghjj");
	t.TrieInsert("brwweh");

	t.TrieSearch("jkdls");
	t.TrieSearch("brwweh");
	t.TrieSearch("fdsd");
	t.TrieSearch("fhh");
	t.TrieSearch("aaaaaa");
	t.TrieSearch("kuyfsbghjj");

	t.TrieDelete("fhh");
	t.TrieSearch("fhh");
	return 0;
}


