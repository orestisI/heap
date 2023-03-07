#include"heap.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ex_s{
	int id;
	char *name;
};

void ex_init(struct ex_s *ex,int id,const char *name){
	ex->id = id;
	ex->name = (char *)malloc(strlen(name) + 1);
	strcpy(ex->name,name);
}

void ex_free(void *v){
	struct ex_s *ex = (struct ex_s *)v;
	free(ex->name);
}

void ex_print(void *v){
	struct ex_s *ex = (struct ex_s *)v;
	printf("------\n");
	printf("id = %d\n",ex->id);
	printf("Name = %s\n",ex->name);
	printf("\n");
}

int ex_cmp(void *v1,void *v2){
	struct ex_s *ex1 = (struct ex_s *)v1;
	struct ex_s *ex2 = (struct ex_s *)v2;

	return ex1->id > ex2->id;
}

void heap_sort(){
	struct heap_s heap;
	heap_init(&heap);
	//
	struct ex_s ex1,ex2,ex3,ex4;
	ex_init(&ex1,0,"orestis");
	ex_init(&ex2,1,"antry");
	ex_init(&ex3,2,"romina");
	ex_init(&ex4,3,"ippokratis");
	//
	heap_push(&heap,&ex2,ex_cmp);
	heap_push(&heap,&ex1,ex_cmp);
	heap_push(&heap,&ex3,ex_cmp);
	heap_push(&heap,&ex4,ex_cmp);
	//
	void *p1,*p2,*p3,*p4;
	p1 = heap_extract_root(&heap,ex_cmp);
	p2 = heap_extract_root(&heap,ex_cmp);
	p3 = heap_extract_root(&heap,ex_cmp);
	p4 = heap_extract_root(&heap,ex_cmp);
	//
	ex_print(p1);
	ex_print(p2);
	ex_print(p3);
	ex_print(p4);
	//
	heap_freee(&heap,ex_free);
}

int main(){
	heap_sort();

	return 1;
}

