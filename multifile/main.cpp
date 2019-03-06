#include<iostream>
#include<string>
#include<stack>
using namespace std;
double division(double, double);
double addition(double, double);
double subtraction(double, double);
double multiplication(double, double);
bool balancingParanthesis(string exp)
{
	stack<char> s_balancing;
	char ch;
	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
		{
			s_balancing.push(exp[i]);
			continue;
		}
		

		switch (exp[i])
		{
		case ')':

			ch = s_balancing.top();
			s_balancing.pop();
			if (ch == '{' || ch == '[')
				return false;
			break;

		case '}':

			ch = s_balancing.top();
			s_balancing.pop();
			if (ch == '(' || ch == '[')
				return false;
			break;

		case ']':

			ch = s_balancing.top();
			s_balancing.pop();
			if (ch == '(' || ch == '{')
				return false;
			break;
		}
	}
	return (s_balancing.empty());
}

int postfixEvaluation(string str) {
	stack<double> s_eval;
	double left, right;
	int i = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]))
		{
			double a = (double)str[i];
			s_eval.push(a - 48);
		}
		else
		{
			if (str[i] == '*') {
				right = s_eval.top();
				s_eval.pop();
				left = s_eval.top();
				s_eval.pop();
				double res = multiplication(right, left);
				s_eval.push(res);
			}
			if (str[i] == '/') {
				left = s_eval.top();
				s_eval.pop();
				right = s_eval.top();
				s_eval.pop();
				double res = division(right, left);
				s_eval.push(res);
			}
			if (str[i] == '+') {
				right = s_eval.top();
				s_eval.pop();
				left = s_eval.top();
				s_eval.pop();
				double s = addition(right, left);
				s_eval.push(s);
			}
			if (str[i] == '-') {
				left = s_eval.top();
				s_eval.pop();
				right = s_eval.top();
				s_eval.pop();
				double s = subtraction(right, left);
				s_eval.push(s);
			}
		}

	}
	cout << endl << "result is " << s_eval.top();
	return 0;
}

int priority(char ch)
{
	if (ch == '/' || ch == '*')
		return 2;
	else if (ch == '-' || ch == '+')
		return 1;
	else if (ch == ')') 
		return 6;
	else if (ch == ']')
		return 5;
	else if (ch == '}')
		return 4;
	else
		return -1;
}
int main()
{
	stack<char> s_main;
	string input, postfix_str, post_eval;
	cout << "enter an equation :";
	cin >> input;
	if (!balancingParanthesis(input))
	{
		cout << "Invalid Input" << endl;
		getchar();
		return 0;
	}
	else
	{
		
		int len = input.length();
		char c;
		for (int i = 0; i < len; i++)
		{
			char ch = input[i];
			if (ch >= '0'&&ch <= '9')
			{
				postfix_str+= ch;
		
			}
			else
			{
				if (s_main.empty())
				{
					s_main.push(ch);
					ch = s_main.top();
		
				}
				else

				{
					if (priority(ch) > priority(s_main.top()))
					{
						if (priority(ch) == 6)
						{
							while (s_main.top() != '(')
							{
								postfix_str+= s_main.top();
								
								s_main.pop();
	
							}
							s_main.pop();

						}
						else if (priority(ch) == 5)
						{
							while (s_main.top() != '[')
							{
								postfix_str += s_main.top();
								
								s_main.pop();

							}
							s_main.pop();

						}
						else if (priority(ch) == 4)
						{
							while (s_main.top() != '{')
							{
								postfix_str += s_main.top();
							
								s_main.pop();

							}
							s_main.pop();

						}
						else
							s_main.push(ch);
					}

					else
					{
						if (priority(ch) == -1)
						{
							s_main.push(ch);
						}
						else
						{
							while (!s_main.empty())
							{
								if (s_main.top() != '('&&s_main.top() != '['&&s_main.top() != '{')
								{
									postfix_str += s_main.top();
									s_main.pop();
								}
								else
									break;
							}
							
							s_main.push(ch);
							
						}
					}
				}
			}
		}
		while (!s_main.empty())
		{
			postfix_str += s_main.top();
			s_main.pop();
		}
		
	
		postfixEvaluation(postfix_str);
	}
	getchar();
	return 0;
}
