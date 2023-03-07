#include"heap.h"
#include<stdio.h>
#include<stdlib.h>

#define max(a,b) ((a < b) ? a : b)
#define is_leaf(a) (a->left == NULL && a->right == NULL)

void heap_init(struct heap_s *heap){
	heap->root = NULL;
	heap->height = 0;
	heap->nodes_num = 0;
}

int heap_push_h(struct heap_node_s *root,struct heap_node_s *n_node,
		int (*cmp)(void *,void *)){
	if (cmp(n_node->data,root->data)){
		void *data = root->data;
		root->data = n_node->data;
		n_node->data = data;
		heap_push_h(root,n_node,cmp);
	}
	else{
		if (root->l_height > root->r_height){
			if (root->right == NULL){
				root->right = n_node;
				root->r_height = 1;
			}
			else{
				int r_height;
				r_height = heap_push_h(root->right,n_node,cmp);
				root->r_height = r_height + 1;
			}
		}
		else{
			if (root->left == NULL){
				root->left = n_node;
				root->l_height = 1;
			}
			else{
				int l_height;
				l_height = heap_push_h(root->left,n_node,cmp);
				root->l_height = l_height + 1;
			}
		}
	}
	return max(root->r_height,root->l_height);
}

void heap_push(struct heap_s *heap,void *data,int (*cmp)(void *,void *)){
	struct heap_node_s *heap_node = (struct heap_node_s *)
		malloc(sizeof(struct heap_node_s));
	heap_node->data = data;
	heap_node->left = NULL;
	heap_node->right = NULL;
	heap_node->r_height = 0;
	heap_node->l_height = 0;
	if (heap->root == NULL) {
		heap->root = heap_node;
	}
	else{
		heap->height = heap_push_h(heap->root,heap_node,cmp);
	}
	heap->nodes_num++;
}

void *heap_get_root(struct heap_s *heap){
	if (heap->root != NULL) return (heap->root)->data;
	return NULL;
}

//Begining from root that is assumed not to be a leaf, it 
//finds the data of a leaf,it removes the leaf from the tree
//it corrects requersively the heights.
int heap_extract_root_h1(struct heap_node_s *root,void **data){
	struct heap_node_s *left = root->left;
	struct heap_node_s *right = root->right;
	if (root->l_height >= root->r_height){
		if (is_leaf(left)){
			*data = left->data;
			root->left = NULL;
			root->l_height = 0;
			free(left);
		}
		else{
			root->l_height = heap_extract_root_h1(left,data) + 1;
		}
	}
	else{
		if (is_leaf(right)){
			*data = right->data;
			root->right = NULL;
			root->r_height = 0;
			free(right);
		}
		else{
			root->r_height = heap_extract_root_h1(right,data) + 1;
		}
	}
	return max(root->l_height,root->r_height);
}

//Corrects the tree
void heap_extract_root_h2(struct heap_node_s *root,int (*cmp)(void *,void *)){
	struct heap_node_s *left = root->left;
	struct heap_node_s *right = root->right;
	void *data = root->data;
	if (left == NULL){
		if (right != NULL){
			root->data = right->data;
			right->data = data;
		}
	}
	else{
		if (right == NULL){
			root->data = left->data;
			left->data = data;
		}
		else{
			if (cmp(left->data,right->data)){
				root->data = left->data;
				left->data = data;
				heap_extract_root_h2(left,cmp);
			}
			else{
				root->data = right->data;
				right->data = data;
				heap_extract_root_h2(right,cmp);
			}
		}
	}
}

void *heap_extract_root(struct heap_s *heap,int (*cmp)(void *,void *)){
	struct heap_node_s *root = heap->root;
	if (root == NULL) return NULL;
	void *res = root->data;
	if (is_leaf(root)){
		heap->root = NULL;
		heap->height = 0;
		heap->nodes_num = 0;
		free(root);
		return res;
	}
	void *data;
	heap->height = heap_extract_root_h1(root,&data);
	heap->nodes_num--;
	root->data = data;
	heap_extract_root_h2(root,cmp);
	return res;
}

int heap_get_height(struct heap_s *heap){
	return heap->height;
}

int heap_get_nodes_num(struct heap_s *heap){
	return heap->nodes_num;
}

void heap_free_h(struct heap_node_s *heap_node){
	if (heap_node != NULL){
		heap_free_h(heap_node->left);
		heap_free_h(heap_node->right);
		free(heap_node);
	}
}

void heap_free(struct heap_s *heap){
	heap_free_h(heap->root);
	heap->root == NULL;
	heap->height = 0;
	heap->nodes_num = 0;
}

void heap_freee_h(struct heap_node_s *heap_node,void (*free_data)(void *)){
	if (heap_node != NULL){
		heap_free_h(heap_node->left);
		heap_free_h(heap_node->right);
		free_data(heap_node->data);
		free(heap_node);
	}
}

void heap_freee(struct heap_s *heap,void (*free_data)(void *)){
	heap_freee_h(heap->root,free_data);
	heap->root == NULL;
	heap->height = 0;
	heap->nodes_num = 0;
}

