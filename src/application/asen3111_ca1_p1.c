#include "asen3111_ca1_p1.h"
#include "src/core/numerical_integration.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

/// Represents the cirulation about a (rotating) cylinder.
///
/// Gamma =  pi * R * V_inf
static inline double Gamma(double radius, double vinf) {
  // return M_PI * radius * vinf;
  return 0;
}

/// Coefficient of Pressure of a cylinder.
///
/// Cp(theta) = 1 - [4*sin^2(theta) + 2*Gamma*sin(theta)/pi*R*V_inf +
/// (Gamma/2*pi*R*V_inf)^2]
static inline double Cp(double theta, double radius, double vinf) {
  double gamma = Gamma(radius, vinf);

  double term1 = 4 * sin(theta) * sin(theta);
  double term2 = (2 * gamma * sin(theta)) / (M_PI * radius * vinf);
  double term3 =
      (gamma * gamma) / (4 * M_PI * M_PI * radius * radius * vinf * vinf);

  return 1 - (term1 + term2 + term3);
}

ak_doubleArray *variedPanelsCp(const ak_Allocator *allocator,
                               const size_t nmax) {
  // Limits of integration
  double a = 0;
  double b = 2 * M_PI;

  // Stores all the values of Cp
  ak_doubleArray *Cp_lists = (*allocator->alloc)(nmax, sizeof(ak_doubleArray));

  for (size_t N = 0; N < nmax; N++) {
    // Thetas
    double *thetas = ak_linspace(allocator, a, b, N + 1);

    // Array of Cps for each panel number
    ak_doubleArray Cps;
    Cps.len = N + 1;
    Cps.arr = (*allocator->alloc)(N + 1, sizeof(double));

    for (size_t i = 0; i < N + 1; i++) {
      Cps.arr[i] = Cp(thetas[i], D_CYL / 2.0, V_INF);
    }

    // Store list of Cps for current N
    Cp_lists[N] = Cps;
  }

  return Cp_lists;
}

double radToDeg(double radians) { return radians * (180.0 / M_PI); }

void saveVariedCpArray(const ak_Allocator *allocator, ak_doubleArray *arr,
                       const char *filename, const size_t nmax) {

  FILE *fid = fopen(filename, "wb");
  if (!fid) {
    fprintf(stderr, "[ERROR] Unable to open file %s", filename);
  }

  for (size_t i = 0; i < nmax; i++) {
    // Thetas
    double *thetas = ak_linspace(allocator, 0, 2 * M_PI, i + 1);

    for (size_t j = 0; j < arr[i].len; j++) {
      fprintf(fid, "%f %f\n", radToDeg(thetas[j]), arr[i].arr[j]);
    }
    fprintf(fid, "\n");
  }
}
