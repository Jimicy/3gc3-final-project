#include "BoundedBox.h"

BoundedBox::BoundedBox(double p1[], double p2[], int id)
{
  min.x = p1[0];
  min.y = p1[1];
  min.z = p1[2];
  max.x = p2[0];
  max.y = p2[1];
  max.z = p2[2];
  shapeId = id;
}