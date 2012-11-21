#ifndef ITERATOR_H
#define ITERATOR_H

#include "board.h"
#include "field.h"

class Field;
class Board;
class SearchAlgorithm;

class Iterator
{
    friend class SearchAlgorithm;
public:
    Iterator(Board &board):gameBoard(board){resetToFirst();}
    // reset the iterator to the first field (field number 1)
    void resetToFirst();

    // insert a new field and make the previous and next connection for it
    void insert(int numField, char dataOfField, Field* previousField, Field* nextField, Field* dir_0_Field, Field* dir_60_Field, Field* dir_120_Field, Field* dir_180_Field, Field* dir_240_Field, Field* dir_300_Field);

    // movements
    int operator++();           // go with the iterator to the next fiel (actual fieldnumber +1)
    int operator--();           // go with the iterator to the previous fiel (actual fieldnumber -1)

    // read access methodes
    Field* getCurrentField();
    Field* get_dir_0_Field();
    Field* get_dir_60_Field();
    Field* get_dir_120_Field();
    Field* get_dir_180_Field();
    Field* get_dir_240_Field();
    Field* get_dir_300_Field();

    // this methode yields true or false for the field neighbors(dir=0,60,...,300)
    bool getPossibleDirectionsControl(int dir);

    void getPossibleDirections();       // this methode sets the privat boolean variables
    char getCurrentData();              // get the Data ( '.' or 'x', or 'o' ... )
    int  getCurrentNumber();             // get the current fieldnumber (the hole board goes from 1 to 121)

    // write access methodes
    void setNeighbors(Field* dir_0_Field, Field* dir_60_Field, Field* dir_120_Field, Field* dir_180_Field, Field* dir_240_Field, Field* dir_300_Field);
    void setCurrentData(char data);
    void setCurrentNumber(int numField);

    //this methods alow you to move the iterator in a cerain direction, dosent matter what there is
    int move_0_dir();
    int move_60_dir();
    int move_120_dir();
    int move_180_dir();
    int move_240_dir();
    int move_300_dir();

    // this methods alow the constructor to go and jump over a other field
    int go_0_dir();
    int go_60_dir();
    int go_120_dir();
    int go_180_dir();
    int go_240_dir();
    int go_300_dir();
    int go_dir(int dir);        // combination from the 6 methodes above(dir=0,...,300)

    // if one of this variable is true the iterator can go in this direction :)
    // if it is false, you cannot move in this direction :(
    bool dir_0_possible;
    bool dir_60_possible;
    bool dir_120_possible;
    bool dir_180_possible;
    bool dir_240_possible;
    bool dir_300_possible;


protected:
    Field* current;     // points to the current field
    Field* previous;    // points to the previous field

    Board &gameBoard;   // board to transverse with this iterator
};

#endif // ITERATOR_H
