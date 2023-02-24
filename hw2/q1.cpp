#include <iostream>
#include <string>

using namespace std;

string to_upper(string line);


int main()
{
	string line;
	while (getline(cin,line))
		cout<<to_upper(line)<<endl;

	return 0;
}


string to_upper(string line)
{
	if (line.length() == 0)
		return "";
	
	return (char)toupper(line[0]) + to_upper(line.substr(1));
}
