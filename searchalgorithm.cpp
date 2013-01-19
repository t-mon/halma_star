    #include "searchalgorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <functional>
#include <iostream>
#include <algorithm>

using namespace std;


Field *SearchAlgorithm::getGoalField(){
    return goal;
}

Field *SearchAlgorithm::getStartField(){
    return start;
}

/*
  Methode: startHeuristicsCircular
  Arguments:
  Description:
        starts the Heuristic circular
  Return: void
  by Lukas Holzinger @ 24.11.2012, 14:00
  */
void SearchAlgorithm::startHeuristicsCircular(){

    // reset the NodeList und clear it
    for(unsigned int i = 0; i < NodeList.size(); i++){
        delete NodeList[i];
    }
    NodeList.clear();

    if(DEBUG_HEURISTIC)
        cout << "inizialize the nodeList ... OK" << endl;

    // Push goalfield to the end of the List and set h to zero
    NodeList.push_back(goal);
    goal->h = 0;

    if(DEBUG_HEURISTIC)
        cout << "Push goalfield to NodeList and set h=0 ... OK" << endl;

    // start the BF-algorithm (starting from the goalfield)
    setHeuristicsCircular(NodeList.front());

}

/*
  Methode: setHeuristicsCircular
  Arguments: (Field*) currentField
  Description:
        go throw all Fields in NodeList
  Return: bool
  by Lukas Holzinger @ 24.11.2012, 14:00
  */
bool SearchAlgorithm::setHeuristicsCircular(Field* currentField){

    if(DEBUG_HEURISTIC)
        cout << "currentField is " << currentField->number << endl;
    // go throw the neighbourfields and set h
    setNeighbourHeuristic(currentField);

    // if you are at the end of the list return
    if(currentField == NodeList.back()){
        return true;
    }

    Field* nextField;
    // find the next Field in NodeList
    for(vector<Field*>::iterator listIterator = NodeList.begin(); listIterator != NodeList.end(); ++listIterator){
        if(currentField == *listIterator){
            ++listIterator;
            nextField = *listIterator;
            if(DEBUG_HEURISTIC)
                cout << "nextField is " << nextField->number << endl;
            break;
        }
    }

    if(DEBUG_HEURISTIC)
        print();
    // recursive function call with the next Field in the NodeList
    setHeuristicsCircular(nextField);
    return true;
}

/*
  Methode: setNeighbourHeuristic
  Arguments: (Field*) currentField
  Description:
        Set value h in every possible neighbour Field (distance depending on goal field)
  Return: void
  by Lukas Holzinger @ 24.11.2012, 14:00
  */
