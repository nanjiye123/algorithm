//任意表达式求值，栈的应用
//包括浮点数
#include <iostream>
#include <string>
#include <stack>
using namespace std;

//函数声明
bool isadd_minus(char c);
bool ismul_div(char c);
string shorten(string mid);//中缀转成后缀
double calc(string sur);//计算后缀表达式


bool isadd_minus(char c)
{
	return ( c=='+' || c=='-');//判断c是不是加号减号
}

bool ismul_div(char c)
{
	return ( c=='*' || c=='/');//判断c是不是乘号除号
}

string shorten(string mid)//中缀转成后缀
{//时间复杂度O(N)
	string sur;//后缀表达式
	stack<char> s;

	for(int i=0; i<mid.size(); i++)//遍历mid中每一个字符
	{
		if( isdigit(mid[i]) || mid[i]=='.' )//========判断是数字或者是小数点
		{
			while( isdigit(mid[i]) || mid[i]=='.' )
			{
				sur += mid[i++];//写入后缀表达式
			}
			sur += '$';//每个数字以'$'结束
			i--;//i指向数字的最后一位
		}
		else if( isadd_minus(mid[i]) )//=========判断是不是加减号
		{
			while( s.size() && ( isadd_minus(s.top())||ismul_div(s.top()) ) )
			{//遇到相同或更高优先级，则出栈，但其本身元素入栈
				sur += s.top();
				s.pop();
			}
			s.push( mid[i] );//其本身元素入栈
		}
		else if( ismul_div(mid[i]) )//=========判断是不是乘除号
		{//遇到相同或更高优先级，则出栈，但其本身元素入栈
			while( s.size() && ismul_div(s.top()) )
			{
				sur += s.top();
				s.pop();
			}
			s.push( mid[i] );//其本身元素入栈
		}
		else if( mid[i] == ')' )//==========遇到右括号
		{
			while( s.top() != '(' )
			{
				sur += s.top();
				s.pop();
			}
			s.pop();//左括号出栈，但不写入输出的后缀表达式
		}
		else
		{
			s.push( mid[i] );//遇到左括号，压栈
		}
	}//endfor
	while( s.size() )//在数字都加入后缀表达式之后，栈中符号全部出栈
	{
		sur += s.top();
		s.pop();
	}

	return sur;//返回后缀表达式
}

double calc(string sur)//计算后缀表达式
{
	double result, num;
	string temp = "";//存放要还原的浮点数
	stack<double> numStack;

	for(int i=0; i<sur.size(); i++)
	{
		if( isdigit(sur[i]) || sur[i]=='.' )//是数字或小数点
		{
			while( isdigit(sur[i]) || sur[i]=='.' )
			{
				temp += sur[i++];
			}
			//i--;//不用写这个，因为数字结束后是'$'
			numStack.push( atof(temp.c_str()) );
			temp = "";
		}
		else//是四则运算符
		{
			switch(sur[i])
			{
				case '+':num=numStack.top(); numStack.pop(); num+=numStack.top();    numStack.pop(); numStack.push(num); break;
				case '-':num=numStack.top(); numStack.pop(); num=numStack.top()-num; numStack.pop(); numStack.push(num); break;
				case '*':num=numStack.top(); numStack.pop(); num*=numStack.top();    numStack.pop(); numStack.push(num); break;
				case '/':num=numStack.top(); numStack.pop(); num=numStack.top()/num; numStack.pop(); numStack.push(num); break;
				default: cerr << "result would be wrong!" << endl;
			}
		}
	}//endfor

	result = numStack.top();
	return result;
}

int main()
{
	string mid, sur;//中缀表达式，后缀表达式

	cout << "输入整数或小数：" << endl;
	cin >> mid;
	sur = shorten(mid);

	cout << "后缀表达式为：" << endl;
	cout << sur << endl;
	cout << "结果为：" << calc(sur) << endl;

	return 0;
}



