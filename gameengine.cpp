#include "gameengine.h"
#include <iostream>
#include "board.h"
#include "iterator"
#include "fileparser.h"
#include "searchalgorithm.h"
#include "playerengine.h"

using namespace std;


GameEngine::GameEngine()
{
    FileParser pareser("../halma_star/Graph.txt");
    Board gameBoard = pareser.parse();

    PlayerEngine* playerOne = new PlayerEngine(gameBoard,'x');
    PlayerEngine* playerTwo = new PlayerEngine(gameBoard,'o');


    cout << "player one init" << endl;
    playerOne->initFigures();

    cout << "player two init" << endl;
    playerTwo->initFigures();
    gameBoard.print();
    while(1){
        cout << endl << endl << "================================================================================" << endl;
        char a;
        cin >> a;
        playerOne->doTurnMove();
        cout << endl << endl << "================================================================================" << endl;
        cin >> a;
        playerTwo->doTurnMove();

    }
}
