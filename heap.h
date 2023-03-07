#ifndef HEAP_H
#define HEAP_H

struct heap_node_s{
	void *data;
	struct heap_node_s *left;
	struct heap_node_s *right;
	int r_height;
	int l_height;
};

struct heap_s{
	struct heap_node_s *root;
	int height;
	int nodes_num;
};

void heap_init(struct heap_s *heap);
void heap_push(struct heap_s *heap,void *data,int (*cmp)(void *,void *));
void *heap_get_root(struct heap_s *heap);
void *heap_extract_root(struct heap_s *heap,int (*cmp)(void *,void *));
int heap_get_height(struct heap_s *heap);
int heap_get_nodes_num(struct heap_s *heap);
void heap_free(struct heap_s *heap);
void heap_freee(struct heap_s *heap,void (*free_data)(void *));

#endif
