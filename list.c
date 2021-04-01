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
	if (list->head && list->head->data) {
		list->current = list->head;
		return (void*)list->head->data;
	}
    return NULL;
}

void * nextList(List * list) {
    
	if ((list->current) && (list->current->next != NULL)) 
	{
		list->current = list->current->next;
	} else { 
		return NULL;
	}	
	return (void*)list->current->data;
}


void * lastList(List * list) {
    if(list->tail && list->tail->data) {
		list->current = list->tail;
		return (void*)list->tail->data;
	}
    return NULL;
}

void * prevList(List * list) {
    if(list->current && list->current->prev != NULL) {
		list->current = list->current->prev;
		return (void*)list->current->data;
	}
    return NULL;
}

void pushFront(List * list, const void * data) {
	Node* newNode = createNode (data);
	newNode->prev = NULL;
	newNode->data = data;
	newNode->next = list->head;

	if (list->head == NULL) {
		list->head = newNode;
		list->tail = newNode;
	} 
	else 
	{
		newNode->next = list->head;
		list->head->prev = newNode;
	}

	list->head = newNode;
}

void pushBack(List * list, const void * data) {
	list->current = list->tail;
	pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
	Node* newNode = createNode (data);
	
	if (list->head == NULL) {
		list->head = newNode;
		list->tail = newNode;
		newNode->prev = NULL;
		newNode->next = NULL;
	}
	else 
	{
		if (list->current->next == NULL) {
			newNode->prev = list->current;
			newNode->next = NULL;
			list->current->next = newNode;
			list->tail = newNode;
		}else{
      		newNode->prev = list->current;
			newNode->next = list->current->next;
			list->current->next = newNode;

    	}   
	}
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
	//si sólo hay un elemento
	if (list->head == list->tail) {
		list->head = NULL;
		list->tail = NULL;
		return (void*)list->head->data;
		free (list->head);
		list->current = NULL;
	}
	else 
	{
	//si el current está al inicio
		if (list->current == list->head ) {
			list->head = list->head->next;
			list->head->prev = NULL;
			return (void*)list->head->data;
			free (list->head);
			list->current = list->head->next;
		}
	//si el current está al final
		if (list->current == list->tail){
			list->tail = list->tail->prev;
			list->tail->prev->next = NULL;
			return (void*)list->tail->data;
			free (list->tail);
			list->current = NULL;
		}
	//si el current está en la lista 
		list->current->prev->next = list->current->next;
		list->current->next->prev = list->current->prev;
		return (void*)list->current->data;
		free (list->current);
		list->current = list->current->next;
	}
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}