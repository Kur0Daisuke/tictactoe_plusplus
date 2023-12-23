#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>

std::string gameboard[3][3] = {
	{ "1", "4", "7" },
	{ "2", "5", "8" },
	{ "3", "6", "9" }
};

void renderBoard() {
	std::vector<std::string> torender;

	for(int x = 0; x < 3; x++) {
		for(int y = 0; y < 3; y++) {
			torender.push_back(gameboard[x][y]);
		}
	}
	std::cout <<"\n    |   |   \n"
				"  "<< torender[0] <<" | "<< torender[1] <<" | "<< torender[2] <<"  \n"
				" ___|___|___\n"
				"    |   |     \n"
				"  "<< torender[3] <<" | "<< torender[4] <<" | "<< torender[5] <<"  \n"
				" ___|___|___\n"
				"    |   |     \n"
				"  "<< torender[6] <<" | "<< torender[7] <<" | "<< torender[8] <<"  \n"
				"    |   |     \n";
}

std::string lower_string(std::string str)
{
	for(int i=0;str[i]!='\0';i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')    //checking for uppercase characters
			str[i] = str[i] + 32;         //converting uppercase to lowercase
	}
	return str;
}

void restart(int (*game)(int playerTurn, std::string err)) {
	std::string input;
	std::cout << "\nDo you wish to play again ?\nY\\N?\n";
	std::cin >> input;
	
	if(lower_string(input) == "y") {
		int in = 1;
		for(int x=0;x<3;x++)
		{
			for(int y=0;y<3;y++) {
				gameboard[y][x] = std::to_string(in);
				in++;
			}
		}
		game(1,"");
		return;
	}
	if(lower_string(input) == "n") {
		exit(0);
		return;
	}
	if(lower_string(input) != "y" || lower_string(input) != "n")
	{
		restart(game);
		return;
	}
}

void EndScreen(int x1, int y1,int x2, int y2,int x3, int y3, int playerTurn, int (*game)(int playerTurn, std::string err)) {
	std::cout << "player - " << playerTurn << "wins";
	for(int x=0;x<3;x++) {
		for(int y=0; y < 3; y++) {
			gameboard[y][x] = " ";
		}
	}
	std::string symbol = playerTurn == 1 ? "X" : "O";
	gameboard[y1][x1] = symbol;
	gameboard[y2][x2] = symbol;
	gameboard[y3][x3] = symbol;

	renderBoard();
	restart(game);
}

void checkforwinners(int x, int y, int playerturn, int (*game)(int playerTurn, std::string err)) {
	if((gameboard[y][x] == "X" || gameboard[y][x] == "O") &&
		((gameboard[y][x] == gameboard[y][x+1>2?(x+1)-3:x+1]) && (gameboard[y][x+1>2?(x+1)-3:x+1] == gameboard[y][x+2>2?(x+2)-3:x+2])))
	{
		// X | X | X check
		EndScreen(x,y,x+1>2?(x+1)-3:x+1,y,x+2>2?(x+2)-3:x+2,y,playerturn, game);
	}else if((gameboard[y][x] == "X" || gameboard[y][x] == "O") &&
		((gameboard[y][x] == gameboard[y+1>2?(y+1)-3:y+1][x]) && (gameboard[y+1>2?(y+1)-3:y+1][x] == gameboard[y+2>2?(y+2)-3:y+2][x]))) 
	{
		/*
			X|
			X|  check
			X|
		*/

		EndScreen(x,y,x,y+1>2?(y+1)-3:y+1,x,y+2>2?(y+2)-3:y+2,playerturn, game);
	}else if((gameboard[y][x] == "X" || gameboard[y][x] == "O") &&
		(gameboard[0][0] == gameboard[1][1] &&
		gameboard[1][1] == gameboard[2][+2])) 
	{
		/* 
			Cross check
		*/
		EndScreen(x,y,x+1>2?(x+1)-3:x+1,y+1>2?(y+1)-3:y+1,x+2>2?(x+2)-3:x+2,y+2>2?(y+2)-3:y+2,playerturn, game);
	}else if((gameboard[y][x] == "X" || gameboard[y][x] == "O") &&
		(gameboard[0][2] == gameboard[1][1] &&
		gameboard[1][1] == gameboard[2][0])) 
	{
		/*
			Cross Check
		*/
		EndScreen(x,y,x-1<0?(x-1)+3:x-1,y+1>2?(y+1)-3:y+1,x-2<0?(x-2)+3:x-2,y+2>2?(y+2)-3:y+2,playerturn, game);
	}else {
		game(playerturn == 1 ? 2 : 1, "");
	}
}

void leaveMessage() {
	std::cout << "thanks for trying this out";
}

int game(int playerTurn, std::string err="") {
	bool isChosen = false;
	renderBoard();
	std::string input;

	std::cout << err;
	std::cout << "\n\n▶ type a coordinate - player : " << playerTurn << "\n";
	std::cout << "- ";
	
	std::cin >> input;
	std::string negPlayerSymbol  = playerTurn == 1 ? "O" : "X";

	int X=0;
	int Y=0;

	for(int y = 0; y <= 2; y++) {
		for(int x = 0; x <= 2; x++) {
			if(gameboard[y][x] == input) {
				X = x;
				Y = y;
				gameboard[y][x] = playerTurn == 1 ? "X" : "O";
				isChosen = true;
			}
		}
	}
	if(!isChosen) {
		game(playerTurn, "There could be only one thing. It's either you who typed invalid characters or someone who is blind to see a "+negPlayerSymbol);
	}else {
		checkforwinners(X,Y, playerTurn, game);
	}
	return 0;
}

int main() {
	game(1);
	std::atexit(leaveMessage);
}