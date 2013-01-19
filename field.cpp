#include "field.h"

// ****************************************************************************************************
// friend members

ostream& operator<<(ostream& ostr, const Field& field){
    ostr << field.number;
    return ostr;
}


// ****************************************************************************************************
// public members

Field::Field(int numField, char dataOfField, Field* previousField, Field* nextField, Field* dir_0_Field, Field* dir_60_Field, Field* dir_120_Field, Field* dir_180_Field, Field* dir_240_Field, Field* dir_300_Field){

    // inizialize private members
    previous = previousField;
    next = nextField;

    number = numField;
    data = dataOfField;

    h = 100;
    g = 100;

    dir_0 = dir_0_Field;
    dir_60 = dir_60_Field;
    dir_120 = dir_120_Field;
    dir_180 = dir_180_Field;
    dir_240 = dir_240_Field;
    dir_300 = dir_300_Field;

}

double Field::getF(){
    return g+h;
}

int Field::getH()
{
    return h;
}

int Field::getG()
{
    return g;
}

int Field::getNumber()
{
    return number;
}

char Field::getData()
{
    return data;
}

