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
		if (s_balancing.empty())
			return true;

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
				double res = division(right,left);
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
	cout << endl<<"result is "<<s_eval.top();
	return 0;
}

int priority(char ch)
{
	if (ch == '/' || ch == '*')
		return 2;
	else if (ch == '-' || ch == '+')
		return 1;
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
			if (isdigit(input[i]))
			{
				postfix_str += input[i];
			}
			else if (input[i] == '(')
			{
				s_main.push(input[i]);
			}
			else if (input[i] == ')')
			{
				while (!s_main.empty() && s_main.top()!='(')
				{
					c = s_main.top();
					s_main.pop();
					postfix_str += c;
				}
				if (s_main.top() == '(') {
					c = s_main.top();
					s_main.top();
				}
			}
			else
			{
				while (!s_main.empty() && priority(input[i]) <= priority(s_main.top())) {
					c = s_main.top();
					s_main.pop();
					postfix_str += c;
				}
				s_main.push(input[i]);
			}
		}
		while (!s_main.empty()) {
			c = s_main.top();
			s_main.pop();
			postfix_str += c;
		}
		for (int i = 0; i < len; i++) {
			if (postfix_str[i] == '(') {
				continue;
			}
			post_eval += postfix_str[i];
		}
		postfixEvaluation(post_eval);
	}
	getchar();
	return 0;
}
