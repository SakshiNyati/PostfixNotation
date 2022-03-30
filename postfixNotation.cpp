//Convert infix notation to postfix notation

using namespace std;
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#define MAX 40

class PostfixNotation
{
	char stk[MAX] = {};
	char postfix[40] = {};
	int top, postfixN;
	
	public:
		PostfixNotation()
		{
			top = -1;
			postfixN = 0;
		}
		void push(char);
		char pop();
		int ifOperand(char);
		void rightParenthesis();
		int operatorAlgo(char);
		void postfixAlgo(char*, int);
		void display();
};

void PostfixNotation :: push(char item)
{
	top++;
	stk[top] = item;
}

char PostfixNotation :: pop()
{
	char item = stk[top];
	top--;
	return item;
}

int PostfixNotation :: ifOperand(char item)
{
	for(int k=65; k<=89; k++)
		{
			if(item==k)										//check if operand from A-Z
			{
				return 1;
			}
		}
		
		for(int k=97; k<+122; k++)
		{
			if(item==k)										//check if operand from a-z
			{
				return 1;
			}
		}
		
		return 0;
}

void PostfixNotation :: rightParenthesis()
{
	while(stk[top]!='(')
	{
		postfix[postfixN] = pop();				//pop the top element of Stack and add it to the postfix
		postfixN++;								//increase number of elements in postfix
	}
	pop();										//pop the '(' from the stack
}

int PostfixNotation :: operatorAlgo(char op)
{
	char item;
	if(op=='^')
		push(op);								//push encountered operator onto the Stack
	
	else if(op=='*' || op=='/' || op=='%')
	{
		while(stk[top]=='*' || stk[top]=='/' || stk[top]=='%' || stk[top]=='^')   //while operator on top of Stack is higher or equal precedence
		{
			postfix[postfixN] = pop();				//pop the top element of Stack and add to the postfix
			postfixN++;										//increase number of elements in postfix
		}
		push(op);											//push encountered operator onto the Stack
		
	}
	
	else if(op=='+' || op=='-')
	{
		while(stk[top]!='(')						 //while operator on top of Stack is higher or equal precedence
		{
			postfix[postfixN] = pop();				//pop the top element of Stack and add to the postfix
			postfixN++;								//increase number of elements in postfix
		}
		push(op);									//push encountered operator onto the Stack
	}
	
	else 
	{
		cout<<"Invalid input: "<<op;
		return 1;
	}
}

void PostfixNotation :: postfixAlgo(char* eq,int n)
{
	int i=n-1,j=0,x=0;
	char k;
	while(i>=0)
	{
		eq[i+1] = eq[i];
		i--;
	}	
	eq[0] = '(';								//put equation in parenthesis
	eq[n+1] = ')';	
	n = n+2;
	
	while(eq[j]!='\0')
	{
		if(ifOperand(eq[j]))
		{
			postfix[postfixN] = eq[j];				//add operand to postfix
			postfixN++;								//increase number of elements in postfix
		}
		
		else if(eq[j]=='(')
			push(eq[j]);
		
		else if(eq[j]==')')
			rightParenthesis();
		
		else
		{
			x = operatorAlgo(eq[j]);
		}
		
		if(x==1)
			break;
			
		j++;
	}
	
	if(x==0)
		display();
}

void PostfixNotation :: display()
{
	int i=0;
	cout<<"\n\tPOSTFIX: ";
	while(postfix[i]!='\0')
	{
		cout<<postfix[i];
		i++;
	}
}

int main()
{
	PostfixNotation pn;
	char eq[40];
	int i=0,n=0;
	
	cout<<"\nEnter the equation: ";
	cin>>eq;
	
	while(eq[i]!='\0')
	{
		if(eq[i]=='[' || eq[i]=='{')
			eq[i]='(';
		
		else if(eq[i]==']' || eq[i]=='}')
			eq[i]=')';
		
		n++;
		i++;
	}
	
	pn.postfixAlgo(eq,n);
	
	return 0;
}

