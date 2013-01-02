#include "playerengine.h"
#include "iterator.h"
#include "field.h"
#include "searchalgorithm.h"

PlayerEngine::PlayerEngine(Board &board, char playerSymbol)
    : m_board(board),m_playerSymbole(playerSymbol)
{
    m_goalField = m_board.getLast();
}

void PlayerEngine::initFigures(){
    //delete ervery figure with symbol:
    Iterator it(m_board);
    for(it.resetToFirst(); it.getCurrentField() != m_board.getLast(); ++it){
        if(it.getCurrentData() == m_playerSymbole){
            it.setCurrentData('.');
        }
    }
    it.resetToFirst();

    // if this is player one:
    if(m_playerSymbole == 'x'){
        for(int i = 0; i < 10; i++){
            it.setCurrentData(m_playerSymbole);
            ++it;
        }

    }
}

void PlayerEngine::doTurnMove()
{
    resultsList.clear();
    Iterator it(m_board);

    // for each of my figures make a pathfinding and add it to the resultList
    for(it.resetToFirst(); it.getCurrentField() != m_board.getLast(); ++it){
        if(it.getCurrentData() == m_playerSymbole){
            SearchAlgorithm search(m_board,it.getCurrentField(),m_goalField);
            cout << endl << endl << "----------------------------------------------------------" << endl;
            cout << "Search for Field " << it.getCurrentNumber();
            Field* currentSolution = search.findPath();
            if(currentSolution != 0){
                move solution_move;
                solution_move.from = it.getCurrentField();
                solution_move.to = currentSolution;
                resultsList.push_back(solution_move);
                resultsList.sort(moveCompare);
                cout << endl << "Solution " << it.getCurrentNumber() << " = " << currentSolution->getNumber() << endl;
                m_board.print();

            }else{
                cout << endl << "No solution for field " << it.getCurrentNumber() << endl;
            }

        }
    }
    //now make the best move
    move moveToMake = resultsList.back();
    it.resetToFirst();
    while(it.getCurrentField() != moveToMake.from){
        ++it;
    }
    it.setCurrentData('.');
    it.resetToFirst();
    while(it.getCurrentField() != moveToMake.to){
        ++it;
    }
    it.setCurrentData(m_playerSymbole);

    cout << endl << endl << "best move: MOVE FROM "<< moveToMake.from->getNumber() << " -> " << moveToMake.to->getNumber() << endl;
    m_board.print();
}

bool PlayerEngine::moveCompare(move a, move b)
{
    return (a.to->getF() < b.to->getF());
}
