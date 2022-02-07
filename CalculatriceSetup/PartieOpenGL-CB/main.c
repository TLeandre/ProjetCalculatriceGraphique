/**************************
 * Includes
 *
 **************************/

#include "graph.h"
#include <math.h>
#include "glut.h"
#include "functiongraph.h"

void main(int ac,char *av[])
{
    InitGraph(ac,av,"Calculatrice Graphique",960,960,DrawLine,myKey);

}
