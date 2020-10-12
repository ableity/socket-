#include<iostream>
#include<string>
using namespace std;


std::string& trim(std::string& s)
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
//·şÎñ¶Ë
int main()
{
	string n = "lilei";
	string m = "duhuimin                ";
	string t = n + m;
	cout << t<<"end"<<endl;
	trim(t);
	cout << t<<"end"<<endl;

	while (true)
	{

	}
	return 0;
}
