#pragma once

#include "allocator.h"
#include <stddef.h>

double ak_trapz(const ak_Allocator *allocator, double (*f)(double x),
                double range[2], size_t num_panels);

// TODO: Create a simpson function too!

double *ak_linspace(const ak_Allocator *allocator, double start, double end,

                    size_t num_elems);
