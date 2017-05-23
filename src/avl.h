#pragma once

typedef struct avl_node {
	long key;
	void *data;
	struct avl_node *left;
	struct avl_node *right;
	int height;
} avl_node_t;

#ifndef min
	#define min(a, b) __extension__({__typeof__(a) _a = (a); __typeof__(b) _b = (b); _a < _b ? _a : _b; })
#endif

#ifndef max
	#define max(a, b) __extension__({__typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b ? _a : _b; })
#endif

avl_node_t *avl_insert(avl_node_t *node, int key, void *data);
avl_node_t *avl_remove(avl_node_t *n, int key);
avl_node_t *avl_search(avl_node_t *n, int key);
void avl_destroy(avl_node_t *n);

char *avl_pre(avl_node_t *root);
char *avl_in(avl_node_t *root);
char *avl_post(avl_node_t *root);
