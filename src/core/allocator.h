#pragma once

#include <stddef.h>
#include <stdlib.h>

typedef struct ak_Allocator {
  void *context;

  void *(*alloc)(size_t num_elements, size_t size_of_element);

  void (*free)(void *ptr);
} ak_Allocator;

static const ak_Allocator GPA = {.alloc = calloc, .free = free};
