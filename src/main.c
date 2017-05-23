#include "avl.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
	avl_node_t *root = NULL;

	for(size_t i = 0; i < 0x20; i++) {
		root = avl_insert(root, rand() >> 24, NULL);
	}

	char *in = avl_in(root);
	printf("%s\n", in);
	free(in);

	avl_destroy(root);

	return EXIT_SUCCESS;
}
