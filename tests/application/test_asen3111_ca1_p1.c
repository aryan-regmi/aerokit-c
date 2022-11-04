#include "external/acutest/acutest.h"
#include "src/application/asen3111_ca1_p1.h"
#include "utils.h"

void canCalcCpWithVariedPanels(void) {
  const size_t NMAX = 10;

  ak_doubleArray *Cps = variedPanelsCp(&GPA, NMAX);

  TEST_CHECK(ak_doubleEq(Cps[0].arr[0], 0.75, 0.001));
  TEST_CHECK(
      ak_doubleEq(Cps[NMAX - 1].arr[Cps[NMAX - 1].len - 1], 0.75, 0.001));
  TEST_CHECK(Cps != NULL);
}

void canSaveVariedCpArray(void) {
  const size_t NMAX = 100;

  ak_doubleArray *Cps = variedPanelsCp(&GPA, NMAX);

  saveVariedCpArray(&GPA, Cps,
                    "/home/aryan/Documents/Dev/C/aerokit/data/tst.csv", NMAX);
}

TEST_LIST = {{"[APPLICATION] Can calculate Cp for varying number of panels",
              canCalcCpWithVariedPanels},
             {"[APPLICATION] Can save Cp array", canSaveVariedCpArray},
             {NULL, NULL}};
