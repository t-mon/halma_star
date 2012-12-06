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
    setHeuristicsCircular2(NodeList.front());

}

/*
  Methode: setHeuristicsCircular2
  Arguments: (Field*) currentField
  Description:
        go throw all Fields in NodeList
  Return: bool
  by Lukas Holzinger @ 24.11.2012, 14:00
  */
bool SearchAlgorithm::setHeuristicsCircular2(Field* currentField){

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
    setHeuristicsCircular2(nextField);
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
    // reset the NodeList und clear it
    openBFSearchList.clear();

    // Push goalfield to the end of the List and set h to zero
    openBFSearchList.push_back(goal);

    // start the BF-algorithm
    stepBFSearch(openBFSearchList.front());


}

bool SearchAlgorithm::stepBFSearch(Field *currentField)
{

    // go throw the neighbourfields and try to jump
    tryToJump(currentField);

    // if you are at the end of the list return
    if(currentField == openBFSearchList.back()){
        return true;
    }

    Field* nextField;
    // find the next Field in NodeList
    for(list<Field*>::iterator listIterator = openBFSearchList.begin(); listIterator != openBFSearchList.end(); ++listIterator){
        if(currentField == *listIterator){
            ++listIterator;
            nextField = *listIterator;
            break;
        }
    }

    // recursive function call with the next Field in the NodeList
    stepBFSearch(nextField);
    return true;
}

bool SearchAlgorithm::tryToJump(Field *currentField)
{

    // if i can jump in dir_0 add this field to the openBFSearch list
    Field* nextField = currentField->dir_0;
    Field* sec_nextField;
    if(nextField != 0){
        sec_nextField = currentField->dir_0->dir_0;
    }

    //    // if controllNeighbour returns true we can add this neighbour to the open list
    //    if(nextField != 0){
    //        if(!isInOpenList(nextField) && !isInVisitedList(nextField)){
    //            // is not in open list and not in visited list
    //            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
    //            if(isOccupied(n->dir_0) && n->dir_0->dir_0 != 0){
    //                // if this is true we can jump and we add the next field to the openlist and set parent and g value
    //                if(!isInOpenList(n->dir_0->dir_0) && !isInVisitedList(n->dir_0->dir_0) && !(isOccupied(n->dir_0->dir_0))){
    //                    // make a breath first search and try to jump as far as you can




}


bool SearchAlgorithm::quickSortCompareFunction(Field *a, Field *b)
{
    return (a->getF() > b->getF());
}


/*
  Methode: setHeuristicsCircular
  Arguments: (Field*) goalField
  Description:
        Set value h in every Field (distance depending on goal field)
  Return: void
  by Lukas Holzinger @ 12.11.2012, 18:00
  */
void SearchAlgorithm::setHeuristicsCircular(){
    Iterator iterator(gameBoard);
    int counter_x = 0;
    int counter_y = 0;
    bool control = 0;
    int pri_angle = 0;
    int sec_angle = 0;


    /*    iterator.resetToFirst();
    while(iterator.current->number < 121){
        iterator.current->h=0;
        ++iterator;
    }
*/
    // go to the goalfield with the iterator
    iterator.resetToFirst();
    while(iterator.current->number != goal->number){

        ++iterator;
    }

    // set goalfield heuristic value(h) to 0
    iterator.current->h = 0;

    // go throw all 6 possible neighbor nodes
    for(int i=0; i < 6; i++){

        pri_angle = i*60;               // Primary angle
        sec_angle = (60+pri_angle)%360; // secondary angle

        iterator.getPossibleDirections();


        // do while as long as sec_angle direction is possible
        do {

            if(iterator.getPossibleDirectionsControl(pri_angle)){
                // iterator could go in pri_angle direction
                // iterator goes throw the nodes in pimary angle direction und set the HV
                while(!iterator.go_dir(pri_angle)){
                    counter_x++;
                    iterator.current->h=(counter_x+counter_y);
                }
            }


            while(counter_x != 0){
                iterator.getPossibleDirections();

                if(iterator.getPossibleDirectionsControl(sec_angle) && control == 0){
                    // if the there is a neighbor node in sec_angle direction and it's
                    // the first round (control == FALSE) then go into sec_direction, set
                    // HV and go back
                    while(!iterator.go_dir(sec_angle)){
                        counter_y++;
                        iterator.current->h = (counter_x+counter_y);
                    }
                    while(counter_y != 0){
                        counter_y--;
                        iterator.go_dir((180+sec_angle)%360);

                    }

                }
                // go in pri_angle direction one step back
                iterator.go_dir((180+pri_angle)%360);
                counter_x--;

            }
            // set after the first round (control == TRUE)
            control = 1;


            // Go in the sec_angle direction if possible
            iterator.getPossibleDirections();
            if(iterator.getPossibleDirectionsControl(sec_angle)){
                iterator.go_dir(sec_angle);
                counter_y++;
            }

        } while(iterator.getPossibleDirectionsControl(sec_angle));


        // go back home
        while(counter_y != 0){
            iterator.go_dir((180+sec_angle)%360);
            counter_y--;
        }
        // reset control to FALSE
        control = 0;
    }

}



