#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Game
{
private:
	enum class Player
	{
		Human = 'X',
		Computer = 'O',
		None = '\0'
	};

	struct Move
	{
		unsigned int x = 0;
		unsigned int y = 0;
	};

	Player Board[3][3];
public:
	//Constructor
	Game()
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				Board[i][j] = Player::None;
			}
		}
	}

	void printBoard() const
	{
		system("cls");
		cout << "   ----Tic Tac Toe----\n\n   Human : X\n   AI : O\n" << endl;
		cout << "      0     1     2" << endl;
		cout << "   -------------------";
		for (unsigned int i = 0; i < 3; i++)
		{
			cout << "\n "<<i<<" "<< "|";
			for (unsigned int j = 0; j < 3; j++)
			{
				cout << setw(3) << static_cast<char>(Board[i][j]) << setw(3) << " |";
				
			}
			cout << "\n   -------------------";
		}
		cout << "\n\n";
	}

	bool isTie() const 
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (Board[i][0] == Player::None || Board[i][1] == Player::None || Board[i][2] == Player::None)
				return false;
		}
		return true;
	}

	bool checkWin(Player _player) const
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (Board[i][0] == _player && Board[i][1] == _player && Board[i][2] == _player)
				return true;
			if (Board[0][i] == _player && Board[1][i] == _player && Board[2][i] == _player)
				return true;
		}
		if (Board[0][0] == _player && Board[1][1] == _player && Board[2][2] == _player)
			return true;
		if (Board[0][2] == _player && Board[1][1] == _player && Board[2][0] == _player)
			return true;
		return false;
	}

	Move minimax()
	{
		int score = numeric_limits<int>::max();
		Move move;
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (Board[i][j] == Player::None)
				{
					Board[i][j] = Player::Computer;
					int temp = maxSearch();
					if (temp < score)
					{
						score = temp;
						move.x = i;
						move.y = j;
					}
					Board[i][j] = Player::None;
				}
			}
		}
		return move;
	}

	int maxSearch()
	{
		if (checkWin(Player::Human)) { return 10; }
		else if (checkWin(Player::Computer)) { return -10; }
		else if (isTie()) { return 0; }
		int score = numeric_limits<int>::min();
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (Board[i][j] == Player::None)
				{
					Board[i][j] = Player::Human;
					score = max(score, minSearch());
					Board[i][j] = Player::None;
				}
			}
		}
		return score;
	}

	int minSearch()
	{
		if (checkWin(Player::Human)) { return 10; }
		else if (checkWin(Player::Computer)) { return -10; }
		else if (isTie()) { return 0; }
		int score = numeric_limits<int>::max();
		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				if (Board[i][j] == Player::None)
				{
					Board[i][j] = Player::Computer;
					score = min(score, maxSearch());
					Board[i][j] = Player::None;
				}
			}
		}
		return score;
	}

	void humanTurn()
	{
		bool Status = true;
		unsigned int x = -1, y = -1;
		char c;
		do
		{	//Getting the move coordinates from the user
			cout << "   Your Move: ";
			cin >> c;	
			x = c - '0';
			cin >> c;
			y = c - '0';
			Status = Board[x][y] != Player::None;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (Status);
		Board[x][y] = Player::Human;
	}

	void MainFunc()
	{
		Game();
		unsigned int Turn = 0;
		bool Status = false;
		printBoard();
		do
		{
			if (Turn == 0)
			{
				humanTurn();
				if (checkWin(Player::Human))
				{
					printBoard();
					cout << "   Human Wins\n";
					Status = true;
				}
				else printBoard();
			}
			else
			{
				Move aimove = minimax();
				Board[aimove.x][aimove.y] = Player::Computer;
				if (checkWin(Player::Computer))
				{
					printBoard();
					cout << "   Computer Wins\n";
					Status = true;
				}
				else printBoard();
			}
			if (isTie())
			{
				printBoard();
				cout << "   Tie\n";
				Status = true;
			}
			Turn ^= 1;
		} while (!Status);
	}
};

int main()
{
	char again;
	do
	{
		Game g;	
		g.MainFunc();
		cout << "\n   PLAY AGAIN ? [Y/N] : ";
		cin >> again;
	} while (again=='Y'||again=='y');
}