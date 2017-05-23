#include "avl.h"

#include <stdlib.h>
#include <stdio.h>

/* get the height at a node */
static int avl_height(avl_node_t *n) {
	if(!n) {
		return 0;
	}

	return n->height;
}

/* recalculate the height of a node */
static void avl_reheight(avl_node_t *n) {
	n->height = max(avl_height(n->left), avl_height(n->right)) + 1;
}

/* rotate the tree to the right around a node */
static avl_node_t *avl_rotate_right(avl_node_t *old_root) {
	avl_node_t *new_root = old_root->left;

	old_root->left = new_root->right;
	new_root->right = old_root;

	avl_reheight(new_root);
	avl_reheight(old_root);

	return new_root;
}

/* rotate the tree to the left around a node */
static avl_node_t *avl_rotate_left(avl_node_t *old_root) {
	avl_node_t *new_root = old_root->right;

	old_root->right = new_root->left;
	new_root->left = old_root;

	avl_reheight(old_root);
	avl_reheight(new_root);

	return new_root;
}

/* calculate the balance value for a node */
static int avl_balance(avl_node_t *n) {
	if(!n) {
		return 0;
	}

	return avl_height(n->left) - avl_height(n->right);
}

/* rebalance the (sub)tree with root node */
static avl_node_t *avl_rebalance(avl_node_t *node) {
	avl_reheight(node);

	int b = avl_balance(node);

	if(b == 2) {
		if(avl_balance(node->left) < 0) {
			node->left = avl_rotate_left(node->left);
		}

		return avl_rotate_right(node);
	}

	if(b == -2) {
		if(avl_balance(node->right) > 0) {
			node->right = avl_rotate_right(node->right);
		}

		return avl_rotate_left(node);
	}

	return node;
}

/* find the node with the lowest key */
static avl_node_t *avl_find_min(avl_node_t *n) {
	if(n->left) {
		return avl_find_min(n->left);
	} else {
		return n;
	}
}

/* create a new node for insertion */
static avl_node_t *avl_new_node(int key, void *data) {
	avl_node_t *node = (avl_node_t *) malloc(sizeof(avl_node_t));

	node->key = key;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return node;
}

avl_node_t *avl_insert(avl_node_t *node, int key, void *data) {
	if(!node) {
		return avl_new_node(key, data);
	}

	if(key < node->key) {
		node->left = avl_insert(node->left, key, data);
	} else if(key > node->key) {
		node->right = avl_insert(node->right, key, data);
	} else {
		return node;
	}

	return avl_rebalance(node);
}

avl_node_t *avl_remove(avl_node_t *root, int key) {
	if(!root) {
		return NULL;
	}

	if(key < root->key) {
		root->left = avl_remove(root->left, key);
	} else if(key > root->key) {
		root->right = avl_remove(root->right, key);
	} else {
		if(!root->left || !root->right) {
			avl_node_t *temp = root->left ? root->left : root->right;

			if(!temp) {
				temp = root;
				root = NULL;
			} else {
				*root = *temp;
			}

			free(temp);
		} else {
			avl_node_t *temp = avl_find_min(root->right);

			root->key = temp->key;
			root->right = avl_remove(root->right, temp->key);
		}
	}

	if(!root) {
		return root;
	}

	avl_reheight(root);
	return avl_rebalance(root);
}

avl_node_t *avl_search(avl_node_t *n, int key) {
	if(!n) {
		return NULL;
	}

	if(key < n->key) {
		return avl_search(n->left, key);
	} else if(key > n->key) {
		return avl_search(n->right, key);
	} else {
		return n;
	}
}

void avl_destroy(avl_node_t *n) {
	if(!n) {
		return;
	}

	if(n->left) {
		avl_destroy(n->left);
	}

	if(n->right) {
		avl_destroy(n->right);
	}

	free(n);
}

static char *_avl_pre(avl_node_t *root, char *buf) {
	if(root) {
		asprintf(&buf, "%s%ld ", buf, root->key);
		if(root->left) buf = _avl_pre(root->left, buf);
		if(root->right) buf = _avl_pre(root->right, buf);
	}

	return buf;
}

static char *_avl_in(avl_node_t *root, char *buf) {
	char *n;

	if(root) {
		if(root->left) buf = _avl_in(root->left, buf);
		asprintf(&n, "%s%ld ", buf, root->key);
		if(root->right) buf = _avl_in(root->right, buf);
		free(buf);
	}


	return n;
}

static char *_avl_post(avl_node_t *root, char *buf) {
	if(root) {
		if(root->left) buf = _avl_post(root->left, buf);
		if(root->right) buf = _avl_post(root->right, buf);
		asprintf(&buf, "%s%ld ", buf, root->key);
	}

	return buf;
}

char *avl_pre(avl_node_t *root) {
	char *buf = (char *) calloc(1, 1);

	return _avl_pre(root, buf);
}

char *avl_in(avl_node_t *root) {
	char *buf = (char *) calloc(1, 1);

	return _avl_in(root, buf);
}

char *avl_post(avl_node_t *root) {
	char *buf = (char *) calloc(1, 1);

	return _avl_in(root, buf);
}
