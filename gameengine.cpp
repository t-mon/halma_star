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

    cout << "player one init" << endl;
    playerOne->initFigures();
    gameBoard.print();
    while(1){
        playerOne->doTurnMove();
        char a;
        cin >> a;
    }


}
