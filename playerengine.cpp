#include "playerengine.h"
#include "iterator.h"
#include "field.h"
#include "searchalgorithm.h"

PlayerEngine::PlayerEngine(Board &board, char playerSymbol)
    : m_board(board),m_playerSymbole(playerSymbol)
{

    m_goalField = m_board.getLast();
    m_groupDistance = 0;
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
    m_groupDistance = 0;

    Iterator it(m_board);
    it.resetToFirst();
    cout << endl << endl << "----------------------------------------------------------" << endl;

    // group distance:
    // 1. do the move for first figure
    // 2. than for each figure calculate the path, safe F of every move
    // 3. undo move , safe it with the group distance
    // 4. do the move for the next figure and continue with 2.
    //
    // 5. when we checked every figure make that move with the lowest group distance


    // for each of my figures make a pathfinding and add it to the resultList
    for(it.resetToFirst(); it.getCurrentField() != m_board.getLast(); ++it){
        if(it.getCurrentData() == m_playerSymbole){
            setGoalField(m_board);
            // search the best move for this figure
            SearchAlgorithm search(m_board,it.getCurrentField(),m_goalField);
            cout << "Search for Field " << it.getCurrentNumber();
            Field* currentSolution = search.findPath();
            // if we have a solution for this field
            if(currentSolution != 0){
                move solution_move;
                solution_move.from = it.getCurrentField();
                solution_move.to = currentSolution;
                //now make the move
                it.resetToFirst();
                while(it.getCurrentField() != solution_move.from){
                    ++it;
                }
                it.setCurrentData('.');
                it.resetToFirst();
                while(it.getCurrentField() != solution_move.to){
                    ++it;
                }
                it.setCurrentData(m_playerSymbole);
                cout << endl << "------------------------------- do the move and check the groupdistance" << endl;
                // and check every distance for every figure
                for(it.resetToFirst(); it.getCurrentField() != m_board.getLast(); ++it){
                    if(it.getCurrentData() == m_playerSymbole){
                        setGoalField(m_board);
                        SearchAlgorithm search(m_board,it.getCurrentField(),m_goalField);
                        cout << "Search for Field " << it.getCurrentNumber();
                        Field* currentSolution = search.findPath();
                        if(currentSolution != 0){
                            m_groupDistance = m_groupDistance + currentSolution->getF();
                        }
                    }
                }

                // undo move
                it.resetToFirst();
                while(it.getCurrentField() != solution_move.from){
                    ++it;
                }
                it.setCurrentData(m_playerSymbole);
                it.resetToFirst();
                while(it.getCurrentField() != solution_move.to){
                    ++it;
                }
                it.setCurrentData('.');

                solution_move.groupDistance = m_groupDistance;
                // now push the move to the result lists and sort it
                resultsList.sort(moveCompare);
                resultsList.push_back(solution_move);

                cout << "\tgroup distance for this move: " << m_groupDistance << endl << endl;
                m_groupDistance = 0;


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

    cout << endl << endl << "best move: MOVE FROM "<< moveToMake.from->getNumber() << " -> " << moveToMake.to->getNumber() << "\t\t for goalField: " << *m_goalField << endl;
    m_board.print();
}



//void PlayerEngine::doTurnMove()
//{
//    resultsList.clear();
//    m_groupDistance = 0;
//    Iterator it(m_board);
//    cout << endl << endl << "----------------------------------------------------------" << endl;

//    // group distance:
//    // 1. do the move for first figure
//    // 2. than for each figure calculate the path, safe F of every move
//    // 3. undo move , safe it with the group distance
//    // 4. do the move for the next figure and continue with 2.
//    //
//    // 5. when we checked every figure make that move with the lowest group distance


//    // for each of my figures make a pathfinding and add it to the resultList
//    for(it.resetToFirst(); it.getCurrentField() != m_board.getLast(); ++it){
//        if(it.getCurrentData() == m_playerSymbole){
//           setGoalField(m_board);
//            //cout << "goalfield = " << *m_goalField;
//            SearchAlgorithm search(m_board,it.getCurrentField(),m_goalField);
//            cout << "Search for Field " << it.getCurrentNumber();
//            Field* currentSolution = search.findPath();
//            if(currentSolution != 0){
//                move solution_move;
//                solution_move.from = it.getCurrentField();
//                solution_move.to = currentSolution;
//                resultsList.push_back(solution_move);
//                resultsList.sort(moveCompare);
//                cout << "Solution " << it.getCurrentNumber() << " = " << currentSolution->getNumber() << endl<< endl;
//                //m_board.print();

//            }else{
//                //cout << endl << "No solution for field " << it.getCurrentNumber() << endl;
//            }

//        }
//    }
//    //now make the best move
//    move moveToMake = resultsList.back();
//    it.resetToFirst();
//    while(it.getCurrentField() != moveToMake.from){
//        ++it;
//    }
//    it.setCurrentData('.');
//    it.resetToFirst();
//    while(it.getCurrentField() != moveToMake.to){
//        ++it;
//    }
//    it.setCurrentData(m_playerSymbole);

//    cout << endl << endl << "best move: MOVE FROM "<< moveToMake.from->getNumber() << " -> " << moveToMake.to->getNumber() << "\t\t for goalField: " << *m_goalField << endl;
//    m_board.print();
//}

bool PlayerEngine::moveCompare(move a, move b)
{
    return (a.groupDistance < b.groupDistance);
}

Field *PlayerEngine::setGoalField(Board &gameBoard)
{
    // look in the triangle for a free goalField
    Iterator it(gameBoard);
    it.resetToLast();
    for(int i = 0; i <= 10; i++){
        if(it.getCurrentData() == '.'){
            m_goalField = it.getCurrentField();
            return it.getCurrentField();
        }
        --it;
    }
    it.resetToLast();
    while(it.getCurrentNumber() != 104){
        --it;
    }
    m_goalField = it.getCurrentField();
    return it.getCurrentField();
}
