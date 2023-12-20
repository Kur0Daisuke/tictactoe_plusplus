#include <iostream>
#include <vector>

std::string gameboard[3][3] = {
        { " ", " ", " " },
        { " ", " ", " " },
        { " ", " ", " " }
};

void renderBoard(std::string board[3][3]) {
    std::vector<std::string> torender;
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            torender.push_back(board[x][y]);
        }
    }
    std::cout <<"   1      2     3  \n"
                "       |     |     \n"
                "1  "<< torender[0] <<"   |  "<< torender[1] <<"  |  "<< torender[2] <<"  \n"
                "  _____|_____|_____\n"
                "       |     |     \n"
                "2  "<< torender[3] <<"   |  "<< torender[4] <<"  |  "<< torender[5] <<"  \n"
                "  _____|_____|_____\n"
                "       |     |     \n"
                "3  "<< torender[6] <<"   |  "<< torender[7] <<"  |  "<< torender[8] <<"  \n"
                "       |     |     \n";
}

void game(int playerTurn, std::string err="") {
    renderBoard(gameboard);
    int x;
    int y;

    std::cout << err << "\n";

    std::cout << "X coordinate of where player " << playerTurn << " will place \n";
    std::cout << "Type 1, 2 or 3" << "\n";
    std::cin >> x;

    std::cout << "Y coordinate of where player " << playerTurn << " will place \n";
    std::cout << "Type 1, 2 or 3" << "\n";
    std::cin >> y;

    if(gameboard[x-1][y-1] != " " || x > 3 || y > 3) {
        game(playerTurn,"seems like you've done something illegal, Retry");
    }else {
        gameboard[x-1][y-1] = playerTurn == 1 ? "X" : "O";
        game(playerTurn == 1 ? 2 : 1);
    }
}

int main() {
    game(1);

}