#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
	size_t size;
	size_t len;
	size_t cap;
	void *data;
} vector;

void vector_init(vector *v, const size_t size);
void vector_free(vector *v);
void vector_clear(vector *v);
void vector_print(const vector *v);
int vector_cap_grow(vector *v, const size_t len);
int vector_cap_reserve(vector *v, const size_t len);
int vector_write(vector *v, const void *data, const size_t len);
int vector_append(vector *v, const void *data, const size_t len);
void* vector_at(const vector *v, const size_t index);
void vector_pop(vector *v, const size_t index);
bool vector_isempty(const vector *v);
bool vector_isfull(const vector *v);
void vector_replace(vector *v, void *before, void *after);
bool vector_contains(const vector *v, const void *data);
size_t vector_index(const vector *v, const void *data);
size_t vector_index_ex(const vector *v, const void *data, size_t start);
