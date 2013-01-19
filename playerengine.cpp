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

    // if this is player one:
    if(m_playerSymbole == 'x'){
        it.resetToFirst();
        for(int i = 0; i < 10; i++){
            it.setCurrentData(m_playerSymbole);
            ++it;
        }
    }

    // if this is player two:
    if(m_playerSymbole == 'o'){
        it.resetToLast();
        for(int i = 0; i < 10; i++){
            it.setCurrentData(m_playerSymbole);
            --it;
        }
    }

}

bool PlayerEngine::doTurnMove()
{
    resultsList.clear();
    m_groupDistance = 0;

    Iterator it(m_board);
    it.resetToFirst();
    Iterator it2(m_board);
    it2.resetToFirst();

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
            cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "goal field:" << *m_goalField << endl;
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
                Iterator it4(m_board);
                it4.resetToFirst();
                while(it4.getCurrentField() != solution_move.from){
                    ++it4;
                }
                it4.setCurrentData('.');
                it4.resetToFirst();
                while(it4.getCurrentField() != solution_move.to){
                    ++it4;
                }
                it4.setCurrentData(m_playerSymbole);

                cout << endl << "******************************************* do the move and check the groupdistance" << endl;
                // and check every distance for every figure

                int countPossibleMoves = 0;
                for(it2.resetToFirst(); it2.getCurrentField() != m_board.getLast(); ++it2){
                    if(it2.getCurrentData() == m_playerSymbole){
                        setGoalField(m_board);
                        SearchAlgorithm searchDeep(m_board,it2.getCurrentField(),m_goalField);
                        cout << "Search for Field " << it2.getCurrentNumber();
                        Field* middleSolution = searchDeep.findPath();
                        if(middleSolution != 0){
                            countPossibleMoves++;
                            m_groupDistance = m_groupDistance + middleSolution->getH();
                        }
                    }
                }

                //m_groupDistance = m_groupDistance/countPossibleMoves;
                // undo move
                Iterator it3(m_board);
                it3.resetToFirst();
                while(it3.getCurrentField() != solution_move.from){
                    ++it3;
                }
                it3.setCurrentData(m_playerSymbole);
                it3.resetToFirst();
                while(it3.getCurrentField() != solution_move.to){
                    ++it3;
                }
                it3.setCurrentData('.');

                solution_move.groupDistance = m_groupDistance;
                // now push the move to the result lists and sort it
                resultsList.sort(moveCompare);
                resultsList.push_back(solution_move);
                cout << "undo the move" << endl;
                cout << "\tgroup distance for this move: " << m_groupDistance << " | checked for: " << countPossibleMoves << " moves " << endl << endl;
                m_groupDistance = 0;
            }
        }
    }
    //now make the best move
    resultsList.sort(moveCompare);

    if(resultsList.empty()){
        cout << "ERROR: Game over, list of possible moves is empty, the goalfield is not reachable :(" << endl;
        return false;
    }

    // print the resultlist for controll
    cout << "List of best moves for each figure an the groupdistance" << endl;
    for(list<move>::iterator listit = resultsList.begin(); listit != resultsList.end(); listit++){
        move current = *listit;
        cout << "\t" << *current.from << "->" << *current.to << " group distance:" << current.groupDistance << endl;
    }

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

    cout << endl << endl << "best move for player "<< m_playerSymbole << ": MOVE FROM "<< moveToMake.from->getNumber() << " -> " << moveToMake.to->getNumber() << "\t\t for goalField: " << *m_goalField << endl;
    m_board.print();
    return true;
}

bool PlayerEngine::moveCompare(move a, move b)
{
    return (a.groupDistance > b.groupDistance);
}

Field *PlayerEngine::setGoalField(Board &gameBoard)
{
    if(m_playerSymbole == 'x'){
        // look in the triangle for a free and reachable goalField
        Iterator it(gameBoard);
        it.resetToLast();
        for(int i = 0; i <= 10; i++){
            if(it.getCurrentData() == '.'){
                if(isPotentialGoalField(it.getCurrentField())){
                    m_goalField = it.getCurrentField();
                    return it.getCurrentField();
                }
            }
            --it;
        }
        it.resetToLast();
        while(it.getCurrentNumber() != 104){
            --it;
        }
        if(isPotentialGoalField(it.getCurrentField())){
            m_goalField = it.getCurrentField();
            return it.getCurrentField();
        }
    }
    if(m_playerSymbole == 'o'){
        // look in the triangle for a free and reachable goalField
        Iterator it(gameBoard);
        it.resetToFirst();
        for(int i = 0; i <= 10; i++){
            if(it.getCurrentData() == '.'){
                if(isPotentialGoalField(it.getCurrentField())){
                    m_goalField = it.getCurrentField();
                    return it.getCurrentField();
                }
            }
            ++it;
        }
        it.resetToLast();
        while(it.getCurrentNumber() != 17){
            ++it;
        }
        if(isPotentialGoalField(it.getCurrentField())){
            m_goalField = it.getCurrentField();
            return it.getCurrentField();
        }
    }

}

bool PlayerEngine::isPotentialGoalField(Field *currentField)
{

    if(currentField->dir_0 != 0){
        if(currentField->dir_0->getData() == '.'){
            return true;
        }
        if(currentField->dir_0->dir_0 != 0){
            if(currentField->dir_0->dir_0->getData() == '.'){
                return true;
            }
        }
    }

    if(currentField->dir_60 != 0){
        if(currentField->dir_60->getData() == '.'){
            return true;
        }
        if(currentField->dir_60->dir_60 != 0){
            if(currentField->dir_60->dir_60->getData() == '.'){
                return true;
            }
        }
    }

    if(currentField->dir_120 != 0){
        if(currentField->dir_120->getData() == '.'){
            return true;
        }
        if(currentField->dir_120->dir_120 != 0){
            if(currentField->dir_120->dir_120->getData() == '.'){
                return true;
            }
        }
    }

    if(currentField->dir_180 != 0){
        if(currentField->dir_180->getData() == '.'){
            return true;
        }
        if(currentField->dir_180->dir_180 != 0){
            if(currentField->dir_180->dir_180->getData() == '.'){
                return true;
            }
        }
    }

    if(currentField->dir_240 != 0){
        if(currentField->dir_240->getData() == '.'){
            return true;
        }
        if(currentField->dir_240->dir_240 != 0){
            if(currentField->dir_240->dir_240->getData() == '.'){
                return true;
            }
        }
    }

    if(currentField->dir_300 != 0){
        if(currentField->dir_300->getData() == '.'){
            return true;
        }
        if(currentField->dir_300->dir_300 != 0){
            if(currentField->dir_300->dir_300->getData() == '.'){
                return true;
            }
        }
    }
    return false;

}
