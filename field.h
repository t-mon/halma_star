#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include "iterator.h"
#include "board.h"
#include "field.h"
#include "searchalgorithm.h"

using namespace std;

// forward declaration
class Iterator;
class Board;
class SearchAlgorithm;

class Field{
    friend ostream& operator<<(ostream&, const Field&);
    friend class Iterator;
    friend class Board;
    friend class SearchAlgorithm;
public:
    // the constructor of a field (by default all neighbors are 0 and the fieldnumber is 0)
    Field(int numField = 0, char dataOfField = '.', Field* previousField = 0, Field* nextField = 0, Field* dir_0_Field = 0, Field* dir_60_Field = 0, Field* dir_120_Field = 0, Field* dir_180_Field = 0, Field* dir_240_Field = 0, Field* dir_300_Field = 0);
    double getF();
    int getNumber();

private:
    // data from this field
    char data;              // the data of the field ( '.' for emty field, 'x' for player 1, 'o' for player 2 ...)
    int number;             // the fieldnumber

    double h;   // is the distance between the goalfield and the current field ( the actual heuristic)
    double g;   // is the numbers of steps already made tot the current field

    // generate pointer
    Field *next;            // go to the next field (fieldnumber+1), this is just to move once the hole board forward
    Field *previous;        // go to the previouse field (fieldnumber-1), this is just to move once the hole board forward

    // search tree fields
    Field* parent;          // the parent field in the search tree
    Field* child;           // the child field in the search tree

    // neighbors of this field
    Field *dir_0;       // the field in the 0 direction
    Field *dir_60;      // the field in the 60 direction
    Field *dir_120;     // the field in the 120 direction
    Field *dir_180;     // the field in the 180 direction
    Field *dir_240;     // the field in the 240 direction
    Field *dir_300;     // the field in the 300 direction

};

#endif // FIELD_H
