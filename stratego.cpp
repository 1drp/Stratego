/*
stratego.cpp
Sep 3, 2017
Daniel Peterson
*/
#include <iostream>
#include <cmath>
#include "StratBoard.h"
using namespace std;

void newLocal();
int menu();

int main()
{
	int choice;

	cout << "Welcome to Stratego!" << endl;
	choice = menu();

	if(choice==1) {
		newLocal();
	}

	cin >> choice;
	return 0;
}

void newLocal()
{
	StratBoard board;
	bool turn = 0;
	int winner = -1;

	// debugging layout
	board.printBoardState(turn);

	cout << "Red! Set up your army.\n";
	board.initPos(0);
	cout << "Blue! Set up your army.\n";
	board.initPos(1);

	while(winner < 0){
		board.printBoardState(turn);

		board.pieceMove(turn);

		winner = board.gameOver();

		turn = !turn;
	}

	if(winner == 0) {
		cout << "Congratulations Red!\n";
	} else {
		cout << "Congratulations Blue!\n";
	}

}

int menu()
{
	int choice = 0;
	cout << "1. New Hotseat Game\n" <<
			//"2. New Network Game (Not implemented yet)\n" <<
			"0. Exit\n";
	cin >> choice;

	switch(choice){
	case 1:
		return 1;
	//case 2:
	//	return 1; // defaults to hotseat until network game is implemented
	default:
		return 0;
	}
}
