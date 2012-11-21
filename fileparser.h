#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream>
#include <string>

#include "board.h"
#include "iterator.h"
#include "field.h"


using namespace std;

class FileParser
{
public:
    // constructor gets the path to the graph file
    FileParser(const char* pathToGraph):filepath(pathToGraph){}
    Board pharse();             // pharse from the given file the connections between the boardfields

private:
    const char* filepath;       // filepath with the Graph.txt
    Board gameBoard;            // the gameBoard whitch gets created and connected
    void createEmtyBoard();     // create a empty board (a list of fields with N,S,E,W = 0, just previouse and next gets created)
};

#endif // FILEPARSER_H
