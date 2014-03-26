#include <stdlib.h>
#include <stddef.h>

#include "array.h"

void array_init(array *array, size_t size)
{
  array->elements = malloc( size * sizeof(void*) );
  array->length = 0;
}

void array_add(array *array, void *element)
{
  array->elements[array->length] = element;
  array->length++;
}

size_t array_length(array *array)
{
  return array->length;
}

void * array_get(array *array, size_t index)
{
  return array->elements[index];
}

void array_destroy(array *array)
{
  free(array->elements);
  array->elements = NULL;
  array->length = 0;
}
