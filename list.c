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
    Node* nodoActual = createNode(data);
    if (list->head){
        list->head->prev = nodoActual;
        nodoActual->next = list->head;
        list->head = nodoActual;
    }
    else {
        list->head = nodoActual;
        list->tail = nodoActual;
    }
}

void pushBack(List * list, void * data) {
    Node *nodoActual = createNode(data);
    if (list->tail){
        nodoActual->prev = list->tail;
        list->tail->next = nodoActual;
        list->tail = nodoActual;
    }
    else list->tail = nodoActual;

}

void pushCurrent(List * list, void * data) {
    if(list->current){
        Node *nodoActual = createNode(data);
        Node *aux = list->current->next;
        list->current->next = nodoActual;
        nodoActual->prev = list->current;
        if(aux != NULL){
            aux->prev = nodoActual;
            nodoActual->next = aux;
        }
        else list->tail = nodoActual;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    void * dato = list->head->data;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL; 
    } 
    else {
        list->tail = NULL;
    return dato;
    }
}

void * popBack(List * list) {
    list->current = list->tail;
    void * dato = list->head->data;
    list->tail = list->tail->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    return dato;
}

void * popCurrent(List * list) {
    void *dato = list->current->data;
    if (list->current == list->head)
        dato = popFront(list);
    else if (list->current == list->tail)
        dato = popBack(list);
    else {
        Node *anterior = list->current->prev;
        Node *siguiente = list->current->next;
        anterior->next = siguiente;
        siguiente->prev = anterior;
        list->current = siguiente;
    }
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}