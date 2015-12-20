#include "BoundedSphere.h"

BoundedSphere::BoundedSphere(Vector3D p, int id, float r)
{
  point = p;
  messageId = id;
  radius = r;
}