void SearchAlgorithm::setNeighbourHeuristic(Field* currentField){

    if(DEBUG_HEURISTIC)
        cout << "CurrentField Nr. " << currentField->number << " with Neighbours: ";

    Field* nextField = currentField->dir_0;
    Field* sec_nextField;
    if(nextField != 0)
        sec_nextField = currentField->dir_0->dir_0;

    // find the nextField (next Field in 0 direction) in the NodeList
    // if nextField isn't in the NodeList the iterator points to the end of the List
    vector<Field*>::iterator Sit = find(NodeList.begin(), NodeList.end(), nextField);

    // if nextField isn't zero AND nextField ist free (no stone on this field) AND nextField isn't in the NodeList THEN
    if(nextField != 0 && nextField->data == '.' && *Sit != nextField){
        // Push nextField to the end of the nodeList and set h value
        NodeList.push_back(nextField);
        nextField->h = currentField->h + 1;
        if(DEBUG_HEURISTIC) cout << nextField->number << ", ";
    }
    // else IF nextField isn't zero AND nextField isn't free THEN
    else if(nextField != 0 && nextField->data != '.'){
        // search the sec_nextField (->dir_0->dir_0) in the NodeList
        vector<Field*>::iterator Sit2 = find(NodeList.begin(), NodeList.end(), sec_nextField);
        // if sec_nextField isn't zero AND sec_nextField is free AND sec_nextField isn't in the NodeList THEN
        if(sec_nextField != 0 && sec_nextField->data == '.' && *Sit2 != sec_nextField){
            // Push sec_nextField to the end of the nodeList and set h value
            NodeList.push_back(sec_nextField);
            sec_nextField->h = currentField->h + 1;
            if(DEBUG_HEURISTIC) cout << sec_nextField->number << ", ";
        }

    }

    //... repeat the same for all angles (60,120,180,240,300)...
    nextField = currentField->dir_60;
    if(nextField != 0)
        sec_nextField = currentField->dir_60->dir_60;

    Sit = find(NodeList.begin(), NodeList.end(), nextField);

    if(nextField != 0 && nextField->data == '.' && *Sit != nextField){
        NodeList.push_back(nextField);
        nextField->h = currentField->h + 1;
        if(DEBUG_HEURISTIC) cout << nextField->number << ", ";
    }else if(nextField != 0 && nextField->data != '.'){
        vector<Field*>::iterator Sit2 = find(NodeList.begin(), NodeList.end(), sec_nextField);
        if(sec_nextField != 0 && sec_nextField->data == '.' && *Sit2 != sec_nextField){
            NodeList.push_back(sec_nextField);
            sec_nextField->h = currentField->h + 1;
            if(DEBUG_HEURISTIC) cout << sec_nextField->number << ", ";
        }

    }
    nextField = currentField->dir_120;
    if(nextField != 0)
        sec_nextField = currentField->dir_120->dir_120;

    Sit = find(NodeList.begin(), NodeList.end(), nextField);

    if(nextField != 0 && nextField->data == '.' && *Sit != nextField){
        NodeList.push_back(nextField);
        nextField->h = currentField->h + 1;
        if(DEBUG_HEURISTIC) cout << nextField->number << ", ";
    }else if(nextField != 0 && nextField->data != '.'){
        vector<Field*>::iterator Sit2 = find(NodeList.begin(), NodeList.end(), sec_nextField);
        if(sec_nextField != 0 && sec_nextField->data == '.' && *Sit2 != sec_nextField){
            NodeList.push_back(sec_nextField);
            sec_nextField->h = currentField->h + 1;
            if(DEBUG_HEURISTIC) cout << sec_nextField->number << ", ";
        }

    }
    nextField = currentField->dir_180;
    if(nextField != 0)
        sec_nextField = currentField->dir_180->dir_180;

    Sit = find(NodeList.begin(), NodeList.end(), nextField);

    if(nextField != 0 && nextField->data == '.' && *Sit != nextField){
        NodeList.push_back(nextField);
        nextField->h = currentField->h + 1;
        if(DEBUG_HEURISTIC) cout << nextField->number << ", ";
    }else if(nextField != 0 && nextField->data != '.'){
        vector<Field*>::iterator Sit2 = find(NodeList.begin(), NodeList.end(), sec_nextField);
        if(sec_nextField != 0 && sec_nextField->data == '.' && *Sit2 != sec_nextField){
            NodeList.push_back(sec_nextField);
            sec_nextField->h = currentField->h + 1;
            if(DEBUG_HEURISTIC) cout << sec_nextField->number << ", ";
        }

    }
    nextField = currentField->dir_240;
    if(nextField != 0)
        sec_nextField = currentField->dir_240->dir_240;

    Sit = find(NodeList.begin(), NodeList.end(), nextField);

    if(nextField != 0 && nextField->data == '.' && *Sit != nextField){
        NodeList.push_back(nextField);
        nextField->h = currentField->h + 1;
        if(DEBUG_HEURISTIC) cout << nextField->number << ", ";
    }else if(nextField != 0 && nextField->data != '.'){
        vector<Field*>::iterator Sit2 = find(NodeList.begin(), NodeList.end(), sec_nextField);
        if(sec_nextField != 0 && sec_nextField->data == '.' && *Sit2 != sec_nextField){
            NodeList.push_back(sec_nextField);
            sec_nextField->h = currentField->h + 1;
            if(DEBUG_HEURISTIC) cout << sec_nextField->number << ", ";
        }

    }

    nextField = currentField->dir_300;
    if(nextField != 0)
        sec_nextField = currentField->dir_300->dir_300;

    Sit = find(NodeList.begin(), NodeList.end(), nextField);

    if(nextField != 0 && nextField->data == '.' && *Sit != nextField){
        NodeList.push_back(nextField);
        nextField->h = currentField->h + 1;
        if(DEBUG_HEURISTIC) cout << nextField->number << ", ";
    }else if(nextField != 0 && nextField->data != '.'){
        vector<Field*>::iterator Sit2 = find(NodeList.begin(), NodeList.end(), sec_nextField);
        if(sec_nextField != 0 && sec_nextField->data == '.' && *Sit2 != sec_nextField){
            NodeList.push_back(sec_nextField);
            sec_nextField->h = currentField->h + 1;
            if(DEBUG_HEURISTIC) cout << sec_nextField->number << ", ";
        }

    }

    if(DEBUG_HEURISTIC) cout << endl;
}

