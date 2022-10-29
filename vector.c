#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void vector_init(vector *v, const size_t size) {
	v->size=size;
	v->len=0;
	v->cap=0;
	v->data=NULL;
}

void vector_free(vector *v) {
	v->len=0;
	v->cap=0;
	free(v->data);
	v->data=NULL;
}

void vector_clear(vector *v) {
	v->len=0;
}

void vector_print(const vector *v) {
	printf("<vector@%p size=%zu len=%zu cap=%zu data@%p>\n", v, v->size, v->len, v->cap, v->data);
}

int vector_cap_grow(vector *v, const size_t len) {
	void *tmp;
	if ((tmp = realloc(v->data, (v->cap + len)*v->size))==NULL)
		return 1;
	v->cap+=len;
	v->data=tmp;
	return 0;
}

int vector_cap_reserve(vector *v, const size_t len) {
	if (v->cap >= len)
		return 0;
	if (vector_cap_grow(v, len - v->cap) != 0)
		return 1;
	return 0;
}

int vector_write(vector *v, const void *data, const size_t len) {
	if (vector_cap_reserve(v, len) != 0)
		return 1;
	v->len = len;
	memcpy(v->data, data, len*v->size);
	return 0;
}

int vector_append(vector *v, const void *data, const size_t len) {
	if (vector_cap_reserve(v, len+v->len) != 0)
		return 1;
	memcpy(v->data+(v->size*v->len), data, len*v->size);
	v->len += len;
	return 0;
}

void* vector_at(const vector *v, const size_t index) {
	assert(index < v->len);
	return v->data+(index*v->size);
}

void vector_pop(vector *v, const size_t index) {
	assert(index < v->len);
	memmove(v->data+(v->size*index), v->data+(v->size*(index+1)), v->size*(v->len-index-1));
	v->len--;
}

bool vector_isempty(const vector *v) {
	return v->len == 0;
}

bool vector_isfull(const vector *v) {
	return v->len == v->cap;
}

void vector_replace(vector *v, void *before, void *after) {
	void *tmp;
	for (size_t i = 0; i < v->len; i++)
		if (memcmp((tmp = vector_at(v, i)), before, v->size) == 0)
			memcpy(tmp, after, v->size);
}

bool vector_contains(const vector *v, const void *data) {
	void *tmp;
	for (size_t i = 0; i < v->len; i++)
		if (memcmp((tmp = vector_at(v, i)), data, v->size) == 0)
			return true;
	return false;
}

void* vector_index(const vector *v, const void *data) {
	void *tmp;
	for (size_t i = 0; i < v->len; i++)
		if (memcmp((tmp = vector_at(v, i)), data, v->size) == 0)
			return tmp;
	return NULL;
}
