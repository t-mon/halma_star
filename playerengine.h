#ifndef PLAYERENGINE_H
#define PLAYERENGINE_H
#include "field.h"


class PlayerEngine
{
public:
    PlayerEngine();

private:
    Field* searchBestGoalField();

};

#endif // PLAYERENGINE_H
