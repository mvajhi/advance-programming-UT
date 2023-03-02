#include <iostream>
#include <vector>
#include <cstdlib>

#define BOARD_SIZE 7
#define X -1
#define O 0
#define N 1

#define MOVEMENT_SIZE 2

#define OK 1
#define NOT_OK -1
#define FIND_WAY 1
#define NO_WAY -1

using namespace std;

int get_input(vector<vector<int>> &board);
int solve(vector<vector<int> board, stirng &solution);
bool is_possible_move(vector<vector<int>> board, vector<int> state, vector<vector<int>> next_state);

int main()
{
	vector<vector<int>> board = {
				     {O,O,O,O,O,O,O},
				     {O,O,O,O,O,O,O},
				     {O,O,O,O,O,O,O},
				     {O,O,O,O,O,O,O},
				     {O,O,O,O,O,O,O},
				     {O,O,O,O,O,O,O},
				     {O,O,O,O,O,O,O},
				    };
       	get_input(board);

	string solution;
	solve(board, solution);

	cout << solution << endl;

	return 0;
}

int get_input(vector<vector<int>> &board)
{
	char input;
	
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cin >> input;
			if (input == 'X')
				board[i][j] = X;
			else if (input == 'O')
				board[i][j] = O;
			else if (input == 'N')
				board[i][j] = N;
			else
				cout << "some thing worng     in " << __LINE__ << endl;
		}

	return OK;
}


int solve(vector<vector<int> board, string solution)
{
	vector<vector<int>> moves = {{ MOVEMENT_SIZE, 0		   },
				     {-MOVEMENT_SIZE, 0		   },
				     {0		    ,  MOVEMENT_SIZE},
			     	     {0		    , -MOVEMENT_SIZE}};
	
	for (int i = 0; i < moves.size(); i++)
		if (solve(/*TODO*/) == FIND_WAY)
			return FIND_WAY;
	
	return NO_WAY;
}
bool is_possible_move(vector<vector<int>> board, vector<int> state, vector<vector<int>> next_state)
{
	if (board[next_state[0]][next_state[1]] != O)
		return NOT_OK;
	return OK;
}
