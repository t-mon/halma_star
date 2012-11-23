#include "searchalgorithm.h"

Field *SearchAlgorithm::getGoalField(){
    return goal;
}

Field *SearchAlgorithm::getStartField(){
    return start;
}


void SearchAlgorithm::startHeuristicsCircular(){

    for(unsigned int i = 0; i < NodeList.size(); i++){
        delete NodeList[i];
    }
    NodeList.clear();
 {
    Iterator iterator(gameBoard);
    iterator.resetToFirst();
    while(iterator.current->number < 121){
        iterator.current->h=0;
        ++iterator;
    }
 }
    if(DEBUG_HEURISTIC)
        cout << "inizialize the nodeList and stoneList ... OK" << endl;

    NodeList.push_back(goal);

    goal->h = 0;
    // Set goalField to the NodeList


    setHeuristicsCircular2(NodeList.front());

}

bool SearchAlgorithm::setHeuristicsCircular2(Field* currentField){

    // Wenn kein Weg mehr moeglich ist dann return true
    setNeighbourHeuristic(currentField);

    if(currentField == NodeList.back()){
        return true;
    }
    // Nachbarn in die NodeList hinzufügen
    // NodeList.push_back
    Field* nextField;
    // gehe +1 in der NodeList und rufen setHeuristicsCircular(aktuelles Feld in nodeList) auf

    for(vector<Field*>::iterator listIterator = NodeList.begin(); listIterator != NodeList.end(); ++listIterator){
        if(currentField == *listIterator){
            ++listIterator;
            nextField = *listIterator;
            break;
        }
    }
    if(DEBUG_HEURISTIC) print();
    setHeuristicsCircular2(nextField);
    return true;
}

