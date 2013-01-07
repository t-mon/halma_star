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

    bool gameStillOn = true;
    while(1){
        cout << endl << endl << "================================================================================" << endl;
        char a;
        cin >> a;
        gameStillOn=playerOne->doTurnMove();
        if(gameStillOn == false){
            cout << "================\n    GAME OVER     \n================" << endl;
            break;
        }
        cout << endl << endl << "================================================================================" << endl;
        cin >> a;
        gameStillOn=playerTwo->doTurnMove();
        if(gameStillOn == false){
            cout << "================\n    GAME OVER     \n================" << endl;
            break;
        }
    }
}
