#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
int expand(char i_str[], char o_str[]);
int validrange(char c1, char c2);
int main()
{
	char i_str[50], o_str[50], i = 0;
	printf("enter the string to be expanded :");
	cin >> i_str;
	int len = strlen(i_str);
	while (i != len)
	{
		if (i_str[i] == '-')
		{
			if (!validrange(i_str[i - 1], i_str[i + 1]))
			{
				cout << "invalid string\n";
				system("pause");
				return 0;
			}
			else
			{
				i++;
			}

		}
		else
			i++;
	}

	expand(i_str, o_str);
	system("pause");
	return 0;
}

int validrange(char c1, char c2)
{
	if (('a' <= c1 && c1 <= 'z') && (c1 <= c2 && c2 <= 'z'))/* valid range in a-z */
		return 1;
	else if (('A' <= c1 && c1 <= 'Z') && (c1 <= c2 && c2 <= 'Z'))/* valid range in A-Z */
		return 1;
	else if (('0' <= c1 && c1 <= '9') && (c1 <= c2 && c2 <= '9'))/* valid range in 0-9 */
		return 1;
	else
		return 0;   /* not a valid range */
}
int expand(char i_str[], char o_str[])
{
	int i, j, c;
	i = j = 0;

	while ((c = i_str[i++]) != '\0')
	{
		if (!(c >= 'a'&& c <= 'z') && !(c >= 'A'&& c <= 'Z') && !(c == '-') && !(c>='0'&&c<='9'))

		{
			cout << "invalid string\n";
			system("pause");
			return 0;
		}

		if (i_str[i] == '-' && i_str[i + 1] >= c)
		{
			i++;
			while (c < i_str[i])
				o_str[j++] = c++;
		}
		else
			o_str[j++] = c;

		o_str[j] = '\0';

	}
	cout << "\nThe expanded string is : " << o_str << endl;
	getchar();
	return 0;
}