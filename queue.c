#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "sort.c"
#include "sort.h"
/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh;
    newh = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s) + 1);
    if (newh->value[strlen(s)] != '\0') {
        free(newh->value);
        free(newh);
        return false;
    }
    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newt = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    newt->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (!newt->value) {
        free(newt);
        return false;
    }
    newt->next = NULL;
    strncpy(newt->value, s, strlen(s) + 1);
    if (newt->value[strlen(s)] != '\0') {
        free(newt->value);
        free(newt);
        return false;
    }
    if (!q->head) {
        q->head = newt;
    } else {
        q->tail->next = newt;
    }
    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;

    list_ele_t *tmp = q->head;
    if (sp) {
        strncpy(sp, tmp->value, bufsize);
        if (sp[bufsize - 1] != '\0') {
            return false;
        }
    }
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    if (!q->head)
        q->tail = NULL;
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *pre, *current;
    if (!q)
        return;
    if (q->size <= 1)
        return;
    pre = NULL;
    current = q->head;
    q->tail = q->head;
    while (current->next) {
        list_ele_t *tmp = current;
        current = current->next;
        tmp->next = pre;
        pre = tmp;
    }
    current->next = pre;
    q->head = current;
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || !q->head)
        return;
    if (q->size <= 1)
        return;
    mergesort(&(q->head));
    while (q->tail->next)
        q->tail = q->tail->next;
}
