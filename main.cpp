#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum struct Player {
	none,
	p1,
	p2,
};

class Cell {
	public:
		Player player;

		Cell(int _number) {
			number = _number;
			player = Player::none;
		}

		string Sign() {
			if (player == Player::p1) {
				return string("x");
			} else if (player == Player::p2) {
				return string("o");
			} else {
				return to_string(number + 1);
			}
		}

	protected:
		int number;
};

class Board {
	public:
		Board() {
			for(int i = 0; i < 9; i++) {
				cells.push_back(Cell(i));
			}
		}

		string Picture() {
			string whole_picture = "";
			string row_divider = "---|---|---\n";
			whole_picture += " " + cells[0].Sign() + " | " + cells[1].Sign() + " | " + cells[2].Sign() + " \n";
			whole_picture += row_divider;
			whole_picture += " " + cells[3].Sign() + " | " + cells[4].Sign() + " | " + cells[5].Sign() + " \n";
			whole_picture += row_divider;
			whole_picture += " " + cells[6].Sign() + " | " + cells[7].Sign() + " | " + cells[8].Sign() + " \n";
			return whole_picture;
		}

		void MarkCell(int cell, Player player) {
			cells[cell].player = player;
		}

		Player WinningPlayer() {
			if (PlayerWon(Player::p1)) {
				return Player::p1;
			} else if (PlayerWon(Player::p2)) {
				return Player::p2;
			} else {
				return Player::none;
			}
		}

	protected:
		vector<Cell> cells;

		bool PlayerWon(Player player) {
			int winning_lines[8][3] = {
				{0,1,2}, // top row
				{3,4,5}, // middle row
				{6,7,8}, // bottom row
				{0,3,6}, // left column
				{1,4,7}, // middle column
				{2,5,8}, // right column
				{0,4,8}, // top left to bottom right
				{2,4,6}, // top right to bottom left
			};
			for (int i = 0; i < sizeof(winning_lines)/sizeof(*winning_lines); i++) {
				int *winning_cells = winning_lines[i];
				if (
					cells[winning_cells[0]].player == player
					&& cells[winning_cells[1]].player == player
					&& cells[winning_cells[2]].player == player
				) {
					return true;
				}
			}
			return false;
		}
};

int main() {
	Board board;
	board.MarkCell(0, Player::p1);
	board.MarkCell(1, Player::p2);
	board.MarkCell(4, Player::p1);
	board.MarkCell(2, Player::p2);
	board.MarkCell(8, Player::p1);

	cout << board.Picture();

	Player winning_player = board.WinningPlayer();

	if (winning_player == Player::p1) {
		cout << "Player 1 won!\n";
	} else if (winning_player == Player::p2) {
		cout << "Player 2 won!\n";
	} else if (winning_player == Player::none) {
		cout << "No one won!\n";
	}
}
