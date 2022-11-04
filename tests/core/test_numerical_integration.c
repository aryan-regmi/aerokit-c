#include "external/acutest/acutest.h"
#include "src/core/allocator.h"
#include "src/core/numerical_integration.h"
#include "src/core/utils.h"
#include <stdio.h>

void canCreateLinspaceVector(void) {
  size_t len = 6;
  double range[2] = {0, 5};

  double *vec = ak_linspace(&GPA, range[0], range[1], len);

  double step_size = (range[1] - range[0]) / len;

  double tolerance = 0.001;
  for (size_t i = 1; i < len - 1; i++) {
    TEST_CHECK(ak_doubleEq(vec[i], range[0] + i * step_size, tolerance));
    TEST_MSG("\nExpected: %f", range[0] + i * step_size);
    TEST_MSG("\nActual: %f", vec[i]);
  }
  TEST_CHECK(ak_doubleEq(vec[0], range[0], tolerance));
  TEST_CHECK(ak_doubleEq(vec[len - 1], range[1], tolerance));
}

/// y = x
double f(double x) { return x; }

void canTrapzIntegrate(void) {
  double integral = ak_trapz(&GPA, f, (double[2]){0, 3}, 4498);

  TEST_CHECK(ak_doubleEq(integral, 4.5, 0.001));
  TEST_MSG("\nExpected: %f", 4.5);
  TEST_MSG("\nActual: %f", integral);
}

TEST_LIST = {{"[NumericalIntegration] Can create `linspace` vector ",
              canCreateLinspaceVector},
             {"[NumericalIntegration] Can integate function with `trapz` ",
              canTrapzIntegrate},
             {NULL, NULL}};
