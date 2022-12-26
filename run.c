/*
Contains the main function of the Tic-Tac-Toe game and starts
the game.

Author: Colby Tse
Version: December 20, 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Prints the title of the game.
 */
void display_title() {
	printf("+-----------+\n"
		   "| TICTACTOE |\n");
}

/*
 * Prints the Tic-Tac-Toe board.
 */
void display_board(char* board[9]) {
	printf("+---+---+---+\n");

	char* row1[8] = {"| ", "", " | ", "", " | ", "", " |", "\n"};
	for (int i = 0; i < 9; i += 3) {
		row1[1] = board[i];
		row1[3] = board[i + 1];
		row1[5] = board[i + 2];
		for (int j = 0; j < 8; j++) {
			printf("%s", row1[j]);
		}
		printf("+---+---+---+\n");
	}
}

/*
 * Prints the footer including a message that states which
 * player's turn or, if game finished, who won the game.
 */
void display_footer(int is_p1_turn, int win) {
	printf("| ");
	if (win == 2) {
		printf("  Tied!  ");
	} else if (win == 1) {
		printf("P1 wins! ");
	} else if (win == 0) {
		printf("P2 wins! ");
	} else if (is_p1_turn) {
		printf("P1's turn");
	} else {
		printf("P2's turn");
	}
	printf(" |\n");
	printf("+-----------+\n");
}

/*
 * Processes the player input and makes changes to the board where
 * necessary or sets an error prompt to show.
 */
void handle_input(int pos, char* board[9], int* prompt,
	int* is_p1_turn) {
	if (pos < 1 || pos > 9) {
		*prompt = 1;
	} else if (strcmp(board[pos - 1], "X") == 0 ||
		strcmp(board[pos-1], "O") == 0) {
		*prompt = 2;
	} else {
		if (*is_p1_turn) {
			board[pos-1] = "X";
			*is_p1_turn = 0;
		} else {
			board[pos-1] = "O";
			*is_p1_turn = 1;
		}
	}
}

/*
 * Search for any win conditions (3 in a row). Then, return 1 if
 * 3 consecutive Xs, return 0 if 3 consecutive Os, return 2 if tied
 * or return -1 if no win conditions (game continues).
 */
int search_win_condition(char* board[9]) {
	// search for vertical win condition
	for (int i = 0; i < 3; i++) {
		if (strcmp(board[i], board [i+3]) == 0 &&
			strcmp(board[i+3], board[i+6]) == 0) {
			if (strcmp(board[i], "X") == 0) {
				return 1;
			} else if (strcmp(board[i], "O") == 0) {
				return 0;
			}
		}
	}

	// search for horizontal win condition
	for (int i = 0; i < 9; i += 3) {
		if (strcmp(board[i], board[i+1]) == 0 &&
			strcmp(board[i+1], board[i+2]) == 0) {
			if (strcmp(board[i], "X") == 0) {
				return 1;
			} else if (strcmp(board[i], "O") == 0) {
				return 0;
			}
		}
	}

	// search for diagonal win condition
	if (strcmp(board[0], board[4]) == 0 &&
		strcmp(board[4], board[8]) == 0) {
		if (strcmp(board[0], "X") == 0) {
			return 1;
		} else if (strcmp(board[0], "O") == 0) {
				return 0;
			}
	} else if (strcmp(board[2], board[4]) == 0 &&
		strcmp(board[4], board[6]) == 0) {
		if (strcmp(board[2], "X") == 0) {
			return 1;
		} else if (strcmp(board[2], "O") == 0) {
				return 0;
			}
	}

	// search if tied game
	int tied = 1;
	for (int i = 0; i < 9; i++) {
		if (strcmp(board[i], " ") == 0) {
			tied = 0;
		}
	}
	if (tied) {
		return 2;
	}

	// no win conditions or tie, game continues
	return -1;
}

/*
 * Main function and loop.
 */
int main(int argc, char** argv) {

	if (argc > 1) {
		time_t t;
		srand((unsigned) time(&t));
	}

	// initialise variables
	char* board[9] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
	char pos;
	int prompt = 0;
	int is_p1_turn = 1;
	char play_again[4];

	// main loop
	while (1) {
		system("clear");

		// display the game
		display_title();
		display_board(board);
		display_footer(is_p1_turn, search_win_condition(board));

		// end game if won
		if (search_win_condition(board) != -1) {
			return 1;
		}

		// print any error prompts
		if (prompt == 1) {
			printf("Invalid input.\n");
			prompt = 0;
		} else if (prompt == 2) {
			printf("Space is already occupied.\n");
			prompt = 0;
		}

		// get player input
		printf("Enter a number from 1-9: ");
		pos = getchar();
		if (getchar() != '\n') {
			while (getchar() != '\n');
			handle_input(-1, board, &prompt, &is_p1_turn);
		} else {
			handle_input(pos - '0', board, &prompt, &is_p1_turn);
		}
	}
}