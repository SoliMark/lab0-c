#include "queue.h"
list_ele_t *sortedmerge(list_ele_t *l1, list_ele_t *l2);
void frontbacksplit(list_ele_t *source,
                    list_ele_t **frontref,
                    list_ele_t **backref);
void mergesort(list_ele_t **headref);
