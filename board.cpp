#include "board.h"

using namespace std;

// ****************************************************************************************************
// public members

Board::Board(){
    // inizialise the first an last field of the board with 0 (create a emty board)
    first = 0;
    last = 0;

}



Board::~Board(){
    /*
      Change from
        Field* temp;
      To
        Field* temp = new Field;
      by Lukas Holzinger @ 12.11.2012, 18:00
      */
    Field *temp = new Field;
    // go through the list form the front
    for (Field *n = first; n; ){
        // actual point ist tmp
        temp = n;
        // go to the next field
        n = n->next;
        /*
          Move
            delete temp;
          out of the FORloop
          by Lukas Holzinger @ 12.11.2012, 18:00
          */
    }
    // and delete the temp field
    delete temp;
}

bool Board::isEmpty(){
    // returns true if there is no Field in the board
    return (first == 0);
}

// prints the current board situation
void Board::print(){
    // go through the list
    cout << endl;
    cout << endl;
    Field* n = first;
    // 1. line
    cout << "                        " << n->data << endl;
    n = n->next;

    // 2. line
    cout << "                       " << n->data;
    n = n->next;
    cout << " " << n->data << endl;
    n = n->next;

    // 3. line
    cout << "                      " << n->data;
    for(int i = 0; i < 2; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 4. line
    cout << "                     " << n->data;
    for(int i = 0; i < 3; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 5. line
    cout << "            " << n->data;
    for(int i = 0; i < 12; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 6. line
    cout << "             " << n->data;
    for(int i = 0; i < 11; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 7. line
    cout << "              " << n->data;
    for(int i = 0; i < 10; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 8. line
    cout << "               " << n->data;
    for(int i = 0; i < 9; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 9. line
    cout << "                " << n->data;
    for(int i = 0; i < 8; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 10. line
    cout << "               " << n->data;
    for(int i = 0; i < 9; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 11. line
    cout << "              " << n->data;
    for(int i = 0; i < 10; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 12. line
    cout << "             " << n->data;
    for(int i = 0; i < 11; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 13. line
    cout << "            " << n->data;
    for(int i = 0; i < 12; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 14. line
    cout << "                     " << n->data;
    for(int i = 0; i < 3; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;

    // 15. line
    cout << "                      " << n->data;
    for(int i = 0; i < 2; i++){
        n = n->next;
        cout << " " << n->data;
    }
    cout << endl;
    n = n->next;


    // 16. line
    cout << "                       " << n->data;
    n = n->next;
    cout << " " << n->data << endl;
    n = n->next;

    // 17. line
    cout << "                        " << n->data << endl;


    cout << endl;
    cout << endl;
}
void Board::print_h(){
    // go through the list
    cout << endl;
    cout << endl;
    Field* n = first;

    // 1. line

    cout << "                        ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    cout << endl;
    n = n->next;

    // 2. line
    cout << "                       ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    n = n->next;
    cout << " ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    cout << endl;
    n = n->next;

    // 3. line
    cout << "                      ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 2; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 4. line
    cout << "                     ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 3; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 5. line
    cout << "            ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 12; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 6. line
    cout << "             ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 11; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 7. line
    cout << "              ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 10; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 8. line
    cout << "               ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 9; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 9. line
    cout << "                ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 8; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 10. line
    cout << "               ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 9; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 11. line
    cout << "              ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 10; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 12. line
    cout << "             ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 11; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 13. line
    cout << "            ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 12; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 14. line
    cout << "                     ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 3; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;

    // 15. line
    cout << "                      ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    for(int i = 0; i < 2; i++){
        n = n->next;
        cout << " ";
        if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    }
    cout << endl;
    n = n->next;


    // 16. line
    cout << "                       ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    n = n->next;
    cout << " ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    cout << endl;
    n = n->next;

    // 17. line
    cout << "                        ";
    if(n->data == 'o') cout << 'o'; else if(n->data == 'x') cout << 'x'; else cout << n->h;
    cout << endl;


    cout << endl;
    cout << endl;
}

// ****************************************************************************************************
// protected members

// method to add a new fiel to the board
// this method gets only used when the board gets created
Field *Board::newField(int &numField, char &dataOfField, Field* previousField, Field* nextField, Field* dir_0_Field, Field* dir_60_Field, Field* dir_120_Field, Field* dir_180_Field, Field* dir_240_Field, Field* dir_300_Field){
    // create a new field and return it;
    Field* field = new Field(numField, dataOfField, previousField, nextField, dir_0_Field, dir_60_Field, dir_120_Field, dir_180_Field, dir_240_Field, dir_300_Field);
    return field;
}
