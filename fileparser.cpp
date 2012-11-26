#include "fileparser.h"
#include <stdlib.h>
#include <fstream>

// ****************************************************************************************************
// public members

Board FileParser::parse(){

    //this->generateGraphFile();

    cout << "pharese file " << filepath << endl << endl;
    int fields = 0;             // number of the field
    string fieldArray[122];     // array of lines from the file
    char line[50];              // a line from the file (never longer than 50 characters)

    ifstream fileStream(filepath);

    if (fileStream.is_open()){
        while(fileStream.getline(line,100)){
            fieldArray[fields] = line;
            fields++;
        }
    }
    fileStream.close();
    cout << fields << " fields found in the Graph.txt" << endl << endl;


    // create a emty Board and safe it to the privat varable (gameBoard)
    createEmtyBoard();
    Iterator iterator(gameBoard);
    Iterator iteratorSearch2(gameBoard);

    iterator.resetToFirst();
    iteratorSearch2.resetToFirst();



    // line format--->       <Fieldnumber>:<0>,<60>,<120>,<180>,<240>,<300>
    // for every field

    for( int i = 0; i < fields; i++){

        //************************************************************************************************
        //PHARSE LINE

        int neighboursCount = 0;
        int doublePoint = 0;
        int firstColon = 0;
        int secondColon = 0;
        int thirdColon = 0;
        int fourthColon = 0;
        int fifthColon = 0;

        //cout << fieldArray[i] << endl;
        // go trough the line and safe positions of ':' and ','
        for (unsigned int j=1; j < fieldArray[i].length()+1 ; j++){
            // if a ':' was found: safe the position of ':' in the doublePoint variable
            if (fieldArray[i].substr(j,1) == ":"){
                doublePoint = j;
                //cout << "\tdouble point: " << doublePoint << endl;
            }
            // if a ',' was found: safe the position of the ','
            if (fieldArray[i].substr(j,1) == ","){
                neighboursCount++;
                // safe the positions of the colons to the variables first, second....
                switch(neighboursCount){
                case 1:
                    firstColon = j;
                    //cout << "\tfirst colon: " << firstColon << endl;
                    break;
                case 2:
                    secondColon = j;
                    //cout << "\tsecond colon: " << secondColon << endl;
                    break;
                case 3:
                    thirdColon = j;
                    //cout << "\tthird colon: " << thirdColon << endl << endl << endl;
                    break;
                case 4:
                    fourthColon = j;
                    //cout << "\tthird colon: " << thirdColon << endl << endl << endl;
                    break;
                case 5:
                    fifthColon = j;
                    //cout << "\tthird colon: " << thirdColon << endl << endl << endl;
                    break;
                }
            }

        }
        //cout << "in field " << fields << " are " << neighboursCount+1 << " neighbors" << endl;

        if (neighboursCount != 5){
            cout << "error found in line " << fields << ": not the right amount of neighbors" << endl << endl;
        }

        //************************************************************************************************
        //SAFE NEIGHBOURS

        string fieldNumberString = fieldArray[i].substr(0,doublePoint);
        string dir_0_Str = fieldArray[i].substr(doublePoint+1,firstColon-doublePoint);
        string dir_60_Str = fieldArray[i].substr(firstColon+1,secondColon-firstColon);
        string dir_120_Str = fieldArray[i].substr(secondColon+1,thirdColon-secondColon);
        string dir_180_Str = fieldArray[i].substr(thirdColon+1,fourthColon-thirdColon);
        string dir_240_Str = fieldArray[i].substr(fourthColon+1,fifthColon-fourthColon);
        string dir_300_Str = fieldArray[i].substr(fifthColon+1);

        int dir_0 = atoi(dir_0_Str.c_str());
        int dir_60 = atoi(dir_60_Str.c_str());
        int dir_120 = atoi(dir_120_Str.c_str());
        int dir_180= atoi(dir_180_Str.c_str());
        int dir_240= atoi(dir_240_Str.c_str());
        int dir_300= atoi(dir_300_Str.c_str());


//        cout << fieldArray[i] << endl;
//        cout << "\t" << fieldNumberString << ": 0= " << dir_0 << endl;
//        cout << "\t" << fieldNumberString << ": 60= " << dir_60 << endl;
//        cout << "\t" << fieldNumberString << ": 120= " << dir_120 << endl;
//        cout << "\t" << fieldNumberString << ": 180= " << dir_180 << endl;
//        cout << "\t" << fieldNumberString << ": 240= " << dir_240 << endl;
//        cout << "\t" << fieldNumberString << ": 300= " << dir_300 << endl << endl;

        //************************************************************************************************
        //LINK THE LIST

        //cout << "iterator 1 at the field " << iterator.getCurrentNumber() << endl;

        // Set dir_0 field
        if(dir_0 != 0){
            // go with the second iterator to the south fiel
            iteratorSearch2.resetToFirst();
            while(iteratorSearch2.getCurrentNumber() != dir_0){
                ++iteratorSearch2;
            }
            iterator.setNeighbors(iteratorSearch2.getCurrentField(),0,0,0,0,0);
            //cout << "south field set to " << iteratorSearch2.getCurrentNumber() << endl << endl <<endl;

        }

        // Set dir_60 field
        if(dir_60 != 0){
            // go with the second iterator to the south fiel
            iteratorSearch2.resetToFirst();
            while(iteratorSearch2.getCurrentNumber() != dir_60){
                ++iteratorSearch2;
            }
            iterator.setNeighbors(0,iteratorSearch2.getCurrentField(),0,0,0,0);
            //cout << "south field set to " << iteratorSearch2.getCurrentNumber() << endl << endl <<endl;

        }

        // Set dir_120 field
        if(dir_120 != 0){
            // go with the second iterator to the south fiel
            iteratorSearch2.resetToFirst();
            while(iteratorSearch2.getCurrentNumber() != dir_120){
                ++iteratorSearch2;
            }
            iterator.setNeighbors(0,0,iteratorSearch2.getCurrentField(),0,0,0);
            //cout << "south field set to " << iteratorSearch2.getCurrentNumber() << endl << endl <<endl;

        }

        // Set dir_180 field
        if(dir_180 != 0){
            // go with the second iterator to the south fiel
            iteratorSearch2.resetToFirst();
            while(iteratorSearch2.getCurrentNumber() != dir_180){
                ++iteratorSearch2;
            }
            iterator.setNeighbors(0,0,0,iteratorSearch2.getCurrentField(),0,0);
            //cout << "south field set to " << iteratorSearch2.getCurrentNumber() << endl << endl <<endl;

        }

        // Set dir_240 field
        if(dir_240 != 0){
            // go with the second iterator to the south fiel
            iteratorSearch2.resetToFirst();
            while(iteratorSearch2.getCurrentNumber() != dir_240){
                ++iteratorSearch2;
            }
            iterator.setNeighbors(0,0,0,0,iteratorSearch2.getCurrentField(),0);
            //cout << "south field set to " << iteratorSearch2.getCurrentNumber() << endl << endl <<endl;

        }
        // Set dir_300 field
        if(dir_300 != 0){
            // go with the second iterator to the south fiel
            iteratorSearch2.resetToFirst();
            while(iteratorSearch2.getCurrentNumber() != dir_300){
                ++iteratorSearch2;
            }
            iterator.setNeighbors(0,0,0,0,0,iteratorSearch2.getCurrentField());
            //cout << "south field set to " << iteratorSearch2.getCurrentNumber() << endl << endl <<endl;

        }
        ++iterator;
    }

    cout << "connections between fields created..." << endl << endl;
    return gameBoard;
}



// ****************************************************************************************************
// private members

void FileParser::createEmtyBoard(){
    Iterator gameIterator(gameBoard);

    for(int i = 1; i <= 121; i++){
        gameIterator.insert(i,'.',0,0,0,0,0,0,0,0);
        ++gameIterator;
    }
    cout << "Emty board created. (all fields i one row with a continuous numeration) " << endl << endl;
}