void SearchAlgorithm::startBFSearch(Field *currentField)
{
    bfSteps = 0;
    // reset the NodeList und clear it
    bfSearchList.clear();
    m_BFstartField = currentField;

    // Push goalfield to the end of the List and set h to zero
    bfSearchList.push_front(currentField);

    // start the BF-algorithm
    stepBFSearch(bfSearchList.front());


}

bool SearchAlgorithm::stepBFSearch(Field *currentField)
{


    // go throw the neighbourfields and try to jump
    // if i can jump add that neigbour to the list end
    tryToJump(currentField);

    // this ends a endless loop search
    if(bfSteps > 15){
        bfSearchList.sort(bfSearchQuickSortCompareFunction);
        //watch in the list for the best field an move it to the openlist
        Field* bestOfBfSearch = bfSearchList.back();
        bestOfBfSearch->parent = m_BFstartField;
        bestOfBfSearch->g = steps;
        openList.push_back(bestOfBfSearch);

        // move the other fields to the visited list
        for(list<Field*>::iterator listIterator = bfSearchList.begin(); listIterator != bfSearchList.end(); ++listIterator){
            visitedList.push_back(*listIterator);
        }

        return true;
    }
    // if you are at the end of the list return
    if(currentField == bfSearchList.back()){
        // move it in the openlist

        // the parent of this neighbour is the current field
        currentField->parent = m_BFstartField;
        currentField->g = steps;
        openList.push_back(currentField);
        return true;
    }

    Field* nextField;
    // find the next Field in NodeList
    for(list<Field*>::iterator listIterator = bfSearchList.begin(); listIterator != bfSearchList.end(); ++listIterator){
        if(currentField == *listIterator){
            ++listIterator;
            nextField = *listIterator;
            break;
        }
    }
    // move the next field to the visitedList
    visitedList.push_back(nextField);

    //increment bfSteps counter (if>14 break)
    bfSteps++;
    // recursive function call with the next Field in the NodeList
    stepBFSearch(nextField);
    return true;
}

