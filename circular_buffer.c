#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if(a == NULL || N <= 0) return 1;

    a->ptr = malloc(N * sizeof(int));

    if(a->ptr == NULL) return 2;
    else {
        a->begin = 0;
        a->end = 0;
        a->capacity = N;
        a->full = 0;
        return 0;
    }
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if(cb == NULL || N <= 0) return 1;
    int res;

    *cb = malloc(sizeof(struct circular_buffer_t));
    res = circular_buffer_create(*cb, N);

    if(res == 2) {
        circular_buffer_destroy_struct(cb);
        return 2;
    }

    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if(a == NULL || a->ptr == NULL) return;

    free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if(a == NULL) return;

    circular_buffer_destroy(*a);
    free(*a);
}
int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if(cb == NULL || cb->end > cb->capacity || cb->begin < 0
       || cb->capacity <= 0 || cb->begin > cb->capacity || cb->end < 0) return 1;

    if(!circular_buffer_full(cb)) {
        *(cb->ptr + cb->end) = value;
        cb->end++;

        if(cb->end == cb->capacity) cb->end = 0;

        if (cb->end == cb->begin) cb->full = 1;
    }
    else {
        *(cb->ptr + cb->begin) = value;
        cb->end++;
        cb->begin++;

        if(cb->end == cb->capacity) cb->full = 1;

        if(cb->begin == cb->capacity) {
            cb->full = 1;
            cb->begin = 0;
        }
    }

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *cb, int *err_code) {
    if(cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0
       || cb->begin > cb->capacity || cb->end > cb->capacity) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    int num;

    if (circular_buffer_empty(cb)) {
        if (err_code != NULL) *err_code = 2;
        return -1;
    }
    else {
        num = *(cb->ptr + cb->begin);
        cb->begin++;
        cb->full = 0;

        if(cb->begin == cb->capacity) cb->begin = 0;

        if(err_code != NULL) *err_code = 0;
    }

    return num;
}

int circular_buffer_pop_back(struct circular_buffer_t *cb, int *err_code) {
    if(cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0
       || cb->begin > cb->capacity || cb->end > cb->capacity) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    int num, index_to_read;

    if (circular_buffer_empty(cb)) {
        if(err_code != NULL) *err_code = 2;
        return -1;
    }
    else {
        index_to_read = cb->end - 1;

        if(cb->end <= 0) index_to_read = cb->capacity - 1;

        num = *(cb->ptr + index_to_read);
        cb->end = index_to_read;
        cb->full = 0;

        if(err_code != NULL) *err_code = 0;
    }

    return num;
}

int circular_buffer_empty(const struct circular_buffer_t *cb) {
    if(cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0
       || cb->begin > cb->capacity || cb->end > cb->capacity) return -1;

    if(cb->full == 0 && cb->begin == cb->end) return 1;
    else return 0;
}

int circular_buffer_full(const struct circular_buffer_t *cb) {
    if(cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0
       || cb->begin > cb->capacity || cb->end > cb->capacity) return -1;

    if(cb->full == 1) return 1;
    else return 0;
}

void circular_buffer_display(const struct circular_buffer_t *cb) {
    if (cb == NULL || cb->ptr == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0
        || cb->begin >= cb->capacity || cb->end >= cb->capacity) return;

    if (circular_buffer_empty(cb)) return;

    int i = cb->begin;

    printf("%d ", *(cb->ptr + i));
    i++;

    if(i == cb->capacity) i = 0;

    while (i != cb->end) {
        printf("%d ", *(cb->ptr + i));
        i++;
        if(i == cb->capacity) i = 0;
    }
}
