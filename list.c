#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * list=(List*) malloc (sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    list->current = list->head;
    return list->head;
}

void * nextList(List * list) {
    if(list->current->next != NULL){
        list->current = list->current->next;
    }
    return list->current;
}

void * lastList(List * list) {
    return list->tail;
}

void * prevList(List * list) {
    return NULL;
}

void pushFront(List * list, void * data) {
    Node *nodoActual = createNode(data);
    list->tail->next = nodoActual;
    nodoActual->prev = list->tail;
    nodoActual->next = NULL;
    list->tail = nodoActual;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nodoActual = createNode(data);
    list->current->next = nodoActual;
    nodoActual->prev = list->current;
    nextList(list);
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