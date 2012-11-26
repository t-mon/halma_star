#include <iostream>
#include "board.h"
#include "iterator"
#include "fileparser.h"
#include "searchalgorithm.h"

using namespace std;

int main(){

    FileParser pareser("../halma_star/Graph.txt");
    Board gameBoard = pareser.parse();



    Iterator gameIterator(gameBoard);
//    gameIterator.resetToFirst();
//    gameIterator.setCurrentData('x');
//    gameIterator.go_240_dir();
//    gameIterator.go_240_dir();
//    gameIterator.go_240_dir();
//    gameIterator.go_240_dir();
//    gameIterator.go_240_dir();
//    gameIterator.go_0_dir();
//    gameIterator.go_0_dir();
//    gameIterator.go_0_dir();
//    gameIterator.go_0_dir();
//    gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();
//    gameIterator.go_0_dir();
//    gameIterator.go_0_dir();
//    gameIterator.go_0_dir();
//    gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_180_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_300_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();gameIterator.setCurrentData('o');
//    gameIterator.go_0_dir();
//    gameIterator.setCurrentData('o');




    gameIterator.getPossibleDirections();

    Iterator startFieldIterator(gameBoard);
    Iterator goalFieldIterator(gameBoard);
    startFieldIterator.resetToFirst();
    goalFieldIterator.resetToFirst();

    int start = 0;
    int goal = 0;
    cout << "startfield = ";
    cin >> start;
    cout << endl;

    cout << "goalfield = ";
    cin >> goal;
    cout << endl;

    while(startFieldIterator.getCurrentNumber() != start){
        ++startFieldIterator;
        ++gameIterator;

    }

    while(goalFieldIterator.getCurrentNumber() != goal){
        ++goalFieldIterator;
    }



    //    for(int i = 0; i < 6; i++){
    //        goalFieldIterator.go_240_dir();
    //    }
    //    for(int i = 0; i < 6; i++){
    //        goalFieldIterator.go_300_dir();
    //    }

    SearchAlgorithm suche(gameBoard,startFieldIterator.getCurrentField(),goalFieldIterator.getCurrentField());
    //    suche.startHeuristicsCircular();
    cout << "Current goalfield = " << goalFieldIterator.getCurrentNumber() << endl;
    //    suche.print();
    suche.setRandomStones(50);
    suche.findPath();
    gameIterator.resetToFirst();
    gameIterator.setCurrentData('x');

    cout << endl << endl << "field: " << gameIterator.getCurrentNumber() << endl;
    gameBoard.print();
    cout << "to move the \"x\" press: d = 0, e = 60, w = 120, a = 180, y = 240, x = 300" << endl;


    char direction;

    while(gameIterator.getCurrentField() != suche.getGoalField()){
        cin >> direction;

        switch(direction){
        case 'd':
            gameIterator.setCurrentData('.');
            gameIterator.move_0_dir();
            gameIterator.setCurrentData('x');
            gameIterator.getPossibleDirections();
            break;
        case 'e':
            gameIterator.setCurrentData('.');
            gameIterator.move_60_dir();
            gameIterator.setCurrentData('x');
            gameIterator.getPossibleDirections();
            break;
        case 'w':
            gameIterator.setCurrentData('.');
            gameIterator.move_120_dir();
            gameIterator.setCurrentData('x');
            gameIterator.getPossibleDirections();
            break;
        case 'a':
            gameIterator.setCurrentData('.');
            gameIterator.move_180_dir();
            gameIterator.setCurrentData('x');
            gameIterator.getPossibleDirections();
            break;
        case 'y':
            gameIterator.setCurrentData('.');
            gameIterator.move_240_dir();
            gameIterator.setCurrentData('x');
            gameIterator.getPossibleDirections();
            break;
        case 'x':
            gameIterator.setCurrentData('.');
            gameIterator.move_300_dir();
            gameIterator.setCurrentData('x');
            gameIterator.getPossibleDirections();
            break;
        }
        cout << endl << endl << "field: " << gameIterator.getCurrentNumber() << endl;
        gameBoard.print();
        cout << "to move press: d = 0, e = 60, w = 120, a = 180, y = 240, x = 300" << endl;

    }
    return 0;
}
