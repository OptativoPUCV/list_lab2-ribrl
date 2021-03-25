#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;//nodo inicial
    Node * tail;//nodo final
    Node * current;//nodo actual
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);//si el nodo existe no hace nada
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
	List * list = (List*) calloc (1, sizeof(List));
	list->head = NULL;
	list->current = NULL;
	list->tail = NULL;
    return list;
	//como la lista está vacía el primer, último y actual elemento son NULL
}

void * firstList(List * list) {
	if(list->head && list->head->data) {
		list->current = list->head;
		return (void*)list->head->data;
	}
    return NULL;
}

void * nextList(List * list) {
    if(list->current && list->current->data && list->current->next != NULL) {
		list->current = list->current->next;
		return (void*)list->current->data;
	}
    return NULL;
}

void * lastList(List * list) {
    if(list->tail && list->tail->data) {
		list->current = list->tail;
		return (void*)list->tail->data;
	}
    return NULL;
}

void * prevList(List * list) {
    if(list->current && list->current->data) {
		list->current = list->current->prev;
		return (void*)list->current->data;
	}
    return NULL;
}

void pushFront(List * list, const void * data) {
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}