#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

/*OVERVIEW OF PATHSEARCHING
  findPath -> called from playerEngine and returns the first step (makable move in one round) of the found path
    searchStep() -> until goalField reached
        getNextBestField()
            make a*
                if i can jump make BF Search
    -> cout the shortest path
    return the first step of the path (makable move in one round)
*/


/* http://www.policyalmanac.org/games/aStarTutorial_de.html
 * Prinzipieller Ablauf des A* Algorithmus
 *   1) Fuege das Startquadrat der offenen Liste hinzu.
 *   2) Wiederhole das Folgende:
 *       a)	Suche in der offenen Liste nach dem Quadrat mit dem niedrigsten F-Wert. Wir bezeichnen dieses Quadrat im Folgenden als das aktuelle Quadrat.
 *       b)	Verschiebe es in die geschlossene Liste.
 *       c)	Fuer jedes der 8 an das aktuelle Quadrat angrenzenden Quadrate:
 *          - Wenn es nicht begehbar ist oder sich bereits in der geschlossenen Liste befindet, ignoriere es; andernfalls mach das Folgende:
 *              >Wenn es nicht in der offenen Liste ist, fuege es der offenen Liste hinzu. Trage das aktuelle Quadrat als Vorgaengerquadrat dieses Quadrats ein. Trage zustaezlich die Werte fr die F-, G- und H-Kosten dieses Quadrates ein.
 *              >Falls es bereits in der offenen Liste ist, puerfe, ob der Pfad vom aktuellen Quadrat zu ihm - gemessen am G-Wert -, besser ist, als der Pfad von seinem eingetragenen Vorgngerquadrat (ein geringerer G-Wert bedeutet einen besseren Pfad). Falls dem so ist, ndere sein Vorgngerquadrat auf das aktuelle Quadrat und berechne seine Werte fr G und F neu. Sofern Du Deine offene Liste nach dem F-Wert sortiert hast, ist mglicherweise eine Neusortierung dieser Liste erforderlich, um dieser Vernderung Rechnung zu tragen.
 *       d) Beende den Prozess, falls:
 *          Du das Zielquadrat in die geschlossene Liste verschoben hast; in diesem Fall hast Du den Pfad ermittelt
 *          kein Zielquadrat gefunden werden konnte und die offene Liste leer ist; in diesem Fall gibt es keinen Pfad.
 *
 *   3)	Sichere den Pfad. Der Pfad erschliet sich, indem Du vom Zielquadrat aus Quadrat fr Quadrat
 *      rckwrts schreitend das Startquadrat erreichst.
 */





#include "board.h"
#include "iterator.h"
#include "field.h"
#include <vector>
#include <list>
#include <time.h>
#define DEBUG_HEURISTIC 0

using namespace std;

class Field;
class Board;

class SearchAlgorithm
{
public:
    SearchAlgorithm(Board &board, Field* startField, Field* goalField):gameBoard(board),start(startField), goal(goalField){goalReached = false; noWayToGoal = false; bfSteps = 0; steps = 0; inizializeLists();}

    Field* getGoalField();
    Field* getStartField();

    static bool quickSortCompareFunction(Field *a, Field *b);
    static bool bfSearchQuickSortCompareFunction(Field *a, Field *b);

    // method that searches the path form start to goal and safes it into the shortest path list
    Field *findPath();

    void print();           // print the star with heuristic values
    void setRandomStones(int max_stones =13); // set Random Stones into the field


private:
    // calculates the heuristic with circles start by the goal field
    void startHeuristicsCircular();
    bool setHeuristicsCircular(Field* currentField);
    void setNeighbourHeuristic(Field* currentField);

    bool isInOpenList(Field* directionField);
    bool isInVisitedList(Field* directionField);
    bool isInBFSearchList(Field* directionField);
    bool isOccupied(Field* directionField);


    void startBFSearch(Field* currentField);
    bool stepBFSearch(Field * currentField);
    void tryToJump(Field* currentField);




    // inizialize start an goal fields
    void setStartAndGoal();

    // inizialize the lists
    void inizializeLists();

    // this method returns the neighbour with the best f value
    Field* getNextBestField();
    void searchStep();

    Board &gameBoard;       // the current gameboard situation

    // counter for the steps already made
    int steps;

    // step counter for the bfSearch
    int bfSteps;

    bool goalReached;
    bool noWayToGoal;

    Field* currentSolution; // the field which is currently the best solution
    Field* start;           // the start field from which the algorithm starts
    Field* goal;            // the goal field where the algorithm wants to go
    Field* m_BFstartField;

    list <Field*> openList;
    list <Field*> visitedList;
    list <Field*> shortestPath;
    list <Field*> bfSearchList;     // list for multiple jump

    vector <Field*> NodeList;           // List for heuristic


};

#endif // SEARCHALGORITHM_H
