/*
 * StratBoard.cpp
 *
 *  Created on: Sep 4, 2017
 *      Author: Daniel Peterson
 */
#include <iostream>
#include <cmath>
#include "StratBoard.h"

using namespace std;

// The default constructor creates an empty game board
StratBoard::StratBoard()
{
	char choice;

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			boardState[x][y][0] = boardState[x][y][1] = 0;
		}
	}
	// fill in the lakes
	for (int x = 4; x < 6; x++) {
		for (int y = 0; y < 4; y++) {
			for (int p = 0; p < 2; p++) {
				boardState[x][y + (y / 2) * 2 + 2][p] = -2;
			}
		}
	}
	// create blank board for display
	for (int x = 0; x < 22; x++) {
		for (int y = 0; y < 22; y++) {
			blankBoard[x][y] = ' ';					// initialize with white space
		}
	}
	for (int y = 0; y < 10; y++) {
		blankBoard[21][2 + y * 2] = 48 + y;			// column labels
		if (y < 9) {
			blankBoard[20][3 + y * 2] = 194;		// lower-half-'+' for top line
			blankBoard[0][3 + y * 2] = 193;			// upper-half-'+' for bottom line
		}
	}
	for (int x = 0; x < 10; x++) {
		blankBoard[1 + x * 2][0] = 48 + x;			// row labels
		if (x < 9) {
			blankBoard[2 + x * 2][1] = 195;			// right-half-'+' for leftmost line
			blankBoard[2 + x * 2][21] = 180;		// left-half-'+' for rightmost line
		}
	}
	blankBoard[20][1] = 218;						// top left corner of board
	blankBoard[20][21] = 191;						// top right corner of board
	blankBoard[0][1] = 192;							// bottom left corner of board
	blankBoard[0][21] = 217;						// bottom right corner of board
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			blankBoard[3 + 2 * x][2 + 2 * y] = 197;	// all of the 4-way space corners
		}
	}
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			blankBoard[2 * x][2 + 2 * y] = 196;		// all of the horizontal space borders
			blankBoard[1 + 2 * x][1 + 2 * y] = 179; // all of the vertical space borders
		}
	}
	// creating the lakes will overwrite some of my old work in here, but is algorithmically faster
	blankBoard[12][7] = blankBoard[12][15] = 193;	// upper border of lakes
	blankBoard[8][7] = blankBoard[8][15] = 194;		// lower border of lakes
	blankBoard[10][5] = blankBoard[10][13] = 180;	// left border of lakes
	blankBoard[10][9] = blankBoard[10][17] = 195;	// right border of lakes
	for (int x = 9; x < 12; x++) {
		for (int y = 0; x < 6; y++) {
			blankBoard[x][6 + y + (y / 3) * 5] = '~'; // fill in those beautiful lakes
		}
	}

	// ensure the captured list is empty
	for (int c = 0; c < 13; c++) {
		captured[c][0] = captured[c][1] = 0;
	}
	// Check for optional rules
	cout << "Would you like to play with Aggressor Advantage? (y/n): ";
	cin >> choice;
	if(choice == 'y' || choice == 'Y') {
		ruleSet[0] = true;
	} else {
		ruleSet[0] = false;
	}

	cout << "Would you like to play with Silent Defense? (y/n): ";
	cin >> choice;
	if(choice == 'y' || choice == 'Y') {
		ruleSet[1] = true;
	} else {
		ruleSet[1] = false;
	}

	cout << "Would you like to play with Rescue? (y/n): ";
	cin >> choice;
	if(choice == 'y' || choice == 'Y') {
		ruleSet[2] = true;
	} else {
		ruleSet[2] = false;
	}
}

