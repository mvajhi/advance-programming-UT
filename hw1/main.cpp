#include <iostream>
#include <vector>

#define NORMAL_TEXT 0
#define START_DAY 1
#define SHOW_DAY 2
#define SHOW_THE_LONGEST_DAY 3
#define SHOW_THE_BEST_DAY 4

using namespace std;

int input_detect(string line);
string separate_word(string line);

int main(void)
{
	string line_buffer;
	while (getline(cin, line_buffer))
	{
		switch (input_detect(line_buffer))
		{
			case NORMAL_TEXT:
				//TODO
				cout << "normal text\n";
				break;
			case START_DAY:
				//TODO
				cout << "start day\n";
				break;
			case SHOW_DAY:
				//TODO
				cout << "show day\n";
				break;
			case SHOW_THE_LONGEST_DAY:
				//TODO
				cout << "longest\n";
				break;
			case SHOW_THE_BEST_DAY:
				//TODO
				cout << "best\n";
				break;
			defult:
				cout << "some thing wrong " << __LINE__ << endl;
		}	
	}
	return 0;   
}


int input_detect(string line)
{
	string word = separate_word(line);
	if (word == "start_day")
		return START_DAY;
	else if (word == "show_day")
		return SHOW_DAY;
	else if (word == "show_the_longest_day")
		return SHOW_THE_LONGEST_DAY;
	else if (word == "show_the_best_day")
		return SHOW_THE_BEST_DAY;
	else
		return NORMAL_TEXT;
}


string separate_word(string line)
{
	char buffer;
	int counter = 0;
	string word;
	line += '\0';
	buffer = line[counter];
	while (buffer != ' ' && buffer != '\0')
	{
		counter++;
		cout << buffer << " " << counter << endl;
		word += buffer;
		buffer = line[counter];
	}
	
	return word;
}

