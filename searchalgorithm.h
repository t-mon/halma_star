#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

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
#include <algorithm>

#define DEBUG_HEURISTIC 1

using namespace std;

class Field;
class Board;

class SearchAlgorithm
{
public:
    SearchAlgorithm(Board &board, Field* startField, Field* goalField):gameBoard(board),start(startField), goal(goalField){goalReached = false; noWayToGoal = false;}

    Field* getGoalField();
    Field* getStartField();

    // calculates the heuristic with vectors
    void setHeuristicsGeometrical();
    // (OLD) calculates the heuristic with circles starting by the goal field
    void setHeuristicsCircular();
    // calculates the heuristic with circles start by the goal field
    void startHeuristicsCircular();

    // inizialize start an goal fields
    void setStartAndGoal();

    // inizialize the lists
    void inizializeLists();

    // this method returns the neighbour with the best f value
    Field* getNextBestField();
    void searchStep();
    bool controllNeighbour(Field* directionField);
    bool isInOpenList(Field* directionField);
    bool isInVisitedList(Field* directionField);
    bool isOccupied(Field* directionField);

    // method that searches the path form start to goal and safes it into the shortest path list
    void findPath();

    void print();           // print the star with heuristic values

private:
    bool setHeuristicsCircular2(Field* currentField);
    void setNeighbourHeuristic(Field* currentField);

    Board &gameBoard;       // the current gameboard situation

    // counter for the steps already made
    int steps;

    bool goalReached;
    bool noWayToGoal;

    Field* currentSolution; // the field which is currently the best solution
    Field* start;           // the start field from which the algorithm starts
    Field* goal;            // the goal field where the algorithm wants to go

    vector <Field*> openList;
    vector <Field*> visitedList;
    vector <Field*> shortestPath;

    vector <Field*> NodeList; // List for heuristic
};

#endif // SEARCHALGORITHM_H
