#ifndef PLAYERENGINE_H
#define PLAYERENGINE_H
#include "field.h"
#include "board.h"

struct move{
    Field* from;
    Field* to;
    float groupDistance;
};

class PlayerEngine
{
public:
    PlayerEngine(Board &board, char playerSymbol = 'x');
    void initFigures();
    bool doTurnMove();

    static bool moveCompare(move a, move b);

private:
    Field* m_goalField;
    Board &m_board;
    char m_playerSymbole;

    float m_groupDistance;

    Field* setGoalField(Board &gameBoard);
    bool isPotentialGoalField(Field* currentField);

    list <move> resultsList;


};

#endif // PLAYERENGINE_H
