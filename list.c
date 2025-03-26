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
    if (list->head)
        return list->head->data;
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL && list->current->next != NULL){
        list->current = list->current->next;
        return list->current->data;
    }
    return NULL;
}

void * lastList(List * list) {
    if (list->tail){
        list->current = list->tail;
        return list->tail->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list->current != NULL && list->current->prev != NULL){
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node *nodoActual = createNode(data);
    if (list->tail)
        list->tail->next = nodoActual;
    nodoActual->prev = list->tail;
    list->tail = nodoActual;
}

void pushBack(List * list, void * data) {
    Node* nodoActual = createNode(data);
    nodoActual->next = list->head;
    if (list->head){
        list->head->prev = nodoActual;
    }
    nodoActual->prev = NULL;
    list->head = nodoActual;
}

void pushCurrent(List * list, void * data) {
    if(list->current){
        Node *nodoActual = createNode(data);
        Node *aux = list->current;
        list->current->next = nodoActual;
        nodoActual->prev = list->current;
        if(aux->next)
            aux->next->prev = nodoActual;
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
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}