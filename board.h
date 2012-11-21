#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include "field.h"
#include "iterator.h"

// forward declaration
class Iterator;
class Field;

class Board
{
    friend class Iterator;
public:
    Board();
    ~Board();
    bool isEmpty();         // returns true if the board is emtpty

    //CHANGE
    void print();           // prints the hole field to stdout

    void print_h();         // prints the hole field to stdout with the heuristic values

protected:
    Field* first;       // the first field in the board (1)
    Field* last;        // the last field in the board  (121)

    Field* newField(int &numField, char &dataOfField, Field* previousField, Field* nextField, Field* dir_0_Field, Field* dir_60_Field, Field* dir_120_Field, Field* dir_180_Field, Field* dir_240_Field, Field* dir_300_Field);
};

#endif // BOARD_H
