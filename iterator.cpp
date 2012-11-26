#include "iterator.h"

using namespace std;

// ****************************************************************************************************
// public members

void Iterator::resetToFirst(){
    previous = 0;
    current = gameBoard.first;
}

// insert a new field after the actual field in the board and make the previous and next connection
void Iterator::insert(int numField, char dataOfField, Field* previousField, Field* nextField, Field* dir_0_Field, Field* dir_60_Field, Field* dir_120_Field, Field* dir_180_Field, Field* dir_240_Field, Field* dir_300_Field){
    Field *p = gameBoard.newField(numField,dataOfField,previousField,nextField, dir_0_Field, dir_60_Field, dir_120_Field, dir_180_Field, dir_240_Field, dir_300_Field);

    // if the board is emty the new field is the first and last of the board
    if (gameBoard.isEmpty()){
        gameBoard.first = p;
        gameBoard.last  = p;
    }else{
        // new field is not the first field
        if (current==gameBoard.last){
            gameBoard.last=p;
        }
        // connect the new field with the current field
        p->next = current->next;
        p->previous = current;
        current->next = p;
    }
}

// move to the next field with the iterator (current field data + 1)
int Iterator::operator ++()
{
    if (current == NULL)		// reset current pointer
        if (previous == NULL)
            current = gameBoard.first;
        else
            current = previous->next;
    else				// advance current pointer
    {
        previous = current;
        current = current->next;
    }
    return (current != NULL);
}

// move to the next field with the iterator (current field data - 1)
int Iterator::operator --()
{
    if (current == NULL)		// reset current pointer
        if (previous == NULL)
            current = gameBoard.first;
        else
            current = previous->next;
    else				// move current pointer backwards
    {
        previous = previous->previous;
        current = current->previous;
    }
    return (current != NULL);
}



// get informations of the field and neighborfields
Field *Iterator::getCurrentField(){
    return current;
}

Field *Iterator::get_dir_0_Field(){
    return current->dir_0;
}

Field *Iterator::get_dir_60_Field(){
    return current->dir_60;
}

Field *Iterator::get_dir_120_Field(){
    return current->dir_120;
}

Field *Iterator::get_dir_180_Field(){
    return current->dir_180;
}

Field *Iterator::get_dir_240_Field(){
    return current->dir_240;
}

Field *Iterator::get_dir_300_Field(){
    return current->dir_300;
}

// this methode sets the boolean variables whitch indicate the possible movedirections from the current field
void Iterator::getPossibleDirections(){
    // controll if i can move in direction 0,60,120...

    // can i move in 0 direction?
    // if neighbour = 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is also occupied
    if((current->dir_0 == 0) || (current->dir_0->data != '.' && current->dir_0->dir_0 == 0) || (current->dir_0->data != '.' && current->dir_0->dir_0->data != '.')){
        // No, i can't move in this direction
        dir_0_possible = false;
    }else{
        dir_0_possible = true;
    }

    // can i move in 60 direction?
    // if neighbour = 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is also occupied
    if((current->dir_60 == 0) || (current->dir_60->data != '.' && current->dir_60->dir_60 == 0) || (current->dir_60->data != '.' && current->dir_60->dir_60->data != '.')){
        // No, i can't move in this direction
        dir_60_possible = false;
    }else{
        dir_60_possible = true;
    }

    // can i move in 120 direction?
    // if neighbour = 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is also occupied
    if((current->dir_120 == 0) || (current->dir_120->data != '.' && current->dir_120->dir_120 == 0) || (current->dir_120->data != '.' && current->dir_120->dir_120->data != '.')){
        // No, i can't move in this direction
        dir_120_possible = false;
    }else{
        dir_120_possible = true;
    }

    // can i move in 180 direction?
    // if neighbour = 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is also occupied
    if((current->dir_180 == 0) || (current->dir_180->data != '.' && current->dir_180->dir_180 == 0) || (current->dir_180->data != '.' && current->dir_180->dir_180->data != '.')){
        // No, i can't move in this direction
        dir_180_possible = false;
    }else{
        dir_180_possible = true;
    }

    // can i move in 240 direction?
    // if neighbour = 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is also occupied
    if((current->dir_240 == 0) || (current->dir_240->data != '.' && current->dir_240->dir_240 == 0) || (current->dir_240->data != '.' && current->dir_240->dir_240->data != '.')){
        // No, i can't move in this direction
        dir_240_possible = false;
    }else{
        dir_240_possible = true;
    }

    // can i move in 300 direction?
    // if neighbour = 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is 0 (is a boarder) || neigbour occupied ( with x or o) AND neighbours neighbour is also occupied
    if((current->dir_300 == 0) || (current->dir_300->data != '.' && current->dir_300->dir_300 == 0) || (current->dir_300->data != '.' && current->dir_300->dir_300->data != '.')){
        // No, i can't move in this direction
        dir_300_possible = false;
    }else{
        dir_300_possible = true;
    }

//    // print out which possibilitys i have to move from current field
//    cout << "possible move directions from current field: " << endl;
//    if(dir_0_possible){
//        cout << "\t-> direction 0" << endl;
//    }
//    if(dir_60_possible){
//        cout << "\t-> direction 60" << endl;
//    }
//    if(dir_120_possible){
//        cout << "\t-> direction 120" << endl;
//    }
//    if(dir_180_possible){
//        cout << "\t-> direction 180" << endl;
//    }
//    if(dir_240_possible){
//        cout << "\t-> direction 240" << endl;
//    }
//    if(dir_300_possible){
//        cout << "\t-> direction 300" << endl;
//    }
//    cout << endl;
}

