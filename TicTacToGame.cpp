#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Board
{
private:
    vector<int> cells;

public:
    Board() : cells(9, 0)
    {
        //this.cells = new vector<int>(9,0);
    }
    vector<int> getBoard()
    {
        return this->cells;
    }
    bool updateBoard(int loc, int symbol)
    {
        if (this->cells[loc - 1] != 0)
        {
            cout <<"!!!The cell is already taken. Please select a free cell"<<endl;
            return false;
        }
        if (symbol == 'X')
        {
            this->cells[loc - 1] = 1;
        }
        else
        {
            this->cells[loc - 1] = -1;
        }
        return true;
    }
    int checkColWin()
    {
        if (this->cells[0] == this->cells[3] && this->cells[3] == this->cells[6])
        {
            return (this->cells[0] + this->cells[3] + this->cells[6]);
        }
        if (this->cells[1] == this->cells[4] && this->cells[4] == this->cells[7])
        {
            return (this->cells[1] + this->cells[4] + this->cells[7]);
        }
        if (this->cells[2] == this->cells[5] && this->cells[5] == this->cells[8])
        {
            return (this->cells[2] + this->cells[5] + this->cells[8]);
        }
        return 0;
    }
    int checkRowWin()
    {
        if (this->cells[0] == this->cells[1] && this->cells[1] == this->cells[2])
        {
            return (this->cells[0] + this->cells[1] + this->cells[2]);
        }
        if (this->cells[3] == this->cells[4] && this->cells[4] == this->cells[5])
        {
            return (this->cells[3] + this->cells[4] + this->cells[5]);
        }
        if (this->cells[6] == this->cells[7] && this->cells[7] == this->cells[8])
        {
            return (this->cells[6] + this->cells[7] + this->cells[8]);
        }
        return 0;
    }
    int checkDiagonalWin()
    {
        if (this->cells[0] == this->cells[4] && this->cells[4] == this->cells[8])
        {
            return (this->cells[0] + this->cells[4] + this->cells[8]);
        }
        if (this->cells[2] == this->cells[4] && this->cells[4] == this->cells[6])
        {
            return (this->cells[2] + this->cells[4] + this->cells[6]);
        }
        return 0;
    }
    bool checkBoardStatus()
    {
        vector<int>::iterator it;
        it = find(this->cells.begin(), this->cells.end(), 0);
        if (it != this->cells.end())
        {
            return false;
        }
        return true;
    }
};

class Player
{
private:
    char symbol;

public:
    //static int numOfPlayers = 0;
    Player() {}
    Player(char symbol) : symbol(symbol)
    {
    }
    char getSymbol()
    {
        return this->symbol;
    }
    bool markCellOnBoard(Board *board, int loc)
    {
        if (loc >= 1 && loc <= 9)
        {
            return board->updateBoard(loc, symbol);
        }
        
        cout <<"Please select a valid cell number from the free cells\n";
        return false;
    }
};
class TicTacToeGame
{
private:
    Board *board;
    Player xPlayer, oPlayer;
    Player *currentPlayer;
public:
    TicTacToeGame(){ }
    bool initializeGame(vector<Player> players){
        if(players.size() > 2)
        {
            return false;
        }

        this->board = new Board();

        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].getSymbol() == 'X')
            {
                this->xPlayer = players[i];
                this->currentPlayer = &this->xPlayer;
            }
            else if (players[i].getSymbol() == 'O')
            {
                this->oPlayer = players[i];
            }
        }
        return true;

    }
    Player *getCurrentPlayer()
    {
        return this->currentPlayer;
    }

    bool checkWin()
    {
        if (this->board->checkColWin() == 3 || this->board->checkRowWin() == 3 || this->board->checkDiagonalWin() == 3)
        {
            if (this->currentPlayer->getSymbol() != 'X')
            {
                this->currentPlayer = &this->xPlayer;
            }
            return true;
        }

        if (this->board->checkColWin() == -3 || this->board->checkRowWin() == -3 || this->board->checkDiagonalWin() == -3)
        {
            if (this->currentPlayer->getSymbol() != 'O')
            {
                this->currentPlayer = &this->oPlayer;
            }
            return true;
        }
        return false;
    }
    bool isBoardFull()
    {
        return this->board->checkBoardStatus();
    }
    void printBoard()
    {
        vector<int> cells = this->board->getBoard();

        //cout << "\t\t=================================\n";
        cout << "\t\tPlayer 1 (X)  -  Player 2 (O)" << endl
             << endl;
        cout << endl;
        cout << "     |     |     " << endl;
        cout << "  " << (cells[0] == 0 ? "1" : (cells[0] == 1 ? "X" : "O")) << "  |  "
             << (cells[1] == 0 ? "2" : (cells[1] == 1 ? "X" : "O")) << "  |  "
             << (cells[2] == 0 ? "3" : (cells[2] == 1 ? "X" : "O")) << endl;

        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;

        cout << "  " << (cells[3] == 0 ? "4" : (cells[3] == 1 ? "X" : "O")) << "  |  "
             << (cells[4] == 0 ? "5" : (cells[4] == 1 ? "X" : "O")) << "  |  "
             << (cells[5] == 0 ? "6" : (cells[5] == 1 ? "X" : "O")) << endl;

        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;

        cout << "  " << (cells[6] == 0 ? "7" : cells[6] == 1 ? "X" : "O") << "  |  "
             << (cells[7] == 0 ? "8" : (cells[7] == 1 ? "X" : "O")) << "  |  "
             << (cells[8] == 0 ? "9" : (cells[8] == 1 ? "X" : "O")) << endl;

        cout << "     |     |     " << endl
             << endl;
    }
    Board *getBoard()
    {
        return this->board;
    }
    void switchPlayer()
    {
        if (this->currentPlayer->getSymbol() == 'X')
        {
            this->currentPlayer = &this->oPlayer;
        }
        else
        {
            this->currentPlayer = &this->xPlayer;
        }
    }
    ~TicTacToeGame()
    {
        delete this->board;
    }
};

int main()
{
    cout << "Welcome to tic tac toe game\n";


    Player p1('X'), p2('O');

    vector<Player> players;
    players.push_back(p1);
    players.push_back(p2);
    TicTacToeGame game = TicTacToeGame();
    if(!game.initializeGame(players))
    {
        cout << "Tic Tac Toe game can only have two players\n";
        return 0;
    }

    do
    {
        game.printBoard();
        int loc;
        do
        {
            cout << "Enter the location for Player with symbol " << game.getCurrentPlayer()->getSymbol() << ":" << endl;
            cin >> loc;
        } while (!game.getCurrentPlayer()->markCellOnBoard(game.getBoard(), loc));

        game.switchPlayer();

    } while (!game.checkWin() && !game.isBoardFull());

    if (game.isBoardFull() && !game.checkWin())
    {
        game.printBoard();
        cout << "The game was draw\n";
    }
    else
    {
        game.printBoard();
        string str = "";
        if(game.getCurrentPlayer()->getSymbol() == 'X')
        {
            str = "Player 1";
        }
        else
        {
            str = "Player 2";
        }
        
        cout << str<<" ("<<game.getCurrentPlayer()->getSymbol()<< "s) has won the game\n";
    }

    return 0;
}