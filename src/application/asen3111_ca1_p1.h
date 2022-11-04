#pragma once

#include "src/core/allocator.h"
#include <stddef.h>

/// Givens
#define D_CYL 1.0     // Diameter [m]
#define V_INF 30.0    // Freestream Velocity [m/s]
#define RHO_INF 1.225 // Freestream Density [kg/m^3]
#define P_INF 101.3e3 // Freestream Density [kg/m^3]

typedef struct ak_doubleArray {
  size_t len;

  double *arr;
} ak_doubleArray;

// TODO: Maxk CpArray its own type (fat pointer?)

// TODO: Function to free CpArray (free internal pointer too)

/// Calculates the Coefficent of Pressure for varying panel numbers (up to
/// nmax).
ak_doubleArray *variedPanelsCp(const ak_Allocator *allocator,
                               const size_t nmax);

/// Saves array of Coefficent of Pressures into file.
void saveVariedCpArray(ak_doubleArray *arr, const char *filename,
                       const size_t nmax);
