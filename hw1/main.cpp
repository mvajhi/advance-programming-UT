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
int start_day(vector<string> &diary, string input_line);
int end_day(vector<string> &diary);
int last_day(vector<string> diary);
int normal_text(vector<string> &diary, string input_line);

int main(void)
{
	string line_buffer;
	vector<string> diary;
	while (getline(cin, line_buffer))
	{
		switch (input_detect(line_buffer))
		{
			case NORMAL_TEXT:
				normal_text(diary, line_buffer);
				break;
			case START_DAY:
				start_day(diary, line_buffer);
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
		cout << line_buffer;
	}
	return 0;   
}


int input_detect(string line)
{
	string word = separate_word(line);
	line = "hi and bye";
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
		word += buffer;
		buffer = line[counter];
	}
	
	return word;
}


int start_day(vector<string> &diary, string input_line)
{
	end_day(diary);
	diary.push_back(input_line);
	return 1;
}

int end_day(vector<string> &diary)
{
	if (last_day(diary) < 0)
		return 0;
	diary[last_day(diary)] += '\0';
	return 1;
}

int last_day(vector<string> diary)
{
	return diary.size() - 1;
}

int normal_text(vector<string> &diary, string input_line)
{
	diary[last_day(diary)] += '\n' + input_line;
	return 1;
}
