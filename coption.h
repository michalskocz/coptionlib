/*
Copyright (c) 2026 Michał Skoczylas
Licensed under the BSD 2-Clause License
*/

#ifndef C_OPTION_H
#define C_OPTION_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#define GENERATE_OPTION(type)                                            \
                                                                          \
typedef struct {                                                          \
    type *value;                                                          \
} __option_##type##_t;                                                    \
                                                                          \
typedef struct {                                                          \
    bool exist;                                                           \
} option_##type##_t;                                                      \
                                                                          \
static inline option_##type##_t *option_##type##_init(void)               \
{                                                                         \
    char *buffer = malloc(                                                \
        sizeof(__option_##type##_t) + sizeof(option_##type##_t));         \
                                                                          \
    if (!buffer)                                                          \
        return NULL;                                                      \
                                                                          \
    __option_##type##_t *hidden = (__option_##type##_t *)buffer;          \
    hidden->value = NULL;                                                 \
                                                                          \
    option_##type##_t *opt =                                              \
        (option_##type##_t *)(buffer + sizeof(__option_##type##_t));      \
                                                                          \
    opt->exist = false;                                                   \
                                                                          \
    return opt;                                                           \
}                                                                         \
                                                                          \
static inline void option_##type##_free(option_##type##_t *opt)           \
{                                                                         \
    free((char *)opt - sizeof(__option_##type##_t));                      \
}                                                                         \
                                                                          \
static inline void option_##type##_set(                                   \
    option_##type##_t *opt,                                               \
    type *value)                                                          \
{                                                                         \
    __option_##type##_t *hidden =                                         \
        (__option_##type##_t *)((char *)opt -                            \
        sizeof(__option_##type##_t));                                     \
                                                                          \
    hidden->value = value;                                                \
    opt->exist = (value != NULL);                                         \
}                                                                         \
                                                                          \
static inline type *option_##type##_get(                                  \
    option_##type##_t *opt)                                               \
{                                                                         \
    __option_##type##_t *hidden =                                         \
        (__option_##type##_t *)((char *)opt -                            \
        sizeof(__option_##type##_t));                                     \
                                                                          \
    return hidden->value;                                                 \
}

#endif // C_OPTION_H
