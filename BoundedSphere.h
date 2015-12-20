#ifndef __BOUNDEDSPHERE_H
#define __BOUNDEDSPHERE_H 

#include "structs.h"

class BoundedSphere{
public:
  Vector3D point; //center point of our bounded sphere
  int messageId; //id for the shape that the bounding box is for in the node graph
  float radius;

  BoundedSphere(Vector3D p, int id, float r);
};

#endif


