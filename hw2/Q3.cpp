#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

#define BOARD_SIZE 7
#define BOARD_CENTER 3
#define X -1
#define O 0
#define N 1

#define MOVEMENT_SIZE 2

#define OK 1
#define NOT_OK -1
#define FIND_WAY 1
#define NO_WAY -1
#define REPETITIOUS_WAY 0

using namespace std;

int get_input(vector<vector<int>> &board);
int solve(vector<vector<int>> board, vector<string> &solution, vector<vector<vector<int>>> &history);
bool is_possible_move(vector<vector<int>> board, vector<int> state, vector<int> next_state);
string add_to_solution(vector<int> state, vector<int> next_state);
vector<vector<int>> make_new_board(vector<vector<int>> board, vector<int> state, vector<int> new_state);
vector<vector<int>> find_pieces(vector<vector<int>> board);
bool is_solve (vector<vector<int>> board);
bool is_possible_win(vector<vector<int>> board);
bool is_board_repetitious(vector<vector<int>> board, vector<vector<vector<int>>> history);
int print_solution(vector<string> solution);

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

	vector<string> solution;
	vector<vector<vector<int>>> history;
	int is_find = solve(board, solution, history);
	if(is_find == FIND_WAY)
		print_solution(solution);
	else
		cout << "Loser";
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


int solve(vector<vector<int>> board, vector<string> &solution, vector<vector<vector<int>>> &history)
{
	if (is_solve(board))
		return FIND_WAY;
	if (is_board_repetitious(board, history))
		return REPETITIOUS_WAY;
	else if (is_possible_win(board) == false)
		return NO_WAY;
	else
		history.push_back(board);

	vector<vector<int>> moves = {{ MOVEMENT_SIZE, 0		   },
				     {-MOVEMENT_SIZE, 0		   },
				     {0		    ,  MOVEMENT_SIZE},
			     	     {0		    , -MOVEMENT_SIZE}};

	vector<vector<int>> N_pieces = find_pieces(board);
	for (int i = 0; i < N_pieces.size(); i++)
	{
		vector<int> state = N_pieces[i];
		for (int j = 0; j < moves.size(); j++)
		{
			vector<int> new_state = {state[0] + moves[j][0], state[1] + moves[j][1]};
			if (is_possible_move(board, state, new_state) == false)
				continue;
			if (solve(make_new_board(board, state, new_state), solution, history) == FIND_WAY)
			{
				solution.push_back(add_to_solution(state, new_state));
				return FIND_WAY;
			}
		}
	}
	return NO_WAY;
}


bool is_possible_move(vector<vector<int>> board, vector<int> state, vector<int> next_state)
{
	if (0 > next_state[0] || 0 > next_state[1] || next_state[0] >= BOARD_SIZE || next_state[1] >= BOARD_SIZE)
		return false;
	else if (board[next_state[0]][next_state[1]] != O)
		return false;
	else if (board[(state[0] + next_state[0]) / 2][(state[1] + next_state[1]) / 2] != N)
		return false;
	return true;
}

string add_to_solution(vector<int> state, vector<int> next_state)
{
	char row[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	string output = row[state[0]] + to_string(state[1] + 1) + " ";
	if (next_state[0] - state[0] == MOVEMENT_SIZE)
		output += "UP";
	else if (next_state[0] - state[0] == -MOVEMENT_SIZE)
		output += "DOWN";
	else if (next_state[1] - state[1] == MOVEMENT_SIZE)
		output += "RIGHT";
	else if (next_state[1] - state[1] == -MOVEMENT_SIZE)
		output += "LEFT";
	return output;
}

vector<vector<int>> make_new_board(vector<vector<int>> board, vector<int> state, vector<int> new_state)
{
	board[(state[0] + new_state[0]) / 2][(state[1] + new_state[1]) / 2] = O;
	board[state[0]][state[1]] = O;
	board[new_state[0]][new_state[1]] = N;
	return board;
}

vector<vector<int>> find_pieces(vector<vector<int>> board)
{
	vector<vector<int>> pieces;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == N)
				pieces.push_back({i, j});
	return pieces;
}

bool is_solve(vector<vector<int>> board)
{
	int N_peices_count = find_pieces(board).size();
	if (N_peices_count != 1)
		return false;
	if (board[BOARD_CENTER][BOARD_CENTER] != N)
		return false;
	return true;
}

bool is_possible_win(vector<vector<int>> board)
{
	vector<vector<int>> pieces = find_pieces(board);
	for (int i = 0; i < pieces.size(); i++)
		if (pieces[i][0] % 2 == 1 && pieces[i][1] % 2 == 1)
			return true;
        return false;
}

bool is_board_repetitious(vector<vector<int>> board, vector<vector<vector<int>>> history)
{
	for (int i = 0; i < history.size(); i++)
		if (board == history[i])
			return true;
	return false;
}

int print_solution(vector<string> solution)
{
	reverse(solution.begin(), solution.end());
	for (int i = 0; i < solution.size(); i++)
	{
		if (i == 0)
			cout << solution[i];
		else
			cout << '\n' << solution[i];
	}
	
        return OK;
}