// This mutator populates the starting positions
void StratBoard::initPos(bool player)
{
	int initPlayer[4][10];
	bool playerApproved = false;
	bool validRank = false;
	int available[] = {0, 1, 1, 2, 3, 4, 4, 4, 5, 8, 1, 6, 1};
	char chosenSetup[4][10], choice;

	while(!playerApproved) {
		for(int x = 0; x < 4; x++) {
			for(int y = 0; y < 10; y++) {
				while(validRank == false){
					cout << "Enter a piece (1-12) for row " << x + 1 << ", col " << y + 1 << ": ";
					cin >> initPlayer[x][y];
					// Translate ranks to characters for user confirmation
					switch(initPlayer[x][y]){
					case 1:
						chosenSetup[x][y] = '1';
						break;
					case 2:
						chosenSetup[x][y] = '2';
						break;
					case 3:
						chosenSetup[x][y] = '3';
						break;
					case 4:
						chosenSetup[x][y] = '4';
						break;
					case 5:
						chosenSetup[x][y] = '5';
						break;
					case 6:
						chosenSetup[x][y] = '6';
						break;
					case 7:
						chosenSetup[x][y] = '7';
						break;
					case 8:
						chosenSetup[x][y] = '8';
						break;
					case 9:
						chosenSetup[x][y] = '9';
						break;
					case 10:
						chosenSetup[x][y] = 'S';
						break;
					case 11:
						chosenSetup[x][y] = 'B';
						break;
					case 12:
						chosenSetup[x][y] = 'F';
						break;
					default:
						initPlayer[x][y] = 0;
						cout << "Not a valid entry.\n";
					}
					if(initPlayer[x][y] != 0 && available[initPlayer[x][y]] > 0) {
						available[initPlayer[x][y]]--;
						validRank = true;
					} else if(initPlayer[x][y] != 0 && available[initPlayer[x][y]] <= 0) {
						cout << "You don't have any of those pieces remaining.\n";
					}
				}
				validRank = false;

			}
		}
		cout << "Your setup:\n";
		for(int x = 3; x >= 0; x--) {
			for(int y = 0; y < 10; y++) {
				cout << chosenSetup[x][y] << " ";
			}
			cout << endl;
		}
		cout << "Is this correct? (Y/N): ";
		cin >> choice;
		if(choice == 'y' || choice == 'Y') {
			playerApproved = true;
		} else {
			cout << "Trying again.\n\n";
			available[1] = 1;
			available[2] = 1;
			available[3] = 2;
			available[4] = 3;
			available[5] = 4;
			available[6] = 4;
			available[7] = 4;
			available[8] = 5;
			available[9] = 8;
			available[10] = 1;
			available[11] = 6;
			available[12] = 1;
		}
	}


	if(!player){
		// The Red side of the board
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 10; y++) {
				boardState[x][y][0] = initPlayer[x][y];
				boardState[x][y][1] = -1;
			}
		}
	} else {
		// The Blue side of the board
		for (int x = 6; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				boardState[x][y][1] = initPlayer[9 - x][9 - y];
				boardState[x][y][0] = -1;
			}
		}
	}
}

// The destructor
StratBoard::~StratBoard()
{
	cout << "Thank you for playing!\n";
}

// Access the board state
void StratBoard::printBoardState(bool player)
{
	char printedBoard[22][22];

	// start with a blank board
	for(int x = 0; x < 22; x++){
		for(int y = 0; y < 22; y++) {
			printedBoard[x][y] = blankBoard[x][y];
		}
	}

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			switch(boardState[x][y][player]){
			case -2:
				printedBoard[1 + x * 2][2 + y * 2] = '~';
				break;
			case -1:
				printedBoard[1 + x * 2][2 + y * 2] = 219;
				break;
			case 0:
				printedBoard[1 + x * 2][2 + y * 2] = ' ';
				break;
			case 10:
				printedBoard[1 + x * 2][2 + y * 2] = 'S';
				break;
			case 11:
				printedBoard[1 + x * 2][2 + y * 2] = 'B';
				break;
			case 12:
				printedBoard[1 + x * 2][2 + y * 2] = 'F';
				break;
			default:
				printedBoard[1 + x * 2][2 + y * 2] = boardState[x][y][player] + 48;
			}
		}
	}
	for(int x=21; x>=0; x--) {
		for(int y=0; y<22; y++) {
			cout << printedBoard[x][y];
		}
		cout << endl;
	}
	cout << endl;
}

// Move a piece
void StratBoard::pieceMove(bool player)
{
	bool isValid = false;
	bool wonStrike = true;
	int initPos[2];
	int finPos[2];
	int playerRank = 0;
	int opponentRank = 0;
	char opponentPiece;

	while(isValid == false) {
		cout << "Enter the initial position of the piece you want to move (x y): ";
		cin >> initPos[0];
		cin >> initPos[1];
		cout << "Enter the final position for your move (x y): ";
		cin >> finPos[0];
		cin >> finPos[1];

		isValid = validMove(player,initPos,finPos);
	}
	// populate the rank variables
	playerRank = boardState[initPos[0]][initPos[1]][player];
	opponentRank = boardState[finPos[0]][finPos[1]][!player];

	// convert to char for useful feedback
	if(opponentRank > 0 && opponentRank < 12) {
		switch(opponentRank) {
		case 10:
			opponentPiece = 'S';
			break;
		case 11:
			opponentPiece = 'B';
			break;
		default:
			opponentPiece = opponentRank + 48;
		}
	}

	// check for battle. a "fight" against an empty space will return true.
	wonStrike = battle(playerRank, opponentRank);
	if(wonStrike) {
		// mark opponent piece as captured
		if(opponentRank != 0) {
			captured[opponentRank][!player]++;
			cout << "You captured a " << opponentPiece << endl;
		}
		if(!ruleSet[0] && playerRank == opponentRank) {
			// both  pieces captured in ties under standard rules
			captured[playerRank][player]++;
			boardState[finPos[0]][finPos[1]][player] = boardState[finPos[0]][finPos[1]][!player] = 0;
			cout << "You were captured by a " << opponentPiece << " in a tie.\n";
		} else {
			// populate new piece position
			boardState[finPos[0]][finPos[1]][!player] = -1;
			boardState[finPos[0]][finPos[1]][player] = playerRank;
			// clear old piece position
			boardState[initPos[0]][initPos[1]][0] = boardState[initPos[0]][initPos[1]][1] = 0;
		}
	} else {
		// remove player's piece from the board
		boardState[initPos[0]][initPos[1]][player] = boardState[initPos[0]][initPos[1]][!player] = 0;
		captured[playerRank][player]++;
		if(!ruleSet[1]) {
			cout << "You were captured by a " << opponentPiece << endl;
		}
	}
	if(ruleSet[2] == true && finPos[1] == (!player * 9) && playerRank != 9 && captured[0][player] < 2) {
		rescue(player);
	}

}

