#include <iostream>
#include <vector>

using namespace std;

void rabbit_method(int &method_count, int matrix_size);
void move(int &method_count, int matrix_size, vector<int> state, vector<vector<int>> history);

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
	vector<vector<int>> a;
	move(method_count, matrix_size, {0, matrix_size}, a);
	return;
}

void move(int &method_count, int matrix_size, vector<int> state, vector<vector<int>> history)
{
	history.push_back(state);
	if (state[0] == matrix_size && state[1] == 0)
	{
		method_count++;
		cout << method_count << ". ";
		for (int i = 0; i < history.size(); i++)
			cout << "(" << history[i][0] << ", " << history[i][1] << ") ";
		cout << endl;
		return;
	}
	else if (state[0] > matrix_size || state[1] < 0 || state[0] + state[1] > matrix_size)
	{
		cout << endl;
		return;
	}
	
	move(method_count, matrix_size, {state[0] + 1, state[1]}, history);

	move(method_count, matrix_size, {state[0], state[1] - 1}, history);
	
	return;
}
