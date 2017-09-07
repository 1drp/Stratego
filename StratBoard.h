/*
 * StratBoard.h
 *
 *  Created on: Sep 4, 2017
 *      Author: Daniel Peterson
 */

#ifndef STRATBOARD_H_
#define STRATBOARD_H_

using namespace std;

class StratBoard{
private:
	// Herein lies the game board in all it's glory
	int boardState[10][10][2];
	unsigned char blankBoard[22][22];
	// An array to hold all the pieces that have been removed from the board
	int captured[13][2];
	// Optional Rules
	bool ruleSet[3];

	// Internal Functions
	bool validMove(bool, int[2], int[2]);
	bool battle(int, int);
	void rescue(bool);

public:
	// Constructor
	StratBoard();

	// Destructor
	~StratBoard();

	// Accessors
	void printBoardState(bool);
	int gameOver();

	// Mutators
	void pieceMove(bool);
	void initPos(bool);
};


#endif /* STRATBOARD_H_ */
