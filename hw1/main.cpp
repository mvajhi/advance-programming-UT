#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>

#define NORMAL_TEXT 0
#define START_DAY 1
#define SHOW_DAY 2
#define SHOW_THE_LONGEST_DAY 3
#define SHOW_THE_BEST_DAY 4
#define NOT_FOUND -1
#define OK 1
#define DEFAULT_SUMMERY_LENGHT 20
#define POSITIVE_WORD_FILE_ADDRESS "positive-words.txt"
#define START_DATE_IN_STRING 10

using namespace std;


int input_detect(string line);
string separate_word(string line);


class day
{
private:
	string text_value;
	string date_value;

public:
	day(string str_date)
	{	
		date_value = str_date.substr(START_DATE_IN_STRING, str_date.length() - START_DATE_IN_STRING);
	}
	string date() { return date_value; }
	void add_event(string event) { text_value += event + '\n'; }
	string text() { return text_value + '\0'; }
	int lengnth_text(){ return text_value.length(); }
	string full_report() { return text_value; }
	string summery_report(int length = DEFAULT_SUMMERY_LENGHT)
	{
		string summery_text;
		for (int i = 0; i < length; i++)
			summery_text += text_value[i];
		if (text_value.size() <= DEFAULT_SUMMERY_LENGHT)
			return date_value + '\n' + text_value;
		return date_value + '\n' + summery_text + "...\n";
	}
	int positive_word_count ()
	{
		string positive_word;
		stringstream text_stream(text_value);
		string text_word;
		int positive_word_counter = 0;
		while (getline(text_stream, text_word, ' '))
		{
			ifstream positive_word_file(POSITIVE_WORD_FILE_ADDRESS);
			while (getline(positive_word_file, positive_word, '\n'))
				if (positive_word == text_word)
					positive_word_counter++;
			positive_word_file.close();
		}
		return positive_word_counter;
	}
};

class diary_class
{
private:
	vector<day> days;
	int find_day_with_date(string date)
	{
		for (int i = 0; i < days.size(); i++)
			if (date == days[i].date())
				return i;	
		return NOT_FOUND;
	}
	int find_bigest_day()
	{
		int biggest_value = -1;
		int biggest_num = NOT_FOUND;
		for (int i = 0; i < days.size(); i++)
		{
			if (biggest_value < days[i].lengnth_text())
			{
				biggest_value = days[i].lengnth_text();
				biggest_num = i;
			}
		}
		return biggest_num;
	}
	int find_best_day()
	{
		int best_value = -1;
		int best_num = NOT_FOUND;
		for (int i = 0; i < days.size(); i++)
		{
			if (best_value < days[i].positive_word_count())
			{
				best_value = days[i].positive_word_count();
				best_num = i;
			}
		}
		return best_num;
	}

public:
	void new_day(string date)
	{
		day buffer_day (date);
		days.push_back(buffer_day);
	}
	void add_event(string event) { days.back().add_event(event); }
	string show_day(string str_date)
	{
		int day_num = find_day_with_date (str_date.substr(9,16));
		return days[day_num].full_report();
	}
	string show_the_longest_day()
	{
		return days[find_bigest_day()].summery_report();
	}
	string show_the_best_day()
	{
		return days[find_best_day()].summery_report();
	}

};



int main(void)
{
	string line_buffer;
	diary_class diary;
	while (getline(cin, line_buffer))
	{
		switch (input_detect(line_buffer))
		{
			case NORMAL_TEXT:
				diary.add_event(line_buffer);
				break;
			case START_DAY:
				diary.new_day(line_buffer);
				break;
			case SHOW_DAY:
				cout << diary.show_day(line_buffer);
				break;
			case SHOW_THE_LONGEST_DAY:
				cout << diary.show_the_longest_day();
				break;
			case SHOW_THE_BEST_DAY:
				cout << diary.show_the_best_day();
				break;
			default:
				cout << "some thing wrong " << __LINE__ << endl;
		}
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

