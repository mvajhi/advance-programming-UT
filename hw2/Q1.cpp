#include <iostream>
#include <vector>

#define DEFAULT_MISAG_MOVE_BEFOR_NUMBER 0
#define DEFAULT_MISAG_STATE 0
#define DEFAULT_MISAG_COUNTER 0

using namespace std;

int how_meny_number_enter();
vector<int> get_numbers(int count);
void misag_move(vector<int> &numbers, int state = DEFAULT_MISAG_STATE, int before_number = DEFAULT_MISAG_MOVE_BEFOR_NUMBER, int counter = DEFAULT_MISAG_COUNTER);

int main()
{
	int count = how_meny_number_enter();

	vector<int> numbers = get_numbers(count);

	misag_move(numbers);

	return 0;
}

// return how meny number user want to enter
int how_meny_number_enter()
{
	int input = 0;
	cin >> input;
	return input;
}

// get numbers while count reach arg value and return vector of numbers
vector<int> get_numbers(int count)
{
	vector<int> input_numbers;
	for (int i = 0; i < count; i++)
	{
		int input = 0;
		cin >> input;
		input_numbers.push_back(input);
	}
	return input_numbers;
}

// get int vector and print numbers with using misag algorithm
void misag_move(vector<int> &numbers, int state, int before_number, int counter)
{
	if (state >= numbers.size())
		return;

	if (counter != DEFAULT_MISAG_COUNTER)
		cout << ' ';
	cout << numbers[state];

	int next_state = state;
	if (counter % 2 == 0)
		next_state += max(before_number, numbers[state]);
	else
		next_state += min(before_number, numbers[state]);

	misag_move(numbers, next_state, numbers[state], counter + 1);
	return;
}
