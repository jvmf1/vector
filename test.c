#include "vector.h"
#include <stdio.h>
#include <string.h>

int main() {
	vector v;
	vector_init(&v, sizeof(int));

	for (int i = 0; i < 100; i++)
		vector_append(&v, &i, 1);

	vector_print(&v);

	for (int i = 0; i < 100/2; i++)
		vector_pop(&v, i);

	for (int i = 0; i < v.nmemb; i++)
		printf("%d\n", *(int*)vector_at(&v, i));

	vector_print(&v);

	vector_free(&v);
}
