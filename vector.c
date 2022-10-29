#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void vector_init(vector* v, const size_t size) {
	v->size=size;
	v->nmemb=0;
	v->cap=0;
	v->data=NULL;
}

void vector_free(vector* v) {
	v->nmemb=0;
	v->cap=0;
	free(v->data);
	v->data=NULL;
}

void vector_clear(vector* v) {
	v->nmemb=0;
}

void vector_print(const vector* v) {
	printf("<vector@%p size=%zu nmemb=%zu cap=%zu data@%p>\n", v, v->size, v->nmemb, v->cap, v->data);
}

int vector_cap_grow(vector *v, const size_t nmemb) {
	void *tmp;
	if ((tmp = realloc(v->data, (v->cap + nmemb)*v->size))==NULL)
		return 1;
	v->cap+=nmemb;
	v->data=tmp;
	return 0;
}

int vector_cap_reserve(vector *v, const size_t nmemb) {
	if (v->cap >= nmemb)
		return 0;
	if (vector_cap_grow(v, nmemb - v->cap) != 0)
		return 1;
	return 0;
}

int vector_write(vector *v, const void *data, const size_t nmemb) {
	if (vector_cap_reserve(v, nmemb) != 0)
		return 1;
	v->nmemb = nmemb;
	memcpy(v->data, data, nmemb*v->size);
	return 0;
}

int vector_append(vector *v, const void *data, const size_t nmemb) {
	if (vector_cap_reserve(v, nmemb+v->nmemb) != 0)
		return 1;
	memcpy(v->data+(v->size*v->nmemb), data, nmemb*v->size);
	v->nmemb += nmemb;
	return 0;
}

void* vector_at(const vector *v, const size_t index) {
	assert(index < v->nmemb);
	return v->data+(index*v->size);
}

void vector_pop(vector *v, const size_t index) {
	assert(index < v->nmemb);
	memmove(v->data+(v->size*index), v->data+(v->size*(index+1)), v->size*(v->nmemb-index-1));
	v->nmemb--;
}

bool vector_isempty(const vector *v) {
	return v->nmemb == 0;
}

bool vector_isfull(const vector *v) {
	return v->nmemb == v->cap;
}
