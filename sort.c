#include "sort.h"

#include <string.h>

#include "queue.h"


list_ele_t *sortedmerge(list_ele_t *l1, list_ele_t *l2)
{
    list_ele_t *result;
    if (!l1)
        return l2;
    if (!l2)
        return l1;
    if (strcmp(l1->value, l2->value) < 0) {
        result = l1;
        result->next = sortedmerge(l1->next, l2);
    } else {
        result = l2;
        result->next = sortedmerge(l1, l2->next);
    }
    return result;
}

void frontbacksplit(list_ele_t *source,
                    list_ele_t **frontref,
                    list_ele_t **backref)
{
    list_ele_t *fast, *slow;
    slow = source;
    fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontref = source;
    *backref = slow->next;
    slow->next = NULL;
}

void mergesort(list_ele_t **headref)
{
    list_ele_t *head = *headref;
    list_ele_t *l1, *l2;
    if (!head || !head->next)
        return;
    frontbacksplit(head, &l1, &l2);
    mergesort(&l1);
    mergesort(&l2);
    *headref = sortedmerge(l1, l2);
}
