#include "LinearAxisMgi.h"

float StepsToMm(long steps, int pitch, int steps_per_rev)
{
  float dist_mm = float(steps) * (float(pitch) / float(steps_per_rev));
  return dist_mm;
}

long MmToSteps(float dist_mm, int pitch, int steps_per_rev)
{
  int steps = round(dist_mm * (float (steps_per_rev) / float(pitch)));
  return steps;
}