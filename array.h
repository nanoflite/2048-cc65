#ifndef __ARRAY_H__
#define __ARRAY_H__

typedef struct array {
  void **elements;
  size_t length;
} array;

// array * array_new(size_t size);
void array_init(array *array, size_t size);

void array_add(array *array, void *element);

size_t array_length(array *array);

void * array_get(array *array, size_t index);

void array_destroy(array *array);

#endif
