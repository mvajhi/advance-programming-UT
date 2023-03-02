#include <iostream>
#include <vector>

using namespace std;

void rabbit_method(int &method_count, int matrix_size);
void move(int &method_count, int matrix_size, vector<int> state);

int main()
{
	int matrix_size = 0;
	cin >> matrix_size;

	int method_count = 0;
	
	rabbit_method(method_count, matrix_size);

	cout << method_count;

	return 0;
}

void rabbit_method(int &method_count, int matrix_size)
{
	move(method_count, matrix_size, {0, matrix_size});
	return;
}

void move(int &method_count, int matrix_size, vector<int> state)
{
	if (state[0] == matrix_size && state[1] == 0)
	{
		method_count++;
		return;
	}
	else if (state[0] > matrix_size || state[1] < 0 || state[0] + state[1] > matrix_size)
		return;
	
	move(method_count, matrix_size, {state[0] + 1, state[1]});

	move(method_count, matrix_size, {state[0], state[1] - 1});
	
	return;
}