void SearchAlgorithm::setNeighbourHeuristic(Field* currentField){

    if(DEBUG_HEURISTIC)
        cout << currentField->number << ": ";

    vector<Field*>::iterator Sit = find(NodeList.begin(), NodeList.end(), currentField->dir_0);

    if(currentField->dir_0 != 0 && *Sit != currentField->dir_0){
        NodeList.push_back(currentField->dir_0);
        currentField->dir_0->h = currentField->h + 1;
       if(DEBUG_HEURISTIC) cout << currentField->dir_0->number << ", ";
    }

    Sit = find(NodeList.begin(), NodeList.end(), currentField->dir_60);
    if(currentField->dir_60 != 0 && *Sit != currentField->dir_60){
        NodeList.push_back(currentField->dir_60);
        currentField->dir_60->h = currentField->h + 1;
       if(DEBUG_HEURISTIC) cout << currentField->dir_60->number << ", ";
    }

    Sit = find(NodeList.begin(), NodeList.end(), currentField->dir_120);
    if(currentField->dir_120 != 0 && *Sit != currentField->dir_120){
            NodeList.push_back(currentField->dir_120);
            currentField->dir_120->h = currentField->h + 1;
    if(DEBUG_HEURISTIC) cout << currentField->dir_120->number << ", ";
    }

    Sit = find(NodeList.begin(), NodeList.end(), currentField->dir_180);
    if(currentField->dir_180 != 0 && *Sit != currentField->dir_180){
            NodeList.push_back(currentField->dir_180);
            currentField->dir_180->h = currentField->h + 1;
    if(DEBUG_HEURISTIC) cout << currentField->dir_180->number << ", ";
    }
    Sit = find(NodeList.begin(), NodeList.end(), currentField->dir_240);
    if(currentField->dir_240 != 0 && *Sit != currentField->dir_240){
            NodeList.push_back(currentField->dir_240);
            currentField->dir_240->h = currentField->h + 1;
       if(DEBUG_HEURISTIC)  cout << currentField->dir_240->number << ", ";
    }

    Sit = find(NodeList.begin(), NodeList.end(), currentField->dir_300);
    if(currentField->dir_300 != 0 && *Sit != currentField->dir_300){
            NodeList.push_back(currentField->dir_300);
            currentField->dir_300->h = currentField->h + 1;
       if(DEBUG_HEURISTIC)  cout << currentField->dir_300->number;

    }

    if(DEBUG_HEURISTIC) cout << endl;
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


void SearchAlgorithm::setHeuristicsGeometrical(){
    Iterator iterator(gameBoard);

    // go to the goalfield with the iterator
    iterator.resetToFirst();
    while(iterator.current->number != goal->number){
        ++iterator;
    }

    iterator.current->h = 0;

    // an so on.... :)

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

    setHeuristicsCircular();

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
    for(unsigned int i = 0; i < openList.size(); i++){
        delete openList[i];
    }
    openList.clear();

    // delete every node from the visitedList and clear the list
    for(unsigned int i = 0; i < visitedList.size(); i++){
        delete visitedList[i];
    }
    visitedList.clear();

    // delete every node from the shortestPath - list and clear the list
    for(unsigned int i = 0; i < shortestPath.size(); i++){
        delete shortestPath[i];
    }
    shortestPath.clear();

    cout << "lists inizialized ...OK" << endl;
}


Field *SearchAlgorithm::getNextBestField()
{
    double currentBestF = 1000;
    Field* currentField = 0;
    Field* bestField = 0;

    // go trough the open list and find the field with the best F in the openList (all neighbours which aren't visited yet)
    for(vector<Field*>::iterator openListIterator = openList.begin(); openListIterator != openList.end(); ++openListIterator){
        // get the current field where the iterator stands
        currentField = *openListIterator;
        // if the f of the current field is the best until now safe the f and the field with this best f
        if(currentBestF > currentField->getF()){
            currentBestF = currentField->getF();
            bestField = currentField;
        }
    }

    // return the current best field
    cout << "\tcurrent best solution field = " << bestField->number << endl;
    currentSolution = bestField;
    //shortestPath.push_back(bestField);
    return bestField;
}

void SearchAlgorithm::searchStep()
{
    // loock in the openList for the current best field,
    // remove it from the open list an put it in the visited list

    // first controll if the open list is empty...search finished!!!!!!
    if(openList.empty()){
        cout << "--> end of search! no possibility left" << endl << endl;
        return;
    }

    Field* n = getNextBestField();
    //n->g = steps;
    // steps +1...this will be the g value of the neighbours
    steps++;

    if(n == goal){
        cout << "--------------> GOAL REACHED!!!! <------------------" << endl;
        // write the best path to the shortestPath List
        //vector<double> path;
        shortestPath.push_back(n);
        //path.pop_back(n->number);
        n->data = '*';
        Field *x = n;
        while ( x != start ){
            x = x->parent;
            x->data = '*';
            //path.pop_back(x->number);
            shortestPath.push_back(x);
        }
        cout << "GoalField = " << goal->number << endl;
        cout << "Found path : ";
        for(vector<Field*>::iterator listIterator = shortestPath.end(); listIterator != shortestPath.begin(); listIterator--){
            cout << *listIterator << "->";
        }
        cout << n << endl;

        goalReached = true;
        return;
    }



    // remove it from the openlist
    for(vector<Field*>::iterator openListIterator = openList.begin(); openListIterator != openList.end(); ++openListIterator){
        // is the current field our current best field?
        if(n == *openListIterator){
            openList.erase(openListIterator);
            break;
        }
    }
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
        if(controllNeighbour(n->dir_0)){
            openList.push_back(n->dir_0);
            // the parent of this neighbour is the current field
            n->dir_0->parent = n;
            // set g value of neighbour
            n->dir_0->g = steps;
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_60 != 0){
        if(controllNeighbour(n->dir_60)){
            openList.push_back(n->dir_60);
            // the parent of this neighbour is the current field
            n->dir_60->parent = n;
            // set g value of neighbour
            n->dir_60->g = steps;
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_120 != 0){
        if(controllNeighbour(n->dir_120)){
            openList.push_back(n->dir_120);
            // the parent of this neighbour is the current field
            n->dir_120->parent = n;
            // set g value of neighbour
            n->dir_120->g = steps;
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_180 != 0){
        if(controllNeighbour(n->dir_180)){
            openList.push_back(n->dir_180);
            // the parent of this neighbour is the current field
            n->dir_180->parent = n;
            // set g value of neighbour
            n->dir_180->g = steps;
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_240 != 0){
        if(controllNeighbour(n->dir_240)){
            openList.push_back(n->dir_240);
            // the parent of this neighbour is the current field
            n->dir_240->parent = n;
            // set g value of neighbour
            n->dir_240->g = steps;
        }
    }
    // if controllNeighbour returns true we can add this neighbour to the open list
    if(n->dir_300 != 0){
        if(controllNeighbour(n->dir_300)){
            openList.push_back(n->dir_300);
            // the parent of this neighbour is the current field
            n->dir_300->parent = n;
            // set g value of neighbour
            n->dir_300->g = steps;
        }
    }
    // now we have controlled every neighbour of the current field an added all valid neighbours to the open list

}

bool SearchAlgorithm::controllNeighbour(Field *directionField)
{
    // methode returns false if:
    //      -> field is ocupied
    //      -> field is allready in the openlist
    //      -> field is allready in the visited list

    // is field in the openList?
    bool inOpenList = false;
    for(vector<Field*>::iterator listIterator = openList.begin(); listIterator != openList.end(); ++listIterator){
        if(directionField == *listIterator){
            Field* x = *listIterator;
            //cout << directionField->number << "allready in openlist with g =" << directionField->g << " current g = " << currentSolution->g << endl;
            // check if the g value of the parent from the existing field in the openlist is better than the current
            if(x->parent->g > currentSolution->g){
                x->parent = currentSolution;
            }

            inOpenList = true;
            break;
        }
    }
    // is field in the visitedList?
    bool inVisitedList = false;
    for(vector<Field*>::iterator listIterator = visitedList.begin(); listIterator != visitedList.end(); ++listIterator){
        if(directionField == *listIterator){
            inVisitedList = true;
            break;
        }
    }
    // is field occupied?
    // ....implement later the posibility to jump
    //    bool occupied = false;
    //    if(directionField->data != '.'){
    //        occupied = true;
    //    }

    if(!inOpenList && !inVisitedList){
        cout << "field " << directionField->number << " added to openlist" << endl;
        //set g value
        directionField->g = steps;
        return true;
    }else{
        return false;
    }
}

void SearchAlgorithm::findPath(){
    setStartAndGoal();
    // if we have not reached the goalFild OR if there is no possibility left (openList empty) make the next searchstep
    while(!goalReached){
        searchStep();

        //cout << "next best step field" << getNextBestField()->number;
    }



}


void SearchAlgorithm::print(){
    // go through the list
    gameBoard.print_h();
}