void SearchAlgorithm::setStartAndGoal(){

    cout << "set start and goalfield" << endl;

    // clear all lists
    inizializeLists();

    // inizialize all g values
    Iterator iterator(gameBoard);
    iterator.resetToFirst();
    iterator.current->g = 100;
    while(iterator.getCurrentNumber() != 121){
        ++iterator;
        iterator.current->g = 100;
    }

    startHeuristicsCircular();

    //inizialise start field
    start->g=0;
    start->parent = 0;

    steps = 0;

    // push the first field in the open list
    openList.push_back(start);
    cout << "start and goalfield ... OK!" << endl;

}

void SearchAlgorithm::inizializeLists(){

    cout << "inizialize lists ....." << endl;

    // delete every node from the openlist and clear the list
    //    for(unsigned int i = 0; i < openList.size(); i++){
    //        delete openList[i];
    //    }
    openList.clear();

    // delete every node from the visitedList and clear the list
    //    for(unsigned int i = 0; i < visitedList.size(); i++){
    //        delete visitedList[i];
    //    }
    visitedList.clear();

    // delete every node from the shortestPath - list and clear the list
    //    for(unsigned int i = 0; i < shortestPath.size(); i++){
    //        delete shortestPath[i];
    //    }
    shortestPath.clear();

    cout << "lists inizialized ...OK" << endl;
}


Field *SearchAlgorithm::getNextBestField()
{

    // first controll if the open list is empty...search finished!!!!!!
    if(openList.empty()){
        cout << "--> end of search! no possibility left" << endl << endl;

        shortestPath.clear();

        visitedList.sort(quickSortCompareFunction);
        Field* bestField = openList.back();
        shortestPath.push_front(bestField);
        while(bestField!= start){
            bestField = bestField->parent;
            bestField->data = '*';
            shortestPath.push_front(bestField);
        }


        cout << "GoalField = " << goal->number << endl;
        cout << "Best path as far as i can: ";
        list<Field*>::iterator it;
        for(it = shortestPath.begin(); it != shortestPath.end(); it++){
            cout << **it << "->" ;
        }

        // safe tha path from the best visited list field to start and take that for the best path
        noWayToGoal = true;
        return 0;
    }

    // sort the openlist (best f field is at the end)
    openList.sort(quickSortCompareFunction);

    cout << "f-values of openlist <field>:<f> ,... :  ";
    for(list<Field*>::iterator it = openList.begin(); it != openList.end(); it++){
        Field* x = *it;
        cout << *x << ":" << x->getF() << ", ";
    }
    cout << endl;

    Field* bestField = openList.back();

    // return the current best field
    cout << "\tcurrent best solution field = " << bestField->number << endl;
    currentSolution = bestField;
    return bestField;
}