void SearchAlgorithm::tryToJump(Field *currentField)
{

    Field* nextField;
    Field* sec_nextField;

    // if i can jump in dir_0 add this field to the bfSearchList
    if(currentField->dir_0 != 0){
        nextField = currentField->dir_0;
        if(currentField->dir_0->dir_0 != 0){
            sec_nextField = currentField->dir_0->dir_0;
            // if i can jump in this direction add the sec_nextField to the bfSearchList
            if(nextField->data != '.' && sec_nextField->data == '.'){
                if(!isInBFSearchList(sec_nextField) && !isInVisitedList(sec_nextField)){
                    sec_nextField->parent = currentField;
                    bfSearchList.push_back(sec_nextField);
                }
            }
        }
    }

    // if i can jump in dir_60 add this field to the bfSearchList
    if(currentField->dir_60 != 0){
        nextField = currentField->dir_60;
        if(currentField->dir_60->dir_60 != 0){
            sec_nextField = currentField->dir_60->dir_60;
            // if i can jump in this direction add the sec_nextField to the bfSearchList
            if(nextField->data != '.' && sec_nextField->data == '.'){
                if(!isInBFSearchList(sec_nextField) && !isInVisitedList(sec_nextField)){
                    sec_nextField->parent = currentField;
                    bfSearchList.push_back(sec_nextField);
                }
            }
        }
    }

    // if i can jump in dir_120 add this field to the bfSearchList
    if(currentField->dir_120 != 0){
        nextField = currentField->dir_120;
        if(currentField->dir_120->dir_120 != 0){
            sec_nextField = currentField->dir_120->dir_120;
            // if i can jump in this direction add the sec_nextField to the bfSearchList
            if(nextField->data != '.' && sec_nextField->data == '.'){
                if(!isInBFSearchList(sec_nextField) && !isInVisitedList(sec_nextField)){
                    sec_nextField->parent = currentField;
                    bfSearchList.push_back(sec_nextField);
                }
            }
        }
    }

    // if i can jump in dir_180 add this field to the bfSearchList
    if(currentField->dir_180 != 0){
        nextField = currentField->dir_180;
        if(currentField->dir_180->dir_180 != 0){
            sec_nextField = currentField->dir_180->dir_180;
            // if i can jump in this direction add the sec_nextField to the bfSearchList
            if(nextField->data != '.' && sec_nextField->data == '.'){
                if(!isInBFSearchList(sec_nextField) && !isInVisitedList(sec_nextField)){
                    sec_nextField->parent = currentField;
                    bfSearchList.push_back(sec_nextField);
                }
            }
        }
    }

    // if i can jump in dir_240 add this field to the bfSearchList
    if(currentField->dir_240 != 0){
        nextField = currentField->dir_240;
        if(currentField->dir_240->dir_240 != 0){
            sec_nextField = currentField->dir_240->dir_240;
            // if i can jump in this direction add the sec_nextField to the bfSearchList
            if(nextField->data != '.' && sec_nextField->data == '.'){
                if(!isInBFSearchList(sec_nextField) && !isInVisitedList(sec_nextField)){
                    sec_nextField->parent = currentField;
                    bfSearchList.push_back(sec_nextField);
                }
            }
        }
    }

    // if i can jump in dir_300 add this field to the bfSearchList
    if(currentField->dir_300 != 0){
        nextField = currentField->dir_300;
        if(currentField->dir_300->dir_300 != 0){
            sec_nextField = currentField->dir_300->dir_300;
            // if i can jump in this direction add the sec_nextField to the bfSearchList
            if(nextField->data != '.' && sec_nextField->data == '.'){
                if(!isInBFSearchList(sec_nextField) && !isInVisitedList(sec_nextField)){
                    sec_nextField->parent = currentField;
                    bfSearchList.push_back(sec_nextField);
                }
            }
        }
    }
    //bfSearchList.sort(bfSearchQuickSortCompareFunction);
}


bool SearchAlgorithm::quickSortCompareFunction(Field *a, Field *b)
{
    return (a->getF() > b->getF());
}

bool SearchAlgorithm::bfSearchQuickSortCompareFunction(Field *a, Field *b)
{
    return (a->h > b->h);

}

void SearchAlgorithm::setStartAndGoal(){
    //cout << "set start and goalfield" << endl;

    // clear all lists
    inizializeLists();

    startHeuristicsCircular();

    //inizialise start field
    start->g=0;
    start->parent = 0;

    steps = 0;

    // push the first field in the open list
    openList.push_back(start);
    //cout << "start and goalfield ... OK!" << endl;

}

void SearchAlgorithm::inizializeLists(){

    //cout << "inizialize lists ....." << endl;

    openList.clear();
    visitedList.clear();
    shortestPath.clear();
    bfSearchList.clear();
    m_BFstartField = 0;

    // inizialize all g values
    Iterator iterator(gameBoard);
    iterator.resetToFirst();
    while(iterator.getCurrentField() != gameBoard.getLast()){
        iterator.current->g = 100;
        ++iterator;
    }
    iterator.current->g = 100;

    // inizialize all parent pointer to NULL
    iterator.resetToFirst();
    while(iterator.getCurrentField() != gameBoard.getLast()){
        iterator.current->parent = 0;
        ++iterator;
    }
    iterator.current->parent = 0;

    //cout << "lists inizialized ...OK" << endl;
}


Field *SearchAlgorithm::getNextBestField()
{

    // first controll if the open list is empty...search finished!!!!!!
        if(openList.empty()){
        cout << " -----> end of search! NO possibility left" << endl << endl;

        //cout << "GoalField = " << goal->number << endl;
        //cout << "Best path as far as i can: ";

        // safe tha path from the best visited list field to start and take that for the best path
        noWayToGoal = true;
        return start;
    }

    // sort the openlist (best f field is at the end)
    openList.sort(quickSortCompareFunction);

    //    cout << "f-values of openlist <field>:<f> ,... :  ";
    //    for(list<Field*>::iterator it = openList.begin(); it != openList.end(); it++){
    //        Field* x = *it;
    //        cout << *x << ":" << x->getF() << ", ";
    //    }
    //    cout << endl;

    Field* bestField = openList.back();

    // return the current best field
    //cout << "\tcurrent best solution field = " << bestField->number << endl;
    currentSolution = bestField;
    return bestField;
}