/*
  Methode: go_dir
  Arguments: (int)dir (=direction)
  Description:
        Go in this direction if possible
  Return: 0 (could go this direction), 1 (couldn't go this direction)
  by Lukas Holzinger @ 12.11.2012, 18:00
  */
int Iterator::go_dir(int dir)
{

    switch(dir){
    case 0:
        return this->go_0_dir();
        break;
    case 60:
        return this->go_60_dir();
        break;
    case 120:
        return this->go_120_dir();
        break;
    case 180:
        return this->go_180_dir();
        break;
    case 240:
        return this->go_240_dir();
        break;
    case 300:
        return this->go_300_dir();
        break;
    default:
        return 0;
    }
}

/*
  Methode: getPossibleDirectionsControl
  Arguments: (int)dir (=direction)
  Description:
        If the movement in direction is possible return bool value
  Return: bool true (could go this direction), false (couldn't go this direction)
  by Lukas Holzinger @ 12.11.2012, 18:00
  */
bool Iterator::getPossibleDirectionsControl(int dir){
    switch(dir){
    case 0:
        return this->dir_0_possible;
        break;
    case 60:
        return this->dir_60_possible;
        break;
    case 120:
        return this->dir_120_possible;
        break;
    case 180:
        return this->dir_180_possible;
        break;
    case 240:
        return this->dir_240_possible;
        break;
    case 300:
        return this->dir_300_possible;
        break;
    default:
        return false;
    }
}

char Iterator::getCurrentData(){
    return current->data;
}

int Iterator::getCurrentNumber(){
    return current->number;
}

// set the neighbours of the current field
void Iterator::setNeighbors(Field* dir_0_Field, Field* dir_60_Field, Field* dir_120_Field, Field* dir_180_Field, Field* dir_240_Field, Field* dir_300_Field){
    if(dir_0_Field!=0)  current->dir_0   = dir_0_Field;
    if(dir_60_Field!=0) current->dir_60  = dir_60_Field;
    if(dir_120_Field!=0)current->dir_120 = dir_120_Field;
    if(dir_180_Field!=0)current->dir_180 = dir_180_Field;
    if(dir_240_Field!=0)current->dir_240 = dir_240_Field;
    if(dir_300_Field!=0)current->dir_300 = dir_300_Field;
}

// set the data which gets printed
void Iterator::setCurrentData(char data){
    current->data = data;
}

void Iterator::setCurrentNumber(int numField){
    current->number = numField;
}

// move with the iterator in this direction (not jumping)
int Iterator::move_0_dir(){
    if(current->dir_0 == 0){
        return 1;
    }else{
        current = current->dir_0;
        previous = current->dir_180;
        return 0;
    }
}

// move with the iterator in this direction (not jumping)
int Iterator::move_60_dir(){
    if(current->dir_60 == 0){
        return 1;
    }else{
        current = current->dir_60;
        previous = current->dir_180;
        return 0;
    }
}

// move with the iterator in this direction (not jumping)
int Iterator::move_120_dir(){
    if(current->dir_120 == 0){
        return 1;
    }else{
        current = current->dir_120;
        previous = current->dir_180;
        return 0;
    }
}

// move with the iterator in this direction (not jumping)
int Iterator::move_180_dir(){
    if(current->dir_180 == 0){
        return 1;
    }else{
        current = current->dir_180;
        previous = current->dir_180;
        return 0;
    }
}

// move with the iterator in this direction (not jumping)
int Iterator::move_240_dir(){
    if(current->dir_240 == 0){
        return 1;
    }else{
        current = current->dir_240;
        previous = current->dir_180;
        return 0;
    }
}

// move with the iterator in this direction (not jumping)
int Iterator::move_300_dir(){
    if(current->dir_300 == 0){
        return 1;
    }else{
        current = current->dir_300;
        previous = current->dir_180;
        return 0;
    }
}

// move the iterator in 0-direction (try to jump!!!)
int Iterator::go_0_dir(){
    // if this neighbor doesnt exist or the neighbour is occupied and the next neighbour is it too do nothing
    if ((current->dir_0 == 0) || (current->dir_0->data != '.' && current->dir_0->dir_0 == 0) || (current->dir_0->data != '.' && current->dir_0->dir_0->data != '.')){
        //cout << endl << endl << "cannot go in this direction... :(" << endl;
        return 1;
    }else{
        // if the neighbour is occupied, but the next neighbour isnt jump over the neighbour
        if(current->dir_0->data != '.' && current->dir_0->dir_0->data == '.'){
            current = current->dir_0;
            previous = current->dir_180;
            current = current->dir_0;
            previous = current->dir_180;
            return 0;
            // else nobody is in the next field
        }else{
            current = current->dir_0;
            previous = current->dir_180;
            return 0;
        }

    }
}

