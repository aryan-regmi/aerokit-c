#pragma once

#include <math.h>
#include <stdbool.h>

bool ak_doubleEq(double a, double b, double tolerance) {
  if (fabs(b - a) < tolerance) {
    return true;
  }

  return false;
}