void SearchAlgorithm::searchStep()
{
    // loock in the openList for the current best field,
    // remove it from the open list an put it in the visited list
    bfSearchList.clear();

    Field* n = getNextBestField();
    //n->g = steps;
    // steps +1...this will be the g value of the neighbours
    steps++;

    // check if we have found the goal field
    if(n == goal){
        cout << " -----> GOAL REACHED!!!" << endl;

        // write the best path to the shortestPath List
        shortestPath.clear();

        shortestPath.push_front(n);
        //n->data = '*';
        Field *x = n;
        while ( x != start ){
            x = x->parent;
            //x->data = '*';
            shortestPath.push_front(x);
        }

        //cout << "GoalField = " << goal->number << endl;
        cout << "\tFound path : ";
        list<Field*>::iterator it;
        for(it = shortestPath.begin(); it != shortestPath.end(); it++){
            cout << **it << "->" ;
        }
        cout << endl;
        goalReached = true;
        return;
    }



    if(openList.empty()){
        return;
    }
    // remove it from the openlist

    openList.pop_back();

    // add it to the visited list
    visitedList.push_back(n);
    bfSearchList.clear();

    //cout << "move to field = " << n->number << endl;

    // now controll the neigbours of the current best field:
    // non valid neigbours for the openlist are:
    //      -> neighbour which is ocupied
    //      -> neighbour which is allready in the openlist
    //      -> neighbour which is allready in the visited list

    // if controllNeighbour returns true we can add this neighbour to the open list

    Field* nextField = n->dir_0;
    Field* sec_nextField;
    if(n->dir_0 != 0){
        sec_nextField = n->dir_0->dir_0;
    }

    if(nextField != 0){
        if(!isInOpenList(nextField) && !isInVisitedList(nextField)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(nextField)){
                if(sec_nextField != 0){
                    // if this is true we can jump and we add the next field to the openlist and set parent and g value
                    if(!isInOpenList(sec_nextField) && !isInVisitedList(sec_nextField) && !(isOccupied(sec_nextField))){
                        // make a breath first search and try to jump as far as you can
                        bfSteps = 0;
                        startBFSearch(n);
                    }
                }
            }else{
                openList.push_back(nextField);
                // the parent of this neighbour is the current field
                nextField->parent = n;
                // set g value of neighbour
                nextField->g = steps;
            }
        }
    }


    nextField = n->dir_60;
    if(nextField != 0){
        sec_nextField = n->dir_60->dir_60;
    }
    if(nextField != 0){
        if(!isInOpenList(nextField) && !isInVisitedList(nextField)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(nextField)){
                if(sec_nextField != 0){
                    // if this is true we can jump and we add the next field to the openlist and set parent and g value
                    if(!isInOpenList(sec_nextField) && !isInVisitedList(sec_nextField) && !(isOccupied(sec_nextField))){
                        // make a breath first search and try to jump as far as you can
                        bfSteps = 0;
                        startBFSearch(n);
                    }
                }
            }else{
                openList.push_back(nextField);
                // the parent of this neighbour is the current field
                nextField->parent = n;
                // set g value of neighbour
                nextField->g = steps;
            }
        }
    }

    nextField = n->dir_120;
    if(nextField != 0){
        sec_nextField = n->dir_120->dir_120;
    }
    if(nextField != 0){
        if(!isInOpenList(nextField) && !isInVisitedList(nextField)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(nextField)){
                if(sec_nextField != 0){
                    // if this is true we can jump and we add the next field to the openlist and set parent and g value
                    if(!isInOpenList(sec_nextField) && !isInVisitedList(sec_nextField) && !(isOccupied(sec_nextField))){
                        // make a breath first search and try to jump as far as you can
                        bfSteps = 0;
                        startBFSearch(n);
                    }
                }
            }else{
                openList.push_back(nextField);
                // the parent of this neighbour is the current field
                nextField->parent = n;
                // set g value of neighbour
                nextField->g = steps;
            }
        }
    }

    nextField = n->dir_180;
    if(nextField != 0){
        sec_nextField = n->dir_180->dir_180;
    }
    if(nextField != 0){
        if(!isInOpenList(nextField) && !isInVisitedList(nextField)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(nextField)){
                if(sec_nextField != 0){
                    // if this is true we can jump and we add the next field to the openlist and set parent and g value
                    if(!isInOpenList(sec_nextField) && !isInVisitedList(sec_nextField) && !(isOccupied(sec_nextField))){
                        // make a breath first search and try to jump as far as you can
                        bfSteps = 0;
                        startBFSearch(n);
                    }
                }
            }else{
                openList.push_back(nextField);
                // the parent of this neighbour is the current field
                nextField->parent = n;
                // set g value of neighbour
                nextField->g = steps;
            }
        }
    }

    nextField = n->dir_240;
    if(nextField != 0){
        sec_nextField = n->dir_240->dir_240;
    }
    if(nextField != 0){
        if(!isInOpenList(nextField) && !isInVisitedList(nextField)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(nextField)){
                if(sec_nextField != 0){
                    // if this is true we can jump and we add the next field to the openlist and set parent and g value
                    if(!isInOpenList(sec_nextField) && !isInVisitedList(sec_nextField) && !(isOccupied(sec_nextField))){
                        // make a breath first search and try to jump as far as you can
                        bfSteps = 0;
                        startBFSearch(n);
                    }
                }
            }else{
                openList.push_back(nextField);
                // the parent of this neighbour is the current field
                nextField->parent = n;
                // set g value of neighbour
                nextField->g = steps;
            }
        }
    }

    nextField = n->dir_300;
    if(nextField != 0){
        sec_nextField = n->dir_300->dir_300;
    }
    if(nextField != 0){
        if(!isInOpenList(nextField) && !isInVisitedList(nextField)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(nextField)){
                if(sec_nextField != 0){
                    // if this is true we can jump and we add the next field to the openlist and set parent and g value
                    if(!isInOpenList(sec_nextField) && !isInVisitedList(sec_nextField) && !(isOccupied(sec_nextField))){
                        // make a breath first search and try to jump as far as you can
                        bfSteps = 0;
                        startBFSearch(n);
                    }
                }
            }else{
                openList.push_back(nextField);
                // the parent of this neighbour is the current field
                nextField->parent = n;
                // set g value of neighbour
                nextField->g = steps;
            }
        }
    }

    // now we have controlled every neighbour of the current field an added all valid neighbours to the open list
    // the current field is the parent of all valid neigbours
}


