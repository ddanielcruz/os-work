#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef struct {
    // pthread_t info;
    int time;
    int priority;
} VALUE;

typedef struct ITEM_t {
   VALUE data;
   int key;
   struct ITEM_t *next;
} ITEM;

typedef struct List {
    ITEM *head;
    ITEM *tail;
    int size;
    int limit;
} List;

List *ConstructList(int limit);
int isListEmpty(List* list);
int isListFull(List* list);
int insertITEM(List *list, ITEM *item);
ITEM* getFirstITEM(List *list);
ITEM* getITEMByKey(List *list, int key);
void printList(List *list);
void sortList(List *list);

List *ConstructList(int limit) 
{
    List *list = (List*) malloc(sizeof (List));
    
    if (list == NULL)
        return NULL;

    if (limit <= 0)
        limit = 65535;
    
    list->limit = limit;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

int isListEmpty(List* list) 
{
    if (list == NULL)
        return FALSE;
    
    return (list->size == 0) ? TRUE : FALSE;
}

int isListFull(List* list) 
{
    if (list == NULL)
        return FALSE;

    return (list->size == list->limit) ? TRUE : FALSE;
}

int insertITEM(List *list, ITEM *item)
{
    if (list == NULL || item == NULL)
        return FALSE;

    if (list->size >= list->limit)
        return FALSE;

    if (list->size == 0) {
        list->head = item;
        list->tail = item;
    } else {
        list->tail->next = item;
        list->tail = item;
    }

    list->size++;
    
    return TRUE;
}

ITEM* getFirstITEM(List *list) 
{
   ITEM *tmp = list->head;
	
   list->head = list->head->next;
	
   return tmp;
}

ITEM* getITEMByKey(List *list, int key) 
{
    if (list == NULL)
        return NULL;

    if (isListEmpty(list))
        return NULL;

    ITEM* current = list->head;
    ITEM* next = NULL;

    while(current->key != key) {
        if(current->next == NULL)
            return NULL;
        else {
            next = current;
            current = current->next;
        }
    }


    if(current == list->head)
        list->head = list->head->next;
    else
        next->next = current->next; 

    list->size--;
    return current;
}

void printList(List *list)
{
   ITEM *ptr = list->head;
   printf("[ ");
	
   while(ptr != NULL) {
      printf("%d ",ptr->data.time);
      ptr = ptr->next;
   }
	
   printf("]\n");
}

void sortList(List *list) 
{
    int i, j, k, tempKey, tempData;
    ITEM *current;
    ITEM *next;

    int size = list->size;
    k = size;

    for (i = 0; i < size - 1; i++, k--) 
    {
        current = list->head;
        next = list->head->next;

        for (j = 1; j < k; j++) 
        {   
            if (current->data.time > next->data.time ) {
                tempData = current->data.time;
                current->data.time = next->data.time;
                next->data.time = tempData;

                tempKey = current->key;
                current->key = next->key;
                next->key = tempKey;
            }

            current = current->next;
            next = next->next;
        }
    }   
}