#ifndef __BOUNDEDBOX_H
#define __BOUNDEDBOX_H 

#include "structs.h"

class BoundedBox{
public:
  Vector3D min; //p1 point of our bounded box
  Vector3D max; //p2 point of our bounded box
  int shapeId; //id for the shape that the bounding box is for in the node graph

  BoundedBox(double p1[], double p2[], int id);
};

#endif


