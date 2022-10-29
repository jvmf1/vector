#include "vector.h"
#include <stdio.h>

int main() {
	vector v;
	vector_init(&v, sizeof(int));

	for (int i = 0; i < 100; i++)
		vector_append(&v, &i, 1); // In a real application, should check if the return is 0

	vector_print(&v);

	for (int i = 0; i < 100/2; i++)
		vector_pop(&v, i);

	for (int i = 0; i < v.len; i++)
		printf("%d\n", *(int*)vector_at(&v, i));

	vector_print(&v);

	vector_free(&v);
}