void SearchAlgorithm::searchStep()
{
    // loock in the openList for the current best field,
    // remove it from the open list an put it in the visited list

    Field* n = getNextBestField();
    //n->g = steps;
    // steps +1...this will be the g value of the neighbours
    steps++;

    // check if we have found the goal field
    if(n == goal){
        cout << "--------------> GOAL REACHED!!!! <------------------" << endl;

        // write the best path to the shortestPath List
        shortestPath.clear();

        shortestPath.push_front(n);
        n->data = '*';
        Field *x = n;
        while ( x != start ){
            x = x->parent;
            x->data = '*';
            shortestPath.push_front(x);
        }

        cout << "GoalField = " << goal->number << endl;
        cout << "Found path : ";
        list<Field*>::iterator it;
        for(it = shortestPath.begin(); it != shortestPath.end(); it++){
            cout << **it << "->" ;
        }

        goalReached = true;
        return;
    }



    // remove it from the openlist
    openList.pop_back();

    // add it to the visited list
    visitedList.push_back(n);

    cout << "move to field = " << n->number << endl;

    // now controll the neigbours of the current best field:
    // non valid neigbours for the openlist are:
    //      -> neighbour which is ocupied
    //      -> neighbour which is allready in the openlist
    //      -> neighbour which is allready in the visited list

    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_0 != 0){
        if(!isInOpenList(n->dir_0) && !isInVisitedList(n->dir_0)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(n->dir_0) && n->dir_0->dir_0 != 0){
                // if this is true we can jump and we add the next field to the openlist and set parent and g value
                if(!isInOpenList(n->dir_0->dir_0) && !isInVisitedList(n->dir_0->dir_0) && !(isOccupied(n->dir_0->dir_0))){
                    // make a breath first search and try to jump as far as you can


                    openList.push_back(n->dir_0->dir_0);
                    // the parent of this neighbour is the current field
                    n->dir_0->dir_0->parent = n;
                    // set g value of neighbour
                    n->dir_0->dir_0->g = steps;
                }
            }else{
                openList.push_back(n->dir_0);
                // the parent of this neighbour is the current field
                n->dir_0->parent = n;
                // set g value of neighbour
                n->dir_0->g = steps;
            }
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_60 != 0){
        if(!isInOpenList(n->dir_60) && !isInVisitedList(n->dir_60)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(n->dir_60) && n->dir_60->dir_60 != 0){
                // if this is true we can jump and we add the next field to the openlist and set parent and g value
                if(!isInOpenList(n->dir_60->dir_60) && !isInVisitedList(n->dir_60->dir_60) && !(isOccupied(n->dir_60->dir_60))){
                    openList.push_back(n->dir_60->dir_60);
                    // the parent of this neighbour is the current field
                    n->dir_60->dir_60->parent = n;
                    // set g value of neighbour
                    n->dir_60->dir_60->g = steps;
                }
            }else{
                openList.push_back(n->dir_60);
                // the parent of this neighbour is the current field
                n->dir_60->parent = n;
                // set g value of neighbour
                n->dir_60->g = steps;
            }
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_120 != 0){
        if(!isInOpenList(n->dir_120) && !isInVisitedList(n->dir_120)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(n->dir_120) && n->dir_120->dir_120 != 0){
                // if this is true we can jump and we add the next field to the openlist and set parent and g value
                if(!isInOpenList(n->dir_120->dir_120) && !isInVisitedList(n->dir_120->dir_120) && !(isOccupied(n->dir_120->dir_120))){
                    openList.push_back(n->dir_120->dir_120);
                    // the parent of this neighbour is the current field
                    n->dir_120->dir_120->parent = n;
                    // set g value of neighbour
                    n->dir_120->dir_120->g = steps;
                }
            }else{
                openList.push_back(n->dir_120);
                // the parent of this neighbour is the current field
                n->dir_120->parent = n;
                // set g value of neighbour
                n->dir_120->g = steps;
            }
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_180 != 0){
        if(!isInOpenList(n->dir_180) && !isInVisitedList(n->dir_180)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(n->dir_180) && n->dir_180->dir_180 != 0){
                // if this is true we can jump and we add the next field to the openlist and set parent and g value
                if(!isInOpenList(n->dir_180->dir_180) && !isInVisitedList(n->dir_180->dir_180) && !(isOccupied(n->dir_180->dir_180))){
                    openList.push_back(n->dir_180->dir_180);
                    // the parent of this neighbour is the current field
                    n->dir_180->dir_180->parent = n;
                    // set g value of neighbour
                    n->dir_180->dir_180->g = steps;
                }
            }else{
                openList.push_back(n->dir_180);
                // the parent of this neighbour is the current field
                n->dir_180->parent = n;
                // set g value of neighbour
                n->dir_180->g = steps;
            }
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_240 != 0){
        if(!isInOpenList(n->dir_240) && !isInVisitedList(n->dir_240)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(n->dir_240) && n->dir_240->dir_240 != 0){
                // if this is true we can jump and we add the next field to the openlist and set parent and g value
                if(!isInOpenList(n->dir_240->dir_240) && !isInVisitedList(n->dir_240->dir_240) && !(isOccupied(n->dir_240->dir_240))){
                    openList.push_back(n->dir_240->dir_240);
                    // the parent of this neighbour is the current field
                    n->dir_240->dir_240->parent = n;
                    // set g value of neighbour
                    n->dir_240->dir_240->g = steps;
                }
            }else{
                openList.push_back(n->dir_240);
                // the parent of this neighbour is the current field
                n->dir_240->parent = n;
                // set g value of neighbour
                n->dir_240->g = steps;
            }
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_300 != 0){
        if(!isInOpenList(n->dir_300) && !isInVisitedList(n->dir_300)){
            // is not in open list and not in visited list
            // now check if this field is occupied, if it is occupied, controll the next field in this direction if it exists
            if(isOccupied(n->dir_300) && n->dir_300->dir_300 != 0){
                // if this is true we can jump and we add the next field to the openlist and set parent and g value
                if(!isInOpenList(n->dir_300->dir_300) && !isInVisitedList(n->dir_300->dir_300) && !(isOccupied(n->dir_300->dir_300))){
                    openList.push_back(n->dir_300->dir_300);
                    // the parent of this neighbour is the current field
                    n->dir_300->dir_300->parent = n;
                    // set g value of neighbour
                    n->dir_300->dir_300->g = steps;
                }
            }else{
                openList.push_back(n->dir_300);
                // the parent of this neighbour is the current field
                n->dir_300->parent = n;
                // set g value of neighbour
                n->dir_300->g = steps;
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
            Field* x = *listIterator;
            //cout << directionField->number << "allready in openlist with g =" << directionField->g << " current g = " << currentSolution->g << endl;
            // check if the g value of the parent from the existing field in the openlist is better than the current
            if(x->parent->g > currentSolution->g){
                x->parent = currentSolution;
            }
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

bool SearchAlgorithm::isOccupied(Field *directionField){
    if(directionField->data != '.'){
        return true;
    }else{
        return false;
    }
}


void SearchAlgorithm::findPath(){
    setStartAndGoal();
    // if we have not reached the goalFild OR if there is no possibility left (openList empty) make the next searchstep
    while(!goalReached && !noWayToGoal){
        searchStep();
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



