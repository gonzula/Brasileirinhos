/*
//  list.h
//  DataStructures
//
//  Created by Gonzo Fialho on 5/16/14.
//  Copyright (c) 2014 CEAFDC. All rights reserved.
*/

#ifndef structures_list_h
#define structures_list_h


#define LIST_LOOP(_list) for (Node *node = _list->firstNode; node; node = node->next)

typedef struct _node
{
    void * object;
    struct _node * prev;
    struct _node * next;
} Node;

typedef struct
{
    Node * firstNode;
    Node * lastNode;
    int count;
} List;

List * list_init();
List * list_append(List *aList, void *object);
List * list_push(List *aList, void *object);
void * list_pop(List *aList);
void * list_dequeue(List *aList);
void list_iterate(List *aList, void (*obj_iteration)(void *obj, int i, int count, int *stop));


#endif
