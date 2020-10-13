#include<iostream>
#include<string>
using namespace std;


string editpath(string str)
{
	int n = str.length();
	string temp = "\\";
	for (int i = n - 1;i > 0;i--)
	{
		if (str[i] == '\\')
		{
			
			str.insert(i, temp);
		}
	}
	return str;
}

//·şÎñ¶Ë
int main()
{

	string t = "lil\ei",t1="lilei";
	cout << "t:" << t.length() << endl;
	cout << "t1:" << t1.length() << endl;
	t = editpath(t);
	cout << t<<endl;

	while (true)
	{

	}
	return 0;
}