// move the iterator in 60-direction (try to jump!!!)
int Iterator::go_60_dir(){
    // if this neighbor doesnt exist or the neighbour is occupied and the next neighbour is it too do nothing
    if ((current->dir_60 == 0)  || (current->dir_60->data != '.' && current->dir_60->dir_60 == 0) || (current->dir_60->data != '.' && current->dir_60->dir_60->data != '.')){
        //cout << endl << endl << "cannot go in this direction... :(" << endl;
        return 1;
    }else{
        // if the neighbour is occupied, but the next neighbour isnt jump over the neighbour
        if(current->dir_60->data != '.' && current->dir_60->dir_60->data == '.'){
            current = current->dir_60;
            previous = current->dir_180;
            current = current->dir_60;
            previous = current->dir_180;
            return 0;
            // else nobody is in the next field
        }else{
            current = current->dir_60;
            previous = current->dir_180;
            return 0;
        }

    }
}

// move the iterator in 120-direction (try to jump!!!)
int Iterator::go_120_dir(){
    // if this neighbor doesnt exist or the neighbour is occupied and the next neighbour is it too do nothing
    if ((current->dir_120 == 0) || (current->dir_120->data != '.' && current->dir_120->dir_120 == 0) || (current->dir_120->data != '.' && current->dir_120->dir_120->data != '.')){
        //cout << endl << endl << "cannot go in this direction... :(" << endl;
        return 1;
    }else{
        // if the neighbour is occupied, but the next neighbour isnt jump over the neighbour
        if(current->dir_120->data != '.' && current->dir_120->dir_120->data == '.'){
            current = current->dir_120;
            previous = current->dir_180;
            current = current->dir_120;
            previous = current->dir_180;
            return 0;
            // else nobody is in the next field
        }else{
            current = current->dir_120;
            previous = current->dir_180;
            return 0;
        }

    }
}

// move the iterator in 180-direction (try to jump!!!)
int Iterator::go_180_dir(){
    // if this neighbor doesnt exist or the neighbour is occupied and the next neighbour is it too do nothing
    if ((current->dir_180 == 0) || (current->dir_180->data != '.' && current->dir_180->dir_180 == 0) || (current->dir_180->data != '.' && current->dir_180->dir_180->data != '.')){
        //cout << endl << endl << "cannot go in this direction... :(" << endl;
        return 1;
    }else{
        // if the neighbour is occupied, but the next neighbour isnt jump over the neighbour
        if(current->dir_180->data != '.' && current->dir_180->dir_180->data == '.'){
            current = current->dir_180;
            previous = current->dir_180;
            current = current->dir_180;
            previous = current->dir_180;
            return 0;
            // else nobody is in the next field
        }else{
            current = current->dir_180;
            previous = current->dir_180;
            return 0;
        }

    }
}

// move the iterator in 240-direction (try to jump!!!)
int Iterator::go_240_dir(){
    // if this neighbor doesnt exist or the neighbour is occupied and the next neighbour is it too do nothing
    if ((current->dir_240 == 0) || (current->dir_240->data != '.' && current->dir_240->dir_240 == 0) || (current->dir_240->data != '.' && current->dir_240->dir_240->data != '.')){
        //cout << endl  << endl << "cannot go in this direction... :(" << endl;
        return 1;
    }else{
        // if the neighbour is occupied, but the next neighbour isnt jump over the neighbour
        if(current->dir_240->data != '.' && current->dir_240->dir_240->data == '.'){
            current = current->dir_240;
            previous = current->dir_180;
            current = current->dir_240;
            previous = current->dir_180;
            return 0;
            // else nobody is in the next field
        }else{
            current = current->dir_240;
            previous = current->dir_180;
            return 0;
        }
    }
}

// move the iterator in 300-direction (try to jump!!!)
int Iterator::go_300_dir(){
    // if this neighbor doesnt exist or the neighbour is occupied and the next neighbour is it too do nothing
    if ((current->dir_300 == 0)  || (current->dir_300->data != '.' && current->dir_300->dir_300 == 0) || (current->dir_300->data != '.' && current->dir_300->dir_300->data != '.')){
        //cout << endl << endl << "cannot go in this direction... :(" << endl;
        return 1;
    }else{
        // if the neighbour is occupied, but the next neighbour isnt jump over the neighbour
        if(current->dir_300->data != '.' && current->dir_300->dir_300->data == '.'){
            current = current->dir_300;
            previous = current->dir_180;
            current = current->dir_300;
            previous = current->dir_180;
            return 0;
            // else nobody is in the next field
        }else{
            current = current->dir_300;
            previous = current->dir_180;
            return 0;
        }

    }
}


