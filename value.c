//
// Created by Fabian Simon on 29.09.23.
//

#include <stdio.h>

#include "value.h"
#include "memory.h"

void init_value_array(ValueArray* arr) {
    arr->values = NULL;
    arr->capacity = 0;
    arr->count = 0;
}

void write_value_array(ValueArray* arr, Value val) {
    if (arr->capacity < arr->count+1) {
        int old_capacity = arr->capacity;
        arr->capacity = GROW_CAPACITY(old_capacity);
        arr->values = GROW_ARRAY(Value, arr->values, old_capacity, arr->capacity);
    }

    arr->values[arr->count] = val;
    arr->count++;
}

void free_value_array(ValueArray* arr) {
    FREE_ARRAY(Value, arr->values, arr->capacity);
    init_value_array(arr);
}

void print_value(Value value) {
    switch (value.type) {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NIL: printf("NIL"); break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
    }
}

bool values_equal(Value a, Value b) {
    if (a.type != b.type) return false;
    switch (a.type) {
        case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
        case VAL_NIL:    return true;
        case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
        default:         return false; // unreachable.
    }
}