bool SearchAlgorithm::isInOpenList(Field *directionField)
{
    for(list<Field*>::iterator listIterator = openList.begin(); listIterator != openList.end(); ++listIterator){
        if(directionField == *listIterator){
            return true;
        }
    }
    return false;
}

bool SearchAlgorithm::isInVisitedList(Field *directionField)
{
    for(list<Field*>::iterator listIterator = visitedList.begin(); listIterator != visitedList.end(); ++listIterator){
        if(directionField == *listIterator){
            return true;
        }
    }
    return false;
}

bool SearchAlgorithm::isInBFSearchList(Field *directionField)
{
    for(list<Field*>::iterator listIterator = bfSearchList.begin(); listIterator != bfSearchList.end(); ++listIterator){
        if(directionField == *listIterator){
            return true;
        }
    }
    return false;
}

bool SearchAlgorithm::isOccupied(Field *directionField){
    if(directionField->data != '.'){
        return true;
    }else{
        return false;
    }
}


Field* SearchAlgorithm::findPath(){
    setStartAndGoal();
    // if we have not reached the goalFild OR if there is no possibility left (openList empty) make the next searchstep
    while(!goalReached && !noWayToGoal){
        searchStep();
    }

    // just use the first step of the hole path as solution for one turn (jumps included)
    if(!shortestPath.empty()){
        list<Field*>::iterator it = shortestPath.begin();
        it++;
        Field* solution = *it;

        return solution;
    }else{
        return 0;
    }
}


void SearchAlgorithm::print(){
    gameBoard.print_h();
}

void SearchAlgorithm::setRandomStones(int max_stones ){
    int stone_pos;
    time_t t;
    Iterator it(gameBoard);
    time(&t);
    srand((unsigned int)t);              /* init randomcout */

    for(int i = 0; i < max_stones;i++){
        stone_pos = rand() % 121 + 1;
        it.resetToFirst();
        while(it.current != 0){
            if(it.current->number == stone_pos){
                it.current->data = 'o';
            }
            ++it;
        }
    }
}