// Check validity of a move
bool StratBoard::validMove(bool player, int initPos[2], int finPos[2])
{
	// some local variables that are easier to work with
	int static checkInit[2] = {boardState[initPos[0]][initPos[1]][player], boardState[initPos[0]][initPos[1]][!player]};
	int static checkFin[2] = {boardState[finPos[0]][finPos[1]][player], boardState[finPos[0]][finPos[1]][!player]};
	int static delta[2] = {finPos[0] - initPos[0], finPos[1] - initPos[1]};
	// check for things that the player cannot move
	switch(checkInit[0]) {
	case -2:
		cout << "You cannot move a lake.\n";
		return false;
	case -1:
		cout << "You cannot move an opposing piece.\n";
		return false;
	case 0:
		cout << "There is nothing there to move.\n";
		return false;
	case 11:
		cout << "You cannot move a bomb.\n";
		return false;
	case 12:
		cout << "You cannot move your flag.\n";
		return false;
	default:
		break;
	}
	// make sure the player actually moved
	if(delta[0] == 0 && delta[1] == 0) {
		cout << "You didn't move!\n";
		return false;
	}
	// check for illegal moves
	if(delta[0] != 0 && delta[1] != 0) {
		cout << "Cannot move diagonally.\n";
		return false;
	} else if(delta[0] + delta[1] > 1) {
		if(checkInit[0] != 9) {
			cout << "Only the scout can move more than one space.\n";
			return false;
		} else if(checkFin[0] == -1) {
			cout << "The scout cannot attack more than one space away.\n";
			return false;
		} else if(delta[0] < 0) {
			for(int m = -1; m >= delta[0]; m--) {
				if(boardState[initPos[0] + m][initPos[1]][player] != 0) {
					cout << "The path is blocked.\n";
					return false;
				}
			}
		} else if(delta[0] > 0) {
			for(int m = 1; m <= delta[0]; m++) {
				if(boardState[initPos[0] + m][initPos[1]][player] != 0) {
					cout << "The path is blocked.\n";
					return false;
				}
			}
		} else if(delta[1] < 0) {
			for(int m = -1; m >= delta[1]; m--) {
				if(boardState[initPos[0]][initPos[1] + m][player] != 0) {
					cout << "The path is blocked.\n";
					return false;
				}
			}
		} else {
			for(int m = 1; m <= delta[1]; m++) {
				if(boardState[initPos[0]][initPos[1] + m][player] != 0) {
					cout << "The path is blocked.\n";
					return false;
				}
			}
		}
	} else if(checkFin[0] == -2) {
		cout << "Stratego soldiers sink swiftly. Cannot move into a lake.\n";
		return false;
	}
	// need to place a check for do/undo/do moves.
	// we have a legal move
	return true;
}

// Battle logic
bool StratBoard::battle(int playerRank,int oppRank)
{
	if(oppRank == 12) {
		cout << "You found the enemy flag!\n";
		return true;
	} else if(oppRank == 11) {
		if(playerRank == 8) {
			return true;
		} else {
			return false;
		}
	} else if(oppRank == 1 && playerRank == 10) {
		return true;
	} else {
		return (playerRank >= oppRank);
	}
}

// Rescue functionality for optional rule #3
void StratBoard::rescue(bool player)
{
	int choice = 0;
	int x = 0, y = 0;
	bool again = true;

	while (again == true) {
		cout << "Pieces that you can rescue:\n";
		for(int i = 1; i < 10; i++) {
			cout << i << ": x" << captured[i][player] << endl;
		}
		cout << "S(10): x" << captured[10][player] << endl;
		cout << "B(11): x" << captured[11][player] << endl;
		cout << "Which piece would you like to rescue? ";
		cin >> choice;

		if(choice < 1 || choice > 11) {
			cout << "Please choose a valid piece (1-11):\n";
		} else if(captured[choice][player] == 0) {
			cout << "None of that rank has been captured.\n";
		} else {
			again = false;
		}
	}
	again = true;
	while(again == true) {
		cout << "Where would you like to place it? (x y) ";
		cin >> x;
		cin >> y;

		if(x < 0 || x > 9 || y < 0 || y > 9) {
			cout << "Must place on board.\n";
		} else if((!player && x > 3) || (player && x < 6)) {
			cout << "Must place on your own side of the board.\n";
		} else if(boardState[x][y][player != 0]) {
			cout << "That spot is not empty.\n";
		} else {
			again = false;
		}
	}

}

// Pass captured state of flag (rank 12)
int StratBoard::gameOver()
{
	if(captured[12][0]) {
		return 1;
	}else if(captured[12][1]){
		return 0;
	} else {
		return -1;
	}
}
