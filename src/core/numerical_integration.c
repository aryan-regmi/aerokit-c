#include "numerical_integration.h"

double sumd(size_t len, double *dlist) {
  double sum = 0;
  for (size_t i = 0; i < len; i++) {
    sum += dlist[i];
  }

  return sum;
}

// TODO: Do bounds checking
double *ak_linspace(const ak_Allocator *allocator, double start, double end,
                    size_t num_elems) {
  double step_size = (end - start) / num_elems;

  double *ret = (*allocator->alloc)(num_elems, sizeof(double));
  ret[0] = start;
  ret[num_elems - 1] = end;

  for (size_t i = 1; i < num_elems - 1; i++) {
    ret[i] = ret[i - 1] + step_size;
  }

  return ret;
}

double ak_trapz(const ak_Allocator *allocator, double (*f)(double x),
                double range[2], size_t num_panels) {
  double step_size = (range[1] - range[0]) / (double)num_panels;

  double *xs = ak_linspace(allocator, range[0], range[1], num_panels + 1);

  double res[num_panels];

  for (size_t i = 0; i < num_panels; i++) {
    res[i] = step_size * (((*f)(xs[i]) + (*f)(xs[i + 1])) / 2);
  }

  (*allocator->free)(xs);

  return sumd(num_panels, res);
}
